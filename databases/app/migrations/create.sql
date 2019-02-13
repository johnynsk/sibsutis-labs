DROP TABLE IF EXISTS `Языки`;
CREATE TABLE `Языки` (
  `N` int(2) UNSIGNED NOT NULL,
  `Назв` char(12) NOT NULL,
  `Тип` enum('Процед','Объект','Сценарн','') NOT NULL,
  `Фирма` char(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

ALTER TABLE `Языки`
  ADD PRIMARY KEY (`N`);

ALTER TABLE `Языки`
  MODIFY `N` int(2) UNSIGNED NOT NULL AUTO_INCREMENT;
COMMIT;