<?php

namespace Project\Page;

use Project\Exception\BadRequest;
use Project\Exception\UnspecifiedParameter;

class LanguagesColumn extends PageAbstract {
    public function invoke($payload, $arguments) {
        if (!isset($arguments["column_name"])) {
            throw new UnspecifiedParameter("column_name");
        }

        $columns = (new Column($this->db))->invoke(null, null);
        $columnName = urldecode($arguments["column_name"]);

        if (!in_array($columnName, $columns["columns"])) {
            throw new BadRequest("You have specified the wrong column name.");
        }


        $query = $this->db->prepare("SELECT `${columnName}` FROM `Языки` ORDER BY `N` ASC");
        $query->execute();
        $langs = $query->fetchAll();

        $query = $this->db->prepare("SELECT COUNT(*) AS `count` FROM `Языки`");
        $query->execute();
        $count = $query->fetch();

        return [
            'count' => (int)$count["count"],
            'languages' => $langs
        ];
    }
}
