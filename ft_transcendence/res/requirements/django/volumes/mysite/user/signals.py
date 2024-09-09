from django.db.models.signals import post_save
from django.dispatch import receiver
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
from .models import User

@receiver(post_save, sender=User)
def user_status_changed(sender, instance, **kwargs):
    channel_layer = get_channel_layer()
    for friend in instance.friends.all():
        async_to_sync(channel_layer.group_send)(
            f"user_{friend.id}",
            {
                "type": "friend_status_update",
                "friend_id": instance.id,
                "status": instance.is_active
            }
        )