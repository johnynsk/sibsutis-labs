<?php

namespace Project\Page;

class Root extends PageAbstract {
    public function invoke($payload, $arguments) {
        include TEMPLATES_PATH . "/index.html";
    }
}
