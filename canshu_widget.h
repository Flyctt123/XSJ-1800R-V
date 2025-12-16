#ifndef CANSHU_WIDGET_H
#define CANSHU_WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <mainwindow.h>
#include "keyboard.h"
#include "keyboard_ABC.h"

typedef struct
{
    uint16_t upLimit;
    uint16_t downLimit;
    uint16_t data;
    uint16_t time;
    QString unit;
}KDY;

//功率变送器计算
typedef struct
{
    uint32_t sljst;//水轮机水头
    uint16_t sljxl;//水轮机效率
    uint16_t fdjxl;//发电机效率
}GLBSQ;

typedef struct
{
    double multipy;
    double divide;
    double add;
    double subtract;
}CALCULATE_485;

namespace Ui {
class canshu_widget;
}

class canshu_widget : public QWidget
{
    Q_OBJECT

public:
    explicit canshu_widget(QWidget *parent = nullptr);
    ~canshu_widget();

    QStringList portStringList; //系统串口号
    QStringList portCOM; //显示串口号
    QString currentCOM = "";

public slots:
    void setUploadTimeToUI(uint8_t t);
    void setUploadPasswordToUI(QString p);
    void setUploadBaseSet(void);
    void setUploadRunSet(void);
private slots:
    bool eventFilter(QObject *, QEvent *);
    void callKeyBoard(QLineEdit *a);
    void callKeyBoard_ABC(QLineEdit *a);
    void timerTimeout_second();
    void serial_init(QSerialPort *serial, QString portname, int bundrate);
    void canshu_button_init(QPushButton *button_init);
    void on_save_Button_485_clicked();

    void on_PortBox_currentIndexChanged(const QString &arg1);

    void on_radioButton1_vol_clicked();
    void on_radioButton1_cur_clicked();
    void on_radioButton2_vol_clicked();
    void on_radioButton2_cur_clicked();
    void on_radioButton3_vol_clicked();
    void on_radioButton3_cur_clicked();
    void on_radioButton4_vol_clicked();
    void on_radioButton4_cur_clicked();
    void on_radioButton5_vol_clicked();
    void on_radioButton5_cur_clicked();
    void on_radioButton6_vol_clicked();
    void on_radioButton6_cur_clicked();
    void on_save_Button_sampling_clicked();
    void on_comboBox_485_num_currentIndexChanged(const QString &arg1);

    void modbus_comm_init();

    void on_comboBox_485_currentIndexChanged(const QString &arg1);

    void on_pushButton_kdy_start_clicked();

    void on_pushButton_kdy_slave_clicked();

    void on_pushButton_kdy_stop_clicked();

    void on_save_Button_tcpTime_clicked();

    void on_comboBox_report_currentIndexChanged(const QString &arg1);

    void on_pushButton_SW_test_clicked();

    void on_checkBox_SW_uniform_time_stateChanged(int arg1);

    void on_checkBox_SW_hour_stateChanged(int arg1);

    void on_comboBox_485_protocol_currentIndexChanged(const QString &arg1);

    void on_pushButton_power2flow_save_clicked();

    void on_comboBox_power2flow_select_currentIndexChanged(const QString &arg1);

private:
    KeyBoard *keyBoard=nullptr;
    KeyBoard_ABC *keyBoard_ABC=nullptr;

    Ui::canshu_widget *ui;
    QSerialPort *serial_change;
    QTimer *timer;
    uint8_t time_count = 0;
    uint8_t comm_485_identify[8] = {0x3B,0x27,0x76,0x37,0xF1,0xF2,0xF3,0xFF};//modbus标识符:0x3B水位、0x27瞬时流量、0x76累计流量、0x37流速、0xF1功率转流量1、0xF2功率转流量2、0xF3功率转流量3、0xFF禁用
    uint8_t comm_485_fun_code[4] = {0x03,0x04,0x06,0x16};//modbus功能码
    uint16_t comm_485_reg_count[4] = {0x01,0x02,0x03,0x04};//modbus寄存器数量，主要用于设置modbus读取寄存器数量，便于适配传感器帧格式，不支持单帧报文读取多个寄存器

signals:
    void kdy_signal(int);
    void SW_test_signal(int);
    void ReSendClear(int);
};


#endif // CANSHU_WIDGET_H
