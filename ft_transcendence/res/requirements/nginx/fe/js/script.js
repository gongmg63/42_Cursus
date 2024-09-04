document.querySelector('.login-btn').addEventListener('click', function() {
    
	// 42 Login 버튼 클릭 시 해당 URL로 리다이렉트
	fetchOAuth();

	function fetchOAuth() {
		fetch('https://localhost/api/user/oauth', {
			method: 'GET'
		})
		.then(response => response.json())
		.then(data => {
			console.log('Fetched user successfully');
			// updateToken(data);
			// window.location.href = data.redirect_url;
			console.log(data);
		})
		.catch(error => console.error('Error fetching user data: ', error));
	}

	function updateToken(data) {
		if (data) {
			const accessToken = data.access_token;
			const refreshToken = data.refresh_token;
			
			localStorage.setItem('access_token', accessToken);
			localStorage.setItem('refresh_token', refreshToken);
			console.log('Token stored successfully');
		}
		else {
			console.error('Data is undefined');
		}
	}
});