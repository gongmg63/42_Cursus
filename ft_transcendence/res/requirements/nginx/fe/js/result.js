import { checkAndRefreshToken } from "./jwtRefresh.js";
import { navigateTo, render } from "./transcendence.js";

let gameType = null;

window.loadResult = function ()
{
	console.log('[loadResult]')
	const hash = window.location.hash;
	const queryParams = new URLSearchParams(hash.split('?')[1]);
	gameType = queryParams.get('gameType');
	
	console.log("result gameType : ", gameType);
	if (gameType === "single")
	{
		singleResult()
	}
	else
	{
		updateResult(gameType);
	}
	// console.log(result);
	// cleanUpPong();
	// postMatchAPI(result);
}

document.body.addEventListener('click', function(event) {
    if (event.target && event.target.matches('#continueBtn')) {
        event.preventDefault();
        // window.history.pushState(null, null, '#/index');
        // navigateTo('/index');
		// if (gameType == 'tournament1' || gameType == "tournament2")
		// 	render('#/matchmaking?gameType=final');
		// else
		render('#/index');
    }
});

function singleResult()
{
	const nickname = localStorage.getItem('nickname');
	const userNickname = document.getElementById('userNickname');
	userNickname.textContent = nickname;

	const avatarUrl = localStorage.getItem('profile');
	const userAvatar = document.getElementById('userAvatar');
	userAvatar.src = avatarUrl;

	const resultMessage = document.getElementById('resultMessage');
	resultMessage.textContent = 'You Win!';
	resultMessage.classList.add('win');
}

function updateResult(gameType)
{
	checkAndRefreshToken().then(()=> {
		const access_token = localStorage.getItem("access_token");
		fetch('/api/game/result/me/recent', {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${access_token}`,
				'Content-Type': 'application/json'
			},
		})
		.then(response => {
			if (response.status === 404)
				throw new Error('User data not found (404)');
			else if (response.status === 500)
				throw new Error('Server error (500)')
			else if (!response.ok)
			{
				return response.json().then(errData => {
					throw new Error(`Unexpected error (${response.status}): ${errData.detail || 'Unknown error'}`);
				});
			}
			return response.json();
		})
		.then(data => {
			const avatarUrl = localStorage.getItem('profile');
			const nickname = localStorage.getItem('nickname');
			
			const userNickname = document.getElementById('userNickname');
			userNickname.textContent = nickname;
			
			const userAvatar = document.getElementById('userAvatar');
			userAvatar.src = avatarUrl;
			
			const resultMessage = document.getElementById('resultMessage');
			const recentMatch = data;
			if (recentMatch.winner.nickname === nickname)
			{
				resultMessage.textContent = 'You Win!';
				resultMessage.classList.add('win');
				if (gameType === "tournament1" || gameType === "tournament2")
				{
					matchTimer = setTimeout(() => {
						render('#/matchmaking?gameType=final');
					}, 2000);
				}
			}
			else
			{
				resultMessage.textContent = 'You Lose!';
				resultMessage.classList.add('lose');
			}
			
			console.log(recentMatch.winner.nickname, recentMatch.winner_score, recentMatch.loser.nickname, recentMatch.loser_score, recentMatch.game_date);
		})
		.catch(error => {
			console.error('Error fetching user data: ', error);
		});
	});
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
	if (result.game_type === 'single' || result.game_type === 'tournament1' || result.game_type === 'tournament2' || result.gameType === 'final')
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
		if (response.status === 404)
			throw new Error('User data not found (404)');
		else if (response.status === 500)
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