import { handleError, updateFriendsList } from "./utils.js";
import { friends, pushFriends } from "./index.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

const modal = document.getElementById("addFriendModal");
const addFriendBtn = document.querySelector(".friends-controls .btn");
const closeBtn = document.querySelector(".close");

if (addFriendBtn)
{
	addFriendBtn.addEventListener("click", () => {
		modal.style.display = "block";
	});
}

if (closeBtn)
{
	closeBtn.addEventListener("click", () => {
		modal.style.display = "none";
	});
}

window.addEventListener("click", (event) => {
	if (event.target === modal) {
		modal.style.display = "none";
	}
});

export function addFriend()
{
	const friendName = document.getElementById("friendNameInput").value;
    
    // 실제로는 여기서 서버에 추가 요청을 보냄
    console.log(`Added friend: ${friendName}`);
	const data = { nickname: friendName };
	const access_token = localStorage.getItem("access_token");
	postFriendAPI(data, access_token);
}

function postFriendAPI(data, access_token)
{
	checkAndRefreshToken().then(() => {
		console.log("data: ", data);
		fetch('/api/user/friend/', {
			method: 'POST',
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
			console.log('Friend added successfully:', data);
			
			// friends -> readonly data, index.js 쪽에서 수정.
			pushFriends(data.friend);
			// Update friends UI 
			// renderFriends();
			updateFriendsList(friends);
	
			modal.style.display = "none";
			document.getElementById("friendNameInput").value = "";
		})
		.catch(error => {
			console.error('Error updating profile:', error);
			handleError(error);
		});
	
		modal.style.display = "none";
		document.getElementById("friendNameInput").value = "";
	});
}