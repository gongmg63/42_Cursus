class LogAllRequestsMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        print(f"Method: {request.method}")
        print(f"Path: {request.get_full_path()}")

        if request.method in ['POST', 'PUT', 'PATCH']:
            print(f"Body: {request.body.decode('utf-8', errors='ignore')}")

        response = self.get_response(request)

        print(f"Response status: {response.status_code}")
        
        return response

