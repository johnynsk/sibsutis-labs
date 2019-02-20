<?php

namespace Project\Page;

class Types extends PageAbstract {
    public function invoke($payload, $arguments) {
        $query = $this->db->prepare("SELECT DISTINCT(`Тип`) FROM `Языки` ORDER BY `Тип` ASC");
        $query->execute();

        $types = array_map(function($type) {
            return reset(array_values($type));
        }, $query->fetchAll());

        return [
            'count' => count($types),
            'types' => $types
        ];
    }
}
