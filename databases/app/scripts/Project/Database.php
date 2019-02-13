<?php

namespace Project;
use \PDO;

class Database extends PDO {
    public function __construct($hostname, $user, $password, $database) {
        parent::__construct("mysql:host=${hostname};dbname=${database};charset=utf8", $user, $password);
        $this->setAttribute(self::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $this->setAttribute(self::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    }
}
