import { editLocalStorage, handleError, populateFriendSelect, updateFriendsList } from "./utils.js";
import { friends, setFriends } from "./index.js";
import { setTFA } from "./2FA.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

const editUserBtn = document.querySelector('.edit-user-btn');
const editUserModal = document.getElementById('editUserModal');
const closeButn = editUserModal?.querySelector('.close');

editUserBtn?.addEventListener('click', function() {
	editUserModal.style.display = 'block';
});

closeButn?.addEventListener('click', function() {
	editUserModal.style.display = 'none';
});

window.addEventListener('click', function(event) {
	if (event.target === editUserModal) {
		editUserModal.style.display = 'none';
	}
});

// export function friend_websocket()
// {
// 	return new Promise((resolve, reject) => {
// 		const access_token = localStorage.getItem("access_token");
// 		const websocket = new WebSocket('wss://cx1r5s2.42seoul.kr/ws/friend/status/?token=' + access_token);
        
		
//         // 연결이 성공했을 때 호출
//         websocket.onopen = () => {
//             console.log("웹소켓 연결 완료");
//             resolve(websocket);  // 웹소켓 객체를 반환하여 다른 곳에서 사용 가능
//         };

//         // 메시지를 수신할 때 호출
//         websocket.onmessage = (event) => {
//             const data = JSON.parse(event.data);
// 			if (data.type == 'friend_status_update')
//             {
// 				console.log("서버로부터 받은 메시지:", data);
// 				// populateFriendSelect();
// 				updateFriendsList(data.friends);
// 				// 여기에서 메시지에 따라 처리하는 로직을 추가
// 			}
// 			else if (data.type == 'friend_update')
// 				setFriends(data.friends);
//         };

//         // 오류가 발생했을 때 호출
//         websocket.onerror = (error) => {
//             console.error("웹소켓 연결 오류:", error);
//             reject(error);  // 연결 실패 시 Promise를 거부
//         };

//         // 연결이 종료되었을 때 호출
//         websocket.onclose = () => {
//             console.log("웹소켓 연결 종료");
//         };
//     });
// }

export function fetchUserData()
{
	checkAndRefreshToken().then(()=> {
		const access_token = localStorage.getItem("access_token");
		fetch('/api/user/me', {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${access_token}`,
				'Content-Type': 'application/json'
			},
		})
		.then(response => {
			if (response.status == 404)
				throw new Error('User data not found (404)');
			else if (response.status == 500)
				throw new Error('Server error (500)')
			else if (!response.ok)
			{
				return response.json().then(errData => {
					throw new Error(`Unexpected error (${response.status}): ${errData.detail || 'Unknown error'}`);
				});
			}
			return response.json();
		})
		.then(data => {
			// User 정보 업데이트
			updateUserInfo(data);
		
			// 친구 목록 업데이트
			setFriends(data.friends);
			updateFriendsList(data.friends);
		
			// 최근 경기 기록 업데이트 - user 말고 다른 테이블에서 조회
			// updateRecentMatches(data.recentMatches);
		})
		.catch(error => {
			console.error('Error fetching user data: ', error);
			handleError(error);
		});
	});
}

export function fetchRecentMatch()
{
	checkAndRefreshToken().then(()=> {
		const access_token = localStorage.getItem("access_token");
		fetch('/api/game/result/me', {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${access_token}`,
				'Content-Type': 'application/json'
			},
		})
		.then(response => {
			if (response.status == 404)
				throw new Error('User data not found (404)');
			else if (response.status == 500)
				throw new Error('Server error (500)')
			else if (!response.ok)
			{
				return response.json().then(errData => {
					throw new Error(`Unexpected error (${response.status}): ${errData.detail || 'Unknown error'}`);
				});
			}
			return response.json();
		})
		.then(data => {
			if (Array.isArray(data))
			{
				if (data.length == 0)
					console.log("No Recent Matches");
				else
					updateRecentMatches(data);
			}
		})
		.catch(error => {
			console.error('Error fetching user data: ', error);
			handleError(error);
		});
	});
}

function updateUserInfo(user)
{
	const userDetails = document.querySelector('.user-details h1');
	const userStats = document.querySelector('.user-details p');
	const userAvatar = document.querySelector('.avatar-container img');

	if (userDetails)
		userDetails.textContent = user.nickname || 'Unknown User';
	if (userStats)
		userStats.textContent = `Total Stats: ${user.wins || 0}W ${user.losses || 0}L`;

	// if (user.profile && user.profile.trim() !== "")
	// 	userAvatar.src = user.profile.replace('/images', '');
	// else
	// 	userAvatar.src = '../images/Retriever.jpeg';
	if (userAvatar)
		userAvatar.src = user.profile;
	setTFA(user.is_tfa_active);
	if (userAvatar)
		editLocalStorage(user.nickname, userAvatar.src);
}

function updateRecentMatches(recentMatches)
{
	const matchHistoryContainer = document.querySelector('.match-history-container');
	// 최근 전적 중 5개만 가져오게

	// match.game_date - 연월일 가져오기
	if(matchHistoryContainer)
	{
		matchHistoryContainer.innerHTML = '';
		recentMatches.slice(-5).forEach(match => {
			const matchDiv = document.createElement('div');
			const myNickname = localStorage.getItem("nickname");
			const myProfile = localStorage.getItem("profile");
			const opNickname = match.winner.nickname == myNickname ? match.loser.nickname : match.winner.nickname;
			const opProfile = match.winner.nickname == myNickname ? match.loser.profile : match.winner.profile;
			const myScore = match.winner.nickname == myNickname ? match.winner_score : match.loser_score;
			const opScore = match.winner.nickname == myNickname ? match.loser_score : match.winner_score;
			
			// 날짜 포맷팅 (연-월-일 형식)
			const gameDate = new Date(match.game_date);
			const formattedDate = `${gameDate.getFullYear()}-${String(gameDate.getMonth() + 1).padStart(2, '0')}-${String(gameDate.getDate()).padStart(2, '0')}`;

			matchDiv.classList.add('match');
	
			const userAvatarContainer = document.createElement('div');
			userAvatarContainer.classList.add('match-avatar-container');
			const userAvatarImg = document.createElement('img');
			userAvatarImg.src = `${myProfile}`;
			userAvatarImg.alt = 'User Avatar';
			userAvatarImg.classList.add('match-avatar');
			const userNickname = document.createElement('p');
			userNickname.classList.add('match-nickname');
	
			userNickname.textContent = myNickname;
	
			userAvatarContainer.appendChild(userAvatarImg);
			userAvatarContainer.appendChild(userNickname);
	
			const matchInfo = document.createElement('div');
			matchInfo.classList.add('match-info');
			
			// 날짜 출력
			const matchDate = document.createElement('p');
			matchDate.classList.add('match-date');
			matchDate.textContent = formattedDate;

			const matchScore = document.createElement('p');
			matchScore.classList.add('match-score');
			matchScore.textContent = `${myScore} - ${opScore}`;
	
			const matchResult = document.createElement('p');
			matchResult.classList.add('match-result', match.result);
	
			if (match.winner.nickname == localStorage.getItem("nickname"))
				matchResult.textContent = "WIN";
			else
				matchResult.textContent = "LOSE";

			matchInfo.appendChild(matchDate); // 날짜 추가
			matchInfo.appendChild(matchScore);
			matchInfo.appendChild(matchResult);
	
			const opponentAvatarContainer = document.createElement('div');
			opponentAvatarContainer.classList.add('match-avatar-container');
			const opponentAvatarImg = document.createElement('img');
			opponentAvatarImg.src = `${opProfile}`;
			opponentAvatarImg.alt = 'Opponent Avatar';
			opponentAvatarImg.classList.add('match-avatar');
			const opponentNickname = document.createElement('p');
			opponentNickname.classList.add('match-nickname');
	
			opponentNickname.textContent = opNickname;
	
			opponentAvatarContainer.appendChild(opponentAvatarImg);
			opponentAvatarContainer.appendChild(opponentNickname);
	
			matchDiv.appendChild(userAvatarContainer);
			matchDiv.appendChild(matchInfo);
			matchDiv.appendChild(opponentAvatarContainer);
	
			matchHistoryContainer.appendChild(matchDiv);
		})
	}
}

export function editUser()
{
	const nickname = document.getElementById('nicknameInput').value;
    const avatarFile = document.getElementById('avatarInput').files[0];
	const access_token = localStorage.getItem("access_token");

    const formData = new FormData();
    formData.append('nickname', nickname);
    if (avatarFile) {
        formData.append('profile', avatarFile);
    }
	checkAndRefreshToken().then(() => {
		patchUserAPI(formData, nickname, avatarFile, access_token);
	});
}

function patchUserAPI(formData, nickname, avatarFile, access_token)
{
	fetch('/api/user/me', {
        method: 'PATCH',
		headers: {
			'Authorization': `Bearer ${access_token}`,
		},
		body: formData
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
        console.log('User profile updated:', data);
        document.querySelector('.user-details h1').textContent = nickname;
        if (avatarFile) {
            const reader = new FileReader();
            reader.onload = function(e) {
                document.querySelector('.avatar-container img').src = e.target.result;
            };
            reader.readAsDataURL(avatarFile);
        }
        editUserModal.style.display = 'none';
		editLocalStorage(nickname, avatarFile);
    })
    .catch(error => {
        console.error('Error updating profile:', error);
		handleError(error);
    });
}
