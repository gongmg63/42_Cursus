from .views import AddGameResultView, GetGameResultView, GetGameResultByNicknameView, GetRecentGameResultView
from django.urls import path
from . import views


urlpatterns = [
	# 게임 결과 추가
    path('result/add/', AddGameResultView.as_view(), name='add-game-result'),
	# 내 1vs1 전적 조회
	path('result/me', GetGameResultView.as_view(), name='get-my-game-result'),
	# 가장 최근 전적
	path('result/me/recent', GetRecentGameResultView.as_view(), name='get-my-recent-game-result'),
	# 다른 유저 결과 조회
	path('result/<str:nickname>', GetGameResultByNicknameView.as_view(), name='get-other-game-result'),
]