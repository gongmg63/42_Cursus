import { editLocalStorage, handleError, populateFriendSelect, updateFriendsList } from "./utils.js";
import { friends, setFriends } from "./index.js";
import { setTFA } from "./2FA.js";

const editUserBtn = document.querySelector('.edit-user-btn');
const editUserModal = document.getElementById('editUserModal');
const closeButn = editUserModal.querySelector('.close');

editUserBtn.addEventListener('click', function() {
	editUserModal.style.display = 'block';
});

closeButn.addEventListener('click', function() {
	editUserModal.style.display = 'none';
});

window.addEventListener('click', function(event) {
	if (event.target === editUserModal) {
		editUserModal.style.display = 'none';
	}
});

export function fetchUserData()
{
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
				throw new Error(`Unexpected error: ${response.status}`);
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
}

function updateUserInfo(user)
{
	const userDetails = document.querySelector('.user-details h1');
	const userStats = document.querySelector('.user-details p');
	const userAvatar = document.querySelector('.avatar-container img');

	userDetails.textContent = user.nickname || 'Unknown User';
	userStats.textContent = `Total Stats: ${user.wins || 0}W ${user.losses || 0}L`;

	// if (user.profile && user.profile.trim() !== "")
	// 	userAvatar.src = user.profile.replace('/images', '');
	// else
	// 	userAvatar.src = '../images/Retriever.jpeg';
	userAvatar.src = user.profile;
	setTFA(user.is_tfa_active);
	editLocalStorage(user.nickname, userAvatar.src);
}

function updateRecentMatches(recentMatches)
{
	const matchHistoryContainer = document.querySelector('.match-history-container');
	matchHistoryContainer.innerHTML = '';

	recentMatches.forEach(match => {
		const matchDiv = document.createElement('div');
		matchDiv.classList.add('match');

		const userAvatarContainer = document.createElement('div');
		userAvatarContainer.classList.add('match-avatar-container');
		const userAvatarImg = document.createElement('img');
		userAvatarImg.src = `${match.userAvatar}`;
		userAvatarImg.alt = 'User Avatar';
		userAvatarImg.classList.add('match-avatar');
		const userNickname = document.createElement('p');
		userNickname.classList.add('match-nickname');
		userNickname.textContent = 'You';
		userAvatarContainer.appendChild(userAvatarImg);
		userAvatarContainer.appendChild(userNickname);

		const matchInfo = document.createElement('div');
		matchInfo.classList.add('match-info');
		const matchScore = document.createElement('p');
		matchScore.classList.add('match-score');
		matchScore.textContent = `${match.userScore} - ${match.opponentScore}`;
		const matchResult = document.createElement('p');
		matchResult.classList.add('match-result', match.result);
		matchResult.textContent = match.result.charAt(0).toUpperCase() + match.result.slice(1);
		matchInfo.appendChild(matchScore);
		matchInfo.appendChild(matchResult);

		const opponentAvatarContainer = document.createElement('div');
		opponentAvatarContainer.classList.add('match-avatar-container');
		const opponentAvatarImg = document.createElement('img');
		opponentAvatarImg.src = `../images/${match.opponentAvatar}`;
		opponentAvatarImg.alt = 'Opponent Avatar';
		opponentAvatarImg.classList.add('match-avatar');
		const opponentNickname = document.createElement('p');
		opponentNickname.classList.add('match-nickname');
		opponentNickname.textContent = 'Opponent';
		opponentAvatarContainer.appendChild(opponentAvatarImg);
		opponentAvatarContainer.appendChild(opponentNickname);

		matchDiv.appendChild(userAvatarContainer);
		matchDiv.appendChild(matchInfo);
		matchDiv.appendChild(opponentAvatarContainer);

		matchHistoryContainer.appendChild(matchDiv);
	})
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
	patchUserAPI(formData, nickname, avatarFile, access_token);
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

const access_token = localStorage.getItem("access_token");
const socket = new WebSocket('wss://localhost/ws/friend/status/?token=' + access_token);

const friendStatusSocket = socket;

friendStatusSocket.onopen = function() {
    console.log('WebSocket connection established.');
};

friendStatusSocket.onerror = function(error) {
    console.log('WebSocket error: ' + error.message);
};

friendStatusSocket.onclose = function(event) {
    if (event.wasClean) {
        console.log('WebSocket connection closed cleanly, code=' + event.code + ', reason=' + event.reason);
    } else {
        console.log('WebSocket connection closed with error');
    }
};

friendStatusSocket.onmessage = function(e) {
    const data = JSON.parse(e.data);
    if (data.type === 'friend_status') {
        updateFriendStatusUI(data.friends);
    } else if (data.type === 'friend_status_update') {
        updateSingleFriendStatus(data.friend_id, data.status);
    }
};

function updateFriendStatusUI(friends) {
    for (const [friendId, status] of Object.entries(friends)) {
        updateSingleFriendStatus(friendId, status);
		console.log(status.className);
    }
}

function updateSingleFriendStatus(friendId, status) {
    const statusElement = document.getElementById(`friend-status-${friendId}`);
    if (statusElement) {
        statusElement.textContent = status ? '온라인' : '오프라인';
        statusElement.className = status ? 'online' : 'offline';
    }
}