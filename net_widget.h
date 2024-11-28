#ifndef NET_WIDGET_H
#define NET_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTabWidget>
#include "keyboard.h"
#include "keyboard_ABC.h"
#include "mainwindow.h"
#include <QNetworkInterface>
#include <QHostInfo>
#include <QSerialPort>
#include <QSerialPortInfo>

typedef struct
{
    uint8_t point_addr;//目标地址
    uint8_t fre;//通信速率
    uint8_t channel;//通信信道
}LORA_CONFIG;

namespace Ui {
class net_widget;
}

class net_widget : public QWidget
{
    Q_OBJECT

public:
    explicit net_widget(QWidget *parent = nullptr);
    ~net_widget();

public slots:
     void setUpload_IpSet(void);
private slots:
    void net_button_init(QPushButton *button_init);
    bool eventFilter(QObject *, QEvent *);
    void callKeyBoard(QLineEdit *a);
    void callKeyBoard_ABC(QLineEdit *a);
    void wifi_init();
    uint8_t on_checkBox_wifi_stateChanged(int arg1);
    uint8_t on_pushButton_wifiname_clicked();
    uint8_t on_pushButton_wifi_password_clicked();
    void on_pushButton_local_ip_clicked();
    void on_pushButton_net_check_clicked();
    void onLookupHost(QHostInfo host);
    void on_pushButton_sim_flag_clicked();

    void on_pushButton_sim_signal_clicked();
    QString strMid(QString src, QString start, QString end);//截取两字符串中间的字符串
    void serial_net_init(QSerialPort *serial, QString portname, int bundrate);
    void serialport_recive_4G();
    void serialport_recive_LORA();
    void on_pushButton_save_clicked();

    void on_save_Button_lora_clicked();

    void on_pushButton_mobile_clicked();

private:
    KeyBoard *keyBoard=nullptr;
    KeyBoard_ABC *keyBoard_ABC=nullptr;

    Ui::net_widget *ui;
    QPushButton *button_test;
    QString wifi_off_cmd = "";
    QString wifi_on_cmd = "";
    QString wifi_name_cmd = "";
    QString wifi_password_cmd = "";
    QString sim_select = "";
    QString lora_select = "";

signals:
    void ReSendclear(int);
};

#endif // NET_WIDGET_H
