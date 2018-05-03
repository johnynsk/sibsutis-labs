#include "user.h"

User::User()
{
    this->_field_RegDate = new QDateTime();
}

User::User(QString userName)
{
    this->_field_UserName = userName;
    this->_field_RegDate = new QDateTime();
}

User::User(int userId)
{
    this->_userId = userId;
    this->_field_RegDate = new QDateTime();
}

User * User::setPassword(const QString password)
{
    return this->setEncodedPassword(QCryptographicHash::hash(QByteArray::fromRawData(password.toStdString().c_str(), password.length()), QCryptographicHash::Sha256).toHex());
}

int User::getUserId() const
{
    return this->_userId;
}

User * User::setRegDate(int timestamp)
{
    QDateTime * date = new QDateTime();

    if (timestamp) {
        date->setTime_t(timestamp);
    }

    return this->setRegDate(date);
}

bool User::isAdmin()
{
    return (this->getPrivileges() & PERMISSIONS_ADMIN);
}
