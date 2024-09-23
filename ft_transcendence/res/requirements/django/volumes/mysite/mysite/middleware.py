class LogAllRequestsMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        # 요청 메서드, URL, 헤더, 바디를 출력
        print(f"Method: {request.method}")
        print(f"Path: {request.get_full_path()}")
        # print(f"Headers: {request.headers}")

        # POST, PUT 등의 경우 요청 바디 출력 (바디가 클 경우 주의 필요)
        if request.method in ['POST', 'PUT', 'PATCH']:
            print(f"Body: {request.body.decode('utf-8', errors='ignore')}")

        response = self.get_response(request)

        # 응답 코드도 출력하고 싶다면 여기에 추가 가능
        print(f"Response status: {response.status_code}")
        
        return response

