var $ = require("jquery");
var _ = require("lodash");

var FormBuilder = function ($container, config, values) {
    var that = {};
    var form = null;
    var changed = false;

    (function() {
        form = $('<form class="ui form"/>');

        if (!config.fields || !Object.keys(config.fields).length) {
            config.fields = {};
        }
    })();

    var addRow = function ($values, field) {
         return function () {
             $values.append('<input type="text" data-group-name="' + field.name + '" placeholder="' + field.placeholder + '" value="">')
         };
    }

    var renderRow = function (field, value) {
        if (!field.placeholder) {
            field.placeholder = field.label
        }

        value = value ? value : null

        if (field.type == "string") {
            return $('<div class="field"><label>' + field.label + '</label><input type="text" data-name="' + field.name + '" placeholder="' + field.placeholder + '" value="' + value +'"></div>')
        }

        if (field.type == "text") {
            return $('<div class="field"><label>' + field.label + '</label><textarea data-name="' + field.name + '">' + value + '</textarea></div>')
        }

        if (field.type == "string[]") {
            $item = $('<div class="field"><label>' + field.label + '</label><div class="values"></div></div>')
            $values = $item.find('.values')

            if (value && value.length) {
                for (offset in value) {
                    $values.append('<input type="text" data-group-name="' + field.name + '" placeholder="' + field.placeholder + '" value="' + value[offset] + '">')
                }
            } else {
                $values.append('<input type="text" data-group-name="' + field.name + '" placeholder="' + field.placeholder + '" value="">')
            }

            $addButton = $('<div class="ui icon button" data-content="Добавить строку"><i class="add icon"></i> Добавить строку</div>')
            $addButton.click(addRow($values, field));

            $item.append($addButton)
            return $item
        }
    }

    var buildResult = function () {
        var result = _.clone(values);

        for (fieldKey in config.fields) {
            var field = config.fields[fieldKey];
            var value = null;
            field.name = field.name ? field.name : fieldKey
            field.type = field.type ? field.type : "string"

            if (field.type == "string[]") {
                var value = [];
                var founded = form.find('[data-group-name="' + field.name + '"]')
                    .each((index, el) => $(el).val().length ? value.push($(el).val()) : null);
            }

            if (field.type == "string" || field.type == "text") {
                value = form.find('[data-name="' + field.name + '"]').val();
            }

            result[fieldKey] = value;
            if (result[fieldKey] != values[fieldKey]) {
                changed = true;
            }
        }

        return Promise.resolve(result);
    }

    that.render = function () {
        return new Promise((resolve, reject) => {
            var result = $('<div />');

            for (fieldKey in config.fields) {
                var field = config.fields[fieldKey]
                field.name = field.name ? field.name : fieldKey
                field.type = field.type ? field.type : "string"
                var value = values ? values[fieldKey] ? values[fieldKey] : [] : null
                var item = renderRow(field, value)

                result.append(item)
            }

            form.html(result)

            controls = $('<div/>');
            var saveButton = $('<button class="ui primary button">Сохранить</button>');
            saveButton.click(() => {
                var result = buildResult();

                if (result) {
                    resolve(result);
                }
            });
            controls.append(saveButton);

            var cancelButton = $('<button class="ui button">Отменить</button>');
            cancelButton.click(() => {
                reject(Error('changes was discarded'))
            })
            controls.append(cancelButton);

            form.append(controls);
            $container.html(form);
        });
    }

    that.hasChanged = function () {
        return changed;
    }

    that.getNewValue = function () {
        return
    }

    return that
}

module.exports = FormBuilder;
