import { render } from "./transcendence.js";

let websocket = null;

// 매칭 중 뒤로가기 시 checkCancel 플래그를 true로 바꿔 startPongGame이 실행되는걸 방지
// 남아있는 사람에게는 matchingOut 메시지를 보내 그 사람 역시 startPongGame이 실행되는 걸 방지
// 뒤로 가기, 앞으로 가기 시에는 웹소켓이 끊기지 않는 걸 이용
let checkCancel;
let matchTimer = null; // 2초안에 다시 들어오는 걸 방지

export function match_websocket(currentPath, type)
{
	checkCancel = false;

	if (currentPath !== '/matchmaking')
	{
		if (websocket && websocket.readyState === WebSocket.OPEN)
			websocket.close();
		return ;
	}
	if (currentPath === '/matchmaking' && type === null)
	{
		render('#/mode');
		return ;
	}

	const access_token = localStorage.getItem("access_token");
	websocket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/game/match/?token=' + access_token);
	// websocket = new WebSocket('wss://cx1r5s3.42seoul.kr/ws/game/match/?token=' + access_token);
	// websocket = new WebSocket('wss://cx1r4s6.42seoul.kr/ws/game/match/?token=' + access_token);

	websocket.onopen = function(event) {
		console.log("매칭 웹소켓 연결");
		console.log("게임 타입", type);
		if (websocket.readyState === WebSocket.OPEN)
		{
			websocket.send(JSON.stringify({
				type: type
			}));
		}
	};

	websocket.onmessage = function(event) {
		const data = JSON.parse(event.data);
		console.log("서버로부터 받은 메시지:", data);

		// 매치 성공 메시지인 경우 처리
		if (data.type === "match_found") {
			updateMatchInfo(data);
			if (matchTimer) {
				clearTimeout(matchTimer);
			}

			matchTimer = setTimeout(() => {
				if (!checkCancel) {
					startPongGame(data);
				}
			}, 2000);
		}
		else if (data.type === "match_cancel")
		{
			if (matchTimer) {
				clearTimeout(matchTimer);
				matchTimer = null;
			}

			websocket.close();
			checkCancel = true;
			render('#/mode');
		}
	};

	websocket.onclose = function(event) {
		checkCancel = true;
		if (matchTimer) {
			clearTimeout(matchTimer);
			matchTimer = null;
		}
		console.log("매칭 웹소켓 연결 종료");
	};
	
	websocket.onerror = function(error) {
		console.error("매칭 웹소켓 에러:", error);
	};
}

function updateMatchInfo(matchData) {
	
	if (matchData.gameType == "1vs1")
	{
		// 로딩 메시지 숨기기
		document.querySelector('.loading-container').style.display = 'none';
		
		// 매치 컨테이너 표시
		const matchContainer = document.querySelector('.match-container');
		matchContainer.style.display = 'flex';
		
		// Player 1 정보 업데이트
		document.getElementById('player1Avatar').src = matchData.player1.profile;
		document.getElementById('player1Nickname').textContent = matchData.player1.nickname;
		document.getElementById('player1Stats').textContent = `Wins: ${matchData.player1.wins} | Losses: ${matchData.player1.losses}`;
		
		// Player 2 정보 업데이트
		document.getElementById('player2Avatar').src = matchData.player2.profile;
		document.getElementById('player2Nickname').textContent = matchData.player2.nickname;
		document.getElementById('player2Stats').textContent = `Wins: ${matchData.player2.wins} | Losses: ${matchData.player2.losses}`;
	}
	// game type이 tournament이면 tournament 매치 화면
	else if (matchData.gameType == "tournament1" || matchData.gameType == "tournament2")
	{
		document.querySelector('.loading-container').style.display = 'none';
		const tournament = document.querySelector('.tournament');
		tournament.style.display = 'flex';
		updateTournamentUI(matchData);
	}
	else // gameType == final
	{
		document.querySelector('.loading-container').style.display = 'none';
		const tournament = document.querySelector('.tournament');
		tournament.style.display = 'flex';
		updateFinalUI(matchData);
	}
}

function startPongGame(matchData)
{
	const gameType = matchData.gameType;
	let player1, player2, id1, id2;

	if (gameType == '1vs1' || gameType == 'tournament1')
	{
		player1 = matchData.player1.nickname;
		player2 = matchData.player2.nickname;
		id1 = matchData.player1.id;
		id2 = matchData.player2.id;
	}
	else if (gameType == 'tournament2')
	{
		player1 = matchData.player3.nickname;
		player2 = matchData.player4.nickname;
		id1 = matchData.player3.id;
		id2 = matchData.player4.id;
	}
	else //gameType == final
	{
		player1 = matchData.player1.nickname;
		player2 = matchData.player3.nickname;
		id1 = matchData.player1.id;
		id2 = matchData.player3.id;
	}
	
	render(`#/multiPong?gameType=${gameType}`);
}

function updateTournamentUI(matchData)
{
	// player 1, player 2, player 3, player 4
	const gameTop1 = document.querySelector('.round-1 .game-top:nth-child(2)');
	const gameBottom1 = document.querySelector('.round-1 .game-bottom:nth-child(4)');

	gameTop1.textContent = `${matchData.player1.t_nickname} `;
	gameBottom1.textContent = `${matchData.player2.t_nickname} `;

	const gameTop2 = document.querySelector('.round-1 .nth-child(6)');
	const gameBottom2 = document.querySelector('.round-1 .game-bottom:nth-child(8)');

	gameTop2.textContent = `${matchData.player3.t_nickname} `;
	gameBottom2.textContent = `${matchData.player4.t_nickname} `;
}

function updateFinalUI(matchData) {
	const gameTop1 = document.querySelector('.round-1 .game-top:nth-child(2)');
	const gameBottom1 = document.querySelector('.round-1 .game-bottom:nth-child(4))');
	
	gameTop1.textContent = `${matchData.player1.t_nickname} `;
	gameBottom1.textContent = `${matchData.player2} `;
	
	const gameTop2 = document.querySelector('.round-1 .nth-child(6)');
	const gameBottom2 = document.querySelector('.round-1 .game-bottom:nth-child(8))');
	
	gameTop2.textContent = `${matchData.player3.t_nickname} `;
	gameBottom2.textContent = `${matchData.player4} `;

    const finalTop = document.querySelector('.round-2 .game-top:nth-child(2)');
    const finalBottom = document.querySelector('.round-2 .game-bottom:nth-child(4)');
    
    finalTop.querySelector('span').textContent = matchData.player1.t_nickname;
    finalBottom.querySelector('span').textContent = matchData.player3.t_nickname;
}