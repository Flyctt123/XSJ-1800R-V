#include "xitong_widget.h"
#include "ui_xitong_widget.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <QTimer>

extern bool KeyBoard_Code,KeyBoard_ABC_Code,keyBoard_flag,keyBoard_ABC_flag;
extern QSerialPort *serial[7];
bool sys_busy = false;

xitong_widget::xitong_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::xitong_widget)
{
    ui->setupUi(this);
    ui->label_version->setText("软件版本：" + MainWindow::Version);
    ui->tabWidget->setStyleSheet(
        "QTabBar::tab{font-size:15px;}"
        "QTabWidget::pane{border: 2px solid rgb(210, 210, 210);\
        background:rgb(246, 246, 246);\
        border-top-color:transparent;}\
        QTabWidget::tab-bar{background:rgb(0, 0, 0);subcontrol-position:left;}\
        QTabBar::tab{width:80px;/*宽度根据实际需要进行调整*/"
        "height:16px;\
        background:rgb(210, 210, 210);\
        border: 5px solid rgb(210, 210, 210);\
        border-top-left-radius: 8px;\
        border-top-right-radius: 8px;}"
        "QTabBar::tab:selected{"
        "background:rgb(246, 246, 246);"
        "border-bottom-color:rgb(246, 246, 246);}"
        "QTabBar::tab:!selected{"
        "background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240, 240, 240),"
        "stop:0.5 rgb(190, 190, 190), stop:1 rgb(225, 225, 225));}"
    );
    ui->tabWidget->setCurrentIndex(0);

    ui->lineEdit_station_info->installEventFilter(this);
    ui->lineEdit_year->installEventFilter(this);
    ui->lineEdit_mon->installEventFilter(this);
    ui->lineEdit_day->installEventFilter(this);
    ui->lineEdit_hour->installEventFilter(this);
    ui->lineEdit_min->installEventFilter(this);
    ui->lineEdit_sec->installEventFilter(this);

    xitong_button_init(ui->pushButton_save_info);
    xitong_button_init(ui->usb_Button_check);
    xitong_button_init(ui->usb_Button_picture);
    xitong_button_init(ui->usb_Button_data);
    xitong_button_init(ui->usb_Button_history);
    xitong_button_init(ui->pushButton_restart);
    xitong_button_init(ui->pushButton_reset);
    xitong_button_init(ui->usb_Button_update);
    xitong_button_init(ui->pushButton_save_time);
    xitong_button_init(ui->pushButton_sysclear);
    xitong_button_init(ui->pushButton_reSendclear);
    xitong_button_init(ui->usb_Button_Config_update);

    ui->lineEdit_station_info->setText(MainWindow::iniFile->value("/STATION_INFO/ID").toString());

    //xitong_button_init(ui->pushButton_ts);
//    pProgressBar = new QProgressBar(this);
//    pProgressBar->setAlignment(Qt::AlignHCenter);
//    pProgressBar->setGeometry(210,370,360,25);
//    pProgressBar->setOrientation(Qt::Horizontal);  // 水平方向
//    pProgressBar->setRange(0,400);
//    pProgressBar->setValue(0);
//    pProgressBar->setStyleSheet("QProgressBar{height:22px; text-align:center; font-size:14px; color:white; border-radius:11px; background:#1D5573;}"

//                                "QProgressBar::chunk{border-radius:11px;background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #41d6ff);}");
    timer =new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout_hour()));
    timer->start(1000 * 60 * 60);
}

xitong_widget::~xitong_widget()
{
    delete ui;
}

bool xitong_widget::eventFilter(QObject *watch, QEvent  *evn)
{
    if ((watch == ui->lineEdit_station_info) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_station_info);
    }
    if ((watch == ui->lineEdit_year) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_year);
    }
    if ((watch == ui->lineEdit_mon) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_mon);
    }
    if ((watch == ui->lineEdit_day) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_day);
    }
    if ((watch == ui->lineEdit_hour) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_hour);
    }
    if ((watch == ui->lineEdit_min) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_min);
    }
    if ((watch == ui->lineEdit_sec) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_sec);
    }

    return QWidget::eventFilter(watch,evn);
}

void xitong_widget::callKeyBoard(QLineEdit *a)
{
    if(KeyBoard_Code==false)
    {
        keyBoard = new KeyBoard(0, a);
        keyBoard->setGeometry(298, 130, 180, 140);
        keyBoard->show();
        KeyBoard_Code=true;
    }
    else
    {
        if(keyBoard_flag==true)
        {
            keyBoard->close();
        }
        keyBoard = new KeyBoard(0, a);
        keyBoard->setGeometry(298, 130, 180, 140);
        keyBoard->show();
    }
}

void xitong_widget::callKeyBoard_ABC(QLineEdit *a)
{
    if(KeyBoard_ABC_Code==false)
    {
        keyBoard_ABC = new KeyBoard_ABC(0, a);
        keyBoard_ABC->setGeometry(0, 120, 476, 150);
        keyBoard_ABC->show();
        KeyBoard_ABC_Code=true;
    }
    else
    {
        if(keyBoard_ABC_flag==true)
        {
            keyBoard_ABC->close();
        }
        keyBoard_ABC = new KeyBoard_ABC(0, a);
        keyBoard_ABC->setGeometry(2, 120, 476, 150);
        keyBoard_ABC->show();
    }
}

int32_t xitong_widget::myexec(const char *cmd, std::vector<std::string> &resvec)
{
    resvec.clear();
    FILE *pp = popen(cmd, "r"); //建立管道
    if (!pp)
    {
        return -1;
    }
    char tmp[1024]; //设置一个合适的长度，以存储每一行输出
    while (fgets(tmp, sizeof(tmp), pp) != NULL)
    {
        if (tmp[strlen(tmp) - 1] == '\n')
        {
            tmp[strlen(tmp) - 1] = '\0'; //去除换行符
        }
        resvec.push_back(tmp);
    }
    pclose(pp); //关闭管道
//    for (int i = 0; i<(int)resvec.size(); i++)
//    {
//        ui->textBrowser->append(QString(resvec.at(i).c_str()));
//    }
    return resvec.size();
}

void xitong_widget::xitong_button_init(QPushButton *button_init)
{
    button_init->setStyleSheet(
        /**正常情况下样式**/
        "QPushButton{"
            "font: 9pt '微软雅黑';"
            "color: #2f3640;"
            "background-color: #f5f6fa;"
            "border-color: #2f3640;"
            "border-radius: 10px;"
            "border-style: solid;"
            "border-width: 2px;"
            "padding: 2px;"
        "}"

        /**鼠标停留在按钮上的样式**/
        "QPushButton::hover{"
            "color: #FFFFFF;"
            "background-color: #718093;"
            "border-color: #2f3640;"
        "}"

        /**鼠标按压下去的样式**/
        "QPushButton::pressed,QPushButton::checked{"
            "color: #FFFFFF;"
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);"
        "}"

        /**按钮失能情况下样式**/
        "QPushButton::disabled{"
            "color: #FFFFFF;"
            "background-color: #dcdde1;"
            "border-color: #dcdde1;"
        "}"
    );
}

void xitong_widget::serial_send_disconnect()
{
    QByteArray data_send,data_crc;//data1为数据，data2为CRC校验码
    uint16_t crc16;

    data_send[0]=0xAA;
    data_send[1]=0x22;
    data_send[2]=0x01;
    data_send[3]=0x00;
    data_send[4]=0x00;
    data_send[5]=0x00;
    data_send[6]=0x00;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;
    data_crc[1]=crc16>>8 & 0xff;

    serial[2]->write(data_send);//串口发送头
    serial[2]->write(data_crc);//发送CRC校验码
}

uint16_t xitong_widget::ModBusCRC16(QByteArray data)
{
    int len = data.size();
    uint16_t crc=0xffff;
    uint8_t i, j;
    uint8_t temp=0;
    for(i=0; i<len; i++)
    {
        temp=data.at(i);
        crc^=temp;
        for(j=0;j<8;j++)
        {
        //判断右移出的是不是1，如果是1则与多项式进行异或。
            if(crc&0X0001)
            {
                crc>>=1;//先将数据右移一位
                crc^=0XA001;//与上面的多项式进行异或
            }
            else//如果不是1，则直接移出
                crc>>=1;//直接移出
        }
    }
    return  crc;
}

void xitong_widget::on_usb_Button_check_clicked()
{
    ui->label_usb->clear();
    usb_path = "";
    DIR *dir_ptr;
    if ((dir_ptr = opendir("/proc/scsi/usb-storage")) == NULL)
    {
        ui->label_usb->setText("U盘不存在");
        qDebug()<<"USB NOT Find";
    }
    else
    {
        ui->label_usb->setText("U盘存在");

        //找出sd**
        for (int i = 0; i < 6; i++)
        {
            const char *sdx[] = {"sda", "sdb", "sdc", "sdd", "sde", "sdf"};
            char open_path[64] = {0};
            sprintf(open_path, "/sys/block/%s/removable", sdx[i]);

            //判断磁盘是否属于U盘
            int fd = open(open_path, O_RDONLY);
            if (fd == -1)
            {
                ui->label_usb->setText("U盘打开失败");
                continue;
            }
            else
            {
                ui->label_usb->setText("U盘打开成功");
                char buf[32] = {0};
                if (read(fd, buf, sizeof(buf)) > 0)//读
                {
                    if (buf[0] == '1')//属于U盘
                    {
                        // 如果已经自动挂载，找到目录，拷贝就行
                        std::vector<std::string> resvec;
                        char df_path[64] = {0};
                        sprintf(df_path,"df -h|grep /dev/%s", sdx[i]);
                        myexec(df_path, resvec);//执行df_path，把显示结果赋给resvec
                        if (resvec.size() == 0)// 执行df_path，没有结果，需要手动挂载
                        {
                            ui->label_usb->setText("自动挂载失败");
                        }
                        else
                        {
                            char *str = (char *)resvec.back().c_str();
                            const char s[2] = " ";
                            char path[128] = {0};
                            char *token;
                            token = strtok(str, " "); //获取第一个子字符串
                            while (token != NULL)
                            { //继续获取其他的子字符串
                                strcpy(path, token);
                                token = strtok(NULL, s);
                            }
                            //自动挂在路径
                            usb_path = QString(path);
                            qDebug()<<"USB OPEN SUCCEED = "<< usb_path;
                            break;
                        }
                    }
                    else
                    {
                        ui->label_usb->setText("U盘设备异常");
                    }
                }
            }
           // QWidget::close()与stdio.h中的文件关闭标准函数close()产生了歧义
           // 区分成员函数与全局函数，就要在全局函数前面增加"::"双冒号的标志
           ::close(fd);
        }
        closedir(dir_ptr);
    }

    if(usb_path == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("未检测到U盘"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ;
        }
        else
        {
            ;
        }
    }
}

void xitong_widget::on_usb_Button_picture_clicked()
{
    sys_busy = true;
    QString copy_path = "";
    if(ui->comboBox->currentIndex() == 0)
    {
        copy_path = "cp -rf /home/images/images1 " + usb_path;
    }
    else if(ui->comboBox->currentIndex() == 1)
    {
        copy_path = "cp -rf /home/images/images2 " + usb_path;
    }
    else
    {
        copy_path = "cp -rf /home/images/images3 " + usb_path;
    }

    if(usb_path == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("请先检测USB设备"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ;
        }
        else
        {
            ;
        }
    }
    else
    {
        ui->label_usb->setText("图片导出中，请稍等...");
        ui->label_usb->adjustSize();//强制刷新页面
        system(copy_path.toLatin1());
        system("sync");

        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("图片导出完成"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ui->label_usb->setText("");
            usb_path = "";
        }
        else
        {
            ;
        }
    }
    sys_busy = false;
}

void xitong_widget::on_usb_Button_data_clicked()
{
    sys_busy = true;
    QString copy_path = "cp /home/MyDataBase.db " + usb_path;
    if(usb_path == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("请先检测USB设备"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ;
        }
        else
        {
            ;
        }
    }
    else
    {
        ui->label_usb->setText("数据导出中，请稍等...");
        ui->label_usb->adjustSize();//强制刷新页面
        system(copy_path.toLatin1());
        system("sync");

        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("数据导出完成"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ui->label_usb->setText("");
            usb_path = "";
        }
        else
        {
            ;
        }
    }
    sys_busy = false;
}

bool xitong_widget::FindFileForDelete(const QString &path)
{
    QDir dir(path);
    if (!dir.exists())//不存在
        return false;
    dir.setFilter(QDir::Dirs|QDir::Files);//获取所有的文件夹和文件
    dir.setSorting(QDir::DirsFirst);//文件夹排在前面
    QFileInfoList list = dir.entryInfoList();//获取文件夹和文件列表
    int i=0;
    qDebug()<<"rm picture judge!";
    do{

        QFileInfo fileInfo = list.at(i);
        if((fileInfo.fileName()==".") | (fileInfo.fileName()==".."))//去掉.和..文件夹，这是linux特有的
        {
               i++;
               continue;
        }
        bool bisDir=fileInfo.isDir();
        if(bisDir)//该路径是目录
        {
            FindFileForDelete(fileInfo.filePath());
        }
        else
        {
            //如果是文件，判断文件日期 目前默认是30天。
           QDateTime delDateTime = QDateTime::currentDateTime().addDays(-30);
           qDebug()<<"DEL DateTime="<<delDateTime;

           qint64 nSecs = delDateTime.secsTo(fileInfo.created());//Linux 30天前的时间和该文件创建时间的差值秒
           //qint64 nSecs = delDateTime.secsTo(fileInfo.birthTime());//Windows 30天前的时间和该文件创建时间的差值秒
           qDebug()<<"cut Time="<<nSecs;
           if (nSecs < 0)
           {
               qDebug()<<"rm SATRT";
               //qDebug() << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10).arg(fileInfo.fileName(),10).arg(fileInfo.path()))<<endl;
               //删除30天前的文件
               fileInfo.dir().remove(fileInfo.fileName());
           }
        }
        i++;
    }while(i<list.size());
    return true;
}

void xitong_widget::on_pushButton_restart_clicked()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("确认重启设备？"));
    m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

    int ret = m_box->exec();
    if (ret == QMessageBox::Yes)
    {
        qDebug()<<"Restart";
        serial_send_disconnect();
        system("reboot -f");
    }
    else
    {
        ;
    }
}

void xitong_widget::timerTimeout_hour()
{
    if(QTime::currentTime().hour() == 0)
        emit check_time_signal(1);//每天0点校时
#ifdef ARM
    FindFileForDelete("/home/images/images1");
#else
    QString path = QDir::currentPath();
    FindFileForDelete(path + "/home/images/images1");
#endif
}

void xitong_widget::on_usb_Button_update_clicked()
{
    QString copy_path = "cp " + usb_path + "/XSJ* /home/XSJ1800RV";
    if(usb_path == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("请先检测USB设备"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ;
        }
        else
        {
            ;
        }
    }
    else
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("程序本地升级？"));
        m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Yes)
        {
            serial_send_disconnect();
            system("killall XSJ1800RV");
            //qDebug()<<copy_path;
            system(copy_path.toLatin1());
            system("sync");
            system("reboot -f");
        }
        else
        {
            ;
        }
    }
}

void xitong_widget::on_pushButton_save_time_clicked()
{
    QString year = ui->lineEdit_year->text();
    QString mon = ui->lineEdit_mon->text();
    QString day = ui->lineEdit_day->text();
    QString hour = ui->lineEdit_hour->text();
    QString min = ui->lineEdit_min->text();
    QString sec = ui->lineEdit_sec->text();

    QString dateTime = "date -s \"" +  year + "-" + mon + "-" + day + " " + hour + ":" + min + ":" + sec + "\"";
    qDebug()<<dateTime;
    QString timetohw = "hwclock -w";
    QString hwtotime = "hwclock -s";
#ifdef ARM
    system(dateTime.toLatin1());
    QThread::msleep(200);
    system(timetohw.toLatin1());
    QThread::msleep(200);
    system(hwtotime.toLatin1());
#endif
}

void xitong_widget::on_tabWidget_tabBarClicked(int index)
{
    if(index == 3)
    {
        QString time = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
        ui->lineEdit_year->setText(time.mid(0,4));
        ui->lineEdit_mon->setText(time.mid(4,2));
        ui->lineEdit_day->setText(time.mid(6,2));
        ui->lineEdit_hour->setText(time.mid(8,2));
        ui->lineEdit_min->setText(time.mid(10,2));
        ui->lineEdit_sec->setText(time.mid(12,2));
    }
}

void xitong_widget::on_pushButton_reset_clicked()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("恢复出厂设置会重启设备"));
    m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

    int ret = m_box->exec();
    if (ret == QMessageBox::Yes)
    {
        qDebug()<<"Reset";
        serial_send_disconnect();
        system("cp /home/Config_backup.ini /home/Config.ini");
        system("sync");
        system("reboot -f");
    }
    else
    {
        ;
    }
}

void xitong_widget::on_pushButton_sysclear_clicked()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("清除历史数据?"));
    m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

    int ret = m_box->exec();
    if (ret == QMessageBox::Yes)
    {
        qDebug()<<"History Clear";
        emit sysClear(1);
    }
    else
    {
        ;
    }
}

void xitong_widget::on_usb_Button_Config_update_clicked()
{
    QString copy_path = "cp " + usb_path + "/Config.ini /home/Config.ini";
    if(usb_path == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("请先检测USB设备"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ;
        }
        else
        {
            ;
        }
    }
    else
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("配置文件更新？"));
        m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Yes)
        {
            serial_send_disconnect();
            system("killall XSJ1800RV");
            system(copy_path.toLatin1());
            system("sync");
            system("reboot -f");
        }
        else
        {
            ;
        }
    }
}

void xitong_widget::on_pushButton_reSendclear_clicked()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("清空补传数据？"));
    m_box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

    int ret = m_box->exec();
    if (ret == QMessageBox::Yes)
    {
        qDebug()<<"ReSend Clear";
        emit reSendClear(1);
    }
    else
    {
        ;
    }
}

void xitong_widget::on_usb_Button_history_clicked()
{
    sys_busy = true;
    QString copy_path = "cp /home/log.txt " + usb_path;
    if(usb_path == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("请先检测USB设备"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ;
        }
        else
        {
            ;
        }
    }
    else
    {
        ui->label_usb->setText("日志导出中，请稍等...");
        ui->label_usb->adjustSize();//强制刷新页面
        system(copy_path.toLatin1());
        system("sync");

        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("日志导出完成"));
        m_box->setStandardButtons(QMessageBox::Ok);
        QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

        int ret = m_box->exec();
        if (ret == QMessageBox::Ok)
        {
            ui->label_usb->setText("");
            usb_path = "";
        }
        else
        {
            ;
        }
    }
    sys_busy = false;
}

void xitong_widget::on_pushButton_save_info_clicked()
{
    MainWindow::iniFile->setValue("/STATION_INFO/ID",ui->lineEdit_station_info->text());
}
