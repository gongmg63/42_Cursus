import { updateFriendsList, populateFriendSelect, handleError } from "./utils.js";
import { friends } from "./index.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

const removeModal = document.getElementById("removeFriendModal");
const removeFriendBtn = document.querySelector(".friends-controls .btn:nth-child(2)"); // - 버튼
const closeRemoveBtn = removeModal?.querySelector(".close");

removeFriendBtn?.addEventListener("click", () => {
	console.log(friends);
	populateFriendSelect();
	removeModal.style.display = "block";
});

closeRemoveBtn?.addEventListener("click", () => {
	removeModal.style.display = "none";
});

window.addEventListener("click", (event) => {
	if (event.target === removeModal) {
		removeModal.style.display = "none";
	}
});

export function deleteFriend()
{
	const friendSelect = document.getElementById("friendSelect");
    const selectedFriend = friendSelect.value;
	const data = { nickname: selectedFriend };
	const access_token = localStorage.getItem("access_token");

	deleteFriendAPI(data, access_token, selectedFriend);
}

function deleteFriendAPI(data, access_token, selectedFriend)
{
	checkAndRefreshToken().then(() => {
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
				throw new Error(`Unexpected error: ${response.status}`);
			return response.json();
		})
		.then(data => {
			const index = friends.findIndex(friend => friend.nickname === selectedFriend);
			if (index !== -1)
				friends.splice(index, 1);  // 배열에서 해당 친구를 삭제
	
			console.log(`Removed friend: ${selectedFriend}`);
		
			removeModal.style.display = "none";
			populateFriendSelect();
		
			// 친구 목록 UI 업데이트
			updateFriendsList(friends);
		})
		.catch(error => {
			console.error('Error removing friend:', error);
			handleError(error);
		})
	})
}