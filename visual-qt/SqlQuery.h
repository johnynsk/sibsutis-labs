#ifndef SQLQUERY_H
#define SQLQUERY_H
#include <QSqlQuery>
class SqlQuery : QSqlQuery {
public:
    virtual long size()
    {
        last();
        long result = at() + 1;
        first();

        return result;
    }
};

#endif // SQLQUERY_H
