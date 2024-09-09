import { updateFriendsList, populateFriendSelect } from "./utils.js";
import { friends } from "./index.js";

const removeModal = document.getElementById("removeFriendModal");
const removeFriendBtn = document.querySelector(".friends-controls .btn:nth-child(2)"); // - 버튼
const closeRemoveBtn = removeModal.querySelector(".close");

removeFriendBtn.addEventListener("click", () => {
	console.log(friends);
	populateFriendSelect();
	removeModal.style.display = "block";
});

closeRemoveBtn.addEventListener("click", () => {
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
	fetch('https://127.0.0.1/api/user/friend/', {
		method: 'DELETE',
		headers: {
			'Authorization': `Bearer ${access_token}`,
			'Content-Type': 'application/json'
		},
		body: JSON.stringify(data)
	})
	.then(response => {
		if (!response.ok) {
			throw new Error('Network response was not ok');
		}
		return response.json();
	})
	.then(data => {
		// selectedFriend 꼭 필요??
		// friends -> readonly data, index.js 쪽에서 수정.
		// friends = friends.filter(friend => friend.nickname !== selectedFriend);
	
		const index = friends.findIndex(friend => friend.nickname === selectedFriend);
		if (index !== -1)
			friends.splice(index, 1);  // 배열에서 해당 친구를 삭제

		console.log(`Removed friend: ${selectedFriend}`);
	
		removeModal.style.display = "none";
		populateFriendSelect(); // 업데이트된 목록 반영
	
		// 친구 목록 UI 업데이트
		updateFriendsList(friends);
	})
	.catch(error => {
		console.error('Error removing friend:', error);
	})
}