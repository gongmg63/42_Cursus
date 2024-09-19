FROM python:3.12-alpine

RUN apk update && \
	apk add postgresql-client
RUN pip3 install Django \
	djangorestframework-simplejwt \
	django-oauth-toolkit \
	djangorestframework \
	django-cors-headers \
	psycopg2-binary \
	django-environ \
	channels \
	requests \
	daphne \
	pillow \
	pyotp \
	qrcode
	# uvicorn \
# RUN pinstall --upgrade djangorestframework-simplejwt

# RUN django-admin startproject mysite 
# RUN cd /mysite/mysite/ && \
	# sed -i 's/ALLOWED_HOSTS = \[]/ALLOWED_HOSTS = \["*"]/g' settings.py

WORKDIR /volumes/mysite/
COPY init.sh /usr/local/bin/

ENTRYPOINT ["init.sh"]

EXPOSE 8000