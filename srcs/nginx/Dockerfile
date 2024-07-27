# NGINX / Dockerfile

FROM debian:bookworm

# Install NGINX
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install nginx && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy default file
COPY ./default /etc/nginx/sites-available/default
COPY ./server_pkey.pem /etc/ssl/private/
COPY ./server.crt /etc/ssl/certs/

# Set environment variables
# ENV WORDPRESS_HOST=172.17.0.3

# Modify default file
# RUN apt-get -y update && \
# 	apt-get -y upgrade && \
# 	apt-get -y install gettext-base && \
# 	envsubst '${WORDPRESS_HOST}' < /etc/nginx/sites-available/default > ./tmp_default && \
# 	mv ./tmp_default /etc/nginx/sites-available/default && \
# 	apt-get clean && \
# 	rm -rf /var/lib/apt/lists/*


# Start NGINX server
CMD ["nginx", "-g", "daemon off;"]

# Expose NGINX port
EXPOSE 443
