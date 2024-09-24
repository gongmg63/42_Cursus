import { friend_websocket } from "./friendWebsocket.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

checkAndRefreshToken().then(() => {
	friend_websocket()
		.catch((error) => {
			console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
		});
})

window.addEventListener("beforeunload", function (e) {
	// e.returnValue = "refresh message";
	
	const message = JSON.stringify({
		type: 'outPage',
		id: playerNumber,
	});
	socket.send(message);
    window.location.href = "https://cx1r5s2.42seoul.kr/index.html";
});

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

// const keyPressed = [];
const KEY_ARROWUP = "ArrowUp";
const KEY_ARROWDOWN = "ArrowDown";

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

// window.addEventListener('keyup', function(e) {
// });

let ballX = 200;
let ballY = 200;
let ballRadius = 20;
let ballVelocityX = 20;
let ballVelocityY = 15;

let ball = new Ball(vec2(ballX, ballY), vec2(ballVelocityX, ballVelocityY), ballRadius);
let myPad, opPad;
let playerNumber;

// game 시작 전에 player 1, 2 이름, game type 파싱.
let player1, player2, gameType;
let id1, id2;
parseGameURL();

// 추후 조건 수정 가능.
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

const access_token = localStorage.getItem("access_token");
// url 수정 필요
const socket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/game/play/?token=' + access_token);

socket.onopen = function() {
    // 서버로 플레이어 정보와 게임 타입을 보냄
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
				document.getElementById("player2Score").innerHTML = myPad.score;
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
			opPad.score = 11;
			// if (playerNumber == id1)
			// {
			// 	document.getElementById("player1Score").innerHTML = 0;
			// 	document.getElementById("player2Score").innerHTML = 11;
			// }
			// else
			// {
			// 	document.getElementById("player1Score").innerHTML = 11;
			// 	document.getElementById("player2Score").innerHTML = 0;
			// }
		}
		else
		{
			myPad.score = 11;
			opPad.score = 0;
			// if (playerNumber == id1)
			// {
			// 	document.getElementById("player1Score").innerHTML = 11;
			// 	document.getElementById("player2Score").innerHTML = 0;
			// }
			// else
			// {
			// 	document.getElementById("player1Score").innerHTML = 0;
			// 	document.getElementById("player2Score").innerHTML = 11;
			// }
		}
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
	const urlParams = new URLSearchParams(window.location.search);
	gameType = urlParams.get('gameType');

	if (gameType == 'single')
	{
		player1 = localStorage.getItem('nickname');
		player2 = player1;
	}
	else if (gameType == '1vs1' || gameType == 'tournament')
	{
		player1 = urlParams.get('player1');
		player2 = urlParams.get('player2');
		id1 = urlParams.get('id1');
		id2 = urlParams.get('id2');
	}

	document.getElementById("player1Name").textContent = player1;
	document.getElementById("player2Name").textContent = player2;
}

function gameLoop()
{
	// ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	window.requestAnimationFrame(gameLoop);	

	checkGameEnd();
	gameUpdate();
	gameDraw();
}

function checkGameEnd()
{
	// 점수 설정
	let endScore = 3;
	if (myPad.score >= endScore || opPad.score >= endScore)
	{
        let winner, loser;
        let winnerScore, loserScore;

		if (myPad.score < opPad.score)
		{
			if (playerNumber == id1)
			{
				winner = player1;
				loser = player2;
			}
			else
			{
				winner = player2;
				loser = player1;
			}
            winnerScore = opPad.score;
            loserScore = myPad.score;
		}
		else
		{
			if (playerNumber == id1)
			{
				winner = player2;
				loser = player1;
			}
			else
			{
				winner = player1;
				loser = player2;
			}
            winnerScore = myPad.score;
            loserScore = opPad.score;
		}
		// game type에 따라 다르게 redirect - 1vs1, tournament
        window.location.href = `/result.html?winner=${winner}&winnerScore=${winnerScore}&loser=${loser}&loserScore=${loserScore}&gameType=${gameType}`;
	}
}

function gameUpdate()
{
	// ball.update();
	// myPad.update();
	// opPad.opUpdate();
	// paddleCollisionWithEdges(myPad);
	// paddleCollisionWithEdges(opPad);
	// ballCollisionWithEdges(ball);
	// if (ballPaddleCollision(ball, myPad))
	// {
	// 	ball.velocity.x *= -1;
	// 	ball.pos.x = myPad.pos.x + myPad.width;
	// }
	// if(ballPaddleCollision(ball, opPad))
	// {
	// 	ball.velocity.x *= -1;
	// 	ball.pos.x = opPad.pos.x - ball.radius;
	// }
	// increaseScore(ball, myPad, opPad);

	// paddle 위치
	// socket.send(JSON.stringify({
	// 	type: 'paddleMove',
	// 	id: playerNumber,
	// 	y: myPad.pos.y
	// }));

	// 공 위치
	// socket.send(JSON.stringify({
	// 	type: 'ballMove',
	// 	ball
	// }));
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

