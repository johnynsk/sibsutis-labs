#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "hexsummator.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_hexA_textEdited(const QString &arg1);

    void on_decA_textEdited(const QString &arg1);

    void on_hexB_textEdited(const QString &arg1);

    void on_decB_textEdited(const QString &arg1);

    void on_sumToA_clicked();

    void on_subToA_clicked();

    void on_clearA_clicked();

    void on_clearB_clicked();

private:
    Ui::MainWindow *ui;
    QString oldHexA, oldHexB, oldDecA, oldDecB;
    void calcAll();
};

#endif // MAINWINDOW_H
