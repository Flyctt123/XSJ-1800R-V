#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <mainwindow.h>
#include "keyboard.h"
#include "keyboard_ABC.h"

//字符叠加配置
typedef struct
{
    uint8_t osd_water = 0;
    uint8_t osd_flow_inst = 0;
}OSD_flag;

namespace Ui {
class camera_widget;
}

class camera_widget : public QWidget
{
    Q_OBJECT

public:
    explicit camera_widget(QWidget *parent = nullptr);
    ~camera_widget();
    KeyBoard *keyBoard=nullptr;
    KeyBoard_ABC *keyBoard_ABC=nullptr;

private slots:
    bool eventFilter(QObject *, QEvent *);
    void callKeyBoard(QLineEdit *a);
    void callKeyBoard_ABC(QLineEdit *a);
    void camera_button_init(QPushButton *button_init);
    void on_pushButton_takephoto_clicked();
    void on_checkBox_water_stateChanged(int arg1);

    void on_checkBox_flow_current_stateChanged(int arg1);

    void on_pushButton_save_clicked();

    void on_comboBox_init_currentIndexChanged(int index);

    void on_checkBox_open_stateChanged(int arg1);
    void time_out();

    void on_pushButton_osd_save_clicked();

private:
    Ui::camera_widget *ui;
    QTimer *timer;
};

#endif // CAMERA_WIDGET_H
