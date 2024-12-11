from channels.middleware import BaseMiddleware
from urllib.parse import parse_qs
from rest_framework_simplejwt.exceptions import InvalidToken, TokenError
from rest_framework_simplejwt.tokens import UntypedToken
from django.contrib.auth.models import AnonymousUser
from django.contrib.auth import get_user_model
from jwt import decode as jwt_decode
from channels.db import database_sync_to_async
from django.contrib.auth import get_user_model

User = get_user_model()

class JWTAuthMiddleware(BaseMiddleware):
    async def __call__(self, scope, receive, send):
        query_string = parse_qs(scope['query_string'].decode())
        token = query_string.get('token', [None])[0]
        if token:
            try:
                UntypedToken(token)  # 토큰 검증
                id = self.get_id_from_token(token)
                user = await self.get_user(id)
                scope['user'] = user
            except InvalidToken:
                scope['user'] = AnonymousUser()
        else:
            scope['user'] = AnonymousUser()

        return await super().__call__(scope, receive, send)

    def get_id_from_token(self, token):
        # 실제 사용자 ID를 토큰에서 추출하는 방법에 맞게 구현
        decoded_token = UntypedToken(token)
        return decoded_token['id']

    @database_sync_to_async
    def get_user(self, id):
        try:
            return User.objects.get(id=id)
        except User.DoesNotExist:
            return AnonymousUser()