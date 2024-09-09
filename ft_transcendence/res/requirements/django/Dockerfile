FROM python:3.12-alpine

RUN apk update && \
	apk add postgresql-client
RUN pip3 install Django
RUN pip install psycopg2-binary \
	djangorestframework \
	uvicorn \
	requests \
	django-oauth-toolkit \
	djangorestframework-simplejwt \
	django-cors-headers \
	pillow \
	channels
# RUN django-admin startproject mysite 
# RUN cd /mysite/mysite/ && \
	# sed -i 's/ALLOWED_HOSTS = \[]/ALLOWED_HOSTS = \["*"]/g' settings.py

WORKDIR /volumes/mysite/
COPY init.sh /usr/local/bin/

ENTRYPOINT ["init.sh"]

EXPOSE 8000