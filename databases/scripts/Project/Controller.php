<?php

namespace Project;

use Project\Page\PageAbstract;

class Controller {
    private $controllers = [];
    public function __construct() {
    }

    public function register($regexp, $methods, Page\PageAbstract $controller) {
        array_push($this->controllers, [
            'regexp' => $regexp,
            'methods' => $methods,
            'invoker' => $controller
            ]);
    }

    /**
     * @param $path
     * @param $method
     * @return object
     * @throws UnknownInvokerException
     */
    public function getInvokerAndArguments($path, $method)
    {
        foreach ($this->controllers as $controller) {
            if (!preg_match($controller['regexp'], $path, $matches)) {
                continue;
            }

            if (!in_array($method, $controller['methods'])) {
                continue;
            }

            return [$controller['invoker'], $matches];
        }

        throw new UnknownInvokerException("You have specified the wrong URL. The handler does not exists.");
    }
}
