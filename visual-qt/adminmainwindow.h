#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include "exceptions.h"
namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = 0);
    ~AdminMainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AdminMainWindow *ui;
};

#endif // ADMINMAINWINDOW_H
