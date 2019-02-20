<?php

namespace Project\Page;

use Project\Exception\UnspecifiedParameter;

class LanguagesExcludingType extends PageAbstract {
    public function invoke($payload, $arguments) {
        if (!isset($arguments["exclude_type"])) {
            throw new UnspecifiedParameter("exclude_type");
        }

        $type = urldecode($arguments['exclude_type']);

        if ($type == 'first') {
            $query = $this->db->prepare("SELECT * FROM `Языки` WHERE `Тип` != (SELECT DISTINCT(`Тип`) FROM `Языки` ORDER BY `Тип` ASC LIMIT 1) ORDER BY `N` ASC");
            $query->execute();
        } else if ($type == 'last') {
            $query = $this->db->prepare("SELECT * FROM `Языки` WHERE `Тип` != (SELECT DISTINCT(`Тип`) FROM `Языки` ORDER BY `Тип` DESC LIMIT 1) ORDER BY `N` ASC");
            $query->execute();
        } else {
            $query = $this->db->prepare("SELECT * FROM `Языки` WHERE `Тип` != ? ORDER BY `N` ASC");
            $query->execute([$type]);
        }

        $langs = $query->fetchAll();

        return [
            'count' => count($langs),
            'languages' => $langs
        ];
    }
}
