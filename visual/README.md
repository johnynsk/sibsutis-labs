# Сборка и установка

Потребуется nodejs 9.2.0

    npm install
    # затем отвечаем на все вопросы в процессе распаковки
    cd semantic
    ../node_modules/.bin/gulp build # это если не был глобально установлен gulp
    cd ..
    ./node_modules/.bin/electron . # запуск приложения
