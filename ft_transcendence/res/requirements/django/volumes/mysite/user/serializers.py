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

class AddFriendSerializer(serializers.Serializer):
    oauthid = serializers.IntegerField()  # 친구로 추가할 사용자의 OAuthID
    nickname = serializers.CharField(max_length=20)  # 친구의 닉네임
    profile = serializers.URLField(max_length=500, required=False)  # 프로필 이미지 URL

    def validate(self, data):
        try:
            friend = User.objects.get(oauthid=data['oauthid'], nickname=data['nickname'])
        except User.DoesNotExist:
            raise serializers.ValidationError("해당 정보를 가진 사용자가 존재하지 않습니다.")
        
        data['friend'] = friend  # validated_data에 친구 객체를 추가
        return data

    def update(self, instance, validated_data):
        friend = validated_data['friend']
        
        if friend in instance.friends.all():
            raise serializers.ValidationError("이미 친구로 등록된 사용자입니다.")
        
        # 친구 추가
        instance.friends.add(friend)
        return instance
