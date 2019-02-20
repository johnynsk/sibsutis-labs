FROM php:fpm

RUN docker-php-ext-configure pdo_mysql --with-pdo-mysql \
        && docker-php-ext-install pdo_mysql
