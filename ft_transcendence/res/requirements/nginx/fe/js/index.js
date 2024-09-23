import { fetchUserData, editUser, friend_websocket, fetchRecentMatch } from "./manageUser.js";
import { addFriend } from "./addFriend.js";
import { deleteFriend } from "./deleteFriend.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

export let friends = [];

document.addEventListener('DOMContentLoaded', function() {
    checkAndRefreshToken().then(() => {
        friend_websocket()
            .then((websocket) => {
                console.log("웹소켓이 연결되었습니다.");
                fetchUserData();
				fetchRecentMatch();
            })
            .catch((error) => {
                console.error("웹소켓 연결 중 오류가 발생했습니다:", error);
            });
    });
});

document.getElementById("addFriendForm").addEventListener("submit", (event) => {
    event.preventDefault(); // 폼 제출 시 페이지 리로드 방지
	addFriend();
});

document.getElementById("removeFriendForm").addEventListener("submit", (event) => {
    event.preventDefault(); // 폼 제출 시 페이지 리로드 방지
	deleteFriend();
});

document.getElementById('editUserForm').addEventListener('submit', function(event) {
    event.preventDefault();
	editUser();
});

document.querySelector('.game-start-btn').addEventListener('click', function() {
	window.location.href = '/mode.html';
})

export function pushFriends(friend)
{
	friends.push(friend);
}

export function setFriends(newFriends)
{
	friends = newFriends;
}