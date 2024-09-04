document.addEventListener('DOMContentLoaded', function() {
    const singleBtn = document.getElementById('single');
    const pvpBtn = document.getElementById('pvp');
    const tournamentBtn = document.getElementById('tournament');

    singleBtn.addEventListener('click', function() {
        console.log('Single mode selected');
		window.location.href = 'http://localhost:5500/html/pong.html';
    });

    pvpBtn.addEventListener('click', function() {
        console.log('1 vs 1 mode selected');
		// 매치 메이킹 페이지
    });

    tournamentBtn.addEventListener('click', function() {
        console.log('Tournament mode selected');
		// 토너먼트 페이지
    });
});
