#ifndef EDITFILM_H
#define EDITFILM_H

#include <QWidget>

namespace Ui {
class editfilm;
}

class editfilm : public QWidget
{
    Q_OBJECT

public:
    explicit editfilm(QWidget *parent = 0);
    ~editfilm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::editfilm *ui;
};

#endif // EDITFILM_H
