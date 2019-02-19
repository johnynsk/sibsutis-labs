<?php

define('ROOT_DIR', dirname(__DIR__));
define('SCRIPTS_DIR', __DIR__);

/**
 * PSR-0 autoload
 */
spl_autoload_register(function ($className) {
    $base_dir = __DIR__;

    $file = __DIR__ . '/' . str_replace(['\\', '_'], '/', $className) . '.php';

    if (file_exists($file)) {
        require $file;
    }
});

define('MIGRATIONS_PATH', implode([ROOT_DIR, 'migrations'], DIRECTORY_SEPARATOR));
define('TEMPLATES_PATH', implode([ROOT_DIR, 'templates'], DIRECTORY_SEPARATOR));

