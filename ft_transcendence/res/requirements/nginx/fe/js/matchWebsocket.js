import { navigateTo, render } from "./transcendence.js";

let websocket = null;

export function match_websocket(currentPath, type)
{
	if (currentPath !== '/matchmaking')
	{
		if (websocket && websocket.readyState === WebSocket.OPEN)
			websocket.close();
		return currentPath;
	}
	if (currentPath === '/matchmaking' && type === null)
	{
		// window.history.pushState(null, null, '#/mode');
		// navigateTo('/mode');
		render('#/mode');
	}

	const access_token = localStorage.getItem("access_token");
	websocket = new WebSocket('wss://cx1r5s3.42seoul.kr/ws/game/match/?token=' + access_token);

	websocket.onopen = function(event) {
		console.log("매칭 웹소켓 연결");
		console.log("게임 타입", type);
		websocket.send(JSON.stringify({
			type: type
		}));
	};

	websocket.onmessage = function(event) {
		const data = JSON.parse(event.data);
		console.log("서버로부터 받은 메시지:", data);

		// 매치 성공 메시지인 경우 처리
		if (data.type === "match_found") {
			updateMatchInfo(data);
			setTimeout(() => startPongGame(data), 2000);
			websocket.close();
		}
	};

	websocket.onclose = function(event) {
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
	else if (matchData.gameType == "tournament1")
	{
		// window.history.pushState(null, null, '#/tournament?round=1');
		// navigateTo('/tournament');
		render('#/tournament?round=1');
		document.querySelector('.loading-container').style.display = 'none';
		const tournament = document.querySelector('.tournament');
		tournament.style.display = 'flex';
		// player 1 2 3 4 지정
	}
	else if (matchData.gameType == "tournament2")
	{
		document.querySelector('.loading-container').style.display = 'none';
		const tournament = document.querySelector('.tournament');
		tournament.style.display = 'flex';
		// player 1 2 3 4 지정
	}
	else // gameType == final
	{
		document.querySelector('.loading-container').style.display = 'none';
		const tournament = document.querySelector('.tournament');
		tournament.style.display = 'flex';
		// player 1 2 3 4 지정
	}
}

function startPongGame(matchData)
{
	const gameType = matchData.gameType;
	
	if (gameType == '1vs1' || gameType == 'tournament1')
	{
		const player1 = matchData.player1.nickname;
		const player2 = matchData.player2.nickname;
		const id1 = matchData.player1.id;
		const id2 = matchData.player2.id;
		
		// window.history.pushState(null, null, `#/multiPong?player1=${player1}&id1=${id1}\
		// &player2=${player2}&id2=${id2}&gameType=${gameType}`);
		// navigateTo('/multiPong');

		render(`#/multiPong?player1=${player1}&id1=${id1}\
		&player2=${player2}&id2=${id2}&gameType=${gameType}`);
	}
	else if (gameType == 'tournament2')
	{
		const player1 = matchData.player3.nickname;
		const player2 = matchData.player4.nickname;
		const id1 = matchData.player3.id;
		const id2 = matchData.player4.id;
	}
	else //gameType == final
	{
		const player1 = matchData.player1.nickname;
		const player2 = matchData.player3.nickname;
		const id1 = matchData.player1.id;
		const id2 = matchData.player3.id;
	}
}