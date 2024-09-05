from django.urls import path
from rest_framework_simplejwt.views import TokenRefreshView, TokenVerifyView
from . import views
from .views import UserAPI, OtherUserInfo, FriendAPIView

urlpatterns = [
	#oauth 로그인
    path('oauth', views.Oauth, name='Oauth'),
    path('oauth/callback', views.OauthCallback, name='OauthCallback'),
    # JWT 토큰 재발급
    path('token/refresh', TokenRefreshView.as_view(), name='TokenRefresh'), # 성공 시 200과 함께 access token, refresh token( rotate refresh token 이므로 ), 실패 시 401
    # JWT 토큰 검증
    path('token/verify', TokenVerifyView.as_view(), name='TokenVerify'), # 성공 시 200, 실패 시 401
	# 내 정보 확인, 수정, 삭제
    path('me', UserAPI.as_view(), name='UserAPI'),
    # nickname을 통해 정보 확인
    path('<str:nickname>', OtherUserInfo, name='OtherUserInfo'),
    # nickname을 통해 친구 추가, 삭제
	path('friend', FriendAPIView.as_view(), name='FriendAPI'),
]