import json
from channels.generic.websocket import AsyncWebsocketConsumer

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
        self.id = self.scope["user"].id
        await self.accept()

    async def disconnect(self, close_code):
        # 연결 해제 시 대기열에서 제거
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
            await self.handle_match_request("1vs1")
        elif message_type == "tournament_match_request":
            await self.handle_match_request("tournament")
        elif message_type == "final_match_request":
            await self.handle_match_request("final")

    async def handle_match_request(self, gametype):
        global vs_waiting_queue
        global tournament_waiting_queue
        self.user = self.scope["user"]

        # 1vs1 매칭
        if gametype == "1vs1" and self.user.nickname not in vs_waiting_queue:
            vs_waiting_queue.append(self.user.nickname)
            if len(vs_waiting_queue) == 2:
                player1 = vs_waiting_queue.pop(0)
                player2 = vs_waiting_queue.pop(0)
        	    # 두 유저에게 매칭 정보를 전송
                await self.send_to_user(player1, player2, gametype)
        # tournament 매칭
        elif gametype == "tournament" and self.user.nickname not in tournament_waiting_queue:
            tournament_waiting_queue.append(self.user.nickname)
            if len(tournament_waiting_queue) == 4:
                player1 = tournament_waiting_queue.pop(0)
                player2 = tournament_waiting_queue.pop(0)
                await self.send_to_user(player1, player2, gametype)
                player3 = tournament_waiting_queue.pop(0)
                player4 = tournament_waiting_queue.pop(0)
                await self.send_to_user(player3, player4, gametype)
        # final 매칭
        elif gametype == "final" and self.user.nickname not in final_waiting_queue:
            final_waiting_queue.append(self.user.nickname)
            if len(final_waiting_queue) == 2:
                player1 = final_waiting_queue.pop(0)
                player2 = final_waiting_queue.pop(0)
                await self.send_to_uer(player1, player2, gametype)

    async def send_to_user(self, player1, player2, gametype):
        self.user = self.scope["user"]
		# 상대방 정보 전송
    	# 양쪽에 이 메시지를 똑같이 보내야 하나..? 아님 상대방만 보내야하나..?
        if self.user.nickname == player1:
            await self.send(json.dumps({
        	    "type": "match_found",
        	    "gameType": gametype,
        	    "player1": player1,
        	    "player2": player2,
        	    "opponent": player2 
        	}))
        elif self.user.nickname == player2:
            await self.send(json.dumps({
        	    "type": "match_found",
        	    "gameType": gametype,
        	    "player1": player1,
        	    "player2": player2,
        	    "opponent": player1 
        	}))
    
# class GameConsumer(AsyncWebsocketConsumer):
    