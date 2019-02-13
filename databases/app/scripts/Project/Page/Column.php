<?php

namespace Project\Page;

class Column extends PageAbstract {
    public function invoke($payload, $arguments) {
        $query = $this->di->getMysql()->prepare("SELECT COLUMN_NAME FROM information_schema.columns
WHERE table_schema='mydb' AND table_name='Языки'");
        $query->execute();
        $columns = array_map(function($item) {
            return reset(array_values($item));
        }, $query->fetchAll());

        return [
            'count' => count($columns),
            'columns' => $columns
        ];
    }
}
