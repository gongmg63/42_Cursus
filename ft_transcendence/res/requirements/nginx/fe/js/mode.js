import { checkAndRefreshToken } from "./jwtRefresh.js";
import { friend_websocket } from "./friendWebsocket.js";

document.addEventListener('DOMContentLoaded', function() {
    const singleBtn = document.getElementById('single');
    const pvpBtn = document.getElementById('pvp');
    const tournamentBtn = document.getElementById('tournament');

    checkAndRefreshToken().then(() => {
        friend_websocket()
            .then((websocket) => {
                console.log("웹소켓이 연결되었습니다.");
            })
            .catch((error) => {
                console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
            });
    })

    singleBtn.addEventListener('click', function() {
        console.log('Single mode selected');
		// player 1, 2 이름, game type이 포함된 url로 redirect
		let gameType = "single";
		window.location.href = `/pong.html?gameType=${gameType}`;
    });

    pvpBtn.addEventListener('click', function() {
        console.log('1 vs 1 mode selected');
		// 매치 메이킹 페이지
		window.location.href = '/matchmaking.html';
    });

    tournamentBtn.addEventListener('click', function() {
        console.log('Tournament mode selected');
		// 토너먼트 페이지
		window.location.href = '/matchmaking.html';
    });
});
