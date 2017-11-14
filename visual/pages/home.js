var $ = require("jquery");
var collections = require('.././collections/all')

var HomePage = function ($container) {
	var that = {};

    var renderMeasure = (label, value, color) => {
        var measure = $('<div class="ui inverted statistic"><div class="value"></div><div class="label"></div></div>');

        measure.find('.value').html(value);
        measure.find('.label').html(label);

        if (color) {
            measure.addClass(color);
        }

        return measure;
    }

	that.render = function () {
		measures = $('<div class="ui inverted segment"></div>')
        collections().films().count().then(count => measures.append(renderMeasure("Фильмов", count, 'olive')))
        collections().clients().count().then(count => measures.append(renderMeasure("Клиентов", count, 'teal')))
        collections().tenants().count().then(count => measures.append(renderMeasure("Арендовано", count, 'green')))
        collections().tenants().count({active: true, expires: {$lt: new Date()}}).then(count => measures.append(renderMeasure("Просрочено", count, 'red')))
  	    $container.html(measures);
	}

	return that;
};

module.exports = HomePage;
