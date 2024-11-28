#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QGridLayout>
#include "sqlite.h"
#include "mian_widget.h"
#include "net_widget.h"
#include "canshu_widget.h"
#include "xitong_widget.h"
#include "camera_widget.h"
#include "history_widget.h"
#include "alarmlog_widget.h"
#include "data_thread.h"
#include "serialport.h"
#include "tcp_socket.h"
#include <stdlib.h>
#include <string.h>
#include <QSettings>
#include <QFile>
#include <cstdlib>
#include "ceventfilter.h"

//#define BRUN 1 //烧录模式
#define ARM 1 //ARM环境
#define RESEND 1 //补传功能
#define FLOOD_FLOW 1 //泄洪流量计算
#define PI acos(-1)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QString Version;
    static QSettings *iniFile;
    static QString dbFile;
    static QString logFile;
private slots:
    void button_init();
    void button_main_clicked();
    void button_net_clicked();
    void button_canshu_clicked();
    void button_xitong_clicked();
    void button_camera_clicked();
    void button_history_clicked();
    void button_alarmLog_clicked();
    void switchPage(int nIndex);//切换设置
public slots:
    void timeUpdate(void);
private:
    QLabel *lowPower_label;//低功耗弹出label，便于触摸退出
    QStackedWidget *stackedWidget;
    QLabel *label_title;
    QLabel *label_back;
    QDateTime dateTime;
    QLabel *label_time;
    QTimer *timer;

    QPushButton *button_main;
    QPushButton *button_net;
    QPushButton *button_canshu;
    QPushButton *button_xitong;
    QPushButton *button_camera;
    QPushButton *button_history;
    QPushButton *button_alarmLog;

    uint8_t OSD_count = 0;//字符叠加计数
};
#endif // MAINWINDOW_H
