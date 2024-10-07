import json
import random
import asyncio

from user.serializers import UserSerializer
from user.models import User
from django.contrib.auth import get_user_model
from channels.db import database_sync_to_async
from channels.generic.websocket import AsyncWebsocketConsumer
from .signals import play_disconnect_signal
from .models import GameResult

# 메모리 내 대기열
vs_waiting_queue = asyncio.Queue()
tournament_waiting_queue = asyncio.Queue()
final_waiting_queue = asyncio.Queue()

match_data = {}

# GameConsumer에서 사용
client = {}
ball_group = {}
game_loop_dict = {}

class MatchConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user = self.scope["user"]
        await self.accept()

    async def disconnect(self, close_code):
        # 연결 성공 시 대기열에서 제거
        print("매칭 웹소켓 연결 종료")
        if await self.is_user_in_queue(vs_waiting_queue, self.user):
            await self.remove_user_from_queue(vs_waiting_queue, self.user)
        elif await self.is_user_in_queue(tournament_waiting_queue, self.user):
            await self.remove_user_from_queue(tournament_waiting_queue, self.user)
        elif await self.is_user_in_queue(final_waiting_queue, self.user):
            await self.remove_user_from_queue(final_waiting_queue, self.user)

    async def remove_user_from_queue(self, queue, user):
        # 큐에 있는 모든 유저를 임시로 저장할 리스트
        temp_queue = []

        # 큐를 비동기적으로 처리
        while not queue.empty():
            current_user = await queue.get()
            if current_user != user:
                temp_queue.append(current_user)  # 제거할 유저가 아니면 임시 리스트에 추가

        # 다시 큐에 남은 유저들을 넣음
        for u in temp_queue:
            await queue.put(u)

    async def receive(self, text_data):
        data = json.loads(text_data)
        message_type = data.get("type")
        if self.user.id in match_data:
            if message_type == "final":
                p1_id = match_data[self.user.id]["player1"]["id"]
                p2_id = match_data[self.user.id]["player2"]["id"]
                p3_id = match_data[self.user.id]["player3"]["id"]
                p4_id = match_data[self.user.id]["player4"]["id"]
                if self.user.id in [p1_id, p2_id]:
                    self.opponent = [p3_id, p4_id]
                else:
                    self.opponent = [p1_id, p2_id]
                asyncio.create_task(self.check_final_end())
            del match_data[self.user.id]
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
    
    async def check_final_end(self):
        try:
            while True:
                if self.opponent[0] in game_loop_dict:
                    await asyncio.sleep(2)  # 2초 간격으로 게임이 끝났는지 확인
                else:
                    await asyncio.sleep(2)
                    if await self.is_user_in_queue(final_waiting_queue, self.user):
                        await self.send(json.dumps({
                            "type": "opponent_leave",
                        }))
        except asyncio.CancelledError:
            print("Check final end cancelled")
        

    async def handle_match_request(self, gametype):
        global vs_waiting_queue
        global tournament_waiting_queue
        global final_waiting_queue

        # 1vs1 매칭
        if gametype == "1vs1":
            if not await self.is_user_in_queue(vs_waiting_queue, self.user):
                await vs_waiting_queue.put(self.user)
                if vs_waiting_queue.qsize() >= 2:
                    await self.send_to_user(gametype)
        # tournament 매칭
        elif gametype == "tournament":
            if not await self.is_user_in_queue(tournament_waiting_queue, self.user):
                await tournament_waiting_queue.put(self.user)
                if tournament_waiting_queue.qsize() >= 4:
        	        # 두 유저에게 매칭 정보를 전송
                    await self.send_to_tourtnament_user(gametype)
        # final 매칭
        elif gametype == "final":
            if not await self.is_user_in_queue(final_waiting_queue, self.user):
                await final_waiting_queue.put(self.user)
                if final_waiting_queue.qsize() >= 2:
        	        # 두 유저에게 매칭 정보를 전송
                    await self.send_to_final_user(gametype)

    async def is_user_in_queue(self, queue, user):
        queue_list = list(queue._queue)  # asyncio.Queue 내부 데이터를 리스트로 변환
        return user in queue_list

    async def send_to_user(self, gametype):
        global vs_waiting_queue

        player1 = await vs_waiting_queue.get()  
        player2 = await vs_waiting_queue.get() 
        player1_user = await database_sync_to_async(get_user_model().objects.get)(id=player1.id)
        player2_user = await database_sync_to_async(get_user_model().objects.get)(id=player2.id)
		

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

        player1 = await tournament_waiting_queue.get()
        player2 = await tournament_waiting_queue.get()
        player3 = await tournament_waiting_queue.get()
        player4 = await tournament_waiting_queue.get()
        
        player1_user = await database_sync_to_async(get_user_model().objects.get)(id=player1.id)
        player2_user = await database_sync_to_async(get_user_model().objects.get)(id=player2.id)
        player3_user = await database_sync_to_async(get_user_model().objects.get)(id=player3.id)
        player4_user = await database_sync_to_async(get_user_model().objects.get)(id=player4.id)
		

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

        # 임시 리스트로 큐 내용을 꺼내면서 특정 유저 제거
        temp_queue = []

        # 큐에서 self.user를 제거
        while not final_waiting_queue.empty():
            user = await final_waiting_queue.get()
            if user == self.user:
                continue  # self.user는 제거
            temp_queue.append(user)  # 나머지 유저들은 임시 리스트에 추가
        
        # opponent 유저 찾기
        for user in temp_queue:
            if user.id in self.opponent:
                winner1 = user
                temp_queue.remove(user)  # opponent 유저도 큐에서 제거
                break

        # 만약 winner1이 없다면, self.user를 다시 큐에 넣음
        if winner1 is None:
            await final_waiting_queue.put(winner2)
            return

        # 큐에 남은 유저들을 다시 넣음
        for user in temp_queue:
            await final_waiting_queue.put(user)

        winner1_user = await database_sync_to_async(get_user_model().objects.get)(id=winner1.id)
        winner2_user = await database_sync_to_async(get_user_model().objects.get)(id=winner2.id)


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
            


class ball():
    x = 200
    y = 200
    velocity_x = 20
    velocity_y = 15
    radius = 20

class GameConsumer(AsyncWebsocketConsumer):
    async def connect(self):
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
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

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
        if message_type == 'initMatch':
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
            await self.channel_layer.group_add(
                self.group_name,
                self.channel_name
            )
            if self.group_name not in ball_group:
                ball_group[self.group_name] = ball()
            client[self.user.id] = True
            await self.check_all_clients_ready(player1_id, player2_id)
        elif message_type == 'paddleMove':
            await self.paddle_move(data.get("id"), data.get("key"))
        elif message_type == 'increaseScore':
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
            winner_user = User.objects.get(nickname=winner)
            loser_user = User.objects.get(nickname=loser)
            
            if game_type == "tournament":
                await self.save_t_loser(winner_user, loser_user.t_nickname)
            elif game_type == "1vs1":
                await self.save_win_lose(winner_user, loser_user)
                
            GameResult.objects.create(
                game_type=game_type,
                winner=winner_user,
                loser=loser_user,
                winner_score=winner_score,
                loser_score=loser_score,
            )
            await self.send(json.dumps({
                'status': 'success',
                'message': 'Game result has been saved successfully.'
            }))
        except User.DoesNotExist:
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
            print("Check ready cancelled")

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
                await asyncio.sleep(0.02)
        except asyncio.CancelledError:
            print("Game loop cancelled")

    async def update_game_state(self):
        ball_group[self.group_name].x += ball_group[self.group_name].velocity_x
        ball_group[self.group_name].y += ball_group[self.group_name].velocity_y

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
        ball = ball_group[self.group_name]
        if self.pos == "left":

            if (ball.x - ball.radius <= self.paddle_pos_x + self.paddle_width and
                ball.x + ball.radius >= self.paddle_pos_x and
                ball.y + ball.radius >= self.paddle_pos_y and
                ball.y - ball.radius <= self.paddle_pos_y + self.paddle_height):

                ball.velocity_x *= -1.1

                ball.x = self.paddle_pos_x + self.paddle_width + ball.radius
        else:
            if (ball.x + ball.radius >= self.paddle_pos_x and
                ball.x - ball.radius <= self.paddle_pos_x + self.paddle_width and
                ball.y + ball.radius >= self.paddle_pos_y and
                ball.y - ball.radius <= self.paddle_pos_y + self.paddle_height):

                ball.velocity_x *= -1.1

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
        ball.velocity_x = 20
        ball.velocity_y = 15
        if self.spawn:
            ball.velocity_x = -abs(ball.velocity_x)
        else:
            ball.velocity_x = abs(ball.velocity_x)
        self.spawn = not self.spawn
        ball.velocity_y *= -1
            
