import { render } from "./transcendence.js";

window.selectMode = function() {

	document.body.removeEventListener('click', handleClickEvent);
	document.body.addEventListener('click', handleClickEvent);
}

function handleClickEvent(event)
{
    const modal = document.getElementById('tournament-modal');
	let gameType;

	if (modal === null)
		return ;
	if (event.target && event.target.matches('#single')) {
		console.log('Single mode selected');
		gameType = "single";
		render(`#/pong?gameType=${gameType}`);
	}

	if (event.target && event.target.matches('#pvp')) {
		// console.log('1 vs 1 mode selected');
		gameType = "1vs1";
		render(`#/matchmaking?gameType=${gameType}`);
	}

	if (event.target && event.target.matches('#tournament')) {
		console.log('Tournament mode selected');
		modal.style.display = "block";
	}

	if (event.target && event.target.matches('.close')) {
		modal.style.display = "none";
	}

	if (event.target === modal) {
		modal.style.display = "none";
	}

	if (event.target && event.target.matches('#start-tournament')) {
		const nickname = document.getElementById('nickname').value.trim();
		if (nickname) {
			gameType = "tournament";
			patchTempUserAPI(nickname, gameType);
		} else {
			alert('Please enter a nickname.');
		}
	}
}

function patchTempUserAPI(nickname, gameType)
{
	const formData = new FormData();
	const access_token = localStorage.getItem("access_token");
	formData.append('t_nickname', nickname);

	fetch('/api/user/me', {
        method: 'PATCH',
		headers: {
			'Authorization': `Bearer ${access_token}`,
		},
		body: formData
    })
    .then(response => {
        if (response.status == 404)
			throw new Error('User data not found (404)');
		else if (response.status == 500)
			throw new Error('Server error (500)')
		else if (!response.ok)
		{
			return response.json().then(errData => {
				throw new Error(`(${response.status}): ${errData.detail || 'Unknown error'}`);
			});
		}
		return response.json();
    })
    .then(data => {
		console.log("tournament patch : ",data);
		render(`#/matchmaking?gameType=${gameType}`);
    })
    .catch(error => {
		alert(error);
        console.error('Error updating profile:', error);
    });
}