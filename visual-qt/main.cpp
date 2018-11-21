#include "loginwindow.h"
#include "usermainwindow.h"
#include "adminmainwindow.h"
#include "userstable.h"
#include "user.h"
#include "exceptions.h"
#include "SqlQuery.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include <sstream>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./project.sqlite");
    db.open();
//    qDebug() <<db.driver()->hasFeature(QSqlDriver::QuerySize);
//    LoginWindow loginWindow;
//    loginWindow.show();
//    UserMainWindow userMainWindow;
//    loginWindow.setUserMainWindow(&userMainWindow);
//    AdminMainWindow adminMainWindow;
//    loginWindow.setAdminMainWindow(&adminMainWindow);

    try {
        UsersTable usersTable(db);
        User * test = new User();

        try {
            test->setUserName("root");
            test->setFirstName("Administrative");
            test->setLastName("Account");
            test->setPassword("123qwe");
            test->setPrivileges(PERMISSIONS_ADMIN);
            test = usersTable.persist(test); 
        } catch (UserExistsException &exception) {
            test = usersTable.getUser(new User("root"));
        }
        qDebug() << test->getUserId();
        loginWindow.setUsersTable(&usersTable);

        //return a.exec();
    } catch (Exception const & exception) {
        qDebug() << exception.what();
        /*QMessageBox::critical(
            &loginWindow,
            QObject::tr("Произошла критическая ошибка"),
            QString("Произошла критическая ошибка:\n")
                .append(QString::fromLocal8Bit(exception.what()))
                .append(QString("\n\nДальнейшая работа приложения невозможна,\nаварийная остановка.\n"))
        );*/
    }
    db.commit();
    db.close();
}
