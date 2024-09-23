from rest_framework.permissions import IsAuthenticated
from rest_framework.generics import get_object_or_404
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework import status
from .serializers import AddGameResultSerializer, GameResultSerializer
from .models import GameResult
from user.models import User

class AddGameResultView(APIView):
    def post(self, request):
        serializer = AddGameResultSerializer(data=request.data)
        
        if serializer.is_valid():
            winner = serializer.validated_data.get('winner')  # 'winner' 필드를 문자열로 처리
            loser = serializer.validated_data.get('loser')  # 'loser' 필드를 문자열로 처리
            if request.user.id == winner.id:
                return
            # 유효성 검사가 통과되면 게임 결과 생성
            game_result = serializer.save()

            # 승리자와 패배자의 승리 수 및 패배 수 업데이트
            winner.wins += 1
            loser.losses += 1
            # 변경 사항을 저장합니다.
            winner.save()
            loser.save()
            
            return Response({
                'message': 'Game result added successfully',
                'game_result': {
                    'winner': game_result.winner.username,
                    'loser': game_result.loser.username,
                    'winner_score': game_result.winner_score,
                    'loser_score': game_result.loser_score,
                    'game_type': game_result.game_type,
                    'game_date': game_result.game_date,
                }
            }, status=status.HTTP_201_CREATED)
        
        # 유효성 검사가 실패하면 오류 반환
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    
class GetGameResultView(APIView):
    permission_classes = [IsAuthenticated]  # JWT 인증된 사용자만 접근 가능

    def get(self, request):
        user = request.user  # 현재 인증된 사용자

        # 사용자가 플레이한 모든 게임을 winner 또는 loser로 조회
        game_results = GameResult.objects.filter(winner=user).union(
            GameResult.objects.filter(loser=user)
        )
        # game_results = list(GameResult.objects.filter(winner=user)) + list(GameResult.objects.filter(loser=user))


        # 시리얼라이저를 사용하여 결과 직렬화
        serializer = GameResultSerializer(game_results, many=True)
        
        return Response(serializer.data, status=status.HTTP_200_OK)
        
class GetGameResultByNicknameView(APIView):
    # permission_classes = [IsAuthenticated]  # JWT 인증된 사용자만 접근 가능

    def get(self, request, nickname):
        # nickname으로 User 조회
        user = get_object_or_404(User, nickname=nickname)  # 닉네임이 없으면 404 반환

        # 사용자가 플레이한 모든 게임을 winner 또는 loser로 조회
        game_results = GameResult.objects.filter(winner=user).union(
            GameResult.objects.filter(loser=user)
        )
        
        # 게임 결과를 시리얼라이저로 직렬화
        serializer = GameResultSerializer(game_results, many=True)
        
        return Response(serializer.data, status=status.HTTP_200_OK)