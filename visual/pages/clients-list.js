var $ = require("jquery");

var ClientsListPage = function ($container) {
    var that = {};

    var renderTable = clients => {
		table = $('<table class="ui celled table"></table>');
        table.append('<thead><tr><th>id</th><th>Название</th></tr></thead>');
        tbody = $('<tbody>');

        clients.forEach(client => tbody.append('<tr><td>' + client._id + '</td><td><a href="#/clients/' + client._id + '">' + client.last_name + ' ' + client.first_name  + '</a></td></tr>'));

        table.append(tbody);
		return table;
	}

    that.render = (clients) => {
        var addButton = $('<div class="ui left labeled button" tabindex="0"><a class="ui basic label">Добавить</a><div class="ui icon button"><i class="fork icon"></i></div></div>')
        addButton.click(() => {
            window.location.hash = "#/clients/add"
        })

        $container.append(addButton);
    	$container.append(renderTable(clients));
    }

    return that;
};

module.exports = ClientsListPage
