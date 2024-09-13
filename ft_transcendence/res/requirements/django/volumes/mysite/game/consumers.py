import json

from user.serializers import UserSerializer
from django.contrib.auth import get_user_model

from channels.db import database_sync_to_async

from channels.generic.websocket import AsyncWebsocketConsumer
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync

# player1 / player2 / gameType 


# 메모리 내 대기열
vs_waiting_queue = []
tournament_waiting_queue = []
final_waiting_queue = []

#     socket.send(JSON.stringify({
#       type: "1vs1 or Tournament or final _match_request",
#		gameType: "1vs1 or Tournament"
#       id: "12345"
#     }));

#	data race...?

class MatchConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user = self.scope["user"]
        self.id = self.scope["user"].id
        await self.accept()

    async def disconnect(self, close_code):
        # 연결 해제 시 대기열에서 제거
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )
        if self.id in vs_waiting_queue:
            vs_waiting_queue.remove(self.id)
        elif self.id in tournament_waiting_queue:
            tournament_waiting_queue.remove(self.id)
        elif self.id in final_waiting_queue:
            final_waiting_queue.remove(self.id)

    async def receive(self, text_data):
        data = json.loads(text_data)
        message_type = data.get("type")

        if message_type == "1vs1_match_request":
            self.group_name = "1vs1_group"
            await self.channel_layer.group_add(
                self.group_name,  # 그룹 이름
                self.channel_name  # 현재 연결된 채널의 이름
            )
            await self.handle_match_request("1vs1")
        elif message_type == "tournament_match_request":
            await self.handle_match_request("tournament")
        elif message_type == "final_match_request":
            await self.handle_match_request("final")

    async def handle_match_request(self, gametype):
        global vs_waiting_queue
        global tournament_waiting_queue

        # 1vs1 매칭
        if gametype == "1vs1" and self.user not in vs_waiting_queue:
            vs_waiting_queue.append(self.user)
            if len(vs_waiting_queue) >= 2:
                player1 = vs_waiting_queue.pop(0)
                player2 = vs_waiting_queue.pop(0)
        	    # 두 유저에게 매칭 정보를 전송
                await self.send_to_user(player1, player2, gametype)
        # tournament 매칭
        elif gametype == "tournament" and self.user not in tournament_waiting_queue:
            tournament_waiting_queue.append(self.user)
            if len(tournament_waiting_queue) >= 4:
                player1 = tournament_waiting_queue.pop(0)
                player2 = tournament_waiting_queue.pop(0)
                await self.send_to_user(player1, player2, gametype)
                player3 = tournament_waiting_queue.pop(0)
                player4 = tournament_waiting_queue.pop(0)
                await self.send_to_user(player3, player4, gametype)
        # final 매칭
        elif gametype == "final" and self.user not in final_waiting_queue:
            final_waiting_queue.append(self.user)
            if len(final_waiting_queue) >= 2:
                player1 = final_waiting_queue.pop(0)
                player2 = final_waiting_queue.pop(0)
                await self.send_to_uer(player1, player2, gametype)

    async def send_to_user(self, player1, player2, gametype):
        player1_user = await database_sync_to_async(get_user_model().objects.get)(id=player1.id)
        player2_user = await database_sync_to_async(get_user_model().objects.get)(id=player2.id)
		
        # 직렬화
        player1_data = UserSerializer(player1_user).data
        player2_data = UserSerializer(player2_user).data
        # 그룹에 player1에게 메시지 전송
        await self.channel_layer.group_send(
        self.group_name,
        {
            "type": "match_found",
            "gameType": gametype,
            "player1": player1_data,
            "player2": player2_data,
        }
    )

    async def match_found(self, event):
        game_type = event["gameType"]
        player1 = event["player1"]
        player2 = event["player2"]

        # sender와 비교해 상대방 정보를 설정
        if self.scope["user"].nickname == player1['nickname']:
            opponent = player2['nickname']
        else:
            opponent = player1['nickname']

        # 클라이언트에 메시지 전송
        await self.send(json.dumps({
            "type": "match_found",
            "gameType": game_type,
            "player1": player1,
            "player2": player2,
            "opponent": opponent  # 상대방 정보 전송
        }))
        
# class GameConsumer(AsyncWebsocketConsumer):
    