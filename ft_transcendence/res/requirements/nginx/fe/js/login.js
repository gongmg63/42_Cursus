document.querySelector('.login-btn').addEventListener('click', function() {
    
	fetchOAuth();

	function fetchOAuth() {
		fetch('https://127.0.0.1/api/user/oauth', {
			method: 'GET'
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
            window.location.href = data.redirect_url;
   		})
		.catch(error => {
			console.error('Error removing friend:', error);
		})
	}
});

window.addEventListener('load', function() {
	const urlParams = new URLSearchParams(window.location.search);
	const accessToken = urlParams.get('access_token');
	const refreshToken = urlParams.get('refresh_token');
	
	if (accessToken && refreshToken)
	{
		localStorage.setItem('access_token', accessToken);
		localStorage.setItem('refresh_token', refreshToken);
		console.log('Token stored successfully');
		this.location.href = 'https://127.0.0.1/index.html';
	}
	else
	{
		console.log('fuck you');
	}
})

