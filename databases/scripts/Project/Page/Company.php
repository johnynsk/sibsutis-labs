<?php

namespace Project\Page;

class Company extends PageAbstract {
    public function invoke($payload, $arguments) {
        $query = $this->db->prepare("SELECT DISTINCT(`Фирма`) FROM `Языки` ORDER BY `Фирма` ASC");
        $query->execute();
        $columns = array_map(function($item) {
            return reset(array_values($item));
        }, $query->fetchAll());

        return [
            'count' => count($columns),
            'companies' => $columns
        ];
    }
}
