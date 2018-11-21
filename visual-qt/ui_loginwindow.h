/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QPushButton *loginButton;
    QLineEdit *password;
    QPushButton *createUserButton;
    QPushButton *restorePasswordButton;
    QLabel *label_2;
    QLineEdit *username;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(342, 168);
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(260, 40, 61, 71));
        loginButton->setDefault(true);
        password = new QLineEdit(LoginWindow);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(20, 80, 231, 31));
        password->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        createUserButton = new QPushButton(LoginWindow);
        createUserButton->setObjectName(QStringLiteral("createUserButton"));
        createUserButton->setGeometry(QRect(20, 120, 171, 31));
        restorePasswordButton = new QPushButton(LoginWindow);
        restorePasswordButton->setObjectName(QStringLiteral("restorePasswordButton"));
        restorePasswordButton->setGeometry(QRect(200, 120, 121, 31));
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 321, 21));
        username = new QLineEdit(LoginWindow);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(20, 40, 231, 31));
        QWidget::setTabOrder(username, password);
        QWidget::setTabOrder(password, loginButton);
        QWidget::setTabOrder(loginButton, restorePasswordButton);
        QWidget::setTabOrder(restorePasswordButton, createUserButton);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Form", 0));
        loginButton->setText(QApplication::translate("LoginWindow", "\320\222\320\276\320\271\321\202\320\270", 0));
        password->setText(QApplication::translate("LoginWindow", "123qwe", 0));
        password->setPlaceholderText(QApplication::translate("LoginWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", 0));
        createUserButton->setText(QApplication::translate("LoginWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\320\276\320\263\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", 0));
        restorePasswordButton->setText(QApplication::translate("LoginWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214", 0));
        label_2->setText(QApplication::translate("LoginWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">\320\244\320\270\320\273\321\214\320\274\320\276\321\202\320\265\320\272\320\260</span></p></body></html>", 0));
        username->setText(QApplication::translate("LoginWindow", "root", 0));
        username->setPlaceholderText(QApplication::translate("LoginWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
