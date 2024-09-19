import json
import asyncio


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
        if self.user in vs_waiting_queue:
            vs_waiting_queue.remove(self.id)
        elif self.user in tournament_waiting_queue:
            tournament_waiting_queue.remove(self.id)
        elif self.user in final_waiting_queue:
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
            self.group_name = "tournament_group"
            await self.channel_layer.group_add(
                self.group_name,  # 그룹 이름
                self.channel_name  # 현재 연결된 채널의 이름
            )
            await self.handle_match_request("tournament")
        elif message_type == "final_match_request":
            self.group_name = "final_group"
            await self.channel_layer.group_add(
                self.group_name,  # 그룹 이름
                self.channel_name  # 현재 연결된 채널의 이름
            )
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


#     socket.send(JSON.stringify({
#       type: "initMatch",
#       player1_id: id1,
#       player2_id: id2,
#     }));
#     socket.send(JSON.stringify({
#       type: "paddleMove",
#       id: "12345" (my id)
#       y: "1.2"
#     }));
#     socket.send(JSON.stringify({
#       type: "ballMove",
#       ball ? -> 확인
#     }));
#     socket.send(JSON.stringify({
#       type: "increaseScore",
#       score1: paddle1.score
#       score2: paddle2.score
#     }));

client = {}
client_lock = asyncio.Lock()

class GameConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        global client
        self.user = self.scope["user"]
        
        async with client_lock:
            client[self.user.id] = False
        
        await self.accept()

    async def disconnect(self, close_code):
        self.client[self.user.id] = False

    async def receive(self, text_data):
        global client
        data = json.loads(text_data)
        message_type = data.get("type")
        print(data)
        if message_type == 'initMatch':
            # 상대 정보를 기반으로 그룹 이름을 설정
            player1_id = data['player1_id']
            player2_id = data['player2_id']
            self.group_name = f"match_{player1_id}_{player2_id}"
            # 그룹 추가
            await self.channel_layer.group_add(
                self.group_name,
                self.channel_name
            )
            async with client_lock:
                client[self.user.id] = True
            await self.check_all_clients_ready(player1_id, player2_id)
        elif message_type == 'paddleMove':
            #상대에게 패들 움직임 전송
            self.paddle_move(data.get("id"), data.get("y"))
        elif message_type == 'ballMove':
            # 상대에게 공 움직임 보내기? 아님 둘 다한테 보내야하나
            self.ball_move(data.get("ball"))
        elif message_type == 'increaseScore':
            # 양쪽 모두에게 점수 보내기
            self.increase_score(data.get("score1"), data.get("score2"))

    async def check_all_clients_ready(self, p1, p2):
        global client

        async with client_lock:
            ready_clients = sum(1 for ready in client.values() if ready)
        
        if ready_clients % 2 == 0 and ready_clients != 0:
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "startGame",
                    'message': 'All clients connected. Starting game...'
                }
            )

    async def startGame(self, event):
        message = event["message"]

        await self.send(json.dumps({
            "type": "startGame",
            "message": message
        }))

    async def paddle_move(self, id, y):
        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "paddleMove",
                "id": id,
                "y": y
            }
        )
    
    async def paddleMove(self, event):
        id = event["id"]
        y = event["y"]

        if self.user.id != id:
            await self.send(json.dumps({
                "type": "paddleMove",
                "id": id,
                "y": y,
            }))

    async def ball_move(self, ball):
        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "ballMove",
                "ball": ball,
            }
        )

    async def ballMove(self, event):
        ball = event["ball"]

        if self.user.id != id:
            await self.send(json.dumps({
                "type": "ballMove",
                "ball": ball,
            }))

    async def increase_score(self, score1, score2):
        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "increaseScore",
                "score1": score1,
                "score2": score2,
            }
        )

    async def increaseScore(self, event):
        score1 = event["score1"]
        score2 = event["score2"]

        await self.send(json.dumps({
            "type": "increaseScore",
            "score1": score1,
            "score2": score2,
        }))