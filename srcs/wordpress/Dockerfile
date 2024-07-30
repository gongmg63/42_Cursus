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
	mariadb-client \
	sendmail && \
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
	chmod +x wp-cli.phar && \
	mv wp-cli.phar /usr/local/bin/wp && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy configuration files
COPY ./www.conf /etc/php/8.2/fpm/pool.d/www.conf
COPY ./init.sh /usr/local/bin/init.sh
COPY ./wp-config.php /

# Start wordpress server
ENTRYPOINT ["/usr/local/bin/init.sh"]

# Expose wordpress port
EXPOSE 9000
