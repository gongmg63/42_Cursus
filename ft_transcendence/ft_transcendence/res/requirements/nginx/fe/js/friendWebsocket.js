import { setFriends } from "./index.js";
import { updateFriendsList } from "./utils.js";

let websocket = null;

export function friend_websocket()
{
	return new Promise((resolve, reject) => {
        if (websocket && websocket.readyState === WebSocket.OPEN) {
            resolve(websocket);  // 기존의 웹소켓 객체 반환
            return;
        }
        
        const access_token = localStorage.getItem("access_token");
		websocket = new WebSocket('wss://127.0.0.1/ws/friend/status/?token=' + access_token);
		
        // 연결이 성공했을 때 호출
        websocket.onopen = () => {
            resolve(websocket);  // 웹소켓 객체를 반환하여 다른 곳에서 사용 가능
        };

        // 메시지를 수신할 때 호출
        websocket.onmessage = (event) => {
            const data = JSON.parse(event.data);
			if (data.type == 'friend_status_update')
            {
				updateFriendsList(data.friends);
			}
			else if (data.type == 'friend_update')
				setFriends(data.friends);
        };
        
        websocket.onclose = (event) => {
            console.log("친구 웹소켓 연결 종료 : ", event.code)
        }

        websocket.onerror = (error) => {
            console.error("웹소켓 연결 오류:", error);
            reject(error);  // 연결 실패 시 Promise를 거부
        };
    });
}