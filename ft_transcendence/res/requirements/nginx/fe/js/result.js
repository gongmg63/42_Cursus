import { checkAndRefreshToken } from "./jwtRefresh.js";
import { navigateTo, render } from "./transcendence.js";

sessionStorage.removeItem('pong_pageLoaded');

checkAndRefreshToken().then(() => {
})

window.loadResult = function ()
{

	const result = resultToJson();
	
	console.log(result);
	// cleanUpPong();

    updateResult(result.winner);

	postMatchAPI(result);
}

document.body.addEventListener('click', function(event) {
    if (event.target && event.target.matches('#continueBtn')) {
        event.preventDefault();
        // window.history.pushState(null, null, '#/index');
        // navigateTo('/index');
		render('#/index');
    }
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
	const hash = window.location.hash;
    const queryParams = new URLSearchParams(hash.split('?')[1]);

	const winner = queryParams.get('winner');
	const loser = queryParams.get('loser');
	const winnerScore = queryParams.get('winnerScore');
	const loserScore = queryParams.get('loserScore');
	const gameType = queryParams.get('gameType');
	const now = new Date();
	const gameDate = new Date(now.getTime() + (9 * 60 * 60 * 1000)).toISOString();

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
    });
}