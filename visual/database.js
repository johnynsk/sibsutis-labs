var Database = function () {
    var that = {};
    var config = {
        clients: [
            {
                id: 1,
                first_name: "Иван",
                last_name: "Иванов",
                address: "630099, г. Новосибирск, ул. Ленина, 2"
            }
        ],
        films: [
            {
                id: 1,
                title: "Побег из Шоушенка",
                original_title: "The Shawshank Redemption",
                director: "Фрэнк Дарабонт",
                actors: [
                    "Тим Роббинс",
                    "Морган Фриман",
                    "Боб Гантон",
                    "Уильям Сэдлер",
                    "Клэнси Браун",
                    "Джил Беллоуз",
                    "Марк Ролстон",
                    "Джеймс Уитмор",
                    "Джеффри ДеМанн",
                    "Ларри Бранденбург"
                ],
                duration: 142,
                countries: ["США"],
                year: 1994,
                poster: "https://www.kinopoisk.ru/images/film_big/326.jpg",
                genres: ["драма", "криминал"],
                description: "Успешный банкир Энди Дюфрейн обвинен в убийстве собственной жены и ее любовника. Оказавшись в тюрьме под названием Шоушенк, он сталкивается с жестокостью и беззаконием, царящими по обе стороны решетки. Каждый, кто попадает в эти стены, становится их рабом до конца жизни. Но Энди, вооруженный живым умом и доброй душой, отказывается мириться с приговором судьбы и начинает разрабатывать невероятно дерзкий план своего освобождения."
            },
            {
                id: 2,
                title: "Крестный отец",
                original_title: "The Godfather",
                director: "Фрэнсис Форд Коппола",
                actors: [
                    "Марлон Брандо",
                    "Аль Пачино",
                    "Джеймс Каан",
                    "Роберт Дювалл",
                    "Ричард С. Кастеллано",
                    "Дайан Китон",
                    "Талия Шайр",
                    "Джон Казале",
                    "Аль Леттьери",
                    "Стерлинг Хейден"
                ],
                countries: ["США"],
                year: 1972,
                genres: ["драма", "криминал"],
                poster: "https://www.kinopoisk.ru/images/film_big/325.jpg",
                duration: 175,
                description: "Криминальная сага, повествующая о нью-йоркской сицилийской мафиозной семье Корлеоне. Фильм охватывает период 1945-1955 годов.\nГлава семьи, Дон Вито Корлеоне, выдаёт замуж свою дочь. В это время со Второй мировой войны возвращается его любимый сын Майкл. Майкл, герой войны, гордость семьи, не выражает желания заняться жестоким семейным бизнесом. Дон Корлеоне ведёт дела по старым правилам, но наступают иные времена, и появляются люди, желающие изменить сложившиеся порядки. На Дона Корлеоне совершается покушение."
            },
            {
                id: 3,
                title: "Крестный отец 2",
                original_title: "The Godfather; Part II",
                director: "Фрэнсис Форд Коппола",
                actors: [
                    "Аль Пачино",
                    "Роберт Де Ниро",
                    "Дайан Китон",
                    "Роберт Дювалл",
                    "Джон Казале",
                    "Ли Страсберг",
                    "Майкл В. Гаццо",
                    "Талия Шайр",
                    "Г.Д. Спрэдлин",
                    "Гастоне Москин"
                ],
                countries: ["США"],
                year: 1974,
                genres: ["драма", "криминал"],
                poster: "https://www.kinopoisk.ru/images/film_big/327.jpg",
                duration: 202,
                description: "В центре драмы представители нового поколения гангстерского клана — дона Корлеоне и его сына, для которых не существует моральных преград на пути достижения поставленных целей. Они превращают мафию, построенную по патриархальным, еще сицилийским законам, в весьма прагматичную, жесткую корпорацию, плавно интегрирующуюся в большой бизнес Америки."
            },
            {
                id: 4,
                title: "Темный рыцарь",
                original_title: "The Dark Knight",
                year: 2008,
                countries: ["США", "Великобритания"],
                director: "Фрэнсис Форд Коппола",
                actors: [
                    "Кристиан Бэйл",
                    "Хит Леджер",
                    "Аарон Экхарт",
                    "Мэгги Джилленхол",
                    "Гари Олдман",
                    "Майкл Кейн",
                    "Морган Фриман",
                    "Чин Хань",
                    "Нестор Карбонелл",
                    "Эрик Робертс"
                ],
                genres: ["фантастика", "боевик", "триллер", "криминал", "драма"],
                poster: "https://www.kinopoisk.ru/images/film_big/111543.jpg",
                duration: 152,
                description: "Бэтмен поднимает ставки в войне с криминалом. С помощью лейтенанта Джима Гордона и прокурора Харви Дента он намерен очистить улицы от преступности, отравляющей город. Сотрудничество оказывается эффективным, но скоро они обнаружат себя посреди хаоса, развязанного восходящим криминальным гением, известным испуганным горожанам под именем Джокер."
            },
            {
                id: 5,
                title: "12 разгневанных мужчин",
                original_title: "12 Angry Men",
                year: 1957,
                countries: ["США"],
                director: "Сидни Люмет",
                actors: [
                    "Мартин Болсам",
                    "Джон Фидлер",
                    "Ли Дж. Кобб",
                    "Э. Г. Маршалл",
                    "Джек Клагмен",
                    "Эд Биннс",
                    "Джек Уорден",
                    "Генри Фонда",
                    "Джозеф Суини",
                    "Эд Бегли"
                ],
                genres: ["драма", "криминал"],
                poster: "https://www.kinopoisk.ru/images/film_big/346.jpg",
                duration: 96,
                description: "Юношу обвиняют в убийстве собственного отца, ему грозит электрический стул. Двенадцать присяжных собираются чтобы вынести вердикт: виновен или нет.\nС начала заседания почти все склонились к тому, что виновен, и лишь только один из двенадцати позволил себе усомниться. Счет голосов присяжных по принципу «виновен — невиновен» был 11:1. К концу собрания мнения судей кардинально изменились…"
            },
            {
                id: 6,
                title: "Список Шиндлера",
                original_title: "Schindler's List",
                year: 1993,
                countries: ["США"],
                director: "Стивен Спилберг",
                actors: [
                    "Лиам Нисон",
                    "Бен Кингсли",
                    "Рэйф Файнс",
                    "Кэролайн Гудолл",
                    "Эмбет Дэвидц",
                    "Йонатан Сэгаль",
                    "Малгоша Гебель",
                    "Шмуэль Леви",
                    "Марк Иванир",
                    "Беатриче Макола"
                ],
                genres: ["драма", "биография", "история"],
                poster: "https://www.kinopoisk.ru/images/film_big/329.jpg",
                duration: 195,
                description: "Фильм рассказывает реальную историю загадочного Оскара Шиндлера, члена нацистской партии, преуспевающего фабриканта, спасшего во время Второй мировой войны почти 1200 евреев."
            },
            {
                id: 7,
                title: "Криминальное чтиво",
                original_title: "Pulp Fiction",
                year: 1994,
                countries: ["США"],
                director: "	Квентин Тарантино",
                actors: [
                    "Джон Траволта",
                    "Сэмюэл Л. Джексон",
                    "Брюс Уиллис",
                    "Ума Турман",
                    "Винг Реймз",
                    "Тим Рот",
                    "Харви Кейтель",
                    "Квентин Тарантино",
                    "Питер Грин",
                    "Аманда Пламмер"
                ],
                genres: ["триллер", "комедия", "криминал"],
                poster: "https://www.kinopoisk.ru/images/film_big/342.jpg",
                duration: 154,
                description: "Двое бандитов Винсент Вега и Джулс Винфилд проводят время в философских беседах в перерыве между разборками и «решением проблем» с должниками своего криминального босса Марселласа Уоллеса. Параллельно разворачиваются три истории.\nВ первой из них Винсент присматривает за женой Марселласа Мией и спасает ее от передозировки наркотиков. Во второй рассказывается о Бутче Кулидже, боксере, нанятом Уоллесом, чтобы сдать бой, но обманувшим его. Третья история объединяет первые две — в кафе парочка молодых неудачливых грабителей — Пампкин и Хани Бани делают попытку ограбления, но Джулс останавливает их."
            },
            {
                id: 8,
                title: "Властелин колец: Возвращение Короля",
                original_title: "The Lord of the Rings: The Return of the King",
                year: 2003,
                countries: ["США", "Новая Зеландия"],
                director: "Питер Джексон",
                actors: [
                    "Элайджа Вуд",
                    "Вигго Мортенсен",
                    "Шон Эстин",
                    "Иэн МакКеллен",
                    "Орландо Блум",
                    "Доминик Монахэн",
                    "Билли Бойд",
                    "Энди Серкис",
                    "Миранда Отто",
                    "Бернард Хилл"
                ],
                genres: ["фэнтези", "драма", "приключение"],
                poster: "https://www.kinopoisk.ru/images/film_big/3498.jpg",
                duration: 201,
                description: "Последняя часть трилогии о Кольце Всевластия и о героях, взявших на себя бремя спасения Средиземья. Повелитель сил Тьмы Саурон направляет свои бесчисленные рати под стены Минас-Тирита, крепости Последней Надежды. Он предвкушает близкую победу, но именно это и мешает ему заметить две крохотные фигурки — хоббитов, приближающихся к Роковой Горе, где им предстоит уничтожить Кольцо Всевластия. Улыбнется ли им счастье?"
            },
            {
                id: 9,
                title: "Хороший, плохой, злой",
                original_title: "Il buono, il brutto, il cattivo",
                year: 1966,
                countries: ["Италия", "Испания", "Германия (ФРГ)"],
                director: "Серджио Леоне",
                actors: [
                    "Клинт Иствуд",
                    "Ли Ван Клиф",
                    "Илай Уоллак",
                    "Альдо Джуффре",
                    "Луиджи Пистилли",
                    "Рада Рассимов",
                    "Энцо Петито",
                    "Клаудио Скаркилли",
                    "Джон Барта",
                    "Ливио Лоренцон"
                ],
                genres: ["вестерн"],
                poster: "https://www.kinopoisk.ru/images/film_big/349.jpg",
                duration: 178,
                description: "В разгар гражданской войны таинственный стрелок скитается по просторам Дикого Запада. У него нет ни дома, ни друзей, ни компаньонов, пока он не встречает двоих незнакомцев, таких же безжалостных и циничных.\nПо воле судьбы трое мужчин вынуждены объединить свои усилия в поисках украденного золота. Но совместная работа — не самое подходящее занятие для таких отъявленных бандитов, как они. Компаньоны вскоре понимают, что в их дерзком и опасном путешествии по разоренной войной стране самое важное — никому не доверять и держать пистолет наготове, если хочешь остаться в живых."
            },
            {
                id: 10,
                title: "Бойцовский клуб",
                original_title: "Fight Club",
                year: 1999,
                countries: ["США", "Германия"],
                director: "Дэвид Финчер",
                actors: [
                    "Эдвард Нортон",
                    "Брэд Питт",
                    "Хелена Бонем Картер",
                    "Мит Лоаф",
                    "Зэк Гренье",
                    "Холт МакКэллани",
                    "Джаред Лето",
                    "Эйон Бэйли",
                    "Ричмонд Аркетт",
                    "Дэвид Эндрюс"
                ],
                genres: ["триллер", "драма", "криминал"],
                poster: "https://www.kinopoisk.ru/images/film_big/361.jpg",
                duration: 131,
                description: "Терзаемый хронической бессонницей и отчаянно пытающийся вырваться из мучительно скучной жизни, клерк встречает некоего Тайлера Дардена, харизматического торговца мылом с извращенной философией. Тайлер уверен, что самосовершенствование — удел слабых, а саморазрушение — единственное, ради чего стоит жить.\nПройдет немного времени, и вот уже главные герои лупят друг друга почем зря на стоянке перед баром, и очищающий мордобой доставляет им высшее блаженство. Приобщая других мужчин к простым радостям физической жестокости, они основывают тайный Бойцовский Клуб, который имеет огромный успех. Но в концовке фильма всех ждет шокирующее открытие, которое может привести к непредсказуемым событиям…"
            },
            {
                id: 11,
                title: "Властелин колец: Братство кольца",
                original_title: "The Lord of the Rings: The Fellowship of the Ring",
                year: 2001,
                countries: ["США", "Новая Зеландия"],
                director: "Питер Джексон",
                actors: [
                    "Элайджа Вуд",
                    "Иэн МакКеллен",
                    "Вигго Мортенсен",
                    "Шон Бин",
                    "Орландо Блум",
                    "Джон Рис-Дэвис",
                    "Иэн Холм",
                    "Шон Эстин",
                    "Билли Бойд",
                    "Доминик Монахэн"
                ],
                genres: ["фэнтези", "драма", "приключения"],
                poster: "https://www.kinopoisk.ru/images/film_big/328.jpg",
                duration: 178,
                description: "Сказания о Средиземье — это хроника Великой войны за Кольцо, войны, длившейся не одну тысячу лет. Тот, кто владел Кольцом, получал власть над всеми живыми тварями, но был обязан служить злу.\nТихая деревня, где живут хоббиты. Волшебник Гэндальф, придя на 111-й день рождения к своему старому другу Бильбо Бэггинсу, начинает вести разговор о кольце, которое Бильбо нашел много лет назад. Это кольцо принадлежало когда-то темному властителю Средиземья Саурону, и оно дает большую власть своему обладателю. Теперь Саурон хочет вернуть себе власть над Средиземьем. Бильбо отдает найденное кольцо своему племяннику Фродо, который пытается научиться справляться с тем страшным могуществом, которое дает ему кольцо…"
            },
            {
                id: 12,
                title: "Форрест Гамп",
                original_title: "Forrest Gump",
                year: 1994,
                countries: ["США"],
                director: "Роберт Земекис",
                actors: [
                    "Том Хэнкс",
                    "Ребекка Уильямс",
                    "Салли Филд",
                    "Майкл Коннер Хэмпфри",
                    "Харольд Дж. Хертэм",
                    "Джордж Келли",
                    "Боб Пенни",
                    "Джон Рэндолл",
                    "Сэм Андерсон",
                    "Марго Мурер"
                ],
                genres: ["драма", "мелодрама", "комедия"],
                poster: "https://www.kinopoisk.ru/images/film_big/448.jpg",
                duration: 142,
                description: "От лица главного героя Форреста Гампа, слабоумного безобидного человека с благородным и открытым сердцем, рассказывается история его необыкновенной жизни.\nФантастическим образом превращается он в известного футболиста, героя войны, преуспевающего бизнесмена. Он становится миллиардером, но остается таким же бесхитростным, глупым и добрым. Форреста ждет постоянный успех во всем, а он любит девочку, с которой дружил в детстве, но взаимность приходит слишком поздно."
            },
            {
                id: 13,
                title: "Звёздные войны: Эпизод 5 – Империя наносит ответный удар",
                original_title: "Star Wars: Episode V - The Empire Strikes Back",
                year: 1980,
                countries: ["США"],
                director: "Ирвин Кершнер",
                actors: [
                    "Марк Хэмилл",
                    "Харрисон Форд",
                    "Кэрри Фишер",
                    "Билли Ди Уильямс",
                    "Энтони Дэниелс",
                    "Дэвид Праус",
                    "Питер Мейхью",
                    "Кенни Бейкер",
                    "Фрэнк Оз",
                    "Алек Гиннесс"
                ],
                genres: ["фантастика", "фэнтези", "боевик", "приключения"],
                poster: "https://www.kinopoisk.ru/images/film_big/338.jpg",
                duration: 124,
                description: "Борьба за Галактику обостряется в пятом эпизоде космической саги. Войска Императора начинают массированную атаку на повстанцев и их союзников.\nХан Соло и принцесса Лейя укрываются в Заоблачном Городе, в котором их и захватывает Дарт Вейдер, в то время как Люк Скайуокер находится на таинственной планете джунглей Дагоба.\nТам Мастер — джедай Йода обучает молодого рыцаря навыкам обретения Силы. Люк даже не предполагает, как скоро ему придется воспользоваться знаниями старого Мастера: впереди битва с превосходящими силами Императора и смертельный поединок с Дартом Вейдером."
            },
            {
                id: 14,
                title: "Начало",
                original_title: "Inception",
                year: 2010,
                countries: ["США", "Великобритания"],
                director: "Кристофер Нолан",
                actors: [
                    "Леонардо ДиКаприо",
                    "Джозеф Гордон-Левитт",
                    "Эллен Пейдж",
                    "Том Харди",
                    "Кен Ватанабе",
                    "Киллиан Мёрфи",
                    "Марион Котийяр",
                    "Дилип Рао",
                    "Том Беренджер",
                    "Майкл Кейн"
                ],
                genres: ["фантастика", "боевик", "триллер", "драма", "детектив"],
                poster: "https://st.kp.yandex.net/images/film_iphone/iphone360_447301.jpg",
                duration: 148,
                description: "Кобб — талантливый вор, лучший из лучших в опасном искусстве извлечения: он крадет ценные секреты из глубин подсознания во время сна, когда человеческий разум наиболее уязвим. Редкие способности Кобба сделали его ценным игроком в привычном к предательству мире промышленного шпионажа, но они же превратили его в извечного беглеца и лишили всего, что он когда-либо любил. \nИ вот у Кобба появляется шанс исправить ошибки. Его последнее дело может вернуть все назад, но для этого ему нужно совершить невозможное — инициацию. Вместо идеальной кражи Кобб и его команда спецов должны будут провернуть обратное. Теперь их задача — не украсть идею, а внедрить ее. Если у них получится, это и станет идеальным преступлением. \nНо никакое планирование или мастерство не могут подготовить команду к встрече с опасным противником, который, кажется, предугадывает каждый их ход. Врагом, увидеть которого мог бы лишь Кобб."
            },
            {
                id: 15,
                title: "Властелин колец: Две крепости",
                original_title: "The Lord of the Rings: The Two Towers",
                year: 2002,
                countries: ["США", "Новая Зеландия"],
                director: "Питер Джексон",
                actors: [
                    "Элайджа Вуд",
                    "Шон Эстин",
                    "Орландо Блум",
                    "Вигго Мортенсен",
                    "Иэн МакКеллен",
                    "Доминик Монахэн",
                    "Миранда Отто",
                    "Джон Рис-Дэвис",
                    "Энди Серкис",
                    "Билли Бойд"
                ],
                genres: ["фэнтези", "драма", "приключения"],
                poster: "https://www.kinopoisk.ru/images/film_big/312.jpg",
                duration: 179,
                description: "Братство распалось, но Кольцо Всевластья должно быть уничтожено. Фродо и Сэм вынуждены доверить свои жизни Голлуму, который взялся провести их к вратам Мордора. Громадная Армия Сарумана приближается: члены братства и их союзники готовы принять бой. Битва за Средиземье продолжается."
            },
            {
                id: 16,
                title: "Пролетая над гнездом кукушки",
                original_title: "One Flew Over the Cuckoo's Nest",
                year: 1975,
                countries: ["США"],
                director: "Милош Форман",
                actors: [
                    "Джек Николсон",
                    "Луиза Флетчер",
                    "Брэд Дуриф",
                    "Уильям Редфилд",
                    "Кристофер Ллойд",
                    "Дэнни ДеВито",
                    "Уилл Сэмпсон",
                    "Нэйтан Джордж",
                    "Дин Р. Брукс",
                    "Майкл Берриман"
                ],
                genres: ["драма"],
                poster: "https://www.kinopoisk.ru/images/film_big/336.jpg",
                duration: 133,
                description: "Сымитировав помешательство в надежде избежать тюремного заключения, Рэндл Патрик МакМерфи попадает в психиатрическую клинику, где почти безраздельным хозяином является жестокосердная сестра Милдред Рэтчед. МакМерфи поражается тому, что прочие пациенты смирились с существующим положением вещей, а некоторые — даже сознательно пришли в лечебницу, прячась от пугающего внешнего мира. И решается на бунт. В одиночку."
            },
            {
                id: 17,
                title: "Славные парни",
                original_title: "Goodfellas",
                year: 1990,
                countries: ["США"],
                director: "Мартин Скорсезе",
                actors: [
                    "Роберт Де Ниро",
                    "Рэй Лиотта",
                    "Джо Пеши",
                    "Лоррейн Бракко",
                    "Пол Сорвино",
                    "Фрэнк Сиверо",
                    "Тони Дарроу",
                    "Майк Старр",
                    "Фрэнк Винсент",
                    "Чак Лоу"
                ],
                genres: ["драма", "криминал"],
                poster: "https://www.kinopoisk.ru/images/film_big/350.jpg",
                duration: 140,
                description: "Фильм рассказывает о Генри Хилле — начинающем гангстере, занимающемся грабежами вместе с Джими Конвеем и Томми Де Вито, которые с легкостью убивают любого, кто встает у них на пути восхождения к вершинам Мафии."
            },
            {
                id: 18,
                title: "Матрица",
                original_title: "The Matrix",
                year: 1999,
                countries: ["США"],
                directors: ["Лана Вачовски, Лилли Вачовски"],
                actors: [
                    "Киану Ривз",
                    "Лоренс Фишбёрн",
                    "Кэрри-Энн Мосс",
                    "Хьюго Уивинг",
                    "Джо Пантольяно",
                    "Глория Фостер",
                    "Маркус Чонг",
                    "Джулиан Араханга",
                    "Мэтт Доран",
                    "Белинда МакКлори"
                ],
                genres: ["фантастика", "боевик"],
                poster: "https://www.kinopoisk.ru/images/film_big/301.jpg",
                duration: 136,
                description: "Жизнь Томаса Андерсона разделена на две части: днём он самый обычный офисный работник, получающий нагоняи от начальства, а ночью превращается в хакера по имени Нео, и нет места в сети, куда он не смог бы дотянуться. Но однажды всё меняется — герой, сам того не желая, узнаёт страшную правду: всё, что его окружает — не более, чем иллюзия, Матрица, а люди — всего лишь источник питания для искусственного интеллекта, поработившего человечество. И только Нео под силу изменить расстановку сил в этом ставшем вдруг чужим и страшным мире."
            },
            {
                id: 19,
                title: "Семь самураев",
                original_title: "Shichinin no samurai",
                year: 1954,
                countries: ["Япония"],
                directors: ["Акира Куросава"],
                actors: [
                    "Тосиро Мифунэ",
                    "Такаси Симура",
                    "Кэйко Цусима",
                    "Юкико Симадзаки",
                    "Каматари Фудзивара",
                    "Дайсукэ Като",
                    "Исао Кимура",
                    "Минору Тиаки",
                    "Сэйдзи Миягути",
                    "Ёсио Косуги"
                ],
                genres: ["драма", "приключения"],
                poster: "https://www.kinopoisk.ru/images/film_big/332.jpg",
                duration: 202,
                description: "Япония. 16 век. В стране полыхает гражданская война, повсюду орудуют банды разбойников и мародеров. Бедные крестьяне нанимают для своей защиты семерых самураев, которые немного сплачивают раздробленных и малодушных жителей деревни в этой борьбе…"
            },
            {
                id: 20,
                title: "Звёздные войны: Эпизод 4 – Новая надежда",
                original_title: "Star Wars",
                year: 1977,
                countries: ["США"],
                directors: ["Джордж Лукас"],
                actors: [
                    "Марк Хэмилл",
                    "Харрисон Форд",
                    "Кэрри Фишер",
                    "Питер Кушинг",
                    "Алек Гиннесс",
                    "Энтони Дэниелс",
                    "Кенни Бейкер",
                    "Питер Мейхью",
                    "Дэвид Праус",
                    "Фил Браун"
                ],
                genres: ["фантастика", "фэнтези", "боевик", "приключения"],
                poster: "https://www.kinopoisk.ru/images/film_big/333.jpg",
                duration: 121,
                description: "Татуин. Планета-пустыня. Уже постаревший рыцарь Джедай Оби Ван Кеноби спасает молодого Люка Скайуокера, когда тот пытается отыскать пропавшего дроида. С этого момента Люк осознает свое истинное назначение: он один из рыцарей Джедай. В то время как гражданская война охватила галактику, а войска повстанцев ведут бои против сил злого Императора, к Люку и Оби Вану присоединяется отчаянный пилот-наемник Хан Соло, и в сопровождении двух дроидов, R2D2 и C-3PO, этот необычный отряд отправляется на поиски предводителя повстанцев — принцессы Леи. Героям предстоит отчаянная схватка с устрашающим Дартом Вейдером — правой рукой Императора и его секретным оружием — «Звездой Смерти»."
            }
        ],
        holds: [
            {
                client: 1,
                film: 1
            }
        ]
    };

    that.getClients = function () {
        return config.clients;
    };

    that.getFilms = function () {
        return config.films;
    };

    that.getFilm = function(id) {
        var filtered = config.films.filter(item => item.id == id)

        if (!filtered) {
            //todo throws exception
        }

        return filtered[0]
    }

    that.getClient = function (id) {
        return config.clients.filter(item => item.id == id);
    }

    return that;
};

module.exports = Database;
