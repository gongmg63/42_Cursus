document.querySelector('.login-btn').addEventListener('click', function() {
    
	fetchOAuth();

	function fetchOAuth() {
		fetch('https://127.0.0.1/api/user/oauth', {
			method: 'GET'
		})
		.then(response => {
			if (!response.ok) {
				throw new Error('Network response was not ok');
			}
			return response.json();
		})
		.then(data => {
            window.location.href = data.redirect_url;
   		})
    	.catch(error => console.error('Error fetching user data: ', error));
	}
	// function fetchCallback() {
	// 	fetch('https://127.0.0.1/api/user/oauth/callback', {
	// 		// method: 'GET'
	// 	})
	// 	.then(response => {
	// 		if (!response.ok) {
	// 			throw new Error('Network response was not ok');
	// 		}
	// 		return response.json();
	// 	})
	// 	.then(data => {
	// 		window.location.href = data.redirect_url;
	// 	})
	// 	.catch(error => console.error('Error fetching user data: ', error));
	// }
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

