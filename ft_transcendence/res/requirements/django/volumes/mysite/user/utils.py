from rest_framework.exceptions import APIException

class CustomValidationError(APIException):
    status_code = 400  # 기본 상태 코드, 여기서 기본적으로 400 Bad Request를 사용
    default_detail = 'A validation error occurred.'
    default_code = 'invalid'

    def __init__(self, detail=None, code=None):
        if detail is not None:
            self.detail = detail
        if code is not None:
            self.default_code = code
        if isinstance(code, int):
            self.status_code = code