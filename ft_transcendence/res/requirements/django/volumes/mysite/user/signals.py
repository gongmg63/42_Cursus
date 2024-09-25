from django.db.models.signals import post_save
from django.db.models.signals import post_delete
from django.dispatch import receiver
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
from .models import User
from django.dispatch import Signal

# 시그널 정의
friend_delete_signal = Signal()

# 시그널 수신기 정의
@receiver(friend_delete_signal, sender=User)
def friend_delete_signal_handler(sender, instance, **kwargs):
    channel_layer = get_channel_layer()
    
    # 본인 삭제 상태 업데이트 전송
    async_to_sync(channel_layer.group_send)(
        f"user_{instance.id}",
        {
            "type": "friend_update",
        }
    )

    async_to_sync(channel_layer.group_send)(
        f"user_{instance.id}",
        {
            "type": "friend_status_update",
        }
    )

# 내가 접속 상태가 바뀔 때 친구들에게 내 상태를 전송
@receiver(post_save, sender=User)
def user_status_changed(sender, instance, **kwargs):
    channel_layer = get_channel_layer()
    for friend in instance.friends.all():
        async_to_sync(channel_layer.group_send)(
            f"user_{friend.id}",
            {
                "type": "friend_status_update",
            }
        )
        async_to_sync(channel_layer.group_send)(
            f"user_{friend.id}",
            {
                "type": "friend_update",
            }
        )

# 사용자가 삭제될 때 친구들에게 상태 전송
@receiver(post_delete, sender=User)
def user_deleted(sender, instance, **kwargs):
    channel_layer = get_channel_layer()
    
    # 본인 삭제 상태 업데이트 전송
    async_to_sync(channel_layer.group_send)(
        f"user_{instance.id}",
        {
            "type": "friend_update",
        }
    )

    async_to_sync(channel_layer.group_send)(
        f"user_{instance.id}",
        {
            "type": "friend_status_update",
        }
    )