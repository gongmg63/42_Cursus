from mysite.utils import uuid_name_upload_to
from django.utils import timezone
from django.conf import settings
from django.db import models

class GameResult(models.Model):
    GAME_TYPE_CHOICES = [
        ('1vs1', '1VS1'),
        ('tournament', 'Tournament'),
        # 필요한 다른 게임 종류 추가
    ]

    winner = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='won_games', on_delete=models.CASCADE)
    loser = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='lost_games', on_delete=models.CASCADE)
    winner_score = models.PositiveIntegerField(verbose_name='승자 점수')
    loser_score = models.PositiveIntegerField(verbose_name='패자 점수')
    game_date = models.DateTimeField(default=timezone.now, verbose_name='게임 날짜')
    game_type = models.CharField(max_length=50, choices=GAME_TYPE_CHOICES, verbose_name='게임 종류')

    def __str__(self):
        return f"{self.winner.nickname} vs {self.loser.nickname} - {self.game_type} on {self.game_date}"
