import { checkAndRefreshToken } from "./jwtRefresh.js";
import { match_websocket } from "./matchWebsocket.js";

// hash 로 수정.
// const urlParams = new URLSearchParams(window.location.search);
// const type = urlParams.get("gameType");
// const nick = urlParams.get("nickname");

// const nick = queryParams.get('nickname');

window.loadMessage = function()
{
	const loadingMessage = document.getElementById('loadingMessage');
	let loadingDots = 0;
	
	// console.log("load message");
	if (loadingMessage)
	{
		setInterval(() => {
			loadingDots = (loadingDots + 1) % 4;
			loadingMessage.textContent = 'Loading' + '.'.repeat(loadingDots);
		}, 500);
	}

	const hash = window.location.hash;
	const queryParams = new URLSearchParams(hash.split('?')[1]);  // ?gameType= 이후의 파라미터만 추출
	const type = queryParams.get('gameType');

	checkAndRefreshToken().then(() => {
		match_websocket('/matchmaking', type);
	})
	.catch((error) => {
		console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
	});
}
