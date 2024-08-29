from rest_framework import serializers
from .models import User

class FriendSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['oauthid', 'nickname', 'profile']

class UserSerializer(serializers.ModelSerializer):
    friends = FriendSerializer(many=True, read_only=True)  # 친구 정보를 상세히 출력

    class Meta:
        model = User
        fields = [
            'id', # Django에서 자동으로 생성되는 기본 ID 필드
            'oauthid',
            'nickname',
            'wins', 
            'losses', 
            'profile', 
            'friends'
        ]
        read_only_fields = ['id', 'oauthid', 'wins', 'losses']