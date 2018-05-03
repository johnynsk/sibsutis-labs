#ifndef USERSTABLE_H
#define USERSTABLE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include "exceptions.h"
#include "user.h"
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

class UsersTable
{
public:
    UsersTable(QSqlDatabase instance);
    User * getUser(User * user);
    User * getUser(QString username);
    User * auth(User * user);
    User * auth(QString username, QString password);
    User * persist(User * user);
protected:
    QSqlDatabase db;
};

#endif // USERSTABLE_H
