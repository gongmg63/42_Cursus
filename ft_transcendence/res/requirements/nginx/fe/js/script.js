document.querySelector('.login-btn').addEventListener('click', function() {
    
	// 42 Login 버튼 클릭 시 해당 URL로 리다이렉트
	// 42 Login 버튼 클릭 시 해당 URL로 리다이렉트
	fetchOAuth();

	function fetchOAuth() {
		fetch('https://127.0.0.1/api/user/oauth', {
			method: 'GET'
		})
		.then(response => {
			if (!response.ok) {
				throw new Error('Network response was not ok');
			}
			return response.json();  // 응답을 JSON으로 변환
		})
		.then(data => {
        if (data.redirect_url) {
            window.location.href = data.redirect_url;
        }
		else {
			console.log(data);
            console.error('Redirect URL not found');
        }
   	})
    	.catch(error => console.error('Error fetching user data: ', error));
	}

	function fetchCallback() {
		fetch('https://127.0.0.1/api/user/oauth/callback', {
			// method: 'GET'
		})
		.then(response => {
			if (!response.ok) {
				throw new Error('Network response was not ok');
			}
			return response.json();  // 응답을 JSON으로 변환
		})
		.then(data => {
			window.location.href = data.redirect_url;
		})
		.catch(error => console.error('Error fetching user data: ', error));
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
		console.log('yeah');
	}
})

// function updateToken(data) {
// 	if (data) {
// 		const accessToken = data.access_token;
// 		const refreshToken = data.refresh_token;
		
// 		localStorage.setItem('access_token', accessToken);
// 		localStorage.setItem('refresh_token', refreshToken);
// 		console.log('Token stored successfully');
// 	}
// 	else {
// 		console.error('Data is undefined');
// 	}
// }
