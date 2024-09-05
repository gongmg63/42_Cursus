# signals.py
from django.db.models.signals import post_save
from django.dispatch import receiver
from .models import User

@receiver(post_save, sender=User)
def add_default_friends(sender, instance, created, **kwargs):
    if created:
        # 새로운 사용자 생성 시 자동으로 친구 추가 로직이 있는지 확인
        print(f"New user created: {instance.nickname}")
        # 자동 친구 추가 로직이 여기에 있을 수 있습니다.
