#include "userstable.h"

UsersTable::UsersTable(QSqlDatabase instance) {
    db = instance;
}

User * UsersTable::getUser(QString username) {
    User query = User(username);
    return getUser(&query);
}

User * UsersTable::getUser(User * user) {
    QSqlQuery query(this->db);
    query.prepare("SELECT * FROM users WHERE username=:username");
    query.bindValue(":username", QVariant(user->getUserName()));

    if (!query.exec()) {
        throw UsersException(query.lastError().text());
    }

    query.last();
    if (query.at() + 1 <= 0) {
        throw UserNotFoundException("Пользователь не найден");
    }

    query.first();
    QSqlRecord record = query.record();

    QDateTime date;
    date.setTime_t(record.value("registration_date").toInt());

    User * result = new User(record.value("id").toInt());
    result->setUserName(record.value("username").toString())
        ->setFirstName(record.value("first_name").toString())
        ->setLastName(record.value("last_name").toString())
        ->setRegDate(0);

    return result;
}

User * UsersTable::auth(QString username, QString password)
{
    User * query = new User(username);
    query->setPassword(password);
    return auth(query);
}

User * UsersTable::auth(User * user) {
    QSqlQuery query = QSqlQuery(this->db);
    query.prepare("SELECT * FROM users WHERE username=:username AND password=:password");
    query.bindValue(":username", user->getUserName());
    query.bindValue(":password", user->getEncodedPassword());

    if (!query.exec()) {
        throw DataBaseException(query.lastError().text());
    }

    query.last();

    if (query.at() + 1 <= 0) {
        throw UserNotFoundException("Пользователь с такими данными не найден");
    }

    return getUser(user);
}

User * UsersTable::persist(User * user) {
    bool needCreate = false;
    QSqlQuery query(this->db);

    if (!user->getUserId()) {
        try {
            if (getUser(user)) {
                throw UserExistsException("Пользователь с такими данными уже существует");
            }
        } catch (UserNotFoundException &exception) {
        }
        query.prepare("INSERT INTO users (id, username, password, first_name, last_name, privileges, registration_date) VALUES (NULL, :username, :password, :first_name, :last_name, :privileges, :registration_date)");
        needCreate = true;
    } else {
        query.prepare("UPDATE users SET username=:username, password=:password, first_name=:first_name, last_name=:last_name, privileges=:privileges, registration_date=:registration_date WHERE id=:userId");
        query.bindValue(":userId", QVariant(user->getUserId()));
    }

    query.bindValue(":username", QVariant(user->getUserName()));
    query.bindValue(":password", QVariant(user->getEncodedPassword()));
    query.bindValue(":first_name", QVariant(user->getUserName()));
    query.bindValue(":last_name", QVariant(user->getUserName()));
    query.bindValue(":privileges", QVariant(user->getPrivileges()));
    query.bindValue(":registration_date", QVariant(user->getRegDate()->toTime_t()));

    if (!query.exec()) {
        throw UserPersistException(query.lastError().text());
    }

    if (needCreate) {
        return getUser(new User(user->getUserName()));
    }

    return user;
}
