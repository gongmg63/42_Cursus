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
	{
		console.log("modal is null");
		return ;
	}
	if (event.target && event.target.matches('#single')) {
		console.log('Single mode selected');
		gameType = "single";
		// window.history.pushState(null, null, `#/pong?gameType=${gameType}`);
		// navigateTo('/pong');
		render(`#/pong?gameType=${gameType}`);
	}

	if (event.target && event.target.matches('#pvp')) {
		// console.log('1 vs 1 mode selected');
		gameType = "1vs1";
		// window.history.pushState(null, null, `#/matchmaking?gameType=${gameType}`);
		// navigateTo('/matchmaking');
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
			// window.history.pushState(null, null, `#/matchmaking?gameType=${gameType}`);
			// navigateTo('/matchmaking');
			render(`#/matchmaking?gameType=${gameType}`);
		} else {
			alert('Please enter a nickname.');
		}
	}
}

// document.addEventListener('DOMContentLoaded', function() {
//     const singleBtn = document.getElementById('single');
//     const pvpBtn = document.getElementById('pvp');
//     const tournamentBtn = document.getElementById('tournament');

//     const modal = document.getElementById('tournament-modal');
//     const closeModal = document.querySelector('.close');
//     const startTournamentBtn = document.getElementById('start-tournament');
// 	let gameType;

//     singleBtn.addEventListener('click', function() {
//         console.log('Single mode selected');
// 		// player 1, 2 이름, game type이 포함된 url로 redirect
// 		gameType = "single";
// 		window.location.href = `/pong.html?gameType=${gameType}`;
//     });

//     pvpBtn.addEventListener('click', function() {
//         console.log('1 vs 1 mode selected');
// 		// 매치 메이킹 페이지
// 		gameType = "1vs1_match_request";
// 		window.location.href = `/matchmaking.html?gameType=${gameType}`;
//     });

//     tournamentBtn.addEventListener('click', function() {
//         console.log('Tournament mode selected');
// 		modal.style.display = "block";
//     });

//     closeModal.addEventListener('click', function() {
//         modal.style.display = "none";
//     });

//     window.addEventListener('click', function(event) {
//         if (event.target == modal) {
//             modal.style.display = "none";
//         }
//     });

//     startTournamentBtn.addEventListener('click', function() {
//         const nickname = document.getElementById('nickname').value.trim();
//         if (nickname) {
// 			gameType = "tournament_match_request";
//             window.location.href = `/matchmaking.html?gameType=${Tournament}&nickname=${nickname}`;
//         } else {
//             alert('Please enter a nickname.');
//         }
//     });
// });
