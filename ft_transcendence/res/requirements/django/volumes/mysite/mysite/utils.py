import os
import random
from uuid import uuid4
from django.utils import timezone
from django.conf import settings

def uuid_name_upload_to(instance, filename):
	app_label = instance.__class__._meta.app_label #앱 별로
	cls_name = instance.__class__.__name__.lower() #모델 별로
	# ymd_path = timezone.now().strftime('%Y/%m/%d') #업로드하는 년/월/일 별로
	uuid_name = uuid4().hex # 랜덤한 문자열
	extension = os.path.splitext(filename)[-1].lower()
	return '/'.join([
		app_label,
		cls_name,
		# ymd_path,
		# uuid_name[:2],
		uuid_name + extension,
	])

def get_random_image_path():
    media_root = os.path.join(settings.MEDIA_ROOT, 'images')
    image_files = [f for f in os.listdir(media_root) if os.path.isfile(os.path.join(media_root, f))]
    if not image_files:
        return None
    random_image = random.choice(image_files)
    return os.path.join('/images', random_image)
