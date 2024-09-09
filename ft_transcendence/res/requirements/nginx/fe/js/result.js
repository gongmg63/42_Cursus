
document.addEventListener('DOMContentLoaded', function() {
	
	// single, 1 vs 1, tournament에 따라 결과 다르게 - gameType 설정.
	const result = resultToJson();
	
	console.log(result);

    updateResult(result.winner);

	// postMatchAPI(result);
});

document.getElementById('continueBtn').addEventListener('click', function() {
    window.location.href = 'https://127.0.0.1/index.html';
});

function updateResult(winner)
{
    const avatarUrl = localStorage.getItem('profile');
    const nickname = localStorage.getItem('nickname');

    const resultMessage = document.getElementById('resultMessage');
	if (winner == nickname)
	{
		resultMessage.textContent = 'You Win!';
        resultMessage.classList.add('win');
	}
	else 
	{
		resultMessage.textContent = 'You Lose!';
        resultMessage.classList.add('lose');
	}

    const userAvatar = document.getElementById('userAvatar');
    const userNickname = document.getElementById('userNickname');
    userAvatar.src = avatarUrl;
    userNickname.textContent = nickname;
}

function resultToJson()
{
	const urlParams = new URLSearchParams(window.location.search);
	const winner = urlParams.get('winner');
	const loser = urlParams.get('loser');
	const winnerScore = urlParams.get('winnerScore');
	const loserScore = urlParams.get('loserScore');
	const gameType = urlParams.get('gameType');
	const gameDate = new Date().toISOString();

	// {
	// 	"winner": "winnerUsername",
	// 	"loser": "loserUsername",
	// 	"winner_score": 100,
	// 	"loser_score": 80,
	// 	"game_type": "1VS1 or Tournament",
	// 	"game_date": "2024-09-01T12:00:00Z"
	// }

	return {
        winner: winner,
        loser: loser,
        winner_score: parseInt(winnerScore),
        loser_score: parseInt(loserScore),
        game_type: gameType,
        game_date: gameDate
    };
}

function postMatchAPI(result)
{
	if (result.gameType == 'single')
		return ;
	fetch('https://127.0.0.1/api/game/result/add/', {
		method: 'POST',
		headers: {
			'Authorization': `Bearer ${access_token}`,
			'Content-Type': 'application/json'
		},
		body: result
	})
	.then(response => {
		return response.json();
	})
	.then(data => {
		console.log('Match updated successfully:', data);
	})
	.catch(error => {
        console.error('Error updating match:', error);
    });
}