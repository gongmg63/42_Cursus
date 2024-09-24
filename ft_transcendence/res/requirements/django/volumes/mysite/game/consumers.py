import json
import asyncio


from user.serializers import UserSerializer
from django.contrib.auth import get_user_model

from channels.db import database_sync_to_async

from channels.generic.websocket import AsyncWebsocketConsumer
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
import math
import random

# player1 / player2 / gameType 


# 메모리 내 대기열
vs_waiting_queue = []
tournament_waiting_queue = []
final_waiting_queue = []

#     socket.send(JSON.stringify({
#       type: "1vs1 or tournament or final_match_request",
#		gameType: "1vs1 or tournament"
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
#     socket.send(JSON.stringify({ // 받는 내용
#       type: "paddleMove",
#       id: "12345" (my id)
#       key: up or down
#     }));
#     socket.send(JSON.stringify({ // 보내는 내용
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

# Ball ( pos(vec(200, 200)), velocity(vec(20, 20)), radius(20) )
# Paddle ( pos(vec), velocity(vec(15, 15)), width (20), height (200), upKey, downKey )

client = {}
client_lock = asyncio.Lock()
ball_group = {}

class ball():
    x = 200
    y = 200
    velocity_x = 20
    velocity_y = 15
    radius = 20

ball()

class GameConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        global client
        self.user = self.scope["user"]
        self.paddle_velocity_x = 25
        self.paddle_velocity_y = 25
        self.paddle_width = 20
        self.paddle_height = 200
        self.score = 0
        
        async with client_lock:
            client[self.user.id] = False
        
        await self.accept()

    async def disconnect(self, close_code):
        self.client[self.user.id] = False
        if hasattr(self, 'game_loop_task'):
            self.game_loop_task.cancel()  # 태스크 취소
            try:
                await self.game_loop_task  # 태스크가 제대로 종료될 때까지 기다림
            except asyncio.CancelledError:
                print("Game loop task properly cancelled")

    async def receive(self, text_data):
        global client
        data = json.loads(text_data)
        message_type = data.get("type")
        if message_type == 'initMatch':
            # 상대 정보를 기반으로 그룹 이름을 설정
            player1_id = data['player1_id']
            player2_id = data['player2_id']
            if str(self.user.id) == str(player1_id):
                self.pos = "left"
            else:
                self.pos = "right"
            self.group_name = f"match_{player1_id}_{player2_id}"
            self.canvas_width = data['canvas_width']
            self.canvas_height = data['canvas_height']
            if str(self.user.id) == str(player1_id):
                self.paddle_pos_x = 0
                self.paddle_pos_y = 50
            else:
                self.paddle_pos_x = self.canvas_width - 20
                self.paddle_pos_y = 30
            # 그룹 추가
            await self.channel_layer.group_add(
                self.group_name,
                self.channel_name
            )
            # 그룹 공 생성
            if self.group_name not in ball_group:
                ball_group[self.group_name] = ball()
            async with client_lock:
                client[self.user.id] = True
            await self.check_all_clients_ready(player1_id, player2_id)
        elif message_type == 'paddleMove':
            #상대에게 패들 움직임 전송
            await self.paddle_move(data.get("id"), data.get("key"))
        elif message_type == 'increaseScore':
            # 양쪽 모두에게 점수 보내기
            await self.increase_score(data.get("score1"), data.get("score2"))

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
            self.ball = ball_group[self.group_name]
            self.game_loop_task = asyncio.create_task(self.game_loop())


    async def startGame(self, event):
        message = event["message"]

        await self.send(json.dumps({
            "type": "startGame",
            "message": message
        }))

    async def paddle_move(self, id, key):
        check_move = True

        if key == "up":
            self.paddle_pos_y -= self.paddle_velocity_y
            if self.paddle_pos_y <= 0:
                self.paddle_pos_y = 0
                check_move = False
        else:
            self.paddle_pos_y += self.paddle_velocity_y
            if self.paddle_pos_y + self.paddle_height >= self.canvas_height:
                self.paddle_pos_y = self.canvas_height - self.paddle_height
                check_move = False
        if check_move:
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "paddleMove",
                    "id": id,
                    "y": self.paddle_pos_y
                }
            )
    
    async def paddleMove(self, event):
        id = event["id"]
        y = event["y"]

        await self.send(json.dumps({
            "type": "paddleMove",
            "id": id,
            "y": y,
        }))
    
    async def game_loop(self):
        try:
            while True:
                await self.update_game_state()
                await asyncio.sleep(0.02)  # 20ms 간격으로 업데이트
        except asyncio.CancelledError:
            # 태스크가 취소될 때 필요한 정리 작업
            print("Game loop cancelled")

    async def update_game_state(self):
        # 공 위치 업데이트
        ball_group[self.group_name].x += ball_group[self.group_name].velocity_x
        ball_group[self.group_name].y += ball_group[self.group_name].velocity_y

        # 벽 충돌 처리
        if ball_group[self.group_name].y - ball_group[self.group_name].radius <= 0 \
            or ball_group[self.group_name].y + ball_group[self.group_name].radius >= self.canvas_height:
            ball_group[self.group_name].velocity_y *= -1

        if ball_group[self.group_name].x <= -ball_group[self.group_name].radius or ball_group[self.group_name].x >= self.canvas_width + ball_group[self.group_name].radius:
            ball_group[self.group_name].velocity_x *= -1
            if ball_group[self.group_name].x <= ball_group[self.group_name].radius:
                winner = "left"
            else:
                winner = "right"
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "increaseScore",
                    "winner": winner
                }
            )
            self.respawn_ball()
        # 게임 상태 전송
        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "ballMove",
            }
        )

    async def ballMove(self, event):
            # 패들 충돌 처리
        ball = ball_group[self.group_name]  # 공 객체 가져오기
        if self.pos == "left":
            # 왼쪽 패들 충돌 처리
            if (ball.x - ball.radius <= self.paddle_pos_x + self.paddle_width and
                ball.x + ball.radius >= self.paddle_pos_x and
                ball.y + ball.radius >= self.paddle_pos_y and
                ball.y - ball.radius <= self.paddle_pos_y + self.paddle_height):
                # 공의 x 방향 반전
                ball.velocity_x *= -1
                # 충돌 후 공의 위치를 패들 바로 앞에 배치
                ball.x = self.paddle_pos_x + self.paddle_width + ball.radius
        else:
            # 오른쪽 패들 충돌 처리
            if (ball.x + ball.radius >= self.paddle_pos_x and
                ball.x - ball.radius <= self.paddle_pos_x + self.paddle_width and
                ball.y + ball.radius >= self.paddle_pos_y and
                ball.y - ball.radius <= self.paddle_pos_y + self.paddle_height):
                # 공의 x 방향 반전
                ball.velocity_x *= -1
                # 충돌 후 공의 위치를 패들 바로 앞에 배치
                ball.x = self.paddle_pos_x - ball.radius

        await self.send(json.dumps({
            "type": "ballMove",
            "ball_pos_x": ball_group[self.group_name].x,
            "ball_pos_y": ball_group[self.group_name].y,
            "ball_velocity_x": ball_group[self.group_name].velocity_x,
            "ball_velocity_y": ball_group[self.group_name].velocity_y,
            "ball_radius": ball_group[self.group_name].radius
        }))

    async def increaseScore(self, event):
        winner = event['winner']

        if self.pos == winner:
            result = "win"
        else:
            result = "lose"
        await self.send(json.dumps({
            "type": "increaseScore",
            "result": result
        }))

    def respawn_ball(self):
        ball = ball_group[self.group_name]
        if ball.velocity_x > 0:
            ball.x = self.canvas_width - 150
            ball.y = random.uniform(100, self.canvas_height - 100)
        elif ball.velocity_x < 0:
            ball.x = 150
            ball.y = random.uniform(100, self.canvas_height - 100)

        ball.velocity_x *= -1
        ball.velocity_y *= -1
