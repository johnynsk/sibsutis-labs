#ifndef TESTSCREENWINDOW_H
#define TESTSCREENWINDOW_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QString>
#include "user.h"
#include <QPushButton>
class TestColorItem {
public:
    TestColorItem(QString Color, int Value) {
        this->setColor(Color)->setValue(Value)->setReal(true);
    }
    TestColorItem() {
        this->setReal(false);
    }

    ADD_FIELD(TestColorItem, QString, Color);
    ADD_FIELD(TestColorItem, int, Value);
    ADD_FIELD(TestColorItem, bool, Real);
};

class TestStepRow {
public:
    TestStepRow * addItem(TestColorItem item) {
        items.append(item);
        return this;
    }

    TestColorItem getItem(int offset) {
        return items[offset];
    }

    int count() {
        return items.length();
    }

private:
    QList<TestColorItem> items;
};

class TestStep {
public:
    TestStep * addStepRow(TestStepRow * row) {
        rows.append(row);
        return this;
    }

    TestStepRow * getStepRow(int offset) {
        return rows[offset];
    }

    int countRows() {
        return rows.length();
    }

private:
    QList<TestStepRow*> rows;
};

class TestConfiguration {
public:
    TestConfiguration * addStep(TestStep * step) {
        _steps.append(step);
        return this;
    }

    TestConfiguration(QString name) {
        this->_name = name;
    }

    TestStep * getStep(int offset) {
        return _steps[offset];
    }

private:
    QList<TestStep *> _steps;
    QString _name;
};

class FullTestConfiguration {
public:
    FullTestConfiguration * addConfiguration(TestConfiguration * configuration) {
        configurations.push_back(configuration);
        return this;
    }

    FullTestConfiguration();

    QList<QPushButton *> getButtons(QWidget * widget) {
        QList<QPushButton *> buttons;

        TestStep * step = this->configurations[2]->getStep(0);
        for (int i = 0; i < step->countRows(); i++) {
            TestStepRow * stepRow = step->getStepRow(i);
            for (int j = 0; j < stepRow->count(); j++) {
                if (!stepRow->getItem(j).getReal()) {
                    continue;
                }

                QPushButton * button;
                button = new QPushButton(widget);
                button->move(100 + 50 * i, 100 + 50 * j);
                QRect rect = button->geometry();
                rect.setHeight(40);
                rect.setWidth(40);
                button->setGeometry(rect);
                button->show();
                buttons.append(button);
            }
        }

        return buttons;
    }

private:
    QList<TestConfiguration *> configurations;
    QList<QPushButton *> buttons;
    QMap<QString, TestConfiguration> passed;
    int currentStep;
    int currentConf;
};

namespace Ui {
class TestScreenWindow;
}

class TestScreenWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TestScreenWindow(QWidget *parent = 0);
    ~TestScreenWindow();

private:
    Ui::TestScreenWindow *ui;
    FullTestConfiguration * fullTestConfiguration;

};

#endif // TESTSCREENWINDOW_H
