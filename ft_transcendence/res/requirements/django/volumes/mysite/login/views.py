import requests
import datetime
import jwt

from django.shortcuts import redirect
from django.conf import settings
from django.http import JsonResponse
from rest_framework_simplejwt.tokens import RefreshToken
from .models import User

def oauth(request):
    auth_url = f"https://api.intra.42.fr/oauth/authorize?client_id={settings.INTRA_42_CLIENT_ID}&redirect_uri={settings.INTRA_42_REDIRECT_CALLBACK_URI}&response_type=code"
    return redirect(auth_url)

def oauth_callback(request):
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

    # 여기에서 사용자 데이터를 처리하고 로그인 로직을 구현합니다.
    user, created = User.objects.get_or_create(oauthid=oauth_user_id)
    
    # 새 유저인 경우 추가 정보 저장
    if created:
        user.oauthid = oauth_user_id
        user.nickname = user_data.get('login')
        if profile:
            user.profile = profile
        else:
            user.profile = ' '  # 기본 이미지 URL 설정
        user.save()

    # JWT 생성
    payload = {
        'user_id': user.oauthid,
        'nickname': user.nickname,
        'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=1)  # 토큰 만료 시간
    }
    
    jwt_token = jwt.encode(payload, settings.SECRET_KEY, algorithm='HS256')

    # JWT와 함께 응답 반환
    return JsonResponse({
        'message': 'Login successful',
        'token': jwt_token,
        'user': {
            'oauthid': user.oauthid,
            'nickname': user.nickname
        }
    })
