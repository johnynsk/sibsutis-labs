<?php

namespace Project\Page;

class Languages extends PageAbstract {
    public function invoke($payload, $arguments) {
        $query = $this->db->prepare("SELECT * FROM `Языки` ORDER BY `N` ASC");
        $query->execute();

        $langs = $query->fetchAll();

        return [
            'count' => count($langs),
            'languages' => $langs
        ];
    }
}
