import { checkAndRefreshToken } from "./jwtRefresh.js";
import { render } from "./transcendence.js";

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
let websocket = null;
let checkEnd;

window.startMultiPong = function()
{
	console.log("Start multi pong");

	const hash = window.location.hash;
	const queryParams = new URLSearchParams(hash.split('?')[1]);  // ?gameType= 이후의 파라미터만 추출
	gameType = queryParams.get('gameType');

	checkEnd = false;
	canvas = document.getElementById('canvas');
	ctx = canvas.getContext('2d');

	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	ball = new Ball(vec2(ballX, ballY), vec2(ballVelocityX, ballVelocityY), ballRadius);
	// parseGameURL();
	// setUpMultiPong();
	console.log("multpong type:", gameType);
	game_play_websocket('/multiPong', gameType);
}


function parseGameURL(data)
{
    console.log(data);

	// gameType = data.gameType;
	player1 = data.player1;
	player2 = data.player2;
	id1 = data.id1;
	id2 = data.id2;
	// player1 = queryParams.get('player1');
	// player2 = queryParams.get('player2');
	// id1 = queryParams.get('id1');
	// id2 = queryParams.get('id2');

	document.getElementById("player1Name").textContent = player1;
	document.getElementById("player2Name").textContent = player2;
	// console.log(player1, player2, id1, id2);
}

function setUpMultiPong()
{
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
export function game_play_websocket(currentPath, type)
{
	if (currentPath !== '/multiPong')
	{
		if (websocket && websocket.readyState === WebSocket.OPEN)
		{
			websocket.send(JSON.stringify({
				"type": 'outPage',
				"id": playerNumber,
				"myScore": myPad.score,
				"opScore": opPad.score,
				"endScore": endScore
			}));
			websocket.close();
		}
		return ;
	}
	console.log("multipong:", type);
	if (currentPath === '/multiPong' && type == null)
	{
		render('#/mode');
		return ;
	}
	access_token = localStorage.getItem("access_token");
	// websocket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/game/play/?token=' + access_token);
	websocket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/game/play/?token=' + access_token);
// const socket = new WebSocket('wss://cx1r4s6.42seoul.kr/ws/game/play/?token=' + access_token);

	websocket.onopen = function() {
		// 서버로 플레이어 정보와 게임 타입을 보냄
		console.log("게임 웹소켓 연결")
		if (websocket.readyState === WebSocket.OPEN)
		{
			websocket.send(JSON.stringify({
				type: "initMatch",
				// player1_id: id1,
				// player2_id: id2,
				canvas_width: canvas.width,
				canvas_height: canvas.height,
			}));
		}
	};

	websocket.onclose = function() {
		console.log("게임 웹소켓 연결 종료");
	}
	websocket.onmessage = function(event) {
		const data = JSON.parse(event.data);
		// console.log(data)
		if (data.type === 'parseGameData')
		{
			parseGameURL(data);
			setUpMultiPong();
		}
		else if (data.type === 'paddleMove')
		{
			if (playerNumber === data.id)
				myPad.update(data.y)
			else
				opPad.opUpdate(data.y);
		}
		else if (data.type === 'ballMove')
		{
			ball.pos.x = data.ball_pos_x;
			ball.pos.y = data.ball_pos_y;
			ball.velocity.x = data.ball_velocity_x;
			ball.velocity.y = data.ball_velocity_y;
			ball.radius = data.ball_radius;
			ball.update();
		}
		else if (data.type === 'increaseScore')
		{
			if (data.result === "win")
			{
				myPad.score++;
				if (playerNumber === id1)
					document.getElementById("player1Score").innerHTML = myPad.score
				else
					document.getElementById("player2Score").innerHTML = myPad.score;
			}
			else
			{
				opPad.score++;
				if (playerNumber === id1)
					document.getElementById("player2Score").innerHTML = opPad.score;
				else
					document.getElementById("player1Score").innerHTML = opPad.score;
			}
		}
		else if (data.type === 'startGame')
			gameLoop();
		else if (data.type === 'outPlayer')
		{
			if (data.out_player === playerNumber)
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
		else if (data.type === 'checkGameEnd')
		{
			if (!checkEnd)
			{
				websocket.send(JSON.stringify({
					"type": 'outPage',
					"id": playerNumber === id1 ? id2 : id1,
					"myScore": myPad.score,
					"opScore": opPad.score,
					"endScore": endScore
				}));
			}
		}
	}
}

// window.addEventListener("beforeunload", function (e) {
// 	// e.returnValue = "refresh message";
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
	if (websocket && websocket.readyState === WebSocket.OPEN)
	{
		if (e.key === KEY_ARROWDOWN) { // 이미 눌린 키에 대해 처리하지 않음
			websocket.send(JSON.stringify({
				type: 'paddleMove',
				id: playerNumber,
				key: 'down'
			}));
		}
		else if (e.key === KEY_ARROWUP) {
			websocket.send(JSON.stringify({
				type: 'paddleMove',
				id: playerNumber,
				key: 'up'
			}));
		}
	}
});

window.cleanUpMultiPong = function()
{
	if (animationFrameId)
		cancelAnimationFrame(animationFrameId);

	// console.log("Multi Pong 게임이 정리되었습니다.");
}

function gameLoop()
{
	// ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	animationFrameId = window.requestAnimationFrame(gameLoop);	

	if (!checkEnd)
		checkGameEnd();
	gameDraw();
}

function checkGameEnd()
{
	// 점수 설정
	if (myPad.score >= endScore || opPad.score >= endScore)
	{
		checkEnd = true;
	
        let winner, loser;
        let winnerScore, loserScore;
		let checkWinner = 'false';

		if (myPad.score < opPad.score) // 내가 졌을 때
		{
			winner = (playerNumber == id1) ? player2 : player1;
			loser = (playerNumber == id1) ? player1 : player2;
            winnerScore = opPad.score;
            loserScore = myPad.score;
		}
		else // 내가 이겼을 때
		{
			checkWinner = 'true';
			winner = (playerNumber == id1) ? player1 : player2;
            loser = (playerNumber == id1) ? player2 : player1;
            winnerScore = myPad.score;
            loserScore = opPad.score;
		}
		websocket.send(JSON.stringify({
			'type': "endGame",
			'gameType': gameType,
			'winner': winner,
			'winnerScore': winnerScore,
			'loser': loser,
			'loserScore': loserScore,
			'checkWinner': checkWinner
		}));
		// game type에 따라 다르게 redirect - 1vs1, tournament
		console.log(playerNumber, id1, id2, myPad.score, opPad.score, gameType);
		// console.log(winner, winnerScore, loser, loserScore, gameType);
		// render(`#/result?winner=${winner}&winnerScore=${winnerScore}&loser=${loser}&loserScore=${loserScore}&gameType=${gameType}`);
		setTimeout(() => {
			render(`#/result?gameType=${gameType}`);
			websocket.close();
		}, 100);
		// setTimeout(() => {
		// }, 100);
	}
}

function vec2(x, y)
{
	return {x: x, y: y};
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

function gameDraw()
{
	ball.draw();
	myPad.draw();
	opPad.draw();
	drawGameScene();
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