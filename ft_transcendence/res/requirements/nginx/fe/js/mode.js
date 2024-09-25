import { friend_websocket } from "./friendWebsocket.js";
import { refreshToken } from "./jwtRefresh.js";

document.addEventListener('DOMContentLoaded', function() {
    const singleBtn = document.getElementById('single');
    const pvpBtn = document.getElementById('pvp');
    const tournamentBtn = document.getElementById('tournament');

    const modal = document.getElementById('tournament-modal');
    const closeModal = document.querySelector('.close');
    const startTournamentBtn = document.getElementById('start-tournament');
	let gameType;
	

    // checkAndRefreshToken().then(() => {
    //     friend_websocket()
    //         .then((websocket) => {
    //             console.log("웹소켓이 연결되었습니다.");
    //         })
    //         .catch((error) => {
    //             console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
    //         });
    // })

    singleBtn.addEventListener('click', function() {
        console.log('Single mode selected');
		// player 1, 2 이름, game type이 포함된 url로 redirect
		gameType = "single";
		window.location.href = `/pong.html?gameType=${gameType}`;
    });

    pvpBtn.addEventListener('click', function() {
        console.log('1 vs 1 mode selected');
		// 매치 메이킹 페이지
		gameType = "1vs1_match_request";
		window.location.href = `/matchmaking.html?gameType=${gameType}`;
    });

    tournamentBtn.addEventListener('click', function() {
        console.log('Tournament mode selected');
		modal.style.display = "block";
    });

    closeModal.addEventListener('click', function() {
        modal.style.display = "none";
    });

    window.addEventListener('click', function(event) {
        if (event.target == modal) {
            modal.style.display = "none";
        }
    });

    startTournamentBtn.addEventListener('click', function() {
        const nickname = document.getElementById('nickname').value.trim();
        if (nickname) {
			gameType = "tournament_match_request";
            window.location.href = `/matchmaking.html?gameType=${Tournament}&nickname=${nickname}`;
        } else {
            alert('Please enter a nickname.');
        }
    });
});
