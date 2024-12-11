"""
ASGI config for mysite project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/asgi/
"""

import os
import django
from django.core.asgi import get_asgi_application
from channels.routing import ProtocolTypeRouter, URLRouter

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'mysite.settings')
django.setup()
django_asgi_app = get_asgi_application()

from django.urls import path
from user.consumers import FriendStatusConsumer
from user.routing import websocket_urlpatterns as user_websocket_urlpatterns
from game.routing import websocket_urlpatterns as game_websocket_urlpatterns
from .jwt_middleware import JWTAuthMiddleware  # JWT 미들웨어 임포트

websocket_urlpatterns = user_websocket_urlpatterns + game_websocket_urlpatterns

application = ProtocolTypeRouter({
    "http": django_asgi_app,
    "websocket": JWTAuthMiddleware( # JWTAuthMiddleware를 적용
        URLRouter(
            websocket_urlpatterns
        )
    ),
})