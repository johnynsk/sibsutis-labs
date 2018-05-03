#include "editfilm.h"
#include "ui_editfilm.h"

editfilm::editfilm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editfilm)
{
    ui->setupUi(this);
}

editfilm::~editfilm()
{
    delete ui;
}

void editfilm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
