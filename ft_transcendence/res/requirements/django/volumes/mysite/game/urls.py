from django.urls import path
from . import views
# from .views import UserAPI, OtherUserInfo, FriendAPIView

urlpatterns = [
	#oauth 로그인
    # path('oauth/callback', views.OauthCallback, name='OauthCallback'),
	# # 내 정보 확인, 수정, 삭제
    # path('me', UserAPI.as_view(), name='UserAPI'),
    # # nickname을 통해 정보 확인
    # path('<str:nickname>', OtherUserInfo, name='OtherUserInfo'),
    # # nickname을 통해 친구 추가, 삭제
	# path('frined', FriendAPIView.as_view(), name='FriendAPI'),
]