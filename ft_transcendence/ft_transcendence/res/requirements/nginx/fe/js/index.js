import { fetchUserData, editUser, fetchRecentMatch } from "./manageUser.js";
import { addFriend } from "./addFriend.js";
import { deleteFriend } from "./deleteFriend.js";
import { render } from "./transcendence.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";

export let friends = [];

window.getUser = function()
{
    fetchUserData();
    fetchRecentMatch();
}

// 이벤트 위임을 사용하여 상위 요소(body)에 이벤트 리스너 등록
document.body.addEventListener('click', function(event) {
    if (event.target && event.target.matches('.game-start-btn')) {
        checkAndRefreshToken().then(() => {
            event.preventDefault();
            // window.history.pushState(null, null, '#/mode');
            // navigateTo('/mode');
            render('#/mode');
        })
        .catch(error => {
            alert('토큰이 유효하지 않습니다. 다시 로그인하세요')
            render('#/');
        });
    }
});

document.body.addEventListener('submit', function(event) {
    if (event.target && event.target.matches('#addFriendForm')) {
        event.preventDefault();
        addFriend();
    }

    if (event.target && event.target.matches('#removeFriendForm')) {
        event.preventDefault();
        deleteFriend();
    }

    if (event.target && event.target.matches('#editUserForm')) {
        event.preventDefault();
        editUser();
    }
});

export function pushFriends(friend)
{
	friends.push(friend);
}

export function setFriends(newFriends)
{
	friends = newFriends;
}
