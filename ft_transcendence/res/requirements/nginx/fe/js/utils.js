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
		nameSpan.textContent = friend.name;

		// Online, Offline 상태 표시
		// const statusSpan = document.createElement('span');
		// statusSpan.classList.add('friend-status', friend.status);
		// statusSpan.textContent = friend.status.charAt(0).toUpperCase() + friend.status.slice(1);
		
		infoDiv.appendChild(nameSpan);
		// infoDiv.appendChild(statusSpan);

		friendItem.appendChild(avatarDiv);
		friendItem.appendChild(infoDiv);
		friendList.appendChild(friendItem);
	})
}