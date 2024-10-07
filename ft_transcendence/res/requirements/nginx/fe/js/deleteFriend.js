import { updateFriendsList, populateFriendSelect } from "./utils.js";
import { friends } from "./index.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";


document.body.addEventListener('click', function(event) {
	
	const removeModal = document.getElementById("removeFriendModal");
    // 친구 제거 버튼 클릭 시 모달 표시
    if (event.target && event.target.matches('.friends-controls .btn:nth-child(2)')) {
        populateFriendSelect();
        removeModal.style.display = 'block';
    }

    // 모달 닫기 버튼 클릭 시 모달 숨김
    if (event.target && event.target.matches('#removeFriendModal .close')) {
        removeModal.style.display = 'none';
    }

    // 모달 외부를 클릭하면 모달 닫기
    if (event.target === removeModal) {
        removeModal.style.display = 'none';
    }
});

export function deleteFriend()
{
	const friendSelect = document.getElementById("friendSelect");
    const selectedFriend = friendSelect.value;
	const data = { nickname: selectedFriend };

	deleteFriendAPI(data, selectedFriend);
}

function deleteFriendAPI(data, selectedFriend)
{
	const removeModal = document.getElementById("removeFriendModal");

	checkAndRefreshToken().then(() => {
		const access_token = localStorage.getItem("access_token");
		fetch('/api/user/friend/', {
			method: 'DELETE',
			headers: {
				'Authorization': `Bearer ${access_token}`,
				'Content-Type': 'application/json'
			},
			body: JSON.stringify(data)
		})
		.then(response => {
			if (response.status == 404)
				throw new Error('User data not found (404)');
			else if (response.status == 500)
				throw new Error('Server error (500)')
			else if (!response.ok)
				throw new Error(`${response.status}`);
			return response.json();
		})
		.then(data => {
			const index = friends.findIndex(friend => friend.nickname === selectedFriend);
			if (index !== -1)
				friends.splice(index, 1);  // 배열에서 해당 친구를 삭제		
			removeModal.style.display = "none";
			populateFriendSelect();
		
			// 친구 목록 UI 업데이트
			updateFriendsList(friends);
		})
		.catch(error => {
			alert(error);
			console.error('Error removing friend:', error);
		})
	})
	.catch(error => {
		alert('토큰이 유효하지 않습니다. 다시 로그인하세요')
		render('#/');
	});
}