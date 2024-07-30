#!/bin/bash
set -e

sleep 1

until mysql -h"mariadb" -u"$USER" -p"$PASSWORD" -e "SHOW DATABASES;" > /dev/null 2>&1; do
  echo "Waiting for MariaDB..."
  sleep 5
done

if ! wp core version --path="$V_PATH" --allow-root; then
	wp core download --path="$V_PATH" --allow-root
	rm "$V_PATH"/wp-config-sample.php
	mv /wp-config.php "$V_PATH"
else
	echo "WordPress is already installed."
fi

if ! wp user get $MDB_USER --path="$V_PATH" --allow-root; then
	wp core install --url="https://127.0.0.1" \
					--title="Inception" \
					--admin_user="$MDB_USER" \
					--admin_password="$USER_PASSWORD" \
					--skip-email --admin_email="hihi@example.com" \
					--path=""$V_PATH"" \
					--allow-root
fi

if ! wp user get guest --path="$V_PATH" --allow-root ; then
	wp user create guest guest@example.com \
					--role=subscriber \
					--user_pass=password \
					--path="$V_PATH" \
					--allow-root
fi

php-fpm8.2 -F
