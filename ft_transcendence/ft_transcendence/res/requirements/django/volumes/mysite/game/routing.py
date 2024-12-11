from django.urls import re_path
from . import consumers

websocket_urlpatterns = [
    re_path(r'ws/game/match/$', consumers.MatchConsumer.as_asgi()),
    re_path(r'ws/game/play/$', consumers.GameConsumer.as_asgi()),
]
