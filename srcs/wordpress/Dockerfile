# wordpress / Dockerfile

FROM debian:bookworm

# Install Wordpress, Php
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install \
	php8.2 \
	php-fpm \
	php-cli \
	wget \
	curl \
	php-mysql \
	php-mbstring \
	php-xml \
	sendmail && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy configuration files
COPY ./www.conf /etc/php/8.2/fpm/pool.d/www.conf

# Set environment variables
# ENV WORDPRESS_DB=wordpress_db
# ENV USER=mkong
# ENV PASSWORD=password
# ENV WORDPRESS_DB_HOST=172.17.0.2

# Start wordpress server
CMD ["php-fpm8.2", "-F"]

# Expose wordpress port
EXPOSE 9000
