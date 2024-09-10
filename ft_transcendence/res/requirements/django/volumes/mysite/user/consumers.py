import json
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from .models import User

class FriendStatusConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user = self.scope["user"]
        if self.user.is_authenticated:
            await self.channel_layer.group_add(
                f"user_{self.user.id}",
                self.channel_name
            )
            await self.accept()
            await self.update_user_status(True)
            await self.send_friend_status()
        else:
            await self.close()

    async def disconnect(self, close_code):
        if self.user.is_authenticated:
            await self.update_user_status(False)
            await self.channel_layer.group_discard(
                f"user_{self.user.id}",
                self.channel_name
            )

    @database_sync_to_async
    def update_user_status(self, status):
        User.objects.filter(id=self.user.id).update(is_active=status)

    @database_sync_to_async
    def get_friends_status(self):
        friends = self.user.friends.all()
        return {friend.id: friend.is_active for friend in friends}

    async def send_friend_status(self):
        friend_status = await self.get_friends_status()
        await self.send(text_data=json.dumps({
            'type': 'friend_status',
            'friends': friend_status
        }))

    async def friend_status_update(self, event):
        await self.send(text_data=json.dumps({
            'type': 'friend_status_update',
            'friend_id': event['friend_id'],
            'status': event['status']
        }))