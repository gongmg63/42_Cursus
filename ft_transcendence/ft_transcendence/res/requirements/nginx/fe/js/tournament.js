document.addEventListener('DOMContentLoaded', () => {
    
	// url로부터 round 파싱
	const round = parseRound();

    // 첫 번째 라운드 데이터 불러오기
    // fetchTournamentData(round);
	updateTournamentUI();
});

function parseRound()
{
	const urlParams = new URLSearchParams(window.location.search);
	return urlParams.get('round');
}

async function fetchTournamentData(round) {
	try {
		// url 추후 수정.
		const response = await fetch(`/api/tournament?round=${round}`);
		const data = await response.json();
		updateTournamentUI(data);
	} catch (error) {
		console.error('Error fetching tournament data:', error);
	}
}

function updateTournamentUI(data) {
	data.matches.forEach((match, index) => {
		const gameTop = document.querySelector(`.round-${data.round} .game-top:nth-child(${index * 4 + 2})`);
		const gameBottom = document.querySelector(`.round-${data.round} .game-bottom:nth-child(${index * 4 + 6})`);

		gameTop.querySelector('span').textContent = match.top.score;
		gameBottom.querySelector('span').textContent = match.bottom.score;

		gameTop.textContent = `${match.top.teamName} `;
		gameBottom.textContent = `${match.bottom.teamName} `;
	});
}