#!/bin/bash
set -e

service mariadb start

while ! mysqladmin ping --silent; do
    sleep 1
done

mysql -e "CREATE DATABASE IF NOT EXISTS $DATABASE;"
mysql -e "CREATE USER '$USER'@'%' IDENTIFIED BY '$PASSWORD';"
mysql -e "GRANT ALL PRIVILEGES ON $DATABASE.* TO '$USER'@'%';"
mysql -e "FLUSH PRIVILEGES;"

service mariadb stop

# Start MariaDB server
exec mysqld_safe
