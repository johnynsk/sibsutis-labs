#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    oldHexA = ui->hexA->text();
    oldDecA = ui->decA->text();
    oldHexB = ui->hexB->text();
    oldDecB = ui->decB->text();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcAll()
{
    std::string hexA(oldHexA.toStdString()), hexB(oldHexB.toStdString());
    std::string mHexB = hexB[0] == '-' ? hexB.substr(1) : std::string("-").append(hexB);

    std::string sum = HexSummator::add(hexA, hexB);
    std::string sub = HexSummator::add(hexA, mHexB);

    ui->hexSum->setText(QString::fromStdString(sum));
    ui->hexSub->setText(QString::fromStdString(sub));
    ui->decSum->setText(QString::number(HexSummator::hexdec(sum)));
    ui->decSub->setText(QString::number(HexSummator::hexdec(sub)));
}

void MainWindow::on_hexA_textEdited(const QString &newValue)
{
    if (!HexSummator::validate(newValue.toStdString())) {
        ui->hexA->setText(oldHexA);
        return;
    }


    oldHexA = ui->hexA->text();
    if (!oldHexA.size()) {
        oldHexA = "0";
    }

    oldDecA = QString::number(HexSummator::hexdec(oldHexA.toStdString()));
    ui->decA->setText(oldDecA);

    calcAll();
}

void MainWindow::on_decA_textEdited(const QString &newValue)
{
    if (!HexSummator::validateDec(newValue.toStdString())) {
        ui->decA->setText(oldDecA);
        return;
    }


    oldDecA = ui->decA->text();
    if (!oldDecA.size()) {
        oldDecA = "0";
    }
    oldHexA = QString::fromStdString(HexSummator::dechex(oldDecA.toLongLong()));
    ui->hexA->setText(oldHexA);


    calcAll();
}

void MainWindow::on_hexB_textEdited(const QString &newValue)
{
    if (!HexSummator::validate(newValue.toStdString())) {
        ui->hexB->setText(oldHexB);
        return;
    }

    oldHexB = ui->hexB->text();
    if (!oldHexB.size()) {
        oldHexB = "0";
    }
    oldDecB = QString::number(HexSummator::hexdec(oldHexB.toStdString()));
    ui->decB->setText(oldDecB);

    calcAll();
}

void MainWindow::on_decB_textEdited(const QString &newValue)
{
    if (!HexSummator::validateDec(newValue.toStdString())) {
        ui->decB->setText(oldDecB);

        return;
    }

    oldDecB = ui->decB->text();
    if (!oldDecB.size()) {
        oldDecB = "0";
    }
    oldHexB = QString::fromStdString(HexSummator::dechex(oldDecB.toLongLong()));
    ui->hexB->setText(oldHexB);

    calcAll();
}

void MainWindow::on_sumToA_clicked()
{
    oldHexA = ui->hexSum->text();
    ui->hexA->setText(oldHexA);
    oldDecA = ui->decSum->text();
    ui->decA->setText(oldDecA);

    calcAll();
}

void MainWindow::on_subToA_clicked()
{
    oldHexA = ui->hexSub->text();
    ui->hexA->setText(oldHexA);
    oldDecA = ui->decSub->text();
    ui->decA->setText(oldDecA);

    calcAll();
}

void MainWindow::on_clearA_clicked()
{
    oldHexA = QString("0");
    ui->hexA->setText(oldHexA);
    oldDecA = QString("0");
    ui->decA->setText(oldDecA);
}

void MainWindow::on_clearB_clicked()
{
    oldHexB = QString("0");
    ui->hexB->setText(oldHexB);
    oldDecB = QString("0");
    ui->decB->setText(oldDecB);
}
