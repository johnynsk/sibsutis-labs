#ifndef USER_H
#define USER_H
#include <QString>
#include <QDateTime>
#include <QCryptographicHash>
#include "magic.h"

#define PERMISSIONS_ADMIN 2

class User
{
    ADD_FIELD(User, QString, UserName)
    ADD_FIELD(User, QString, FirstName)
    ADD_FIELD(User, QString, LastName)
    ADD_DATE_FIELD(User, RegDate)
    ADD_FIELD(User, QString, EncodedPassword)
    ADD_FIELD(User, int, Privileges)
public:
    User();
    User(QString userName);
    User(int userId);

    User * setUserId(int userId);
    User * persist();
    User * setPassword(const QString password);
    User * setRegDate(int timestamp);
    User * setRegDate();

    int getUserId() const;
    bool isAdmin();

private:
    int _userId = 0;
};

#endif // USER_H
