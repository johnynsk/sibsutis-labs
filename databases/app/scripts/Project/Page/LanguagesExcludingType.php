<?php

namespace Project\Page;

use Project\UnspecifiedParameter;

class LanguagesExcludingType extends PageAbstract {
    public function invoke($payload, $arguments) {
        if (!isset($arguments["exclude_type"])) {
            throw new UnspecifiedParameter("exclude_type");
        }

        $type = $arguments['exclude_type'];

        if ($type == 'first') {
            $query = $this->di->getMysql()->prepare("SELECT * FROM `Языки` WHERE `Тип` != (SELECT DISTINCT(`Тип`) FROM `Языки` ORDER BY `Тип` ASC LIMIT 1) ORDER BY `N` ASC");
            $query->execute();
        } else if ($type = 'last') {
            $query = $this->di->getMysql()->prepare("SELECT * FROM `Языки` WHERE `Тип` != (SELECT DISTINCT(`Тип`) FROM `Языки` ORDER BY `Тип` DESC LIMIT 1) ORDER BY `N` ASC");
            $query->execute();
        } else {
            $query = $this->di->getMysql()->prepare("SELECT * FROM `Языки` WHERE `Тип` != ? ORDER BY `N` ASC");
            $query->execute([$type]);
        }

        $langs = $query->fetchAll();

        return [
            'count' => count($langs),
            'languages' => $langs
        ];
    }
}
