from rest_framework import serializers
from django.conf import settings
from .utils import CustomValidationError
from .models import User
import os

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
            'wins', 
            'losses', 
            'profile',
            'active', 
            'friends',
            'is_tfa_active'
        ]
        read_only_fields = ['id', 'oauthid', 'wins', 'losses']
    
    def update(self, instance, validated_data):
        profile = validated_data.get('profile', None)
        
        if profile and instance.profile and instance.profile != profile:
            protected_path = "/images/images"
            if protected_path in instance.profile.path:
                pass  # 삭제하지 않음
            else:
                # 이전 파일 삭제
                instance.profile.delete(save=False)
        
        return super().update(instance, validated_data)
    
class AddFriendSerializer(serializers.Serializer):
    nickname = serializers.CharField(max_length=20)  # 친구의 닉네임

    def validate(self, data):
        try:
            friend = User.objects.get(nickname=data['nickname'])
        except User.DoesNotExist:
            raise CustomValidationError("해당 정보를 가진 사용자가 존재하지 않습니다.", code=404)  # HTTP 404 Not Found
        
        data['friend'] = friend
        return data
    
    def update(self, instance, validated_data):
        friend = validated_data['friend']
        
        if friend.id == instance.id:
            raise CustomValidationError("자기 자신을 친구로 추가할 수 없습니다.", code=400)  # HTTP 400 Bad Request
        
        if friend in instance.friends.all():
            raise CustomValidationError("이미 친구로 등록된 사용자입니다.", code=400)  # HTTP 400 Bad Request
        
        # 친구 추가 로직을 구현하세요
        instance.friends.add(friend)
        friend.friends.add(instance)
        
        # signal 발생
        friend.save()
        
        return friend
