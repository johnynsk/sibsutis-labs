FROM php:7.2-fpm
RUN apt-get update
RUN apt-get install -y \
    libssl-dev

RUN docker-php-ext-configure pdo_mysql --with-pdo-mysql \
        && docker-php-ext-install pdo_mysql
