var formBuilder = require('./form-builder')
var $ = require("jquery");

var Film = function (film, $container) {
    var that = {};

    that.view = function () {
        $grid = $('<div class="ui grid"><div class="sixteen wide column controls"></div><div class="sixteen wide column title"><h1 class="ui header"></h1></div><div class="six wide column poster"></div><div class="ten wide column info"></div><div class="sixteen wide column description"></div></div>');
        $controls = $grid.find('.controls')
        $edit = $('<div class="ui buttons"><button class="ui button negative remove">Удалить</button><div class="or"></div><button class="ui button edit">Редактировать</button></div>')
        $controls.append($edit);

        $edit.find('.remove').click(() => {
            var modal = $('<div class="ui modal"><i class="close icon"></i><div class="header">Удалить фильм?</div><div class="description">Будет удален фильм ' + film.title + '</div></div><div class="actions"><div class="ui button">Отмена</div><div class="ui button">OK</div></div></div>');

            modal.modal('Behavoa', console.log, console.warn);
            $controls.append(modal);
        })

        $edit.find('.edit').click(() => {
            window.location.hash = "#/films/" + film._id + "/edit";
        })

        $poster = $grid.find(".poster");
        $info = $grid.find(".info");
        $description = $grid.find(".description");
        $title = $grid.find(".title h1");

        $title.html(film.title);

        if (!film.poster) {
            $poster.append('<img src="semantic/examples/assets/images/wireframe/square-image.png">');
        } else {
            $poster.append('<img src="' + film.poster + '" alt="' + film.title + '" />');
        }

        if (film.description) {
            $description.text(film.description);
        } else {
            $description.html('<i>Нет описания</i>');
            $description.addClass('warning');
        }

        console.log($grid);

        $container.html($grid);
    };

    var config = {
        fields: {
            title: {
                label: "Название"
            },
            original_title: {
                label: "Оригинальное название"
            },
            year: {
                label: "Год"
            },
            genres: {
                type: "string[]",
                label: "Жанры"
            },
            directors: {
                type: "string[]",
                label: "Режиссеры"
            },
            duration: {
                label: "Продолжительность (в минутах)"
            },
            countries: {
                type: "string[]",
                label: "Страны"
            },
            actors: {
                type: "string[]",
                label: "Актеры"
            },
            poster: {
                label: "Ссылка на постер"
            },
            description: {
                type: "text",
                label: "Описание"
            }
        }
    }

    that.edit = function (id) {
        return formBuilder($container, config, film).render();
    };

    return that;
}

module.exports = Film;
