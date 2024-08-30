from django.urls import path
from rest_framework_simplejwt.views import (
    TokenObtainPairView,
    TokenRefreshView,
    TokenVerifyView,
)
from . import views
from .views import UserAPI, OtherUserInfo

urlpatterns = [
	#oauth 로그인
    path('oauth', views.Oauth, name='Oauth'),
    path('oauth/callback', views.OauthCallback, name='OauthCallback'),
	# JWT 토큰 발급
    path('token', TokenObtainPairView.as_view(), name='TokenObtainPair'),
    # JWT 토큰 재발급
    path('token/refresh', TokenRefreshView.as_view(), name='TokenRefresh'),
    # JWT 토큰 검증
    path('token/verify', TokenVerifyView.as_view(), name='TokenVerify'),
	# 내 정보 확인
    path('me', UserAPI.as_view(), name='UserAPI'),
    # nickname을 통해 정보 확인
    path('<str:nickname>', OtherUserInfo, name='OtherUserInfo'),
]