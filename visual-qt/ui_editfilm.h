/********************************************************************************
** Form generated from reading UI file 'editfilm.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITFILM_H
#define UI_EDITFILM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editfilm
{
public:
    QLineEdit *editTitle;
    QLineEdit *editOriginalTitle;
    QLineEdit *editYear;
    QPlainTextEdit *editDescription;

    void setupUi(QWidget *editfilm)
    {
        if (editfilm->objectName().isEmpty())
            editfilm->setObjectName(QStringLiteral("editfilm"));
        editfilm->resize(400, 300);
        editTitle = new QLineEdit(editfilm);
        editTitle->setObjectName(QStringLiteral("editTitle"));
        editTitle->setGeometry(QRect(10, 10, 381, 41));
        editTitle->setMaxLength(128);
        editOriginalTitle = new QLineEdit(editfilm);
        editOriginalTitle->setObjectName(QStringLiteral("editOriginalTitle"));
        editOriginalTitle->setGeometry(QRect(10, 60, 311, 20));
        editOriginalTitle->setMaxLength(128);
        editYear = new QLineEdit(editfilm);
        editYear->setObjectName(QStringLiteral("editYear"));
        editYear->setGeometry(QRect(330, 60, 61, 20));
        editYear->setMaxLength(4);
        editDescription = new QPlainTextEdit(editfilm);
        editDescription->setObjectName(QStringLiteral("editDescription"));
        editDescription->setGeometry(QRect(13, 160, 381, 131));

        retranslateUi(editfilm);

        QMetaObject::connectSlotsByName(editfilm);
    } // setupUi

    void retranslateUi(QWidget *editfilm)
    {
        editfilm->setWindowTitle(QApplication::translate("editfilm", "Form", 0));
        editTitle->setText(QString());
        editTitle->setPlaceholderText(QApplication::translate("editfilm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\204\320\270\320\273\321\214\320\274\320\260", 0));
        editOriginalTitle->setPlaceholderText(QApplication::translate("editfilm", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\204\320\270\320\273\321\214\320\274\320\260 \320\275\320\260 \321\217\320\267\321\213\320\272\320\265 \320\276\321\200\320\270\320\263\320\270\320\275\320\260\320\273\320\260", 0));
        editYear->setInputMask(QApplication::translate("editfilm", "####", 0));
        editYear->setPlaceholderText(QApplication::translate("editfilm", "\320\263\320\276\320\264", 0));
        editDescription->setDocumentTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class editfilm: public Ui_editfilm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITFILM_H
