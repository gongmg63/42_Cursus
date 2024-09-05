#!/bin/sh

set -e

sleep 5

python manage.py makemigrations user
python manage.py makemigrations game

python manage.py migrate

# python manage.py collectstatic

python manage.py runserver 0.0.0.0:8000
# uvicorn mysite.asgi:application --host 0.0.0.0 --port 8000
