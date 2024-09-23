import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from .models import User
from user.serializers import FriendSerializer

class FriendStatusConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user = self.scope["user"]
        print(f"websocket: connect! nickname: {self.user.nickname}")
        if self.user.is_authenticated:
            await self.channel_layer.group_add(
                f"user_{self.user.id}",
                self.channel_name
            )
            await self.accept()
            await self.save_user_status(True)
        else:
            await self.close()

    async def disconnect(self, close_code):
        print(f"websocket: disconnect... nickname: {self.user.nickname}")
        if self.user.is_authenticated:
            await self.save_user_status(False)
            await self.channel_layer.group_discard(
                f"user_{self.user.nickname}",
                self.channel_name
            )

    @database_sync_to_async
    def save_user_status(self, status):
        user = User.objects.get(id=self.user.id)
        user.active = status
        user.save()

    @database_sync_to_async
    def get_friends_status(self):
        friends = self.user.friends.all()
        return {friend.id: friend.active for friend in friends}

    async def friend_status_update(self, event):
        friends = self.user.friends.all()  # 모든 친구를 가져오기
        friend_list = FriendSerializer(friends, many=True)

        await self.send(text_data=json.dumps({
            'type': 'friend_status_update',
            'friends': friend_list.data
        }))

    async def friend_update(self, event):
        friends = self.user.friends.all()  # 모든 친구를 가져오기
        friend_list = FriendSerializer(friends, many=True)
        
        await self.send(text_data=json.dumps({
            'type': 'friend_update',
            'friends': friend_list.data
        }))