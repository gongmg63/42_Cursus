# mariadb / Dockerfile

FROM debian:bookworm

# Install MariaDB server
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y install mariadb-server && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN chmod -R 755 /var/lib/mysql

# Copy configuration files
COPY ./50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./init.sh /usr/local/bin/init.sh

RUN chmod +x /usr/local/bin/init.sh

# Start MariaDB server
ENTRYPOINT ["/usr/local/bin/init.sh"]

# Expose MariaDB port
EXPOSE 3306
