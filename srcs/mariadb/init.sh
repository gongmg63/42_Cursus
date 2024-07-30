#!/bin/bash
set -e

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

if ! mysql -e "SELECT User FROM mysql.user WHERE User='$USER';" | grep -q "$USER"; then
    echo "Creating user $USER..."
    mysql -e "CREATE USER '$USER'@'%' IDENTIFIED BY '$PASSWORD';"
    mysql -e "GRANT ALL PRIVILEGES ON $DATABASE.* TO '$USER'@'%';"
    mysql -e "FLUSH PRIVILEGES;"
else
    echo "User $USER already exists."
fi

# mysql -e "CREATE DATABASE IF NOT EXISTS $DATABASE;"
# mysql -e "CREATE USER '$USER'@'%' IDENTIFIED BY '$PASSWORD';"
# mysql -e "GRANT ALL PRIVILEGES ON $DATABASE.* TO '$USER'@'%';"
# mysql -e "FLUSH PRIVILEGES;"

service mariadb stop

# Start MariaDB server
exec mysqld_safe
