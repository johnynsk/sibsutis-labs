<?php

namespace Project\Page;
use Project\Di;

abstract class PageAbstract {
    /**
     * @var Di
     */
    protected $di;

    private $headers = [];

    public function __construct(Di $di) {
        $this->di = $di;
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
