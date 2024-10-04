// import { checkAndRefreshToken } from "./jwtRefresh.js";
import { render } from "./transcendence.js";

let inputs;

window.initAuth = function()
{
	inputs = document.querySelectorAll('.auth-input');

	inputs.forEach((input) => {
		input.value = '';
		input.removeEventListener('input', handleInput);
		input.removeEventListener('keydown', handleBackspace);
		input.addEventListener('input', handleInput);
		input.addEventListener('keydown', handleBackspace);
	});
}

document.body.addEventListener('click', function(event) {
    if (event.target && event.target.matches('#verifyBtn')) {
        postAuthCodeAPI();
    }
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
	// const access_token = localStorage.getItem("n");
	const hash = window.location.hash;
    const queryParams = new URLSearchParams(hash.split('?')[1]);
	const nickname = queryParams.get('nickname');
	const data = { nickname: nickname, code: code };

	fetch('/api/user/verify/', {
		method: 'POST',
		headers: {
			'nickname': nickname,
			'Content-Type': 'application/json',
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
		console.log(data.accessToken);
		localStorage.setItem('access_token', data.access_token);
		localStorage.setItem('refresh_token', data.refresh_token);
		console.log('Token stored successfully');
		render('#/index');
	})
	.catch(error => {
		console.error('Error fetching user data: ', error);
		handleError(error);
	});
}