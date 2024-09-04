from django.contrib.auth.models import AbstractUser
from django.db import models
from mysite.utils import uuid_name_upload_to
from django.contrib.auth.hashers import make_password

# Create your models here.
class User(AbstractUser):
	oauthid = models.IntegerField(unique=True, verbose_name='OAuth2.0')
	nickname = models.CharField(max_length=20, unique=True, verbose_name='닉네임')
	wins = models.PositiveIntegerField(default=0, verbose_name='승')
	losses = models.PositiveIntegerField(default=0, verbose_name='패')
	# profile = models.URLField(max_length=500, null=True, blank=True, verbose_name='프로필 이미지 URL')
	profile = models.ImageField(blank=True, upload_to=uuid_name_upload_to)
	friends = models.ManyToManyField('self', blank=True, symmetrical=False, related_name='friend_set', verbose_name='친구')

	def __str__(self):
		return str(self.oauthid)  # 기본적으로 아이디(=oauthid)로 반환
	
	class Meta:
		verbose_name = '사용자'
		verbose_name_plural = '사용자들'
		
	# 	super().save(*args, **kwargs)
	# def save(self, *args, **kwargs):
	# 	if self._state.adding and not self.pk:
	# 		self.friends.set([])  # 새 유저가 추가될 때 friends 관계를 자동으로 설정하지 않음
	# 	super().save(*args, **kwargs)