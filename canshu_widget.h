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

typedef struct
{
    uint16_t multipy;
    uint16_t divide;
    uint16_t add;
    uint16_t subtract;
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
    //void callKeyBoard_ABC(QLineEdit *a);
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
    void on_clear_Button_485_clicked();

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

private:
    KeyBoard *keyBoard=nullptr;
    KeyBoard_ABC *keyBoard_ABC=nullptr;

    Ui::canshu_widget *ui;
    QSerialPort *serial_change;
    QTimer *timer;
    uint8_t time_count = 0;
    uint8_t comm_485_identify[5] = {0x3B,0x27,0x76,0x37,0xFF};//modbus标识符
    uint8_t comm_485_fun_code[4] = {0x03,0x04,0x06,0x16};//modbus功能码
    uint16_t comm_485_reg_count[2] = {0x0001,0x0002};//modbus寄存器数量

signals:
    void kdy_signal(int);
    void SW_test_signal(int);
    void ReSendClear(int);
};


#endif // CANSHU_WIDGET_H
