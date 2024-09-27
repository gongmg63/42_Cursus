import { fetchUserData, editUser, friend_websocket, fetchRecentMatch } from "./manageUser.js";
import { addFriend } from "./addFriend.js";
import { deleteFriend } from "./deleteFriend.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";
import { friend_websocket } from "./friendWebsocket.js";
import { navigateTo } from "./transcendence.js";

export let friends = [];

window.getUser = function()
{
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
}

// 이벤트 위임을 사용하여 상위 요소(body)에 이벤트 리스너 등록
document.body.addEventListener('click', function(event) {
    if (event.target && event.target.matches('.game-start-btn')) {
        event.preventDefault();
        window.history.pushState(null, null, '#/mode');
        navigateTo('/mode');
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
