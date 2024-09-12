document.addEventListener('DOMContentLoaded', function() {
    let loadingDots = 0;
    const loadingMessage = document.getElementById('loadingMessage');
    
    // Loading 메시지 애니메이션
    const loadingInterval = setInterval(() => {
        loadingDots = (loadingDots + 1) % 4;  // 0, 1, 2, 3 순환
        loadingMessage.textContent = 'Loading' + '.'.repeat(loadingDots);
    }, 500); // 0.5초마다 점을 추가
	
	// 매치 정보 가져오기 - websocket으로 연결?
	fetchMatchData();
});

function fetchMatchData() {
	setTimeout(function() {
		fetch('https://127.0.0.1/api/match')
		.then(response => response.json())
		.then(data => {
			// 매치 데이터를 성공적으로 가져왔을 경우 화면 업데이트
			updateMatchInfo(data);
			// 잠시 후에 pong 게임 시작.
			startPongGame(data);
		})
		.catch(error => {
			console.error('Error fetching match data:', error);
			// 매치 정보를 가져오는 데 실패하면 다시 시도하거나 오류 처리 가능
		});
	}, 2000); // 테스트 목적으로 2초 대기 후 데이터를 가져옴
}

function updateMatchInfo(matchData) {

	// game type이 multi 이면 1 vs 1 화면
	// game type이 tournament이면 tournament 매치 화면

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

function startPongGame(matchData)
{
	const player1 = matchData.player1.nickname;
	const player2 = matchData.player1.nickname;
	const gameType = matchData.gameType;

	window.location.href = `https://127.0.0.1/pong.html?player1=${player1}&player2=${player2}&gameType=${gameType}`;
}