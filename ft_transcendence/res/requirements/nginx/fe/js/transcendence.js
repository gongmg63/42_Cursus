import { checkAndRefreshToken } from "./jwtRefresh.js";
import { friend_websocket } from "./friendWebsocket.js";
import { match_websocket } from "./matchWebsocket.js";
import { game_play_websocket } from "./multiPong.js";

const routes = {
	'/': { page: 'login.html', css: 'styles.css', js: [{ file: 'login.js', type: 'module' }] },
	'/index': { page: 'index.html', css: 'index.css', js: [{ file: 'index.js', type: 'module'}, { file: '2FA.js', type: 'module'}] },
	'/matchmaking': { page: 'matchmaking.html', css: 'matchmaking.css', js: [{file: 'matchMaking.js', type: 'module'}] },
	'/pong': { page: 'pong.html', css: 'pong.css', js: [{ file: 'pong.js', type: 'module'}] },
	'/multiPong': { page: 'multiPong.html', css: 'multiPong.css', js: [{ file: 'multiPong.js', type: 'module'}] },
	'/result': { page: 'result.html', css: 'result.css', js: [{ file: 'result.js', type: 'module'}] },
	'/tournament': { page: 'tournament.html', css: 'tournament.css', js: [{ file: 'tournament.js', type: 'module'}] },
	'/mode': { page: 'mode.html', css: 'mode.css', js: [{ file: 'mode.js', type: 'module'}] },
	'/authentication': { page: 'authentication.html', css: 'authentication.css', js: [{file: 'authentication.js', type: 'module'}] }
};
const forbiddenHashTo = {
	'/authentication':true,
	'/result':true,
};

const forbiddenHashFrom = {
};

const app = document.getElementById('app');
const dynamicCSS = document.getElementById('dynamicCSS');
let currentScripts = []; // 현재 로드된 자바스크립트 파일

document.querySelectorAll('nav a').forEach(link => {
    link.style.display = 'none';  // 모든 링크를 숨김
})

// 초기 로딩
console.log('초기 로딩');

let currentPath = window.location.hash.slice(1) || '/';
let previousPath = window.location.hash.slice(1) || '/';

if (currentPath.includes('?')) {
	currentPath = currentPath.split('?')[0];  // ? 앞의 경로 부분만 추출
}

// console.log(currentPath);
// if (currentPath !== '/pong')
// {
// 	cleanUpPong();
// }

if (currentPath === '/multiPong')
{
	render('#/mode');
}
// else if (currentPath === '/matchmaking')
// {

// }
else
{
	navigateTo(currentPath);
}

// 경우에 따라 나눠야 할듯 - 초기 로딩

// 페이지 이동 시 실행됨
export async function navigateTo(url) {
	const route = routes[url] || routes['/'];
	const res = await fetch(route.page);
	const content = await res.text();
	app.innerHTML = content;

	console.log("navigate To url: ", url);
	// CSS 파일을 동적으로 로드
	if (route.css) {
		dynamicCSS.setAttribute('href', `/css/${route.css}`);
		// console.log("css: ", route.css);
	} else {
		dynamicCSS.removeAttribute('href'); // CSS가 없으면 제거
	}

	 // 이전에 로드된 스크립트 파일들을 제거
	currentScripts.forEach(script => script.remove());
	currentScripts = [];

	if (route.js.length > 0) {
		// 새로운 JS 파일을 동적으로 로드하고 실행
		route.js.forEach(js => {
			const script = document.createElement('script');
			script.src = `/js/${js.file}`;
			script.type = js.type || 'text/javascript';
			script.defer = true;
			script.onload = () => {
				if (js.file === 'login.js')
					initializeLogin();
				else if (js.file === 'index.js')
					getUser();
				else if (js.file === 'mode.js')
					selectMode();
				else if (js.file === 'matchMaking.js')
					loadMessage();
				else if (js.file === 'result.js')
					loadResult();
				else if (js.file === 'authentication.js')
					authToken();
				else if (js.file === 'pong.js')
					startPong();
				else if (js.file === 'multiPong.js')
					startMultiPong();
			};
			document.body.appendChild(script);
			currentScripts.push(script);
		});
		
		if (url === '/result') {
			cleanUpPong();
		}
		else if (url !== '/' && url !== '/authentication')
		{
			checkAndRefreshToken().then(() => {
				friend_websocket()
					.then((websocket) => {
					})
					.catch((error) => {
						console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
					});
			});
		}
		else if (url !== '/multiPong')
		{
			if (typeof cleanUpMultiPong === 'function')
				cleanUpMultiPong();
		}
	}
}

// 뒤로가기, 앞으로 가기 시 실행됨
window.addEventListener('hashchange', () => {
	let currentPath = window.location.hash.slice(1) || '/';
	if (currentPath.includes('?')) {
		currentPath = currentPath.split('?')[0];  // ? 앞의 경로 부분만 추출
    }

    if (currentPath !== '/pong')
	{ 
		// 게임 관련 리소스 정리
		console.log('hashchange pong');
		if (typeof cleanupPong === 'function')
			cleanupPong(); 
    }
	if (currentPath === '/pong' && typeof startPong === 'function')
	{
		console.log("hashchange start pong");
		startPong();
	}

	if (currentPath !== '/multiPong')
	{
		console.log('hashchange multipong')
		if (typeof cleanUpMultiPong === 'function')
			cleanUpMultiPong();
	}
	game_play_websocket(currentPath, null);
	match_websocket(currentPath, null);
	console.log("hashchange: ", currentPath);
	navigateTo(currentPath);
});


export function render(hash)
{
	let path = hash.slice(1);
	let pathwithoutparam = path.split('?')[0];
	previousPath = path;
	window.history.pushState({ page: pathwithoutparam }, null, hash);
	match_websocket(path, null);
	game_play_websocket(path, null);
	console.log("render:", pathwithoutparam);
	navigateTo(pathwithoutparam);
}

// 뒤로가기, 앞으로가기 버튼을 눌렀을 시 호출되는 함수
// pushState 함수의 첫번째 인자로 페이지의 해시 정보를 넣어주면 event.state 에서 조회가능.
// hashchange 함수는 pushState 의 세번쨰 인자인 url의 변경을 감지하고 실행된다.
window.onpopstate = function(event) {

	let pathFrom = previousPath.split('?')[0];

	console.log("[onpopstate]: page from", pathFrom);
	console.log("[onpopstate]: page to:", event.state);

	if (event.state && event.state.page in forbiddenHashTo)
	{
		alert("이 페이지로 이동 할 수 없습니다.");
		render('#/index');
	}
	if (pathFrom in forbiddenHashFrom)
	{
		alert("이 페이지에서는 이동 할 수 없습니다.");
		render('#/index');
	}
};