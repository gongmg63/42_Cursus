document.addEventListener('DOMContentLoaded', function() {
    const singleBtn = document.getElementById('single');
    const pvpBtn = document.getElementById('pvp');
    const tournamentBtn = document.getElementById('tournament');

    singleBtn.addEventListener('click', function() {
        console.log('Single mode selected');
		// player 1, 2 이름, game type이 포함된 url로 redirect
		let gameType = "single";
		window.location.href = `https://127.0.0.1/pong.html?gameType=${gameType}`;
    });

    pvpBtn.addEventListener('click', function() {
        console.log('1 vs 1 mode selected');
		// 매치 메이킹 페이지
		window.location.href = 'https://127.0.0.1/matchmaking.html';
    });

    tournamentBtn.addEventListener('click', function() {
        console.log('Tournament mode selected');
		// 토너먼트 페이지
		window.location.href = 'https://127.0.0.1/matchmaking.html';
    });
});
