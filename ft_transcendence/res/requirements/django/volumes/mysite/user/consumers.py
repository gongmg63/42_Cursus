from channels.generic.websocket import WebsocketConsumer
import json
from asgiref.sync import async_to_sync

class OnlineStatusConsumer(WebsocketConsumer):
    def connect(self):
        # 사용자 인증 확인
        self.user = self.scope["user"]
        if self.user.is_authenticated:
            # 그룹에 사용자 추가
            async_to_sync(self.channel_layer.group_add)(
                "online_users", self.channel_name
            )
            # 온라인 상태로 설정
            self.user.is_active = True
            self.user.save()
            self.accept()

    def disconnect(self, close_code):
        # 그룹에서 사용자 제거
        async_to_sync(self.channel_layer.group_discard)(
            "online_users", self.channel_name
        )
        if self.user.is_authenticated:
            # 오프라인 상태로 설정
            self.user.is_active = False
            self.user.save()

    def receive(self, text_data):
        data = json.loads(text_data)
        message = data.get("message", "")

        # 메시지를 같은 그룹에 있는 사용자에게 브로드캐스트
        async_to_sync(self.channel_layer.group_send)(
            "online_users",
            {
                "type": "broadcast_message",
                "message": message,
            },
        )

    def broadcast_message(self, event):
        message = event["message"]

        # 클라이언트에 메시지 전송
        self.send(text_data=json.dumps({
            "message": message,
        }))
