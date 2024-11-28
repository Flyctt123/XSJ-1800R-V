#include "mainwindow.h"
#include <QApplication>
#include<QtDebug>
#include<QMutex>
#include<QFile>
#include<QDate>
#include<QDir>
#include <iostream>
#include "ui_mian_widget.h"

extern TCP_COMM tcp_comm[5];
extern Modbus modbus[5];//COM1~3 + 开度仪 + LPC1778串口
sqlite *sqlite_thread;
serialport *serialport_thread;
tcp_socket *Tcp_socket;
data_Thread *data_thread;
extern DATA_RES data_result;
extern uint8_t DO_Flag;//开出控制
extern OSD_flag osd_flag;
uint8_t log_max_M = 5;//日志最多存5M

QString MainWindow::Version = "XSJ1800RV1.04A/D(NM.2024.01234.00)";
#ifdef ARM
    QSettings *MainWindow::iniFile = new QSettings("/home/Config.ini",QSettings::IniFormat);
    QString MainWindow::dbFile = "/home/MyDataBase.db";
    QString MainWindow::logFile = "/home/log.txt";
    QDir dir_images1("/home/images/images1");
    QDir dir_images2("/home/images/images2");
    QDir dir_images3("/home/images/images3");
#else
    QString path = QDir::currentPath();
    QSettings *MainWindow::iniFile = new QSettings(path + "/home/Config.ini",QSettings::IniFormat);
    QString MainWindow::dbFile = path +  "/home/MyDataBase.db";
    QString MainWindow::logFile = path +  "/home/log.txt";
    QDir dir_images1(path + "/home/images/images1");
    QDir dir_images2(path + "/home/images/images2");
    QDir dir_images3(path + "/home/images/images3");
#endif

void LogMsgOutput(QtMsgType type,const QMessageLogContext &context,const QString &msg);//日志功能

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug()<<"Version=" << Version;
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);

    iniFile->setIniCodec(QTextCodec::codecForName("UTF-8"));//ini配置文件支持中文

    if(!dir_images1.exists())
        dir_images1.mkpath("/home/images/images1");//创建文件夹
    if(!dir_images2.exists())
        dir_images2.mkpath("/home/images/images2");//创建文件夹
    if(!dir_images3.exists())
        dir_images3.mkpath("/home/images/images3");//创建文件夹

    QFontDatabase::addApplicationFont(":/fonts/fonts/simsun.ttc");//加载字体耗时

    QPalette pal =this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/back/image/blue_color_back.png")));
    setPalette(pal);

    lowPower_label = new QLabel();//低功耗弹窗
    lowPower_label->setGeometry(0,0,480,272);
    lowPower_label->hide();
    lowPower_label->installEventFilter(this);

    label_back = new QLabel(this);
    label_back->setFixedSize(380,220);
    label_back->setStyleSheet("background: rgb(234,234,234)");

    label_time = new QLabel(this);
    label_time->setFixedSize(67,25);
    label_time->setStyleSheet("font-size:12px;");
    dateTime = QDateTime::currentDateTime();
    label_time->setText(dateTime.toString("yyyy-MM-dd \nHH:mm:ss"));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeUpdate);
#ifdef BRUN
    //timer->start(1000);//烧录程序不刷新
#else
    timer->start(1000);
#endif

    stackedWidget = new QStackedWidget(widget);
#ifdef BRUN
    label_title = new QLabel("烧录程序",widget);
#else
    label_title = new QLabel("遥测终端机",widget);
#endif

    label_title->setStyleSheet("font-size:24px;font-weight:bold;");
    label_title->setAlignment(Qt::AlignCenter);

    mian_widget *main_widegt_page = new mian_widget();
    net_widget *net_widget_page = new net_widget();
    canshu_widget *canshu_widget_page = new canshu_widget();
    xitong_widget *xitong_widegt_page = new xitong_widget();
    camera_widget *camera_widget_page = new camera_widget();
    history_widget *history_widget_page = new history_widget();
    alarmLog_widget *alarmLog_widget_page = new alarmLog_widget();

    button_main = new QPushButton("主界面",widget);
    button_net = new QPushButton("网络信息",widget);
    button_canshu = new QPushButton("参数配置",widget);
    button_xitong = new QPushButton("系统设置",widget);
    button_camera = new QPushButton("摄像头",widget);
    button_history = new QPushButton("历史数据",widget);
    button_alarmLog = new QPushButton("告警记录",widget);

    button_main->setFixedSize(81,35);
    button_net->setFixedSize(81,35);
    button_canshu->setFixedSize(81,35);
    button_xitong->setFixedSize(81,35);
    button_camera->setFixedSize(81,35);
    button_history->setFixedSize(81,35);
    button_alarmLog->setFixedSize(81,35);

    stackedWidget->addWidget(main_widegt_page);
    stackedWidget->addWidget(net_widget_page);
    stackedWidget->addWidget(canshu_widget_page);
    stackedWidget->addWidget(xitong_widegt_page);
    stackedWidget->addWidget(camera_widget_page);
    stackedWidget->addWidget(history_widget_page);
    stackedWidget->addWidget(alarmLog_widget_page);

    QGridLayout *pLayout = new QGridLayout(widget);
    pLayout->addWidget(label_title,0,0,1,2);
    pLayout->addWidget(button_main,0,2,1,1);
    pLayout->addWidget(button_net,0,3,1,1);
    pLayout->addWidget(button_canshu,0,4,1,1);
    pLayout->addWidget(button_xitong,0,5,1,1);
    pLayout->addWidget(button_camera,1,0,1,1);
    pLayout->addWidget(button_history,2,0,1,1);
    pLayout->addWidget(button_alarmLog,3,0,1,1);
    pLayout->addWidget(label_time,5,0,1,1);
    pLayout->addWidget(label_back,1,1,5,5);
    pLayout->addWidget(stackedWidget,1,1,5,5);  //addWidget(待添加QWidget，行数，列数，跨越行数，跨越列数);
    pLayout->setHorizontalSpacing(3);//设置水平间距
    pLayout->setVerticalSpacing(3);//设置垂直间距
    pLayout->setContentsMargins(6,6,6,6);//设置布局内部四边的空隙
    widget->setLayout(pLayout);
    stackedWidget->raise();

    connect(button_main, &QPushButton::clicked, this, &MainWindow::button_main_clicked);
    connect(button_net, &QPushButton::clicked, this, &MainWindow::button_net_clicked);
    connect(button_canshu, &QPushButton::clicked, this, &MainWindow::button_canshu_clicked);
    connect(button_xitong, &QPushButton::clicked, this, &MainWindow::button_xitong_clicked);
    connect(button_camera, &QPushButton::clicked, this, &MainWindow::button_camera_clicked);
    connect(button_history, &QPushButton::clicked, this, &MainWindow::button_history_clicked);
    connect(button_alarmLog, &QPushButton::clicked, this, &MainWindow::button_alarmLog_clicked);

    button_init();
    button_main_clicked();

    data_thread = new data_Thread(this);
    data_thread->start();
    sqlite_thread = new sqlite(this);
    serialport_thread = new serialport(this);
    Tcp_socket = new tcp_socket(this);

    connect(Tcp_socket,SIGNAL(uploadBaseSet(int)),net_widget_page,SLOT(setUpload_IpSet(void)));//水文协议 更改IP地址
    connect(Tcp_socket,SIGNAL(uploadRunSet(int)),canshu_widget_page,SLOT(setUploadRunSet(void)));//水文协议 更改运行参数配置表
    connect(Tcp_socket,SIGNAL(uploadBaseSet(int)),canshu_widget_page,SLOT(setUploadBaseSet(void)));//水文协议 更改基本配置表
    connect(Tcp_socket,SIGNAL(uploadPassword(QString)),canshu_widget_page,SLOT(setUploadPasswordToUI(QString)));//水文协议 更改密码
    connect(canshu_widget_page,SIGNAL(kdy_signal(int)),serialport_thread,SLOT(kdy_send_Modbus(int)));//水文协议 开度仪控制
    connect(canshu_widget_page,SIGNAL(SW_test_signal(int)),Tcp_socket,SLOT(report_SW_test(void)));//水文协议 测试报
    connect(serialport_thread,SIGNAL(tcp_alarm_signal(int)),Tcp_socket,SLOT(report_SW_add(void)));//水文协议 告警信号触发加报报
    connect(xitong_widegt_page,SIGNAL(check_time_signal(int)),Tcp_socket,SLOT(report_SW_test(void)));//水文协议 0点校时
    connect(Tcp_socket,SIGNAL(uploadTime(uint8_t)),canshu_widget_page,SLOT(setUploadTimeToUI(uint8_t)));//水资源协议 刷新定时报时间
    connect(Tcp_socket,SIGNAL(kdy_signal(int)),serialport_thread,SLOT(kdy_send_Modbus(int)));//水资源协议 开度仪启停控制
    connect(xitong_widegt_page,SIGNAL(sysClear(int)),Tcp_socket,SLOT(delete_AllData_Total(void)));//清空历史数据
    connect(xitong_widegt_page,SIGNAL(reSendClear(int)),Tcp_socket,SLOT(delete_ReSendData_Total(void)));//清空补传数据
    connect(canshu_widget_page,SIGNAL(ReSendClear(int)),Tcp_socket,SLOT(delete_ReSendData_Total(void)));//清空补传数据
    connect(net_widget_page,SIGNAL(ReSendclear(int)),Tcp_socket,SLOT(delete_ReSendData_Total(void)));//清空补传数据

    //开出检测放在main_widget会死机，不知道为啥，暂时放mainwidow下面
    if((DO_Flag >> 0) & 1)
        main_widegt_page->ui->checkBox_DO1->setChecked(true);
    else
        main_widegt_page->ui->checkBox_DO1->setChecked(false);
    if((DO_Flag >> 1) & 1)
        main_widegt_page->ui->checkBox_DO2->setChecked(true);
    else
        main_widegt_page->ui->checkBox_DO2->setChecked(false);
    if((DO_Flag >> 2) & 1)
        main_widegt_page->ui->checkBox_DO3->setChecked(true);
    else
        main_widegt_page->ui->checkBox_DO3->setChecked(false);

    qInstallMessageHandler(LogMsgOutput);//安装日志功能
    qDebug()<<"Version=" << Version;
#ifdef ARM
    system("echo 208 > /sys/class/gpio/export");//看门狗
    system("echo out > /sys/class/gpio/gpio208/direction");

    //系统时间校正，防止时间+8小时
    system("hwclock -s");
#endif
}

MainWindow::~MainWindow()
{
}

void LogMsgOutput(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    //加锁
   static QMutex mutex;
   mutex.lock();

   QByteArray localMsg = msg.toLocal8Bit();

   QString strMsg("");
   switch(type)
   {
       case QtDebugMsg:
           strMsg = QString("Debug:");
       break;
       case QtWarningMsg:
           strMsg = QString("Warning:");
       break;
       case QtCriticalMsg:
           strMsg = QString("Critical:");
       break;
       case QtFatalMsg:
           strMsg = QString("Fatal:");
       break;
       default:
       break;
   }

   // 设置输出信息格式
   QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

   //详细打印
   //QString strMessage = QString("%1  File:%2  Line:%3  Function:%4  DateTime:%5 Message:%6")
   //        .arg(strMsg).arg(context.file).arg(context.line).arg(context.function).arg(strDateTime).arg(localMsg.constData());

   //简略打印
   QString strMessage = QString("%1").arg(context.line);//随便赋值一下，解决编译告警
   strMessage = QString("%1 Message:%2").arg(strDateTime).arg(localMsg.constData());

   // 输出信息至文件中（读写、追加形式）
#ifdef ARM
    QFile file("/home/log.txt");
#else
    QString path = QDir::currentPath();
    QFile file(path + "/home/log.txt");
#endif
    if (file.size() > (log_max_M * 1024 * 1024))
    {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))//覆盖
            return;
    }
    else
    {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))//追加
            return;
    }
    QTextStream stream(&file);
    stream << strMessage << "\r\n";
    file.flush();
    file.close();
    // 解锁
    mutex.unlock();
}

void MainWindow::button_init()
{
    button_main->setStyleSheet(/**正常情况下样式**/
                               "QPushButton{"
                                   "font: bold 9.5pt 'simsun';"
                                   "color: #2f3640;"
                                   "background-color: #a2bcd0;"
                                   "border-color: #2f3640;"
                                   "border-radius: 15px;"
                                   "border-style: solid;"
                                   "border-width: 2px;"
                                   "padding: 5px;"
                               "}");

    button_main->setFocusPolicy(Qt::NoFocus);
    button_net->setStyleSheet("QPushButton{"
                              "font: bold 9.5pt 'simsun';"
                              "color: #2f3640;"
                              "background-color: #a2bcd0;"
                              "border-color: #2f3640;"
                              "border-radius: 15px;"
                              "border-style: solid;"
                              "border-width: 2px;"
                              "padding: 5px;"
                          "}");
    button_net->setFocusPolicy(Qt::NoFocus);
    button_canshu->setStyleSheet("QPushButton{"
                                 "font: bold 9.5pt 'simsun';"
                                 "color: #2f3640;"
                                 "background-color: #a2bcd0;"
                                 "border-color: #2f3640;"
                                 "border-radius: 15px;"
                                 "border-style: solid;"
                                 "border-width: 2px;"
                                 "padding: 5px;"
                             "}");
    button_canshu->setFocusPolicy(Qt::NoFocus);
    button_xitong->setStyleSheet("QPushButton{"
                                 "font: bold 9.5pt 'simsun';"
                                 "color: #2f3640;"
                                 "background-color: #a2bcd0;"
                                 "border-color: #2f3640;"
                                 "border-radius: 15px;"
                                 "border-style: solid;"
                                 "border-width: 2px;"
                                 "padding: 5px;"
                             "}");
    button_xitong->setFocusPolicy(Qt::NoFocus);
    button_camera->setStyleSheet("QPushButton{"
                                 "font: bold 9.5pt 'simsun';"
                                 "color: #2f3640;"
                                 "background-color: #a2bcd0;"
                                 "border-color: #2f3640;"
                                 "border-radius: 15px;"
                                 "border-style: solid;"
                                 "border-width: 2px;"
                                 "padding: 5px;"
                             "}");
    button_camera->setFocusPolicy(Qt::NoFocus);
    button_history->setStyleSheet("QPushButton{"
                                  "font: bold 9.5pt 'simsun';"
                                  "color: #2f3640;"
                                  "background-color: #a2bcd0;"
                                  "border-color: #2f3640;"
                                  "border-radius: 15px;"
                                  "border-style: solid;"
                                  "border-width: 2px;"
                                  "padding: 5px;"
                              "}");
    button_history->setFocusPolicy(Qt::NoFocus);
    button_alarmLog->setStyleSheet("QPushButton{"
                                   "font: bold 9.5pt 'simsun';"
                                   "color: #2f3640;"
                                   "background-color: #a2bcd0;"
                                   "border-color: #2f3640;"
                                   "border-radius: 15px;"
                                   "border-style: solid;"
                                   "border-width: 2px;"
                                   "padding: 5px;"
                               "}");
    button_alarmLog->setFocusPolicy(Qt::NoFocus);
    //button_backups->setFixedSize(100,81);
    //button_backups->setStyleSheet("font-size:22px;font-weight:bold;");
}

void MainWindow::button_main_clicked()
{
    int i = 0;
    switchPage(i);
    button_init();
    button_main->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::button_net_clicked()
{
    int i = 1;
    switchPage(i);
    button_init();
    button_net->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::button_canshu_clicked()
{
    int i = 2;
    switchPage(i);
    button_init();
    button_canshu->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::button_xitong_clicked()
{
    int i = 3;
    switchPage(i);
    button_init();
    button_xitong->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::button_camera_clicked()
{
    int i = 4;
    switchPage(i);
    button_init();
    button_camera->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::button_history_clicked()
{
    int i = 5;
    switchPage(i);
    button_init();
    button_history->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::button_alarmLog_clicked()
{
    int i = 6;
    switchPage(i);
    button_init();
    button_alarmLog->setStyleSheet("QPushButton{"
                               "font: bold 9.5pt 'simsun';"
                               "color: #FFFFFF;"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
                               "border-color: #2f3640;"
                               "border-radius: 15px;"
                               "border-style: solid;"
                               "border-width: 2px;"
                               "padding: 5px;"
                           "}");
}

void MainWindow::switchPage(int nIndex)
{
    stackedWidget->setCurrentIndex(nIndex);
}

bool led_run_flag = true;
bool watch_dog_flag = true;
void MainWindow::timeUpdate()
{
    OSD_count ++;
    if(OSD_count > 4)
    {
        OSD_count = 0;
#ifdef ARM
        QFile file("/home/power_value.txt");
        system("cat /sys/bus/iio/devices/iio:device0/in_voltage0_raw > /home/power_value.txt");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString btnstate=file.readAll();
        file.close();
        data_result.power_value=(btnstate.toInt() / (2.2 / 19.1) / 1000) + 0.28;//0.28微调

        //看门狗
        if(watch_dog_flag)
            system("echo 1 > /sys/class/gpio/gpio208/value");
        else
            system("echo 0 > /sys/class/gpio/gpio208/value");
        watch_dog_flag = !watch_dog_flag;

        //字符叠加
        if(MainWindow::iniFile->value("/Camera/Open1").toUInt() == 1)
        {
            QString camera_ip = MainWindow::iniFile->value("/Camera/IP1").toString();
            QString camera_name = MainWindow::iniFile->value("/Camera/Name1").toString();
            QString camera_password = MainWindow::iniFile->value("/Camera/Password1").toString();
            QString osd_code = "";
            if(osd_flag.osd_water)
                osd_code += "<TextOverlay><id>1</id><enabled>true</enabled><positionX>0</positionX><positionY>80</positionY><displayText>" + QString::fromLocal8Bit("水位 ") + QString::number(data_result.data_water,'f',2) +" m</displayText></TextOverlay>";
            else
                osd_code += "<TextOverlay><id>1</id><enabled>false</enabled><positionX>0</positionX><positionY>80</positionY><displayText>" + QString::fromLocal8Bit("水位 ") + QString::number(data_result.data_water,'f',2) +" m</displayText></TextOverlay>";
            if(osd_flag.osd_flow_inst)
                osd_code += "<TextOverlay><id>2</id><enabled>true</enabled><positionX>0</positionX><positionY>60</positionY><displayText>" + QString::fromLocal8Bit("瞬时流量 ") + QString::number(data_result.data_flow_inst,'f',2) +" m3/s</displayText></TextOverlay>";
            else
                osd_code += "<TextOverlay><id>2</id><enabled>false</enabled><positionX>0</positionX><positionY>60</positionY><displayText>" + QString::fromLocal8Bit("瞬时流量 ") + QString::number(data_result.data_flow_inst,'f',2) +" m3/s</displayText></TextOverlay>";

            //字符叠加
            QString osd_cmd = "curl --insecure --anyauth -u " + camera_name + ":" + camera_password + " -H \"Content-Type: text/plain;charset=UTF-8\" -X PUT "
                              "-d '<TextOverlayList>" + osd_code + "</TextOverlayList>' http://" + camera_name + ":" + camera_password + "@" + camera_ip +"/ISAPI/System/Video/inputs/channels/1/overlays/text"  + " &";
            system(osd_cmd.toLatin1());
        }
#endif
    }

    dateTime = QDateTime::currentDateTime();
    label_time->setText(dateTime.toString("yyyy-MM-dd \nHH:mm:ss"));

#ifdef ARM
    if(led_run_flag)
        system("echo 1 > /sys/class/leds/user-led-run/brightness");
    else
        system("echo 0 > /sys/class/leds/user-led-run/brightness");
    led_run_flag = !led_run_flag;
#endif
}
