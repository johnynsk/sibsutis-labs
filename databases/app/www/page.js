(function () {
    $('.menu .item').tab();

    let store = {
        columns: null,
    };

    let renderTable = function(data) {
        let table = $("<table/>");

        let thead = $("<thead/>");
        let headRow = $("<tr/>");
        store.columns.forEach(column => headRow.add($(`<th>${column}</th>`)));
        thead.add(headRow);
        table.add(thead);

        data.forEach(item => {
            let row = $("<tr>");
            store.columns.forEach(column => row.add($(`<tr>${column in item ? item[column] : '&dash;'}</tr>`)));
            table.add(row);
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
                $.get(url, function (response) {
                    if ('error' in response) {
                        return fail();
                    }

                    success();
                })
            },
            post: function (url, payload) {
                load();
                $.post(url, function (response) {
                    if ('error' in response) {
                        return fail();
                    }

                    success();
                })
            }
        };

        return public;
    };

    $.get("/column", function (response) {
        store.columns = response.columns;
    });

    $('button[data-action="recreate"]').click(function () {

    });
})();