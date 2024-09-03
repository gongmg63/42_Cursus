from django.utils.safestring import mark_safe
from django.contrib import admin
from .models import User

# Register your models here.
@admin.register(User)
class UserAdmin(admin.ModelAdmin):
	list_display = ['id', 'oauthid', 'nickname', 'wins', 'losses', 'profile']
	list_display_links = ['id']
	
	def profile(self, post):
		if post.profile:
			return mark_safe(f'<img src="{post.profile.url}" style="width: 72px;"/>')
		return None
