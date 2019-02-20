(function () {
    $('.menu .item').tab();

    let store = {
        columns: null,
    };

    let renderTable = function (data) {
        let table = $('<table class="ui celled table"></table>');

        let thead = $('<thead></thead>');
        let headRow = $("<tr></tr>");
        store.columns.forEach(column => headRow.append($(`<th>${column}</th>`)));
        thead.append(headRow);
        table.append(thead);

        data.forEach(item => {
            let row = $("<tr></tr>");
            store.columns.forEach(column => row.append($(`<td>${column in item ? item[column] : '&mdash;'}</td>`)));
            table.append(row);
        });

        return table;
    };

    let bindRenderBlock = function (tabName, optionsEndpoint, mapper, filteringEndpoint, tableMapper, buttonText) {
        $(`a[data-tab="${tabName}"]`).click(function () {
            let resultTable = $(`div[data-tab="${tabName}"] .table-data`);

            operate.get(optionsEndpoint, function (response) {
                let records = mapper(response);

                let container = $(`div[data-tab="${tabName}"] .buttons-data`);
                container.html("");

                records.forEach((item, order) => {
                    container.append($(`<div class="field">
    <div class="ui checkbox radio">
        <input type="radio" name="${tabName}" value="${item}" id="${tabName}_${order}">
        <label for="${tabName}_${order}">${item}</label>
    </div>
</div>`));
                });

                let button = $(`<button class="ui button green">${buttonText}</button>`)
                button.click(function () {
                    let type = $(`input[name=${tabName}]:checked`).val();

                    operate.get(`${filteringEndpoint}${type}`, function (response) {
                        resultTable.html(renderTable(tableMapper(response)));

                        if ('count' in response) {
                            $(`div[data-tab="${tabName}"] h3.counter`).html(`Found ${response.count} items:`)
                        }
                    });
                });

                container.append(button);
            });
        });
    };

    let operate = function () {
        let notificate = function () {

        };

        let load = function () {

        };

        let public = {
            get: function (url, success, fail) {
                load();
                $.get(url, null, function (response) {
                    if ('error' in response) {
                        if (typeof fail != 'undefined') {
                            return fail(response);
                        }
                    }

                    if (typeof success != 'undefined') {
                        return success(response);
                    }
                }, 'json')
            },
            post: function (url, payload, success, fail) {
                load();
                $.post(url, JSON.stringify(payload), function (response) {
                    if ('error' in response) {
                        if (typeof fail != 'undefined') {
                            return fail(response);
                        }
                    }

                    if (typeof success != 'undefined') {
                        success(response);
                    }
                }, 'json')
            }
        };

        return public;
    }();


    var syncColumns = function (callback) {
        operate.get("/column", function (response) {
            store.columns = response.columns;
            if (typeof callback !== 'undefined') {
                callback(response);
            }
        });
    };
    syncColumns();

    $('button[data-action="columns-refresh"]').click(syncColumns);

    $('button[data-action="recreate"]').click(function () {
        operate.post("/init", {structure: true});
    });

    $('button[data-action="fill"]').click(function () {
        operate.post("/init", {data: true});
    });

    $('button[data-action="recreate-fill"]').click(function () {
        operate.post("/init", {data: true, structure: true});
    });

    $('button[data-action="reload-all"]').click(function () {
        operate.get("/language", function (response) {
            $('div[data-tab="all-records"] .table-data').html(renderTable(response.languages));
        });
    });

    bindRenderBlock("excluding", "/type", response => {
        let result = response.types;
        result.unshift("first");
        result.push("last");
        return result;
    }, "/language/exclude_by_type/", item => item.languages, 'Exclude type');

    bindRenderBlock("companies", "/company", response => response.companies,
        "/language/familiar/", item => item.languages, 'Show familiar languages');

    bindRenderBlock("columns", "/column", response => store.columns = response.columns,
        "/language/column/", item => item.languages, 'Show only one column');
})();
