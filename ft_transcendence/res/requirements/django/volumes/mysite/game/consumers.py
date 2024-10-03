import json
import random
import asyncio

from user.serializers import UserSerializer
from user.models import User
from django.contrib.auth import get_user_model
from channels.db import database_sync_to_async
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
from .signals import play_disconnect_signal
from .models import GameResult

# 메모리 내 대기열
vs_waiting_queue = []
tournament_waiting_queue = []
final_waiting_queue = []
match_data = {}

class MatchConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user = self.scope["user"]
        await self.accept()

    async def disconnect(self, close_code):
        # 연결 성공 시 대기열에서 제거
        print("매칭 웹소켓 연결 종료")
        if hasattr(self, 'group_name'):
            await self.matching_out()
        if self.user in vs_waiting_queue:
            vs_waiting_queue.remove(self.user)
        elif self.user in tournament_waiting_queue:
            tournament_waiting_queue.remove(self.user)
        elif self.user in final_waiting_queue:
            final_waiting_queue.remove(self.user)

    async def receive(self, text_data):
        data = json.loads(text_data)
        message_type = data.get("type")
        if self.user.id in match_data:
            if message_type == "final":
                p1_id = match_data[self.user.id]["player1"]["id"]
                p2_id = match_data[self.user.id]["player2"]["id"]
                p3_id = match_data[self.user.id]["player3"]["id"]
                p4_id = match_data[self.user.id]["player4"]["id"]
                if self.user.id in {p1_id, p2_id}:
                    self.opponent = {p3_id, p4_id}
                else:
                    self.opponent = {p1_id, p2_id}
            del match_data[self.user.id]
        print("매칭 데이터:", data)
        if message_type == "1vs1":
            self.group_name = "1vs1_group"
            await self.channel_layer.group_add(
                self.group_name,  # 그룹 이름
                self.channel_name  # 현재 연결된 채널의 이름
            )
            await self.handle_match_request(message_type)
        elif message_type == "tournament":
            self.group_name = "tournament_group"
            await self.channel_layer.group_add(
                self.group_name,  # 그룹 이름
                self.channel_name  # 현재 연결된 채널의 이름
            )
            await self.handle_match_request(message_type)
        elif message_type == "final":
            self.group_name = "final_group"
            await self.channel_layer.group_add(
                self.group_name,  # 그룹 이름
                self.channel_name  # 현재 연결된 채널의 이름
            )
            await self.handle_match_request(message_type)
        elif message_type == 'matchingOut':
            if hasattr(self, 'group_name'):
                await self.matching_out()
        
    async def matching_out(self):
        print("matching out", self.user.nickname)
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )
        # 그룹 내 다른 사용자들에게 disconnect 메시지 보내기
        # await self.channel_layer.group_send(
        #     self.group_name,
        #     {
        #         'type': 'matchingOut',
        #         'out_id': self.user.id,
        #     }
        # )
    
    async def matchingOut(self, event):
        out_id = event["out_id"]
        if self.user.id in match_data:
            my_match = match_data[self.user.id]
            if my_match["gameType"] == "1vs1":
                if out_id in [my_match["player1"]["id"], my_match["player2"]["id"]]:
                    await self.send(json.dumps({
                        "type": "match_cancel",
                    }))
            elif my_match["gameType"] == "final":
                if out_id in [my_match["player1"]["id"], my_match["player3"]["id"]]:
                    await self.send(json.dumps({
                        "type": "match_cancel",
                    }))
            else:
                if out_id in [my_match["player1"]["id"], my_match["player2"]["id"], my_match["player3"]["id"], my_match["player4"]["id"]]:
                    await self.send(json.dumps({
                        "type": "match_cancel",
                    }))

    async def handle_match_request(self, gametype):
        global vs_waiting_queue
        global tournament_waiting_queue

        # 1vs1 매칭
        if gametype == "1vs1" and self.user not in vs_waiting_queue:
            vs_waiting_queue.append(self.user)
            if len(vs_waiting_queue) >= 2:
        	    # 두 유저에게 매칭 정보를 전송
                await self.send_to_user(gametype)
        # tournament 매칭
        elif gametype == "tournament" and self.user not in tournament_waiting_queue:
            tournament_waiting_queue.append(self.user)
            if len(tournament_waiting_queue) >= 4:
                await self.send_to_tourtnament_user(gametype)
        # final 매칭
        elif gametype == "final" and self.user not in final_waiting_queue:
            final_waiting_queue.append(self.user)
            if len(final_waiting_queue) >= 2:
                await self.send_to_final_user(gametype)

    async def send_to_user(self, gametype):
        global tournament_waiting_queue

        player1 = vs_waiting_queue.pop(0)
        player2 = vs_waiting_queue.pop(0)
        player1_user = await database_sync_to_async(get_user_model().objects.get)(id=player1.id)
        player2_user = await database_sync_to_async(get_user_model().objects.get)(id=player2.id)
		
        # 직렬화
        player1_data = UserSerializer(player1_user).data
        player2_data = UserSerializer(player2_user).data
        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "match_found",
                "gameType": gametype,
                "player1": player1_data,
                "player2": player2_data,
            }
        )

    async def send_to_tourtnament_user(self, gametype):
        global tournament_waiting_queue

        player1 = tournament_waiting_queue.pop(0)
        player2 = tournament_waiting_queue.pop(0)
        player3 = tournament_waiting_queue.pop(0)
        player4 = tournament_waiting_queue.pop(0)
        
        player1_user = await database_sync_to_async(get_user_model().objects.get)(id=player1.id)
        player2_user = await database_sync_to_async(get_user_model().objects.get)(id=player2.id)
        player3_user = await database_sync_to_async(get_user_model().objects.get)(id=player3.id)
        player4_user = await database_sync_to_async(get_user_model().objects.get)(id=player4.id)
		
        # 직렬화
        player1_data = UserSerializer(player1_user).data
        player2_data = UserSerializer(player2_user).data
        player3_data = UserSerializer(player3_user).data
        player4_data = UserSerializer(player4_user).data

        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "match_found",
                "gameType": gametype,
                "player1": player1_data,
                "player2": player2_data,
                "player3": player3_data,
                "player4": player4_data,
            }
        )

    async def send_to_final_user(self, gametype):
        global final_waiting_queue
        
        winner1 = None
        winner2 = self.user
        final_waiting_queue.pop(final_waiting_queue.index(self.user))
        for user in final_waiting_queue:
            if  user.id in self.opponent:
                winner1 = user
                final_waiting_queue.pop(final_waiting_queue.index(user))
                break

        if winner1 == None:
            final_waiting_queue.append(winner2)
            return
        
        winner1_user = await database_sync_to_async(get_user_model().objects.get)(id=winner1.id)
        winner2_user = await database_sync_to_async(get_user_model().objects.get)(id=winner2.id)

        #직렬화
        winner1_data = UserSerializer(winner1_user).data
        winner2_data = UserSerializer(winner2_user).data

        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "match_found",
                "gameType": gametype,
                "winner1": winner1_data,
                "winner2": winner2_data,
            }
        )

    async def match_found(self, event):
        game_type = event["gameType"]
        if game_type == "1vs1":
            player1 = event["player1"]
            player2 = event["player2"]
            if self.user.id in [player1["id"], player2["id"]]:
                match_data[self.user.id] = {
                    "gameType": game_type,
                    "player1": player1,
                    "player2": player2
                }

                # 클라이언트에 메시지 전송
                await self.send(json.dumps({
                    "type": "match_found",
                    "gameType": game_type,
                    "player1": player1,
                    "player2": player2,
                }))
        elif game_type == "tournament":
            player1 = event["player1"]
            player2 = event["player2"]
            player3 = event["player3"]
            player4 = event["player4"]

            if self.user.id in [player1["id"], player2["id"], player3["id"], player4["id"]]:
                if self.user.id == player1["id"] or self.user.id == player2["id"]:
                    game_type += '1'
                else:
                    game_type += '2'

                match_data[self.user.id] = {
                    "gameType": game_type,
                    "player1": player1,
                    "player2": player2,
                    "player3": player3,
                    "player4": player4,
                }

                # 클라이언트에 메시지 전송
                await self.send(json.dumps({
                    "type": "match_found",
                    "gameType": game_type,
                    "player1": player1,
                    "player2": player2,
                    "player3": player3,
                    "player4": player4,
                }))
        else:
            winner1 = event["winner1"]
            winner2 = event["winner2"]
            if self.user.id in [winner1["id"], winner2["id"]]:
                match_data[self.user.id] = {
                    "gameType": game_type,
                    "player1": winner1,
                    "player2": winner1["t_loser"],
                    "player3": winner2,
                    "player4": winner2["t_loser"],
                }
                await self.send(json.dumps({
                    "type": "match_found",
                    "gameType": game_type,
                    "player1": winner1,
                    "player2": winner1["t_loser"],
                    "player3": winner2,
                    "player4": winner2["t_loser"],
                }))
            

ball_group = {}

class ball():
    x = 200
    y = 200
    velocity_x = 20
    velocity_y = 15
    radius = 20

client = {}
client_lock = asyncio.Lock()
game_loop_dict = {}

class GameConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        print("게임 웹소켓 연결")
        global client
        self.user = self.scope["user"]
        self.paddle_velocity_x = 25
        self.paddle_velocity_y = 25
        self.paddle_width = 20
        self.paddle_height = 200
        self.score = 0
        self.spawn = False

        await self.accept()

    async def disconnect(self, close_code):
        global client
        print("게임 웹소켓 연결 종료")
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

        # 그룹 내 다른 사용자들에게 disconnect 메시지 보내기
        await self.channel_layer.group_send(
            self.group_name,
            {
                'type': 'userDisconnected',
            }
        )
        del client[self.user.id]
        play_disconnect_signal.send(sender=self.__class__, instance=self)
        if hasattr(self, 'game_loop_task') and not self.game_loop_task.done():
            self.game_loop_task.cancel()
            try: 
                await self.game_loop_task
            except:
                print("Game loop task properly cancelled")
            if self.player1 in game_loop_dict:
                del game_loop_dict[self.player1]

    async def userDisconnected(self, event):
        await self.send(json.dumps({
            "type": "checkGameEnd",
            "message": "Other player disconnected. Check game end."
        }))

    async def play_disconnect(self, event):
        if hasattr(self, "game_loop_task") and not self.game_loop_task.done():
            self.game_loop_task.cancel()
            try: 
                await self.game_loop_task
            except:
                print("Game loop task properly cancelled")

    async def receive(self, text_data):
        global client
        data = json.loads(text_data)
        message_type = data.get("type")
        gameType = match_data[self.user.id]["gameType"]
        print("message Type : ", message_type)
        if message_type == 'initMatch':
            # 상대 정보를 기반으로 그룹 이름을 설정
            player1 = None
            player2 = None
            if gameType == "1vs1" or gameType == "tournament1":
                player1 = match_data[self.user.id]["player1"]
                player2 = match_data[self.user.id]["player2"]
            elif gameType == "tournament2":
                player1 = match_data[self.user.id]["player3"]
                player2 = match_data[self.user.id]["player4"]
            else:
                player1 = match_data[self.user.id]["player1"]
                player2 = match_data[self.user.id]["player3"]

            await self.send(json.dumps({
                "type": "parseGameData",
                "gameType": gameType,
                "player1": player1["nickname"],
                "player1_t": player1["t_nickname"],
                "player2": player2["nickname"],
                "player2_t": player2["t_nickname"],
                "id1": player1["id"],
                "id2": player2["id"],
            }))
            player1_id = player1["id"]
            player2_id = player2["id"]
            self.player1 = player1_id
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
            client[self.user.id] = True
            await self.check_all_clients_ready(player1_id, player2_id)
        elif message_type == 'paddleMove':
            #상대에게 패들 움직임 전송
            await self.paddle_move(data.get("id"), data.get("key"))
        elif message_type == 'increaseScore':
            # 양쪽 모두에게 점수 보내기
            await self.increase_score(data.get("score1"), data.get("score2"))
        elif message_type == 'outPage':
            await self.check_refresh_page(data)
        elif message_type == 'endGame':
            await self.save_result(data)
    
    async def save_result(self, data):
        check_winner = data.get('checkWinner')
        if check_winner == 'false':
            return

        game_type = data.get('gameType')
        if game_type == 'tournament1' or game_type == 'tournament2':
            game_type = 'tournament'
        winner = data.get('winner')
        loser = data.get('loser')
        winner_score = data.get('winnerScore')
        loser_score = data.get('loserScore')

        User = get_user_model()
        try:
            # 승자와 패자를 데이터베이스에서 가져옴
            winner_user = User.objects.get(nickname=winner)
            loser_user = User.objects.get(nickname=loser)
            
            if game_type == "tournament":
                await self.save_t_loser(winner_user, loser_user.t_nickname)
                print("save t_nickname : ", winner_user.t_nickname, loser_user.t_nickname)
            elif game_type == "1vs1":
                await self.save_win_lose(winner_user, loser_user)
                

            # GameResult 모델에 결과 저장
            GameResult.objects.create(
                game_type=game_type,
                winner=winner_user,
                loser=loser_user,
                winner_score=winner_score,
                loser_score=loser_score,
            )
            print("게임 결과 저장 완료")
            # 성공적으로 저장되면 클라이언트에게 응답
            await self.send(json.dumps({
                'status': 'success',
                'message': 'Game result has been saved successfully.'
            }))
        except User.DoesNotExist:
            # 사용자가 없을 때 예외 처리
            await self.send(json.dumps({
                'status': 'error',
                'message': 'Invalid winner or loser ID.'
            }))

    @database_sync_to_async
    def save_t_loser(self, winner, loser):
        winner.t_loser = loser
        winner.save()

    @database_sync_to_async
    def save_win_lose(self, winner, loser):
        winner.wins += 1
        loser.losses += 1
        winner.save()
        loser.save()
    

    async def check_refresh_page(self, data):
        out_player = data.get("id")
        out_score = data.get("myScore")
        op_score = data.get("opScore")
        end_score = data.get("endScore")

        if out_score != end_score and op_score != end_score:
            print("data :", data)
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "outPlayer",
                    "id": out_player
                }
            )
        
    async def outPlayer(self, event):
        await self.send(json.dumps({
            "type": "outPlayer",
            "out_player": event["id"],
        }))

    async def check_all_clients_ready(self, player1_id, player2_id):
        global client
        global game_loop_dict

        asyncio.create_task(self.check_ready(player1_id))
        if player1_id in client and player2_id in client:
            self.ball = ball_group[self.group_name]
            if player1_id not in game_loop_dict:
                game_loop_dict[player1_id] = asyncio.create_task(self.game_loop())
            self.game_loop_task = game_loop_dict[player1_id]
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "startGame",
                    'message': 'All clients connected. Starting game...'
                }
            )
    
    async def check_ready(self, player1_id):
        global game_loop_dict
        
        try:
            await asyncio.sleep(0.5)
            if not player1_id in game_loop_dict:
                await self.send(json.dumps({
                    "type": "freeWin"
                }))
        except asyncio.CancelledError:
            # 태스크가 취소될 때 필요한 정리 작업
            print("Game loop cancelled")

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

        # 위 아래 벽 충돌 처리
        if ball_group[self.group_name].y - ball_group[self.group_name].radius <= 0 \
            or ball_group[self.group_name].y + ball_group[self.group_name].radius >= self.canvas_height:
            ball_group[self.group_name].velocity_y *= -1

        if ball_group[self.group_name].x <= -ball_group[self.group_name].radius or ball_group[self.group_name].x >= self.canvas_width + ball_group[self.group_name].radius:
            ball_group[self.group_name].velocity_x *= -1
            if ball_group[self.group_name].x <= ball_group[self.group_name].radius:
                winner = "right"
            else:
                winner = "left"
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

    def respawn_ball(self):
        ball = ball_group[self.group_name]
        ball.x = self.canvas_width / 2
        ball.y = random.uniform(self.canvas_height / 2 - 200, self.canvas_height / 2 + 200)
        print(ball.y)
        if self.spawn:
            ball.velocity_x = -abs(ball.velocity_x)
        else:
            ball.velocity_x = abs(ball.velocity_x)
        self.spawn = not self.spawn
        ball.velocity_y *= -1
            
