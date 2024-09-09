import { fetchUserData, editUser } from "./manageUser.js";
import { addFriend } from "./addFriend.js";
import { deleteFriend } from "./deleteFriend.js";

export let friends = [];

document.addEventListener('DOMContentLoaded', function() {
	fetchUserData();
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
	window.location.href = 'https://127.0.0.1/mode.html';
})