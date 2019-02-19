<?php

namespace Project\Page;

use Project\BadRequestException;

class Init extends PageAbstract {
    public function invoke($payload, $arguments) {
        $result = [];

        if (isset($payload["structure"])) {
            $structure = file_get_contents(MIGRATIONS_PATH . "/create.sql");
            $this->di->getMysql()->exec($structure);
            $result["structure"] = true;
        }

        if (isset($payload["data"])) {
            $data = file_get_contents(MIGRATIONS_PATH . "/data.sql");
            $this->di->getMysql()->exec($data);
            $result["data"] = true;
        }

        if (count($result) == 0) {
            throw new BadRequestException("You have to specify the target for migrations.");
        }

        $this->setHeader("HTTP/1.0 201 Created");

        return $result;
    }
}
