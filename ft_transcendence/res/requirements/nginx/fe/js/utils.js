import { friends } from "./index.js";

export function populateFriendSelect()
{
	const friendSelect = document.getElementById("friendSelect");
    friendSelect.innerHTML = '';

    friends.forEach(friend => {
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
	
			const statusSpan = document.createElement('span');
			if (friend.active) {
				statusSpan.classList.add('friend-status', 'online');
				statusSpan.textContent = 'Online';
			} else {
				statusSpan.classList.add('friend-status', 'offline');
				statusSpan.textContent = 'Offline';
			}
			
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