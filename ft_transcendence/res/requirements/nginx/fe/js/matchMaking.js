import { friend_websocket } from "./friendWebsocket.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

const urlParams = new URLSearchParams(window.location.search);
const type = urlParams.get("gameType");
const nick = urlParams.get("nickname");

checkAndRefreshToken().then(() => {
	friend_websocket()
		.then((websocket) => {
			const access_token = localStorage.getItem("access_token");
			// wss://cx1r5s2.42seoul.kr/ws/game/match/?token=
			const socket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/game/match/?token=' + access_token);
			
			// WebSocket 연결이 열렸을 때 실행
			socket.onopen = function(event) {
				console.log("WebSocket 연결 성공:", event);
				// 서버에 메시지를 보내는 예시 (매칭 요청)
				socket.send(JSON.stringify({
					type: type
				}));
			};
			
			// 서버로부터 메시지를 받을 때 실행
			socket.onmessage = function(event) {
				const data = JSON.parse(event.data);
				console.log("서버로부터 받은 메시지:", data);
			
				// 매치 성공 메시지인 경우 처리
				if (data.type === "match_found") {
					console.log("매칭 성공! 상대방은:", data.opponent);
				}
				updateMatchInfo(data);
				setTimeout(() => startPongGame(data), 2000);
			};
			
			// WebSocket 연결이 닫혔을 때 실행
			socket.onclose = function(event) {
				console.log("WebSocket 연결 종료:", event);
			};
			
			// WebSocket 에러 발생 시 실행
			socket.onerror = function(error) {
				console.error("WebSocket 에러:", error);
			};
			
			document.addEventListener('DOMContentLoaded', function() {
				let loadingDots = 0;
				const loadingMessage = document.getElementById('loadingMessage');
				
				const loadingInterval = setInterval(() => {
					loadingDots = (loadingDots + 1) % 4;
					loadingMessage.textContent = 'Loading' + '.'.repeat(loadingDots);
				}, 500);
			});
			
			
			function updateMatchInfo(matchData) {
				
				// game type이 multi 이면 1 vs 1 화면
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
				else if (matchData.gameType == "tournament")
				{
					
					window.location.href = `/tournament.html?round=1`;
				}
			}
			
			function startPongGame(matchData)
			{
				const player1 = matchData.player1.nickname;
				const player2 = matchData.player2.nickname;
				const gameType = matchData.gameType;
				const id1 = matchData.player1.id;
				const id2 = matchData.player2.id;
				
				window.location.href = `/multiPong.html?player1=${player1}&id1=${id1}\
				&player2=${player2}&id2=${id2}&gameType=${gameType}`;
			}
		})
		.catch((error) => {
			console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
		});
})
