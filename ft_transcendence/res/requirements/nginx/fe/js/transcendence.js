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

const app = document.getElementById('app');
const dynamicCSS = document.getElementById('dynamicCSS');
let currentScripts = []; // 현재 로드된 자바스크립트 파일

document.querySelectorAll('nav a').forEach(link => {
    link.style.display = 'none';  // 모든 링크를 숨김
})

export async function navigateTo(url) {
	const route = routes[url] || routes['/'];
	const res = await fetch(route.page);
	const content = await res.text();
	app.innerHTML = content;

	// CSS 파일을 동적으로 로드
	if (route.css) {
		dynamicCSS.setAttribute('href', `/css/${route.css}`);
		console.log("css: ", route.css);
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
			console.log("js: ", js.file);
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
			};
			document.body.appendChild(script);
			currentScripts.push(script);
		});
		
		if (url !== '/pong') {
			if (typeof cleanupPong === 'function')
				cleanupPong();  // 게임 관련 리소스 정리
		}
	}
}

window.addEventListener('hashchange', () => {
	let currentPath = window.location.hash.slice(1) || '/';

	if (currentPath.includes('?')) {
		currentPath = currentPath.split('?')[0];  // ? 앞의 경로 부분만 추출
    }

    if (currentPath !== '/pong')
	{ 
		// 게임 관련 리소스 정리
		if (typeof cleanupPong === 'function')
			cleanupPong(); 
    }
	if (currentPath === '/pong' && typeof startPong === 'function')
	{
		console.log("hashchange start pong");
		startPong();
	}
	console.log("hashchange: ", currentPath);
	navigateTo(currentPath);
});

// 초기 로딩
console.log('초기 로딩');

let currentPath = window.location.hash.slice(1) || '/';
if (currentPath.includes('?')) {
	currentPath = currentPath.split('?')[0];  // ? 앞의 경로 부분만 추출
}

// 경우에 따라 나눠야 할듯 - 초기 로딩
navigateTo(currentPath);


