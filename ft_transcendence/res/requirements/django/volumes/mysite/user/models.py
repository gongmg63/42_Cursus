from django.contrib.auth.models import AbstractUser
from django.db import models
from mysite.utils import uuid_name_upload_to
import os

class User(AbstractUser):
	oauthid = models.IntegerField(default = 0, unique=True, verbose_name='OAuth2.0')
	nickname = models.CharField(max_length=20, unique=True, verbose_name='닉네임')
	t_nickname = models.CharField(max_length=20, null=True, verbose_name='토너먼트 닉네임')
	t_loser = models.CharField(max_length=20, null=True, verbose_name='토너먼트 패배자')
	wins = models.PositiveIntegerField(default=0, verbose_name='승')
	losses = models.PositiveIntegerField(default=0, verbose_name='패')
	profile = models.ImageField(blank=True, upload_to=uuid_name_upload_to)
	friends = models.ManyToManyField('self', blank=True, symmetrical=False, related_name='friend_set', verbose_name='친구')
	active = models.BooleanField(default=True)  # 접속 여부
	is_tfa_active = models.BooleanField(default=False)
	otp_base32 = models.CharField(max_length=32, blank=True, null=True)
	qrcode_url = models.CharField(max_length=100, blank=True, null=True)

	def save(self, *args, **kwargs):
		super().save(*args, **kwargs)

	def __str__(self):
		return str(self.oauthid)  # 기본적으로 아이디(=oauthid)로 반환
	
	class Meta:
		verbose_name = '사용자'
		verbose_name_plural = '사용자들'