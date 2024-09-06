from rest_framework import serializers
from .models import User

class FriendSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = [
            'id', 
            'oauthid', 
            'nickname', 
            'profile', 
        ]

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
    
    def update(self, instance, validated_data):
        profile = validated_data.get('profile', None)
        
        if profile and instance.profile and instance.profile != profile:
            # 이전 파일 삭제
            instance.profile.delete(save=False)
        
        return super().update(instance, validated_data)
    
class AddFriendSerializer(serializers.Serializer):
    nickname = serializers.CharField(max_length=20)  # 친구의 닉네임

    def validate(self, data):
        try:
            friend = User.objects.get(nickname=data['nickname'])
        except User.DoesNotExist:
            raise serializers.ValidationError("해당 정보를 가진 사용자가 존재하지 않습니다.")
        
        data['friend'] = friend  # validated_data에 친구 객체를 추가
        return data

    def update(self, instance, validated_data):
        friend = validated_data['friend']
        
        # 유저 자신을 친구로 추가하는 것을 방지
        if friend.id == instance.id:
            raise serializers.ValidationError("자기 자신을 친구로 추가할 수 없습니다.")
    
        if friend in instance.friends.all():
            raise serializers.ValidationError("이미 친구로 등록된 사용자입니다.")
        
        # 친구 추가
        instance.friends.add(friend)
        return friend
