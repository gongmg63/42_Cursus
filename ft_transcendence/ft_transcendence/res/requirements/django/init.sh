#!/bin/sh

set -e

until psql -h "$DB_HOST" -p "$DB_PORT" -U "$DB_USER" -d "$DB_NAME" -c "SELECT 1;" > /dev/null 2>&1; do
  echo "Waiting for PostgreSQL..."
  sleep 3
done

python manage.py makemigrations user
python manage.py makemigrations game

python manage.py migrate
python manage.py loaddata users.json

# python manage.py collectstatic

# python manage.py runserver 0.0.0.0:8000
# uvicorn mysite.asgi:application --host 0.0.0.0 --port 8000
# daphne -p 8000 mysite.asgi:application
# daphne -u /tmp/daphne.sock -p 8000 --bind 0.0.0.0 mysite.asgi:application
daphne -b 0.0.0.0 -p 8000 mysite.asgi:application
