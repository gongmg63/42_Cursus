#!/bin/bash
set -e

# PostgreSQL 데이터베이스 생성
psql -U postgres -c "CREATE DATABASE $DB_NAME;"

# 사용자 생성
psql -U postgres -c "CREATE USER $DB_USER WITH ENCRYPTED PASSWORD '$DB_USER_PASSWORD';"
psql -U postgres -c "ALTER DATABASE $DB_NAME OWNER TO $DB_USER;"
