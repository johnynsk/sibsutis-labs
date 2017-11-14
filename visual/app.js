var $ = require("jquery");
var $container = $('.application-body');
var collections = require('./collections/all')
var homePage = require('./pages/home')
var filmsListPage = require('./pages/films-list')
var clientsListPage = require('./pages/clients-list')
var clientPage = require('./pages/client')
var filmPage = require('./pages/film')

$(document).ready(() => {
	$('.visible.example .ui.sidebar').sidebar({context: '.visible.example .bottom.segment'}).sidebar('hide');
	var handleHashChange = function () {
        console.log('hashChange', location.hash);
		if (location.hash.match(/#\/home\/$/) || location.hash.length == 0) {
			homePage($container).render();
			return;
		}

        if (location.hash.match(/#\/films\//)) {
            if (location.hash.match(/#\/films\/$/)) {
				collections().films().getAll().then(films => {
                	filmsListPage($container).render(films);
				});
                return;
            }

            if (location.hash.match(/#\/films\/add$/)) {
                filmPage({}, $container).edit().then((newFilmData) => {
                    collections().films().insert(newFilmData).then(() => {
                        window.history.back(-1)
                    })
                });

                return;
            }

            if (location.hash.match(/#\/films\/([0-9a-zA-Z]+)$/)) {
                var id = location.hash.match(/#\/films\/([0-9a-zA-Z]+)$/);
                collections().films().getOne(id[1]).then((film) => {
                    filmPage(film, $container).view();
                })

                return;
            }

            if (location.hash.match(/#\/films\/([0-9a-zA-Z]+)\/edit$/)) {
                var id = location.hash.match(/#\/films\/([0-9a-zA-Z]+)\/edit$/);
                collections().films().getOne(id[1]).then((film) => {
                    filmPage(film, $container).edit().then((newFilmData) => {
                        collections().films().update(id[1], newFilmData).then(() => {
                            window.history.back(-1)
                        })
                    });
                })


                return;
            }

            if (location.hash.match(/#\/films\/([0-9a-zA-Z]+)\/remove$/)) {
                var id = location.hash.match(/#\/films\/([0-9a-zA-Z]+)\/edit$/);
                collections().films().getOne(id[1]).then((film) => {
                    filmPage(film, $container).remove().then((newFilmData) => {
                        collections().films().update(id[1], newFilmData).then(() => {
                            window.history.back(-1)
                        })
                    });
                })


                return;
            }
        }

        if (location.hash.match(/#\/clients\//)) {
			if (location.hash.match(/#\/clients\/$/)) {
				collections().clients().getAll().then((clients) => {
            		$container.html(clientsListPage($container).render(clients))
				})
				return;
			}

			if (location.hash.match(/#\/clients\/add$/)) {
                clientPage({}, $container).edit().then((newData) => {
                    collections().clients().insert(newData).then((result) => {
                        window.history.back(-1)
                    })
                });

                return;
            }

			if (location.hash.match(/#\/clients\/([0-9a-zA-Z]+)$/)) {
	            var id = location.hash.match(/#\/clients\/([0-9a-zA-Z]+)$/);
                collections().clients().getOne(id[1]).then((client) => {
                    $container.html(clientPage(client, $container).view())
                })

                return;
	        }

			if (location.hash.match(/#\/clients\/([0-9a-zA-Z]+)\/edit$/)) {
	            var id = location.hash.match(/#\/clients\/([0-9a-zA-Z]+)\/edit$/);
                collections().clients().getOne(id[1]).then((client) => {
                    clientPage(client, $container).edit().then((newData, error) => {
						if (error) {
							window.history.back(-1);
							return;
						}

                        collections().clients().update(id[1], newData).then(() => {
                            window.history.back(-1)
                        })
                    });
                })

                return;
	        }
        }

		if (!location.hash.length) {
			return;
			// return processStep();
		}
	};

	window.onhashchange = handleHashChange;
	handleHashChange();
});
