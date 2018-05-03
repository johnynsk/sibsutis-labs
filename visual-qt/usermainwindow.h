#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include "exceptions.h"
#include "user.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT
    LINK_OBJECT(User, UserMainWindow)
public:
    explicit UserMainWindow(QWidget *parent = 0);
    ~UserMainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
