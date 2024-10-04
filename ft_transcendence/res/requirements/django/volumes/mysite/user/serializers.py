from rest_framework import serializers
from django.conf import settings
from .utils import CustomValidationError
from .models import User
import re

class FriendSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = [
            'id', 
            'oauthid', 
            'nickname',
            'active',
            'profile', 
        ]

class UserSerializer(serializers.ModelSerializer):
    friends = FriendSerializer(many=True, read_only=True)  # 친구 정보를 상세히 출력

    class Meta:
        model = User
        fields = [
            'id', # Django에서 자동으로 생성되는 기본 ID 필드
            'oauthid',
            'email',
            'nickname',
            't_nickname',
            't_loser',
            'wins', 
            'losses', 
            'profile',
            'active', 
            'friends',
            'is_tfa_active'
        ]
        read_only_fields = ['id', 'oauthid', 'wins', 'losses']
    
    def validate_nickname(self, nickname):
        if not re.match(r'^[A-Za-z0-9]+$', nickname):
            raise CustomValidationError('Nickname must contain only English letters and numbers, and cannot contain spaces.', code=400)
        return nickname
    
    def validate_t_nickname(self, t_nickname):
        if not re.match(r'^[A-Za-z0-9]+$', t_nickname):
            raise CustomValidationError('Nickname must contain only English letters and numbers, and cannot contain spaces.', code=400)
        return t_nickname
    
    def update(self, instance, validated_data):
        profile = validated_data.get('profile', None)
        
        if profile and instance.profile and instance.profile != profile:
            protected_path = "/images/images"
            if protected_path in instance.profile.path:
                pass  # 삭제하지 않음
            else:
                # 이전 파일 삭제
                instance.profile.delete(save=False)
        
        t_nickname = validated_data.get('t_nickname', None)
        if t_nickname:
            instance.t_nickname = t_nickname

        return super().update(instance, validated_data)
    
class AddFriendSerializer(serializers.Serializer):
    nickname = serializers.CharField(max_length=20)  # 친구의 닉네임

    def validate(self, data):
        try:
            friend = User.objects.get(nickname=data['nickname'])
        except User.DoesNotExist:
            raise CustomValidationError("No user exists with that information.", code=404)  # HTTP 404 Not Found
        
        data['friend'] = friend
        return data
    
    def update(self, instance, validated_data):
        friend = validated_data['friend']
        
        if friend.id == instance.id:
            raise CustomValidationError("You can't add yourself as a friend.", code=400)  # HTTP 400 Bad Request
        
        if friend in instance.friends.all():
            raise CustomValidationError("You are already registered as a friend.", code=400)  # HTTP 400 Bad Request
        
        # 친구 추가 로직을 구현하세요
        instance.friends.add(friend)
        friend.friends.add(instance)
        
        # signal 발생
        instance.save()
        
        return friend
