FROM postgres:16-alpine

# 초기화 스크립트 추가
COPY init.sh /docker-entrypoint-initdb.d/
RUN chmod +x /docker-entrypoint-initdb.d/init.sh

EXPOSE 5432