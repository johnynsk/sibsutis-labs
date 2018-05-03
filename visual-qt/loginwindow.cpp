#include "loginwindow.h"
#include "usermainwindow.h"
#include "ui_loginwindow.h"
#include "user.h"
#include <QMessageBox>
LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
   ui->setupUi(this);
}


LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    if (!ui->username->text().size() || !ui->password->text().size()) {
        return;
    }

    try {
        QString username = ui->username->text();
        QString password = ui->password->text();
        User * user;
        user = new User(1);
        user->setUserName("root")->setPassword("123qwe")->setPrivileges(2)->setFirstName("First")->setLastName("Last");
        //this->_UsersTable->auth(username, password);
        this->_UserMainWindow->setUser(user);
        this->_UserMainWindow->show();
        this->hide();
    } catch(UsersException &exception) {
        QMessageBox::warning(
            this,
            QObject::tr("Произошла ошибка"),
            QString("Произошла ошибка:\n")
                .append(QString::fromLocal8Bit(exception.what()))
        );
    }
}
