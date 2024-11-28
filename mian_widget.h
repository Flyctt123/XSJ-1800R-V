#ifndef MIAN_WIDGET_H
#define MIAN_WIDGET_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class mian_widget;
}

class mian_widget : public QWidget
{
    Q_OBJECT

public:
    explicit mian_widget(QWidget *parent = nullptr);
    ~mian_widget();
    Ui::mian_widget *ui;

private slots:
    void refresh_timeout();
    void serial_send();
    void on_checkBox_DYC_1_stateChanged(int arg1);

    void on_checkBox_DYC_2_stateChanged(int arg1);

    void on_checkBox_DYC_3_stateChanged(int arg1);

    void on_checkBox_DYC_4_stateChanged(int arg1);

    void on_checkBox_DO1_stateChanged(int arg1);

    void on_checkBox_DO2_stateChanged(int arg1);

    void on_checkBox_DO3_stateChanged(int arg1);

private:
    const QString m_grey_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;background:rgb(255,88,88)";
    const QString m_green_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;background:green";

    QTimer *timer1;
    uint8_t AI_unit[6];
};

#endif // MIAN_WIDGET_H
