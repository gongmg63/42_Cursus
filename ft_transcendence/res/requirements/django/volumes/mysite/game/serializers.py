from rest_framework import serializers
from user.serializers import UserSerializer
from user.models import User
from .models import GameResult


class GameResultSerializer(serializers.ModelSerializer):
    winner = UserSerializer(read_only=True)
    loser = UserSerializer(read_only=True)

    class Meta:
        model = GameResult
        fields = [
            'winner',
            'loser',
            'winner_score',
            'loser_score',
            'game_date',
            'game_type',
        ]

class AddGameResultSerializer(serializers.Serializer):
    winner = serializers.CharField(max_length=20)
    loser = serializers.CharField(max_length=20)
    winner_score = serializers.IntegerField()
    loser_score = serializers.IntegerField()
    game_type = serializers.CharField(max_length=50)
    game_date = serializers.DateTimeField()

    def validate(self, data):
        try:
            # winner와 loser는 각각 유저의 username (혹은 다른 필드 값)에 해당합니다.
            winner = User.objects.get(username=data['winner'])
            loser = User.objects.get(username=data['loser'])
        except User.DoesNotExist:
            raise serializers.ValidationError("승자 또는 패자가 존재하지 않습니다.")
        
        # 승자와 패자가 동일하면 안된다는 조건을 추가할 수 있습니다.
        if winner == loser:
            raise serializers.ValidationError("승자와 패자가 동일할 수 없습니다.")

        # 유효성을 통과한 유저 객체를 데이터에 추가
        data['winner'] = winner
        data['loser'] = loser
        
        return data

    def create(self, validated_data):
        game_result = GameResult.objects.create(
            winner=validated_data['winner'],
            loser=validated_data['loser'],
            winner_score=validated_data['winner_score'],
            loser_score=validated_data['loser_score'],
            game_type=validated_data['game_type'],
            game_date=validated_data['game_date']
        )
        return game_result