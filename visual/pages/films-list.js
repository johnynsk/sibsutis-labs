var $ = require("jquery");

var filmsListPage = ($container) => {
    var that = {}

	var renderTable = films => {
		table = $('<table class="ui celled table"></table>');
        table.append('<thead><tr><th>id</th><th>Название</th><th>Год</th></tr></thead>');
        tbody = $('<tbody>');

        films.forEach(film => tbody.append('<tr><td>' + film._id + '</td><td><a href="#/films/' + film._id + '">' + film.title + '</a></td><td>' + film.year + '</td></tr>'));

        table.append(tbody);
		return table;
	}

    that.render = (films) => {
        var addButton = $('<div class="ui left labeled button" tabindex="0"><a class="ui basic label">Добавить</a><div class="ui icon button"><i class="fork icon"></i></div></div>')
        addButton.click(() => {
            window.location.hash = "#/films/add"
        })

        $container.append(addButton);
    	$container.append(renderTable(films));
    }

    return that;
}

module.exports = filmsListPage;
