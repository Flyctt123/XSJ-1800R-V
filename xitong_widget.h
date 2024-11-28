#ifndef XITONG_WIDGET_H
#define XITONG_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <mainwindow.h>
#include "keyboard.h"
#include "keyboard_ABC.h"

namespace Ui {
class xitong_widget;
}

class xitong_widget : public QWidget
{
    Q_OBJECT

public:
    explicit xitong_widget(QWidget *parent = nullptr);
    ~xitong_widget();

private:
    KeyBoard *keyBoard=nullptr;
    KeyBoard_ABC *keyBoard_ABC=nullptr;
    Ui::xitong_widget *ui;
    QString usb_path = "";
    //QProgressBar *pProgressBar;
    QTimer *timer;
private slots:
    bool eventFilter(QObject *, QEvent *);
    void callKeyBoard(QLineEdit *a);
    void callKeyBoard_ABC(QLineEdit *a);
    int32_t myexec(const char *cmd, std::vector<std::string> &resvec);
    void xitong_button_init(QPushButton *button_init);
    void serial_send_disconnect();
    uint16_t ModBusCRC16(QByteArray data);
    void on_usb_Button_check_clicked();
    void on_usb_Button_data_clicked();
    void on_usb_Button_picture_clicked();
    bool FindFileForDelete(const QString & path);
    void on_pushButton_restart_clicked();
    void timerTimeout_hour();
    void on_usb_Button_update_clicked();
    void on_pushButton_save_time_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_reset_clicked();

    void on_pushButton_sysclear_clicked();

    void on_usb_Button_Config_update_clicked();

    void on_pushButton_reSendclear_clicked();

    void on_usb_Button_history_clicked();

    void on_pushButton_save_info_clicked();

signals:
    void check_time_signal(int);
    void sysClear(int);
    void reSendClear(int);
};

#endif // XITONG_WIDGET_H
