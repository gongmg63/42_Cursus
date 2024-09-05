// 친구 목록 - 서버 데이터 읽어오기
let friends = [];

//#region 서버로부터 데이터 가져오기
document.addEventListener('DOMContentLoaded', function() {

	fetchUserData();

	function fetchUserData() {
		const access_token = localStorage.getItem("access_token");
		fetch('https://127.0.0.1/api/user/me', {
			method: 'GET',
			headers: {
				'Authorization': `Bearer ${access_token}`,
				'Content-Type': 'application/json'
			},
		})
		.then(response => response.json())
		.then(data => {
			// User 정보 업데이트
			updateUserInfo(data);
			// 친구 목록 업데이트
			friends = data.friends;
			console.log(friends);
			updateFriendsList(data.friends);

			// 최근 경기 기록 업데이트 - user 말고 다른 테이블에서 조회
			// updateRecentMatches(data.recentMatches);
		})
		// 500 error?
		.catch(error => console.error('Error fetching user data: ', error));
	}

	function updateUserInfo(user)
	{
		const userDetails = document.querySelector('.user-details h1');
		const userStats = document.querySelector('.user-details p');
		const userAvatar = document.querySelector('.avatar-container img');

		if (user) {
			userDetails.textContent = user.nickname || 'Unknown User';
			userStats.textContent = `Total Stats: ${user.wins || 0}W ${user.losses || 0}L`;  // 승패 정보 업데이트

			if (user.profile && user.profile.trim() !== "") {
				userAvatar.src = user.profile;
			}
			else {
				userAvatar.src = '../images/Retriever.jpeg';
			}
		}
		else {
			console.error('User object is undefined or invalid');
		}
	}

	function updateFriendsList(friends)
	{
		const friendList = document.querySelector('.friends-list');
		friendList.innerHTML = '';

		friends.forEach(friend => {
			const friendItem = document.createElement('li');
			friendItem.classList.add('friend-item');

			const avatarDiv = document.createElement('div');
			avatarDiv.classList.add('friend-avatar');
			const avatarImg = document.createElement('img');
			avatarImg.src = `${friend.profile}`;
			avatarImg.alt = `${friend.name} Avatar`;
			avatarImg.classList.add('avatar');
			avatarDiv.appendChild(avatarImg);

			const infoDiv = document.createElement('div');
			infoDiv.classList.add('friend-info');
			const nameSpan = document.createElement('span');
			nameSpan.classList.add('friend-name');
			nameSpan.textContent = friend.name;

			// Online, Offline 상태 표시
			// const statusSpan = document.createElement('span');
			// statusSpan.classList.add('friend-status', friend.status);
			// statusSpan.textContent = friend.status.charAt(0).toUpperCase() + friend.status.slice(1);
			
			infoDiv.appendChild(nameSpan);
			// infoDiv.appendChild(statusSpan);

			friendItem.appendChild(avatarDiv);
			friendItem.appendChild(infoDiv);
			friendsList.appendChild(friendItem);
		})
	}

	function updateRecentMatches(recentMatches) {
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
})

//#endregion

//#region 친구 추가 기능
// 모달 요소 가져오기
const modal = document.getElementById("addFriendModal");
const addFriendBtn = document.querySelector(".friends-controls .btn"); // + 버튼
const closeBtn = document.querySelector(".close");

// + 버튼 클릭 시 모달 열기
addFriendBtn.addEventListener("click", () => {
    modal.style.display = "block";
});

// 닫기 버튼 클릭 시 모달 닫기
closeBtn.addEventListener("click", () => {
    modal.style.display = "none";
});

// 모달 바깥 클릭 시 모달 닫기
window.addEventListener("click", (event) => {
    if (event.target === modal) {
        modal.style.display = "none";
    }
});

// 친구 추가 폼 제출 처리
document.getElementById("addFriendForm").addEventListener("submit", (event) => {
    event.preventDefault(); // 폼 제출 시 페이지 리로드 방지
    const friendName = document.getElementById("friendNameInput").value;
    
    // 실제로는 여기서 서버에 추가 요청을 보냄
    console.log(`Added friend: ${friendName}`);
	const data = { nickname: friendName };
	const access_token = localStorage.access_token;
	fetch('https://127.0.0.1/api/user/friend/', {
		method: 'POST',
		headers: {
			'Authorization': `Bearer ${access_token}`,
			'Content-Type': 'application/json'
		},
		body: JSON.stringify(data)
	})
	.then(response => {
		if (!response.ok) {
			// 친구 없으면 404
			throw new Error('Network response was not ok');
		}
		return response.json();
	})
	.then(data => {
		console.log('Friend added successfully:', data);
		
		// UI 업데이트
		renderFriends();
		modal.style.display = "none";
		document.getElementById("friendNameInput").value = "";
	})
	.catch(error => {
        console.error('Error updating profile:', error);
    });

    // 모달 닫기 및 입력 필드 초기화
    modal.style.display = "none";
    document.getElementById("friendNameInput").value = "";
});

// 모달 요소 가져오기
const removeModal = document.getElementById("removeFriendModal");
const removeFriendBtn = document.querySelector(".friends-controls .btn:nth-child(2)"); // - 버튼
const closeRemoveBtn = removeModal.querySelector(".close");

// - 버튼 클릭 시 모달 열기
removeFriendBtn.addEventListener("click", () => {
    populateFriendSelect();
    removeModal.style.display = "block";
});

// 닫기 버튼 클릭 시 모달 닫기
closeRemoveBtn.addEventListener("click", () => {
    removeModal.style.display = "none";
});

// 모달 바깥 클릭 시 모달 닫기
window.addEventListener("click", (event) => {
    if (event.target === removeModal) {
        removeModal.style.display = "none";
    }
});

//#endregion

//#region 친구 삭제 기능
// 친구 삭제 폼 제출 처리
document.getElementById("removeFriendForm").addEventListener("submit", (event) => {
    event.preventDefault(); // 폼 제출 시 페이지 리로드 방지
    const friendSelect = document.getElementById("friendSelect");
    const selectedFriend = friendSelect.value;

	const data = { friendName: selectedFriend };

	fetch('http://localhost/api/friends/remove', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json'
		},
		body: JSON.stringify(data)
	})
	.then(response => {
		if (!response.ok) {
			// 500 error?
			throw new Error('Network response was not ok');
		}
		return response.json();
	})
	.then(data => {
		// 친구 목록에서 선택된 친구 삭제
		friends = friends.filter(friend => friend.name !== selectedFriend);
	
		// 서버에 친구 삭제 요청
		console.log(`Removed friend: ${selectedFriend}`);
	
		// 모달 닫기 및 드롭다운 초기화
		removeModal.style.display = "none";
		populateFriendSelect(); // 업데이트된 목록 반영
	
		// 친구 목록 UI 업데이트
		renderFriends();
		// updateFriendsList(); - 대체 가능 함수
	})
	.catch(error => {
		console.error('Error removing friend:', error);
	})
});

// 드롭다운에 친구 목록을 동적으로 추가하는 함수
function populateFriendSelect() {
    const friendSelect = document.getElementById("friendSelect");
    friendSelect.innerHTML = ''; // 기존 옵션 초기화

    friends.forEach(friend => {
        const option = document.createElement("option");
        option.value = friend.name;
        option.textContent = friend.name;
        friendSelect.appendChild(option);
    });
}

// 친구 목록을 UI에 렌더링하는 함수 (예시)
function renderFriends() {
    const friendsList = document.querySelector(".friends-list");
    friendsList.innerHTML = '';

    friends.forEach(friend => {
        const friendItem = document.createElement('li');
        friendItem.classList.add('friend-item');

        const avatarDiv = document.createElement('div');
        avatarDiv.classList.add('friend-avatar');
        const avatarImg = document.createElement('img');
        avatarImg.src = `../images/${friend.avatar}`;
        avatarImg.alt = `${friend.name} Avatar`;
        avatarImg.classList.add('avatar');
        avatarDiv.appendChild(avatarImg);

        const infoDiv = document.createElement('div');
        infoDiv.classList.add('friend-info');
        const nameSpan = document.createElement('span');
        nameSpan.classList.add('friend-name');
        nameSpan.textContent = friend.name;
        const statusSpan = document.createElement('span');
        statusSpan.classList.add('friend-status', friend.status);
        statusSpan.textContent = friend.status.charAt(0).toUpperCase() + friend.status.slice(1);
        infoDiv.appendChild(nameSpan);
        infoDiv.appendChild(statusSpan);

        friendItem.appendChild(avatarDiv);
        friendItem.appendChild(infoDiv);

        friendsList.appendChild(friendItem);
    });
}

//#endregion

// // 초기 친구 목록 렌더링
// document.addEventListener('DOMContentLoaded', () => {
//     renderFriends();
// });

//#region 게임 시작 기능
document.querySelector('.game-start-btn').addEventListener('click', function() {
	// url 추후 수정
	window.location.href = 'https://localhost/html/mode.html';
})
//#endregion

//#region User Profile Edit

// 모달 창 열기 및 닫기
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

// 유저 정보 폼 제출 처리
document.getElementById('editUserForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const nickname = document.getElementById('nicknameInput').value;
    const avatarFile = document.getElementById('avatarInput').files[0];
	const access_token = localStorage.getItem("access_token");

	// 두 정보만 필요??
    const formData = new FormData();
    formData.append('nickname', nickname);
    if (avatarFile) {
        formData.append('profile', avatarFile);
    }
	// 둘 중 하나만 있을 때
	// 둘 다 없을 때

    fetch('https://127.0.0.1/api/user/me', {
        method: 'PATCH',
		headers: {
			'Authorization': `Bearer ${access_token}`,
		},
		body: formData
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.json();
    })
    .then(data => {
        console.log('User profile updated:', data);
        // 유저 정보를 업데이트
        document.querySelector('.user-details h1').textContent = nickname;
        if (avatarFile) {
            const reader = new FileReader();
            reader.onload = function(e) {
                document.querySelector('.avatar-container img').src = e.target.result;
            };
            reader.readAsDataURL(avatarFile);
        }
        // 모달 창 닫기
        editUserModal.style.display = 'none';
    })
    .catch(error => {
        console.error('Error updating profile:', error);
    });
});

//#endregion