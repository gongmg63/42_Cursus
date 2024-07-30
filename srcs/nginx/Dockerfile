# NGINX / Dockerfile

FROM debian:bookworm

# Install NGINX
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install nginx && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy default, certification file
COPY ./default /etc/nginx/sites-available/default
COPY ./server_pkey.pem /etc/ssl/private/
COPY ./server.crt /etc/ssl/certs/

# Start NGINX server
CMD ["nginx", "-g", "daemon off;"]

# Expose NGINX port
EXPOSE 443
