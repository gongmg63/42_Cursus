#!/bin/bash
set -e

if [ ! -d /var/lib/mysql/$DATABASE ]; then
    mariadb-install-db
fi

service mariadb start

while ! mysqladmin ping --silent; do
    echo Wait mysql..
    sleep 5
done

if ! mysql -e "USE $DATABASE;" 2>/dev/null; then
    echo "Creating database $DATABASE..."
    mysql -e "CREATE DATABASE $DATABASE;"
else
    echo "Database $DATABASE already exists."
fi

if ! mysql -e "SELECT User FROM mysql.user WHERE User='$MDB_USER';" | grep -q "$MDB_USER"; then
    echo "Creating user $MDB_USER..."
    mysql -e "CREATE USER '$MDB_USER'@'%' IDENTIFIED BY '$USER_PASSWORD';"
    mysql -e "GRANT ALL PRIVILEGES ON $DATABASE.* TO '$MDB_USER'@'%';"
    mysql -e "FLUSH PRIVILEGES;"
else
    echo "User $MDB_USER already exists."
fi

service mariadb stop

# Start MariaDB server
exec mysqld_safe
