// import { checkAndRefreshToken } from "./jwtRefresh.js";

const inputs = document.querySelectorAll('.auth-input');

inputs.forEach((input) => {
    input.addEventListener('input', handleInput);
    input.addEventListener('keydown', handleBackspace);
});

// window.addEventListener('load', function() {
// 	const urlParams = new URLSearchParams(window.location.search);
// 	const accessToken = urlParams.get('access_token');
// 	const refreshToken = urlParams.get('refresh_token');
	
// 	if (accessToken && refreshToken)
// 	{
// 		localStorage.setItem('access_token', accessToken);
// 		localStorage.setItem('refresh_token', refreshToken);
// 		console.log('Token stored successfully');
// 	}
// 	else
// 	{
// 		console.log('fuck you');
// 	}
// })

document.getElementById('verifyBtn').addEventListener('click', () => {
	postAuthCodeAPI();
});

function handleInput(e) {
	const input = e.target;
	const nextInput = document.getElementById(input.dataset.next);

	if (input.value.length === 1 && nextInput)
		nextInput.focus();

	if (isAllFilled())
		document.getElementById('verifyBtn').disabled = false;
}

function handleBackspace(e) {
	const input = e.target;
	const prevInput = document.getElementById(input.dataset.prev);

	if (e.key === "Backspace" && !input.value && prevInput)
		prevInput.focus();
}

function isAllFilled() {
    return Array.from(inputs).every(input => input.value.length === 1);
}

function postAuthCodeAPI()
{
	const code = Array.from(inputs).map(input => input.value).join('');
	const urlParams = new URLSearchParams(window.location.search);
	const nickname = urlParams.get('nickname');
	const data = {
		nickname: nickname,
		code: code
	};
	fetch('/api/user/verify/', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json'
		},
		body: JSON.stringify(data)
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
		localStorage.setItem('access_token', data.access_token);
		localStorage.setItem('refresh_token', data.refresh_token);
		localStorage.setItem('nickname', data.refresh_token);
		localStorage.setItem('profile', data.refresh_token);
		window.location.href = "/index.html";
	})
	.catch(error => {
		console.error('Error fetching user data: ', error);
		handleError(error);
	});
	//#endregion
}