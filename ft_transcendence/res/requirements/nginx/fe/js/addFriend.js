import { updateFriendsList } from "./utils.js";
import { friends, pushFriends } from "./index.js";
import { checkAndRefreshToken } from "./jwtRefresh.js";
import { render } from "./transcendence.js";


// 상위 요소(body)에 이벤트 리스너 등록하여 이벤트 위임 적용
document.body.addEventListener('click', function(event) {

	const modal = document.getElementById("addFriendModal");
	if (modal === null)
		return ;
    // 친구 추가 버튼 클릭 시 모달 표시
    if (event.target && event.target.matches('.friends-controls .btn:first-child')) {
		modal.style.display = 'block';
		console.log(modal.style.display);
    }

    // 모달 닫기 버튼 클릭 시 모달 숨김
    if (event.target && event.target.matches('.close')) {
        modal.style.display = 'none';
    }

    // 모달 외부를 클릭하면 모달 닫기
    if (event.target === modal) {
        modal.style.display = 'none';
    }
});

export function addFriend()
{
	const friendName = document.getElementById("friendNameInput").value;
    
    // 실제로는 여기서 서버에 추가 요청을 보냄
    console.log(`Added friend: ${friendName}`);
	const data = { nickname: friendName };
	postFriendAPI(data);
}

function postFriendAPI(data)
{
	const modal = document.getElementById("addFriendModal");
	
	checkAndRefreshToken().then(() => {
		const access_token = localStorage.getItem("access_token");
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
				{
					return response.json().then(errData => {
						throw new Error(`Error (${response.status}): ${errData.detail || 'Unknown error'}`);
					});
				}
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
			alert(error);
			console.error('Error updating profile:', error);
		});
	
		modal.style.display = "none";
		document.getElementById("friendNameInput").value = "";
	})
	.catch(error => {
		alert('토큰이 유효하지 않습니다. 다시 로그인하세요')
		render('#/');
	});
}