import requests
import datetime
import jwt

from django.shortcuts import redirect
from django.conf import settings
from django.http import JsonResponse
from urllib.parse import urlencode

from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework_simplejwt.tokens import RefreshToken
from rest_framework.permissions import IsAuthenticated
from rest_framework.generics import get_object_or_404
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework import status
from urllib.parse import urlencode

from .models import User
from .serializers import UserSerializer, AddFriendSerializer, FriendSerializer
from mysite.utils import get_random_image_path

def Oauth(request):
    auth_url = f"https://api.intra.42.fr/oauth/authorize?client_id={settings.INTRA_42_CLIENT_ID}&redirect_uri={settings.INTRA_42_REDIRECT_CALLBACK_URI}&response_type=code"
    return JsonResponse({'redirect_url': auth_url})

def OauthCallback(request):
    code = request.GET.get('code')
    if not code:
        return JsonResponse({'error': 'No code provided'}, status=400)

    # 액세스 토큰 요청
    token_url = "https://api.intra.42.fr/oauth/token"
    data = {
        'grant_type': 'authorization_code',
        'client_id': settings.INTRA_42_CLIENT_ID,
        'client_secret': settings.INTRA_42_CLIENT_SECRET,
        'code': code,
        'redirect_uri': settings.INTRA_42_REDIRECT_CALLBACK_URI,
    }
    response = requests.post(token_url, data=data)
    if response.status_code != 200:
        return JsonResponse({'error': 'Failed to obtain access token'}, status=400)

    access_token = response.json().get('access_token')
    
    # 사용자 정보 요청
    user_url = "https://api.intra.42.fr/v2/me"
    headers = {'Authorization': f'Bearer {access_token}'}
    user_response = requests.get(user_url, headers=headers)
    if user_response.status_code != 200:
        return JsonResponse({'error': 'Failed to fetch user data'}, status=400)

    user_data = user_response.json()
    oauth_user_id = user_data.get('id')  # OAuth 제공자에서 제공하는 사용자 ID
    profile = user_data.get('image_url')
    email = user_data.get('email')

    # 여기에서 사용자 데이터를 처리하고 로그인 로직을 구현합니다.
    user, created = User.objects.get_or_create(oauthid=oauth_user_id)
    
    user.is_active = True
    # 새 유저인 경우 추가 정보 저장
    if created:
        user.oauthid = oauth_user_id
        user.nickname = user_data.get('login')
        user.email = email
        if profile:
            user.profile = profile
        else:
            user.profile = "/images/Retriever.jpeg"  # 기본 이미지 URL 설정

    user.save()
    # JWT 토큰 생성
    refresh = RefreshToken.for_user(user)
    access_token = str(refresh.access_token)

    # 리다이렉트할 URL에 쿼리 파라미터로 토큰 추가
    redirect_url = "https://127.0.0.1"
    params = {
        'access_token': access_token,
        'refresh_token': str(refresh),
        'oauthid': user.oauthid,
        'nickname': user.nickname,
    }

    # 파라미터를 URL로 인코딩 후 리다이렉트
    url_with_params = f"{redirect_url}?{urlencode(params)}"
    return redirect(url_with_params)


class UserAPI(APIView):
    permission_classes = [IsAuthenticated]  # JWT 인증된 사용자만 접근 가능
	# GET : 내 정보 조회
    def get(self, request):
        user = request.user  # JWT로 인증된 사용자
        serializer = UserSerializer(user)  # 시리얼라이저로 사용자 정보 직렬화
        return Response(serializer.data, status=status.HTTP_200_OK)
    
	# PATCH : 내 정보 수정
    def patch(self, request):
        user = request.user
        serializer = UserSerializer(user, data=request.data, partial=True)  # 부분 업데이트를 허용
        if serializer.is_valid():
            serializer.save()  # 정보 저장
            return Response(serializer.data, status=status.HTTP_200_OK)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    
	# DELETE : 내 계정 삭제
    def delete(self, request):
        user = request.user
        user.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)

# GET : 닉네임을 통해 유저 정보 확인
@api_view(['GET'])
def OtherUserInfo(request, nickname):
	user = get_object_or_404(User, nickname=nickname) #일치하는 nickname이 없으면 404
	serializer = UserSerializer(user)
	return Response(serializer.data, status=status.HTTP_200_OK)


class FriendAPIView(APIView):
    permission_classes = [IsAuthenticated]  # 인증된 사용자만 접근 가능
    
    # POST : 친구 추가
    def post(self, request):
        # 현재 로그인된 사용자 가져오기
        current_user = request.user  
        
        serializer = AddFriendSerializer(data=request.data)
        if serializer.is_valid():
            # 친구 추가 로직 실행
            friend = serializer.update(current_user, serializer.validated_data)

            friend_serializer = FriendSerializer(friend)
            return Response({
                "message": "친구가 성공적으로 추가되었습니다.",
                "friend": friend_serializer.data # 추가된 친구 정보
            }, status=status.HTTP_200_OK)
        
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    
    # DELETE : 친구 삭제
    def delete(self, request):
        # 현재 로그인한 사용자 가져오기
        current_user = request.user
        
        # 요청 데이터에서 친구의 OAuthID 또는 닉네임 받기 (nickname 사용 예시)
        friend_nickname = request.data.get('nickname')
        
        if not friend_nickname:
            return Response({'error': '친구의 닉네임을 제공해야 합니다.'}, status=status.HTTP_400_BAD_REQUEST)

        # 삭제할 친구 찾기
        try:
            friend = User.objects.get(nickname=friend_nickname)
        except User.DoesNotExist:
            return Response({'error': '해당 닉네임의 친구가 존재하지 않습니다.'}, status=status.HTTP_404_NOT_FOUND)
        
        # 친구 관계 해제
        if friend in current_user.friends.all():
            current_user.friends.remove(friend)
            return Response({'message': '친구가 성공적으로 삭제되었습니다.'}, status=status.HTTP_200_OK)
        else:
            return Response({'error': '해당 사용자는 친구 목록에 없습니다.'}, status=status.HTTP_400_BAD_REQUEST)
