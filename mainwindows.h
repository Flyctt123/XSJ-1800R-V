#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QWidget>

namespace Ui {
class mainwindows;
}

class mainwindows : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindows(QWidget *parent = nullptr);
    ~mainwindows();

private:
    Ui::mainwindows *ui;
};

#endif // MAINWINDOWS_H
