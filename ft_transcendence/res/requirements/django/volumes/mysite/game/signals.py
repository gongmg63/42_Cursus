from django.dispatch import Signal
from asgiref.sync import async_to_sync
from django.dispatch import receiver
from channels.layers import get_channel_layer

from user.models import User

play_disconnect_signal = Signal()

@receiver(play_disconnect_signal)
def play_disconnect_handler(instance, **kwargs):
    channel_layer = get_channel_layer()

    instance.channel_layer.group_send(
        instance.group_name,
        {
            "type": "play_disconnect",
            "id": instance.user.id
        }
    )