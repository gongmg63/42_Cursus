from django.urls import path
from . import views
from .views import UserAPI, OtherUserInfo

urlpatterns = [
    path('oauth/', views.Oauth, name='Oauth'),
    path('oauth/callback/', views.OauthCallback, name='OauthCallback'),
	path('me/', UserAPI.as_view(), name='UserAPI'),
    path('<str:nickname>/', OtherUserInfo, name='OtherUserInfo'),
]