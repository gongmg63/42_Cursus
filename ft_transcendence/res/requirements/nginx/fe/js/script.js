document.querySelector('.login-btn').addEventListener('click', function() {
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
			console.log(data);
			updateToken(data);
			window.location.href = "https://127.0.0.1/index.html";
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