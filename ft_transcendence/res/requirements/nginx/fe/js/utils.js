import { friends } from "./index.js";

export function populateFriendSelect()
{
	const friendSelect = document.getElementById("friendSelect");
	// console.log("populate friend select");
    friendSelect.innerHTML = '';

    friends.forEach(friend => {
		console.log(friend);
        const option = document.createElement("option");
        option.value = friend.nickname;
        option.textContent = friend.nickname;
        friendSelect.appendChild(option);
    });
}

export function updateFriendsList(friends)
{
	const friendList = document.querySelector('.friends-list');
	
	if (friendList)
	{
		friendList.innerHTML = '';
		friends.forEach(friend => {
			const friendItem = document.createElement('li');
			friendItem.classList.add('friend-item');
	
			const avatarDiv = document.createElement('div');
			avatarDiv.classList.add('friend-avatar');
			const avatarImg = document.createElement('img');
			avatarImg.src = `${friend.profile}`;
			avatarImg.alt = `${friend.nickname} Avatar`;
			avatarImg.classList.add('avatar');
			avatarDiv.appendChild(avatarImg);
	
			const infoDiv = document.createElement('div');
			infoDiv.classList.add('friend-info');
			const nameSpan = document.createElement('span');
			nameSpan.classList.add('friend-name');
			nameSpan.textContent = friend.nickname;
	
			// Online, Offline 상태 표시
			const statusSpan = document.createElement('span');
			if (friend.active) {
				statusSpan.classList.add('friend-status', 'online'); // 활성 상태 클래스 추가
				statusSpan.textContent = 'Online'; // 또는 friend.status를 사용할 수 있음
			} else {
				statusSpan.classList.add('friend-status', 'offline'); // 비활성 상태 클래스 추가
				statusSpan.textContent = 'Offline'; // 또는 friend.status를 사용할 수 있음
			}
			// statusSpan.classList.add('friend-status', friend.active);
			// statusSpan.textContent = friend.active + friend.status.slice(1);
			// statusSpan.textContent = friend.status.charAt(0).toUpperCase() + friend.status.slice(1);
			
			infoDiv.appendChild(nameSpan);
			infoDiv.appendChild(statusSpan);
	
			friendItem.appendChild(avatarDiv);
			friendItem.appendChild(infoDiv);
			friendList.appendChild(friendItem);
		})
	}
}

export function editLocalStorage(nickname, avatar)
{
	localStorage.setItem('nickname', nickname);
	localStorage.setItem('profile', avatar);
}

export function handleError(error)
{
	if (error.message.includes('404')) 
		alert('Error (404):User data not found. Please check the user information.');
	else if (error.message.includes('500'))
		alert('Error (500):Server error. Please try again later.');
	else
		alert(error.message);
}