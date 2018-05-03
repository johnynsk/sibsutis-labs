#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "userstable.h"
#include "usermainwindow.h"
#include "adminmainwindow.h"
#include "exceptions.h"


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
    LINK_OBJECT(UserMainWindow, LoginWindow)
    LINK_OBJECT(AdminMainWindow, LoginWindow)
    LINK_OBJECT(UsersTable, LoginWindow)
public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
