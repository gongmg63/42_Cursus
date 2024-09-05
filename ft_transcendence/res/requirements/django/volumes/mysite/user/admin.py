from django.utils.safestring import mark_safe
from django.contrib import admin
from .models import User
from game.models import GameResult  # game 앱에서 GameResult 모델 import

@admin.register(User)
class UserAdmin(admin.ModelAdmin):
    list_display = ['id', 'oauthid', 'nickname', 'wins', 'losses', 'profile']
    list_display_links = ['id']

    def profile(self, post):
        if post.profile:
            return mark_safe(f'<img src="{post.profile}" style="width: 72px;"/>')
        return None

    # def get_game_data(self, obj):
    #     # User가 승자로 또는 패자로 등장하는 모든 게임 데이터를 가져옵니다.
    #     game_results = GameResult.objects.filter(winner=obj) | GameResult.objects.filter(loser=obj)
    #     return ", ".join([f"{game.game_type}: {game.winner_score} - {game.loser_score}" for game in game_results])

    # get_game_data.short_description = 'Game Data'
