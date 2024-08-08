# NGINX / Dockerfile

FROM debian:bookworm

# Install NGINX
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install nginx \
    openssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/server_pkey.pem -out /etc/ssl/certs/server.crt -subj "/C=/ST=/L=/O=/CN=" && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy default
COPY ./conf/default /etc/nginx/sites-available/default

# Start NGINX server
ENTRYPOINT ["nginx", "-g", "daemon off;"]

# Expose NGINX port
EXPOSE 443
