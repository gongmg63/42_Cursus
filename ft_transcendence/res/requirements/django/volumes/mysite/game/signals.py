from django.dispatch import Signal
from asgiref.sync import async_to_sync
from django.dispatch import receiver
from channels.layers import get_channel_layer

from user.models import User

# 시그널 정의
play_disconnect_signal = Signal()

# 시그널 수신기 정의 (동기 버전)
@receiver(play_disconnect_signal)
def play_disconnect_handler(instance, **kwargs):
    print(instance.user.nickname, "user disconnect!")
    channel_layer = get_channel_layer()

    # 비동기 작업을 동기적으로 처리 (async_to_sync 사용)
    instance.channel_layer.group_send(
        instance.group_name,
        {
            "type": "play_disconnect",
            "id": instance.user.id
        }
    )