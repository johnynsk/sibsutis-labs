<?php

namespace Project\Page;
use Project\Database;

abstract class PageAbstract {
    /**
     * @var Database
     */
    protected $db;

    private $headers = [];

    public function __construct(Database $db) {
        $this->db = $db;
    }

    abstract public function invoke($payload, $arguments);

    protected function setHeader($header) {
        $this->headers[] = $header;

        return $this;
    }

    public function getHeaders() {
        return $this->headers;
    }
};
