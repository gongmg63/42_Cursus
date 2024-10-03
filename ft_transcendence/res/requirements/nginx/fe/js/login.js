import { navigateTo } from "./transcendence.js";

document.body.addEventListener('click', function(event) {
    if (event.target && event.target.matches('.login-btn')) {
        event.preventDefault(); // 기본 동작 방지
        fetchOAuth();
    }
});

function fetchOAuth() {
    fetch('/api/user/oauth', {
        method: 'GET'
    })
    .then(response => {
        if (response.status == 404)
            throw new Error('User data not found (404)');
        else if (response.status == 500)
            throw new Error('Server error (500)');
        else if (!response.ok)
            throw new Error(`Unexpected error: ${response.status}`);
        return response.json();
    })
    .then(data => {
        window.location.href = data.redirect_url;
    })
    .catch(error => {
        console.error('Error during OAuth request:', error);
    });
}

window.initializeLogin = function() {
    const urlParams = new URLSearchParams(window.location.search);
    const accessToken = urlParams.get('access_token');
    const refreshToken = urlParams.get('refresh_token');

    if (accessToken && refreshToken) {
        localStorage.setItem('access_token', accessToken);
        localStorage.setItem('refresh_token', refreshToken);
        console.log('Token stored successfully');

		window.history.pushState({ page : '/index' }, null, window.location.pathname + '#/index');
		navigateTo('/index');
    } else {
        console.log('Tokens not found');
    }
};