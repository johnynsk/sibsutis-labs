(function () {
    $('.menu .item').tab();

    let store = {
        columns: null,
    };

    let renderTable = function(data) {
        let table = $('<table class="ui celled table"></table>');

        let thead = $('<thead></thead>');
        let headRow = $("<tr></tr>");
        store.columns.forEach(column => headRow.append($(`<th>${column}</th>`)));
        thead.append(headRow);
        table.append(thead);

        data.forEach(item => {
            let row = $("<tr></tr>");
            store.columns.forEach(column => row.append($(`<td>${column in item ? item[column] : '&dash;'}</td>`)));
            table.append(row);
        });

        return table;
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
                    console.log(url, response);
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

    $('a[data-tab="columns"]').click(function () {
        let resultTable = $('div[data-tab="columns"] .table-data');
        syncColumns(function(response) {
            let container = $('div[data-tab="columns"] .buttons-data');
            container.html("");
            response.columns.forEach(type => {
                let button = $(`<button class="ui button green">${type}</button>`)
                button.click(function () {
                    console.log('click', type);
                    operate.get(`/language/column/${encodeURIComponent(type)}`, function (response) {
                        console.log(response);
                        resultTable.html(renderTable(response.languages));
                    });
                });
                container.append(button);
            });
        });
    });

    $('a[data-tab="excluding"]').click(function () {
        let resultTable = $('div[data-tab="excluding"] .table-data');

        operate.get("/type", function(response) {
            response.types.push('last');
            response.types.unshift('first');

            let container = $('div[data-tab="excluding"] .buttons-data');
            container.html("");
            response.types.forEach(type => {
                let button = $(`<button class="ui button green">${type}</button>`)
                button.click(function () {
                    operate.get(`/language/exclude_by_type/${type}`, function (response) {
                        resultTable.html(renderTable(response.languages));
                    });
                });
                container.append(button);
            });
        });
    });

    $('a[data-tab="companies"]').click(function () {
        let resultTable = $('div[data-tab="companies"] .table-data');

        operate.get("/company", function(response) {
            let container = $('div[data-tab="companies"] .buttons-data');
            container.html("");
            response.companies.forEach(type => {
                let button = $(`<button class="ui button green">${type}</button>`)
                button.click(function () {
                    operate.get(`/language/familiar/${encodeURIComponent(type)}`, function (response) {
                        resultTable.html(renderTable(response.languages));
                    });
                });
                container.append(button);
            });
        });
    });
})();
