<?php

namespace Project\Page;

use Project\BadRequestException;
use Project\UnspecifiedParameter;

class LanguagesColumn extends PageAbstract {
    public function invoke($payload, $arguments) {
        if (!isset($arguments["column_name"])) {
            throw new UnspecifiedParameter("column_name");
        }

        $columns = (new Column($this->di))->invoke(null, null);
        $columnName = urldecode($arguments["column_name"]);

        if (!in_array($columnName, $columns["columns"])) {
            throw new BadRequestException("You have specified the wrong column name.");
        }


        $query = $this->di->getMysql()->prepare("SELECT `${columnName}` FROM `Языки` ORDER BY `N` ASC");
        $query->execute();
        $langs = $query->fetchAll();

        $query = $this->di->getMysql()->prepare("SELECT COUNT(*) AS `count` FROM `Языки`");
        $query->execute();
        $count = $query->fetch();

        return [
            'count' => (int)$count["count"],
            'languages' => $langs
        ];
    }
}
