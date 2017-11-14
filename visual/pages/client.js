var formBuilder = require('./form-builder')
var $ = require("jquery");

var Client = function (client, $container) {
    var that = {};

    that.view = function () {
        $grid = $('<div class="ui grid"><div class="sixteen wide column controls"></div><div class="sixteen wide column title"><h1 class="ui header"></h1></div><div class="six wide column poster"></div><div class="ten wide column info"></div><div class="sixteen wide column address"></div><div class="sixteen wide column description"></div></div>');
        $controls = $grid.find('.controls')
        $edit = $('<div class="ui buttons"><button class="ui button negative remove">Удалить</button><div class="or"></div><button class="ui button edit">Редактировать</button></div>')
        $controls.append($edit);

        $edit.find('.remove').click(() => {
            var modal = $('<div class="ui modal"><i class="close icon"></i><div class="header">Удалить фильм?</div><div class="description">Будет удален фильм ' + film.title + '</div></div><div class="actions"><div class="ui button">Отмена</div><div class="ui button">OK</div></div></div>');

            modal.modal('Behavoa', console.log, console.warn);
            $controls.append(modal);
        })

        $edit.find('.edit').click(() => {
            window.location.hash = "#/clients/" + client._id + "/edit";
        })

        $poster = $grid.find(".poster");
        $info = $grid.find(".info");
        $description = $grid.find(".description");
        $address = $grid.find(".address")
        $title = $grid.find(".title h1");

        $title.html(client.last_name + ' ' + client.first_name);
        $address.html(client.address)

        if (client.description) {
            $description.text(client.description);
        } else {
            $description.html('<i>Нет описания</i>');
            $description.addClass('warning');
        }

        return $grid;
    };

    var config = {
        fields: {
            first_name: {
                label: "Имя"
            },
            last_name: {
                label: "Фамилия"
            },
            address: {
                label: "Адрес",
                type: "text"
            },
            description: {
                label: "Комментарий",
                type: "text"
            }
        }
    }

    that.edit = function (id) {
        return formBuilder($container, config, client).render();
    };

    return that;
}

module.exports = Client;
