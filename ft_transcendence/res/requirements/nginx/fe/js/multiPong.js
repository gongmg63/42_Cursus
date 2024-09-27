import { checkAndRefreshToken } from "./jwtRefresh.js";
import { navigateTo } from "./transcendence.js";

checkAndRefreshToken().then(() => {
})

let canvas;
let ctx;
let animationFrameId;

const KEY_ARROWUP = "ArrowUp";
const KEY_ARROWDOWN = "ArrowDown";

let ballX = 200;
let ballY = 200;
let ballRadius = 20;
let ballVelocityX = 20;
let ballVelocityY = 15;
let endScore = 3;

let ball;
let myPad, opPad;
let playerNumber;

// game 시작 전에 player 1, 2 이름, game type 파싱.
let player1, player2, gameType;
let id1, id2;

let access_token;
let socket;

window.startMultiPong = function()
{
	console.log("Start multi pong");

	setUpMultiPong();
	parseGameURL();
	game_play_websocket();
}

function game_play_websocket()
{
	access_token = localStorage.getItem("access_token");
	socket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/game/play/?token=' + access_token);
// const socket = new WebSocket('wss://cx1r4s6.42seoul.kr/ws/game/play/?token=' + access_token);

	socket.onopen = function() {
		// 서버로 플레이어 정보와 게임 타입을 보냄
		console.log("게임 웹소켓 연결")
		socket.send(JSON.stringify({
			type: "initMatch",
			player1_id: id1,
			player2_id: id2,
			canvas_width: canvas.width,
			canvas_height: canvas.height,
		}));
	};

	socket.onmessage = function(event) {
		const data = JSON.parse(event.data);
		// console.log(data)
		if (data.type == 'paddleMove')
		{
			if (playerNumber == data.id)
				myPad.update(data.y)
			else
				opPad.opUpdate(data.y);
		}
		else if (data.type == 'ballMove')
		{
			ball.pos.x = data.ball_pos_x;
			ball.pos.y = data.ball_pos_y;
			ball.velocity.x = data.ball_velocity_x;
			ball.velocity.y = data.ball_velocity_y;
			ball.radius = data.ball_radius;
			ball.update();
		}
		else if (data.type == 'increaseScore')
		{
			if (data.result == "win")
			{
				myPad.score++;
				if (playerNumber == id1)
					document.getElementById("player2Score").innerHTML = myPad.score
				else
					document.getElementById("player1Score").innerHTML = myPad.score;
			}
			else
			{
				opPad.score++;
				if (playerNumber == id1)
					document.getElementById("player1Score").innerHTML = opPad.score;
				else
					document.getElementById("player2Score").innerHTML = opPad.score;
			}
		}
		else if (data.type == 'startGame')
			gameLoop();
		else if (data.type == 'outPlayer')
		{
			if (data.out_player == playerNumber)
			{
				myPad.score = 0;
				opPad.score = endScore;
			}
			else
			{
				myPad.score = endScore;
				opPad.score = 0;
			}
		}
	}
}

// window.addEventListener("beforeunload", function (e) {
// 	// e.returnValue = "refresh message";
// 	const message = JSON.stringify({
// 		"type": 'outPage',
// 		"id": playerNumber,
// 		"myScore": myPad.score,
// 		"opScore": opPad.score,
// 		"endScore": endScore
// 	});
// 	socket.send(message);
// });

// window.onload = function() {
// 	// 페이지가 이미 로드되었는지 확인
// 	if (sessionStorage.getItem('pong_pageLoaded')) {
// 		// 페이지가 이미 로드되었다면 (즉, 새로고침된 경우)
// 		setTimeout(function() {
// 		// 원하는 URL로 변경하세요
// 		myPad.score = 0;
// 		opPad.score = endScore;
// 		checkGameEnd();
// 	  }, 100);
// 	} else {
// 	  // 페이지가 처음 로드된 경우
// 	  sessionStorage.setItem('pong_pageLoaded', 'true');
// 	}
//   };

window.addEventListener('keydown', function(e) {
	if (e.key === KEY_ARROWDOWN) { // 이미 눌린 키에 대해 처리하지 않음
        const message = JSON.stringify({
			type: 'paddleMove',
			id: playerNumber,
            key: 'down'
        });
        socket.send(message);
    }
	else if (e.key === KEY_ARROWUP) {
		const message = JSON.stringify({
			type: 'paddleMove',
			id: playerNumber,
			key: 'up'
		});
		socket.send(message);
	}
});

window.cleanUpMultiPong = function()
{
	if (animationFrameId)
		cancelAnimationFrame(animationFrameId);

	console.log("Multi Pong 게임이 정리되었습니다.");
}

function setUpMultiPong()
{
	canvas = document.getElementById('canvas');
	ctx = canvas.getContext('2d');

	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	ball = new Ball(vec2(ballX, ballY), vec2(ballVelocityX, ballVelocityY), ballRadius);

	if (player1 == localStorage.getItem('nickname'))
	{
		myPad = new Paddle(vec2(0, 50), vec2(15, 15), 20, 200);
		opPad = new Paddle(vec2(canvas.width - 20, 30), vec2(15, 15), 20, 200);
		playerNumber = id1;
	}
	else
	{
		myPad = new Paddle(vec2(canvas.width - 20, 30), vec2(15, 15), 20, 200);
		opPad = new Paddle(vec2(0, 50), vec2(15, 15), 20, 200);
		playerNumber = id2;
	}
}


function drawGameScene()
{
	ctx.strokeStyle = "#ffff00";

	ctx.beginPath();
	ctx.linewidth = 40;
	ctx.moveTo(0, 0);
	ctx.lineTo(canvas.width, 0);
	ctx.stroke();

	ctx.beginPath();
	ctx.linewidth = 40;
	ctx.moveTo(0, canvas.height);
	ctx.lineTo(canvas.width, canvas.height);
	ctx.stroke();

	ctx.beginPath();
	ctx.linewidth = 40;
	ctx.moveTo(0, 0);
	ctx.lineTo(0, canvas.height);
	ctx.stroke();

	ctx.beginPath();
	ctx.linewidth = 40;
	ctx.moveTo(canvas.width, 0);
	ctx.lineTo(canvas.width, canvas.height);
	ctx.stroke();

	ctx.beginPath();
	ctx.linewidth = 40;
	ctx.moveTo(canvas.width / 2, 0);
	ctx.lineTo(canvas.width / 2, canvas.height);
	ctx.stroke();

	ctx.beginPath();
	ctx.arc(canvas.width / 2, canvas.height / 2, 50, 0, Math.PI * 2);
	ctx.stroke();
}

function parseGameURL()
{
	const hash = window.location.hash;
	const queryParams = new URLSearchParams(hash.split('?')[1])
	gameType = queryParams.get('gameType');

	if (gameType == 'single')
	{
		player1 = localStorage.getItem('nickname');
		player2 = player1;
	}
	else
	{
		player1 = queryParams.get('player1');
		player2 = queryParams.get('player2');
		id1 = queryParams.get('id1');
		id2 = queryParams.get('id2');
	}

	document.getElementById("player1Name").textContent = player1;
	document.getElementById("player2Name").textContent = player2;
}

function gameLoop()
{
	// ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	animationFrameId = window.requestAnimationFrame(gameLoop);	

	checkGameEnd();
	gameDraw();
}

function checkGameEnd()
{
	// 점수 설정
	if (myPad.score >= endScore || opPad.score >= endScore)
	{
		//소켓 연결 종료
		socket.send(JSON.stringify({
			type: "initMatch",
			player1_id: id1,
			player2_id: id2,
			canvas_width: canvas.width,
			canvas_height: canvas.height,
		}));
		socket.close();

        let winner, loser;
        let winnerScore, loserScore;

		if (myPad.score < opPad.score) // 내가 졌을 때
		{
			if (playerNumber == id1) // 내가 player1 일 때
			{
				winner = player2;
				loser = player1;
			}
			else //내가 player2 일 때
			{
				winner = player1;
				loser = player2;
			}
            winnerScore = opPad.score;
            loserScore = myPad.score;
		}
		else // 내가 이겼을 때
		{
			if (playerNumber == id1) // 내가 player1 일 때
			{
				winner = player1;
				loser = player2;
			}
			else // 내가 player2 일 때
			{
				winner = player2;
				loser = player1;
			}
            winnerScore = myPad.score;
            loserScore = opPad.score;
		}
		// game type에 따라 다르게 redirect - 1vs1, tournament
        // window.location.href = `/result.html?winner=${winner}&winnerScore=${winnerScore}&loser=${loser}&loserScore=${loserScore}&gameType=${gameType}`;
		// window.history.replaceState({}, document.title, window.location.pathname + `#/result?winner=${winner}&winnerScore=${winnerScore}&loser=${loser}&loserScore=${loserScore}&gameType=${gameType}`);
		console.log(winner, winnerScore, loser, loserScore, gameType);
		window.history.pushState(null, null, `#/result?winner=${winner}&winnerScore=${winnerScore}&loser=${loser}&loserScore=${loserScore}&gameType=${gameType}`);
		navigateTo('/result');
	}
}

function gameDraw()
{
	ball.draw();
	myPad.draw();
	opPad.draw();
	drawGameScene();
}

function vec2(x, y)
{
	return {x: x, y: y};
}

function respawnBall(ball)
{
	if (ball.velocity.x > 0)
	{
		ball.pos.x = canvas.width - 150;
		ball.pos.y = (Math.random() * (canvas.height - 200)) + 100;
	}

	if (ball.velocity.x < 0)
	{
		ball.pos.x = 150;
		ball.pos.y = (Math.random() * (canvas.height - 200)) + 100;
	}

	ball.velocity.x *= -1;
	ball.velocity.y *= -1;
}

function increaseScore(ball, paddle1, paddle2)
{
	if (ball.pos.x <= -ball.radius)
	{
		paddle2.score += 1;
		document.getElementById("player2Score").innerHTML = paddle2.score;
		respawnBall(ball);
	}
	if (ball.pos.x >= canvas.width + ball.radius)
	{
		paddle1.score += 1;
		document.getElementById("player1Score").innerHTML = paddle1.score;
		respawnBall(ball);
	}
}

function Ball(pos, velocity, radius)
{
	this.pos = pos;
	this.velocity = velocity;
	this.radius = radius;

	this.update = function() {
		this.pos.x += this.velocity.x;
		this.pos.y += this.velocity.y;
	};

	this.draw = function() {
		ctx.fillStyle = "#33ff00";
		ctx.strokeStyle = "#33ff00";
		ctx.beginPath();
		ctx.arc(this.pos.x, this.pos.y, this.radius, 0, Math.PI * 2);
		ctx.fill();
		ctx.stroke();
	}
}

function Paddle(pos, velocity, width, height)
{
	this.pos = pos;
	this.velocity = velocity;
	this.width = width;
	this.height = height;
	// this.upKey = upKey;
	// this.downKey = downKey;
	this.score = 0;

	this.update = function(y) {
		this.pos.y = y
	}

	this.opUpdate = function(y) {
		this.pos.y = y;
	}

	this.draw = function() {
		ctx.fillStyle = "#33ff00";
		ctx.fillRect(this.pos.x, this.pos.y, this.width, this.height);
	}

	this.getHalfWidth = function () {
		return this.width / 2;
	}

	this.getHalfHeight = function () {
		return this.height / 2;
	}

	this.getCenter = function () {
		return vec2(
			this.pos.x + this.getHalfWidth(),
			this.pos.y + this.getHalfHeight()
		);
	}
}

function paddleCollisionWithEdges(paddle)
{
	if (paddle.pos.y <= 0)
	{
		paddle.pos.y = 0;
	}
	if (paddle.pos.y + paddle.height >= canvas.height)
	{
		paddle.pos.y = canvas.height - paddle.height;
	}
}

function ballCollisionWithEdges(ball)
{
	if (ball.pos.y - ball.radius <= 0)
	{
		ball.velocity.y *= -1;
	}
	if (ball.pos.y + ball.radius >= canvas.height)
	{
		ball.velocity.y *= -1;
	}
}

// 충돌계산법 수정 필요.
function ballPaddleCollision(ball, paddle)
{
	return (ball.pos.x < paddle.pos.x + paddle.width && ball.pos.x + ball.radius > paddle.pos.x &&
		ball.pos.y < paddle.pos.y + paddle.height && ball.pos.y + ball.radius > paddle.pos.y);
}

