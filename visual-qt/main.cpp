#include "loginwindow.h"
#include "usermainwindow.h"
#include "adminmainwindow.h"
#include "userstable.h"
#include "exceptions.h"
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QtSQL>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include <sstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\shar2\\projects\\course\\project.sqlite");
    db.open();
    LoginWindow loginWindow;
    loginWindow.show();
    UserMainWindow userMainWindow;
    loginWindow.setUserMainWindow(&userMainWindow);
    AdminMainWindow adminMainWindow;
    loginWindow.setAdminMainWindow(&adminMainWindow);

    try {
        UsersTable usersTable(db);
//        test->setUserName("root");
//        test->setFirstName("Administrative");
//        test->setLastName("Account");
//        test->setPassword("123qwe");
//        test->setPrivileges(PERMISSIONS_ADMIN);
//        usersTable.persist(test);
//        usersTable.getUser("root");
        loginWindow.setUsersTable(&usersTable);

        return a.exec();
    } catch (Exception const & exception) {
        qDebug() << exception.what();
        QMessageBox::critical(
            &loginWindow,
            QObject::tr("Произошла критическая ошибка"),
            QString("Произошла критическая ошибка:\n")
                .append(QString::fromLocal8Bit(exception.what()))
                .append(QString("\n\nДальнейшая работа приложения невозможна,\nаварийная остановка.\n"))
        );
    }
    db.commit();
    db.close();
}
