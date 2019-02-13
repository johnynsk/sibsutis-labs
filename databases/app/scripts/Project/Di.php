<?php

namespace Project;

class Di {
    protected $instances = [];

    public function set($key, $instance) {
        $this->instances[$key] = $instance;
        return $this;
    }

    public function get($key) {
        return $this->instances[$key];
    }

    /**
     * @return Database
     */
    public function getMysql() {
        return $this->get('mysql');
    }
}
