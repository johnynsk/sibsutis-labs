<?php

namespace Project\Page;

use Project\Exception\UnspecifiedParameter;

class LanguagesFamiliar extends PageAbstract {
    public function invoke($payload, $arguments) {
        if (!isset($arguments["company_name"])) {
            throw new UnspecifiedParameter("company_name");
        }

        $query = $this->db->prepare("SELECT `Назв` FROM `Языки` WHERE `Тип` IN (SELECT DISTINCT(`Тип`) FROM `Языки` WHERE `Фирма` = ?) ORDER BY `N` ASC");
        $query->execute([urldecode($arguments['company_name'])]);
        $langs = $query->fetchAll();

        return [
            'count' => count($langs),
            'languages' => $langs
        ];
    }
}
