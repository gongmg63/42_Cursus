from django.contrib.auth.models import AbstractUser
from django.db import models
from mysite.utils import uuid_name_upload_to
import os

class User(AbstractUser):
	oauthid = models.IntegerField(default = 0, unique=True, verbose_name='OAuth2.0')
	nickname = models.CharField(max_length=20, unique=True, verbose_name='닉네임')
	wins = models.PositiveIntegerField(default=0, verbose_name='승')
	losses = models.PositiveIntegerField(default=0, verbose_name='패')
	profile = models.ImageField(blank=True, upload_to=uuid_name_upload_to)
	friends = models.ManyToManyField('self', blank=True, symmetrical=False, related_name='friend_set', verbose_name='친구')
	is_active = models.BooleanField(default=True)  # 접속 여부

	def save(self, *args, **kwargs):
		if self.pk:
			old_user = User.objects.get(pk=self.pk)
			if old_user.profile and old_user.profile != self.profile:
				if os.path.isfile(old_user.profile.path):
					os.remove(old_user.profile.path)
		super().save(*args, **kwargs)

	def __str__(self):
		return str(self.oauthid)  # 기본적으로 아이디(=oauthid)로 반환
	
	class Meta:
		verbose_name = '사용자'
		verbose_name_plural = '사용자들'