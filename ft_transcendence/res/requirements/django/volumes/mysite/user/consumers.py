import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from .models import User


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
            # await self.save_user_status(True)
            await self.send_friend_status()
        else:
            await self.close()

    async def disconnect(self, close_code):
        print(f"websocket: disconnect... nickname: {self.user.nickname}")
        if self.user.is_authenticated:
            # await self.save_user_status(False)
            await self.channel_layer.group_discard(
                f"user_{self.user.nickname}",
                self.channel_name
            )

    @database_sync_to_async
    def save_user_status(self, status):
        user = User.objects.get(id=self.user.id)
        user.is_active = status
        user.save()

    @database_sync_to_async
    def get_friends_status(self):
        friends = self.user.friends.all()
        return {friend.id: friend.is_active for friend in friends}

    async def send_friend_status(self):
        print(f"websocket: send_friend_status... nickname: {self.user.nickname}")
        friend_status = await self.get_friends_status()
        await self.send(text_data=json.dumps({
            'type': 'friend_status',
            'friends': friend_status
        }))

    async def friend_status_update(self, event):
        print(f"websocket: friend_status_update... nickname: {self.user.nickname}")
        print(f"Received friend_status_update: {event}")
        await self.send(text_data=json.dumps({
            'type': 'friend_status_update',
            'id': event['id'],
            'is_active': event['is_active']
        }))

    # async def send_status_update_to_friends(self, status):
    #     friends = await self.get_friends_status()
    #     print(f"websocket: send_friend_status... nickname: {self.user.nickname}")
    #     for friend_id, is_active in friends.items():
    #         await self.channel_layer.group_send(
    #             f"user_{friend_id}",
    #             {
    #                 "type": "friend_status_update",
    #                 "id": self.user.id,
    #                 "is_active": status
    #             }
    #         )