// import { handleError } from "./utils.js";
import { friend_websocket } from "./friendWebsocket.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

sessionStorage.removeItem('pong_pageLoaded');

checkAndRefreshToken().then(() => {
	friend_websocket()
		.then((websocket) => {
			console.log("웹소켓이 연결되었습니다.");
		})
		.catch((error) => {
			console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
		});
})

document.addEventListener('DOMContentLoaded', function() {
	// single, 1 vs 1, tournament에 따라 결과 다르게 - gameType 설정.
	const result = resultToJson();
	
	console.log(result);

    updateResult(result.winner);

	postMatchAPI(result);
});

document.getElementById('continueBtn').addEventListener('click', function(event) {
	event.preventDefault();
    window.location.href = '/index.html';
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
	const now = new Date();
	const gameDate = new Date(now.getTime() + (9 * 60 * 60 * 1000)).toISOString();

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
	if (result.game_type == 'single' || result.game_type == 'tournament1' || result.game_type == 'tournament2' || result.gameType == 'final')
		return ;
	const access_token = localStorage.getItem("access_token");
	fetch('/api/game/result/add/', {
		method: 'POST',
		headers: {
			'Authorization': `Bearer ${access_token}`,
			'Content-Type': 'application/json'
		},
		body: JSON.stringify(result)
	})
	.then(response => {
		if (response.status == 404)
			throw new Error('User data not found (404)');
		else if (response.status == 500)
			throw new Error('Server error (500)')
		else if (!response.ok)
			throw new Error(`Unexpected error: ${response.status}`);
		return response.json();
	})
	.then(data => {
		console.log('Match updated successfully:', data);
	})
	.catch(error => {
        console.error('Error updating match:', error);
		// handleError(error);
    });
}