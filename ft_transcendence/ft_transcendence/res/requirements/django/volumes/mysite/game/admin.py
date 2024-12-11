from django.contrib import admin
from .models import GameResult
from user.models import User

# Register your models here.
@admin.register(GameResult)
class UserAdmin(admin.ModelAdmin):
	list_display = ['id', 'winner_score', 'loser_score', 'game_date', 'game_type']
	list_display_links = ['id']
	
