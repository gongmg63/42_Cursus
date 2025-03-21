import { navigateTo, render } from "./transcendence.js";

let canvas;
let ctx;

const keyPressed = [];
const KEY_UP = "w";
const KEY_DOWN = "s";
const KEY_ARROWUP = "ArrowUp";
const KEY_ARROWDOWN = "ArrowDown";

let animationFrameId;

let ballX = 200;
let ballY = 200;
let ballRadius = 20;
let ballVelocityX = 20;
let ballVelocityY = 15;
let player1, player2, gameType;

let ball;
let paddle1;
let paddle2;

function handleKeyUp(e)
{
	keyPressed[e.key] = false;
}

function handleKeyDown(e) {
	keyPressed[e.key] = true;
}

window.startPong = function()
{	
	setUpPong();
	parseGameURL();
	gameLoop();
}

function setUpPong()
{
	canvas = document.getElementById('canvas');
	ctx = canvas.getContext('2d');	

	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	window.addEventListener('keydown', handleKeyDown);
	window.addEventListener('keyup', handleKeyUp);

	ball = new Ball(vec2(ballX, ballY), vec2(ballVelocityX, ballVelocityY), ballRadius);
	paddle1 = new Paddle(vec2(0, 50), vec2(15, 15), 20, 200, KEY_UP, KEY_DOWN);
	paddle2 = new Paddle(vec2(canvas.width - 20, 30), vec2(15, 15), 20, 200, KEY_ARROWUP, KEY_ARROWDOWN);
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
    const queryParams = new URLSearchParams(hash.split('?')[1]);  // ?gameType= 이후의 파라미터만 추출
    gameType = queryParams.get('gameType');

	player1 = localStorage.getItem('nickname');
	player2 = player1;
}

function gameLoop()
{
	// ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	animationFrameId = window.requestAnimationFrame(gameLoop);

	checkGameEnd();
	gameUpdate();
	gameDraw();
}

export function cleanUpPong()
{
    if (animationFrameId) {
        cancelAnimationFrame(animationFrameId);  // 게임 루프 중지
    }
}


function checkGameEnd()
{
	let endScore = 3;
	if (paddle1.score >= endScore || paddle2.score >= endScore)
	{
        let winner, loser;
        let winnerScore, loserScore;

        if (paddle1.score > paddle2.score) {
            winner = player1;
            loser = player2;
            winnerScore = paddle1.score;
            loserScore = paddle2.score;
        }
		else {
            winner = player2;
            loser = player1;
            winnerScore = paddle2.score;
            loserScore = paddle1.score;
        }
		render(`#/result?gameType=${gameType}`);
	}
}

function gameUpdate()
{
	ball.update();
	paddle1.update();
	paddle2.update();
	paddleCollisionWithEdges(paddle1);
	paddleCollisionWithEdges(paddle2);
	ballCollisionWithEdges(ball);
	if (ballPaddleCollision(ball, paddle1))
	{
		ball.velocity.x *= -1;
		ball.pos.x = paddle1.pos.x + paddle1.width;
	}
	if(ballPaddleCollision(ball, paddle2))
	{
		ball.velocity.x *= -1;
		ball.pos.x = paddle2.pos.x - ball.radius;
	}
	increaseScore(ball, paddle1, paddle2);
}

function gameDraw()
{
	ball.draw();
	paddle1.draw();
	paddle2.draw();
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

function Paddle(pos, velocity, width, height, upKey, downKey)
{
	this.pos = pos;
	this.velocity = velocity;
	this.width = width;
	this.height = height;
	this.upKey = upKey;
	this.downKey = downKey;
	this.score = 0;

	this.update = function() {
		if (keyPressed[upKey])
		{
			this.pos.y -= this.velocity.y;
		}
		if (keyPressed[downKey])
		{
			this.pos.y += this.velocity.y;
		}
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

function ballPaddleCollision(ball, paddle)
{
	return (ball.pos.x < paddle.pos.x + paddle.width && ball.pos.x + ball.radius > paddle.pos.x &&
		ball.pos.y < paddle.pos.y + paddle.height && ball.pos.y + ball.radius > paddle.pos.y);
}

