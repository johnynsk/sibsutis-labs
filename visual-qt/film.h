#ifndef FILM_H
#define FILM_H
#include "magic.h"
#include <QString>
class FilmAbstract
{
    ADD_FIELD_VAL(FilmAbstract, int, Id, 0)
    ADD_FIELD(FilmAbstract, QString, Title)
    ADD_FIELD(FilmAbstract, QString, OriginalTitle)
    ADD_FIELD(FilmAbstract, QString, Director)
    ADD_FIELD(FilmAbstract, QString, PosterUrl)
    ADD_FIELD(FilmAbstract, QString, Description)
    ADD_FIELD(FilmAbstract, int, Duration)
    ADD_FIELD(FilmAbstract, int, Quantity)
    ADD_FIELD(FilmAbstract, int, Year)
public:
    FilmAbstract();
    FilmAbstract(int filmId);
};

class Film : FilmAbstract
{
public:
    Film();
    Film(int FilmId);
};

#endif // FILM_H
