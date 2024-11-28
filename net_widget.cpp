#include "net_widget.h"
#include "ui_net_widget.h"

extern bool KeyBoard_Code,KeyBoard_ABC_Code,keyBoard_flag,keyBoard_ABC_flag;
QString HLK_IP = "192.168.16.254";//海凌科路由模块IP
QString HLK_WIFI_NAME = "";
QString HLK_WIFI_PASSWORD = "";
QSerialPort *com_4G;
uint8_t wifi_flag = 0;
LORA_CONFIG lora_config;
extern QSerialPort *serial[7];
QString SIM_CCID = "";

net_widget::net_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::net_widget)
{
    ui->setupUi(this);
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ui->tabWidget->setStyleSheet(
        "QTabBar::tab{font-size:15px;}"
        "QTabWidget::pane{border: 2px solid rgb(210, 210, 210);\
        background:rgb(246, 246, 246);\
        border-top-color:transparent;}\
        QTabWidget::tab-bar{background:rgb(0, 0, 0);subcontrol-position:left;}\
        QTabBar::tab{width:60px;/*宽度根据实际需要进行调整*/"
        "height:16px;\
        background:rgb(210, 210, 210);\
        border: 5px solid rgb(210, 210, 210);\
        border-top-left-radius: 8px;\
        border-top-right-radius: 8px;}"
        "QTabBar::tab:selected{"
        "background:rgb(246, 246, 246);"/*按钮被选中颜色*/
        "border-bottom-color:rgb(246, 246, 246);}"
        "QTabBar::tab:!selected{"
        "background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(240, 240, 240),"
        "stop:0.5 rgb(190, 190, 190), stop:1 rgb(225, 225, 225));}"
    );
    ui->tabWidget->setFocusPolicy(Qt::NoFocus);//取消虚线框
    net_button_init(ui->pushButton_mobile);
    net_button_init(ui->pushButton_sim_flag);
    net_button_init(ui->pushButton_sim_signal);
    net_button_init(ui->pushButton_local_ip);
    net_button_init(ui->pushButton_net_check);
    net_button_init(ui->pushButton_wifiname);
    net_button_init(ui->pushButton_wifi_password);
    net_button_init(ui->pushButton_save);
    net_button_init(ui->save_Button_lora);

    ui->lineEdit_wifi_name->installEventFilter(this);
    ui->lineEdit_wifi_password->installEventFilter(this);
    ui->lineEdit_net_ip1->installEventFilter(this);
    ui->lineEdit_net_ip2->installEventFilter(this);
    ui->lineEdit_net_ip3->installEventFilter(this);
    ui->lineEdit_net_ip4->installEventFilter(this);
    ui->lineEdit_net_ip5->installEventFilter(this);
    ui->lineEdit_net_port1->installEventFilter(this);
    ui->lineEdit_net_port2->installEventFilter(this);
    ui->lineEdit_net_port3->installEventFilter(this);
    ui->lineEdit_net_port4->installEventFilter(this);
    ui->lineEdit_net_port5->installEventFilter(this);
    ui->lineEdit_lora_local_addr->installEventFilter(this);
    ui->lineEdit_lora_point_addr->installEventFilter(this);
    ui->lineEdit_lora_fre->installEventFilter(this);
    ui->lineEdit_lora_channel->installEventFilter(this);

    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setFocusPolicy(Qt::NoFocus);//取消虚线框
    com_4G = new QSerialPort;
    serial_net_init(com_4G,"/dev/ttyAS5",115200);//4G状态串口
    QObject::connect(com_4G, &QSerialPort::readyRead, this, &net_widget::serialport_recive_4G);
    //QObject::connect(serial[5], &QSerialPort::readyRead, this, &net_widget::serialport_recive_LORA);//LORA功能暂时关闭

    if(MainWindow::iniFile->value("/WIFI/Open").toUInt())
    {
        ui->checkBox_wifi->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        ui->checkBox_wifi->setCheckState(Qt::CheckState::Unchecked);
    }
#ifdef ARM
    wifi_init();
#endif
    ui->lineEdit_wifi_name->setText(MainWindow::iniFile->value("/WIFI/Name").toString());
    ui->lineEdit_wifi_password->setText(MainWindow::iniFile->value("/WIFI/Password").toString());  
    ui->lineEdit_net_ip1->setText(MainWindow::iniFile->value("/Server/IP1").toString());
    ui->lineEdit_net_ip2->setText(MainWindow::iniFile->value("/Server/IP2").toString());
    ui->lineEdit_net_ip3->setText(MainWindow::iniFile->value("/Server/IP3").toString());
    ui->lineEdit_net_ip4->setText(MainWindow::iniFile->value("/Server/IP4").toString());
    ui->lineEdit_net_ip5->setText(MainWindow::iniFile->value("/Server/IP5").toString());
    ui->lineEdit_net_port1->setText(MainWindow::iniFile->value("/Server/PORT1").toString());
    ui->lineEdit_net_port2->setText(MainWindow::iniFile->value("/Server/PORT2").toString());
    ui->lineEdit_net_port3->setText(MainWindow::iniFile->value("/Server/PORT3").toString());
    ui->lineEdit_net_port4->setText(MainWindow::iniFile->value("/Server/PORT4").toString());
    ui->lineEdit_net_port5->setText(MainWindow::iniFile->value("/Server/PORT5").toString());
    ui->comboBox_1->setCurrentIndex(MainWindow::iniFile->value("/Server/Protocol1").toInt());
    ui->comboBox_2->setCurrentIndex(MainWindow::iniFile->value("/Server/Protocol2").toInt());
    ui->comboBox_3->setCurrentIndex(MainWindow::iniFile->value("/Server/Protocol3").toInt());
    ui->comboBox_4->setCurrentIndex(MainWindow::iniFile->value("/Server/Protocol4").toInt());
    ui->comboBox_lora_baud->setCurrentText(MainWindow::iniFile->value("/LORA/Baud").toString());
    ui->lineEdit_lora_local_addr->setText(MainWindow::iniFile->value("/LORA/ADDR_local").toString());
    ui->lineEdit_lora_point_addr->setText(MainWindow::iniFile->value("/LORA/ADDR_point").toString());
    ui->lineEdit_lora_fre->setText(MainWindow::iniFile->value("/LORA/ADDR_fre").toString());
    ui->lineEdit_lora_channel->setText(MainWindow::iniFile->value("/LORA/ADDR_channel").toString());

    on_save_Button_lora_clicked();//LORA配置初始化
}

net_widget::~net_widget()
{
    delete ui;
}

void net_widget::setUpload_IpSet(void)
{
    ui->lineEdit_net_ip1->setText(MainWindow::iniFile->value("/Server/IP1").toString());
    ui->lineEdit_net_ip2->setText(MainWindow::iniFile->value("/Server/IP2").toString());
    ui->lineEdit_net_port1->setText(MainWindow::iniFile->value("/Server/PORT1").toString());
    ui->lineEdit_net_port2->setText(MainWindow::iniFile->value("/Server/PORT2").toString());
}

bool net_widget::eventFilter(QObject *watch, QEvent *evn)//鼠标事件，判断触摸
{
    if ((watch == ui->lineEdit_wifi_name) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_wifi_name);
    }
    if ((watch == ui->lineEdit_wifi_password) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_wifi_password);
    }

    if ((watch == ui->lineEdit_net_ip1) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_net_ip1);
    }
    if ((watch == ui->lineEdit_net_ip2) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_net_ip2);
    }
    if ((watch == ui->lineEdit_net_ip3) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_net_ip3);
    }
    if ((watch == ui->lineEdit_net_ip4) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_net_ip4);
    }
    if ((watch == ui->lineEdit_net_ip5) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_net_ip5);
    }
    if ((watch == ui->lineEdit_net_port1) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_net_port1);
    }
    if ((watch == ui->lineEdit_net_port2) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_net_port2);
    }
    if ((watch == ui->lineEdit_net_port3) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_net_port3);
    }
    if ((watch == ui->lineEdit_net_port4) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_net_port4);
    }
    if ((watch == ui->lineEdit_net_port5) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_net_port5);
    }
    if ((watch == ui->lineEdit_lora_local_addr) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_lora_local_addr);
    }
    if ((watch == ui->lineEdit_lora_point_addr) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_lora_point_addr);
    }
    if ((watch == ui->lineEdit_lora_fre) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_lora_fre);
    }
    if ((watch == ui->lineEdit_lora_channel) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_lora_channel);
    }
    return QWidget::eventFilter(watch,evn);
}

void net_widget::callKeyBoard(QLineEdit *a)
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

void net_widget::callKeyBoard_ABC(QLineEdit *a)
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

void net_widget::wifi_init()
{
    if(MainWindow::iniFile->value("/WIFI/Open").toUInt() == 0)
    {
        wifi_off_cmd = "curl -d \"page=basic&wlan_conf=2860&radiohiddenButton=2&wifihiddenButton=0\" -H "
                       "\"Content-Type: application/x-www-form-urlencoded\" -X POST http://admin:admin@" +
                        HLK_IP + "/cgi-bin/wireless.cgi &";
        system(wifi_off_cmd.toLatin1());
        wifi_flag = 0;
        ui->label_wifi_flag->setText("WIFI已关闭");
    }
    else
    {
        wifi_on_cmd = "curl -d \"page=basic&wlan_conf=2860&radiohiddenButton=2&wifihiddenButton=1\" -H "
                      "\"Content-Type: application/x-www-form-urlencoded\" -X POST http://admin:admin@" +
                        HLK_IP + "/cgi-bin/wireless.cgi &";
        system(wifi_on_cmd.toLatin1());
        wifi_flag = 1;
        ui->label_wifi_flag->setText("WIFI已开启");
    }
}

void net_widget::net_button_init(QPushButton *button_init)
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

uint8_t net_widget::on_checkBox_wifi_stateChanged(int arg1)
{
#ifdef ARM
    if(arg1)
    {
        qDebug()<<"WIFI Open";
        wifi_on_cmd = "curl -d \"page=basic&wlan_conf=2860&radiohiddenButton=2&wifihiddenButton=1\" -H "
                      "\"Content-Type: application/x-www-form-urlencoded\" -X POST http://admin:admin@" +
                        HLK_IP + "/cgi-bin/wireless.cgi &";
        system(wifi_on_cmd.toLatin1());
        wifi_flag = 1;
        ui->label_wifi_flag->setText("WIFI已开启");
        MainWindow::iniFile->setValue("/WIFI/Open",wifi_flag);
        return 0;
    }
    else
    {
        qDebug()<<"WIFI Off";
        wifi_off_cmd = "curl -d \"page=basic&wlan_conf=2860&radiohiddenButton=2&wifihiddenButton=0\" -H "
                       "\"Content-Type: application/x-www-form-urlencoded\" -X POST http://admin:admin@" +
                        HLK_IP + "/cgi-bin/wireless.cgi &";
        system(wifi_off_cmd.toLatin1());
        wifi_flag = 0;
        ui->label_wifi_flag->setText("WIFI已关闭");
        MainWindow::iniFile->setValue("/WIFI/Open",wifi_flag);
        return 0;
    }
#endif
}

uint8_t net_widget::on_pushButton_wifiname_clicked()
{
    HLK_WIFI_NAME = ui->lineEdit_wifi_name->text();
    wifi_name_cmd = "curl -d \"page=basic&wlan_conf=2860&radiohiddenButton=2&wifihiddenButton=2"
                    "&wirelessmode=9&mssid_0=" + HLK_WIFI_NAME + "&mssid_1=&mssid_2=&mssid_3=&mssid_4=&mssid_5="
                    "&mssid_6=&mssid_8=&mssid_9=&mssid_10=&mssid_11=&mssid_12=&mssid_13=&mssid_14="
                    "&mssid_15=&broadcastssid=1&apisolated=0&mbssidapisolated=0&sz11gChannel=1&n_mode=0"
                    "&n_bandwidth=1&n_gi=1&n_mcs=33&n_rdg=1&n_extcha=1&n_stbc=1&n_amsdu=0&n_autoba=1"
                    "&n_badecline=0&n_disallow_tkip=1&n_2040_coexit=1&n_ldpc=0&vht_bandwidth=0&vht_stbc=0"
                    "&vht_sgi=0&vht_bw_signal=0&vht_ldpc=0\" -H \"Content-Type: application/x-www-form-urlencoded\""
                    " -X POST http://admin:admin@" + HLK_IP + "/cgi-bin/wireless.cgi &";
    system(wifi_name_cmd.toLatin1());

    MainWindow::iniFile->setValue("/WIFI/Name",ui->lineEdit_wifi_name->text());

    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("WIFI账号已下发！"));
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

    return ret;
}

uint8_t net_widget::on_pushButton_wifi_password_clicked()
{
    if(ui->lineEdit_wifi_password->text().length() < 8)
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("密码不能少于8位！"));
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

        return ret;
    }
    HLK_WIFI_PASSWORD = ui->lineEdit_wifi_password->text();
    wifi_password_cmd = "curl -d \"page=security&wlan_conf=2860&ssidIndex=0&security_mode=WPA2PSK&wep_default_key=2"
                        "&wep_key_1=12345678&WEP1Select=0&wep_key_2=&WEP2Select=0&wep_key_3=&WEP3Select=0&wep_key_4=&WEP4Select=0"
                        "&cipher=1&passphrase=" + HLK_WIFI_PASSWORD + "\" -H \"Content-Type: application/x-www-form-urlencoded\""
                        " -X POST http://admin:admin@" + HLK_IP + "/cgi-bin/wireless.cgi &";
    system(wifi_password_cmd.toLatin1());

    MainWindow::iniFile->setValue("/WIFI/Password",ui->lineEdit_wifi_password->text());

    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("WIFI密码已下发！"));
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

    return ret;
}

void net_widget::on_pushButton_local_ip_clicked()
{
        QList<QNetworkAddressEntry> list;
        QHostAddress                addr;
        list = QNetworkInterface::interfaceFromName("eth0").addressEntries();
        if(!list.isEmpty())
            addr = list.at(0).ip();
        ui->label_local_ip->setText(addr.toString());
}

void net_widget::on_pushButton_net_check_clicked()
{
    QHostInfo::lookupHost("www.baidu.com",this,SLOT(onLookupHost(QHostInfo)));
}

void net_widget::onLookupHost(QHostInfo host)
{
    if (host.error() != QHostInfo::NoError)
    {
        qDebug() << "Lookup failed:" << host.errorString();
        //网络未连接，发送信号通知
        ui->label_net_flag->setText("网络连接错误！");
        ui->label_net_flag->setStyleSheet("color: red");
    }
    else
    {
        ui->label_net_flag->setText("网络连接正常！");
        ui->label_net_flag->setStyleSheet("color: green");
    }
}

//截取两字符串中间的字符串
QString net_widget::strMid(QString src, QString start, QString end)
{
    int startIndex = src.indexOf(start, 0);
    int endIndex = src.indexOf(end, startIndex);
    QString subStr = src.mid(startIndex, endIndex - startIndex);
    subStr = subStr.remove(start);
    return subStr;
}

void net_widget::serial_net_init(QSerialPort *serial, QString portname, int bundrate)
{
    //设置串口名
    serial->setPortName(portname);
    //打开串口
    serial->open(QIODevice::ReadWrite);
    //设置波特率
    serial->setBaudRate(bundrate);
    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

void net_widget::serialport_recive_4G()
{
    QByteArray message;
    QString str;
    QThread::msleep(200);
    message.append(com_4G->readAll());
    str = QString(message);
    str.remove(QRegExp("\\s"));//删除空格
    if(sim_select == "SIGNAL")
    {
        QString sim_quility = strMid(str,"CSQ:",",");
        if(!sim_quility.isEmpty())
        {
            ui->label_sim_signal->clear();
            ui->label_sim_signal->setText("信号强度：" + sim_quility);
        }
    }
    else if(sim_select == "QCCID")
    {
        qDebug()<<"CCID1=" <<str;
        SIM_CCID = strMid(str,"QCCID:","OK");
        if(SIM_CCID.length() >= 20)
        {
            qDebug()<<"CCID2=" <<SIM_CCID;
            ui->label_sim_num->clear();
            ui->label_sim_num->setText("SIM卡号：" + SIM_CCID.left(20));
        }
    }
    else
    {
        QString mobile = strMid(str,"+86","\"");
        if(!mobile.isEmpty())
        {
            ui->label_mobile_num->clear();
            ui->label_mobile_num->setText("手机号：" + mobile);
        }
    }
}

void net_widget::serialport_recive_LORA()
{
    QByteArray receive_data;
    QString str;
    receive_data.append(serial[5]->readAll());
    str = QString(receive_data);
    str.remove(QRegExp("\\s"));//删除空格
    if(lora_select == "a")
    {
        if(str.contains("a",Qt::CaseSensitive))//包含字符串
        {
            QString str = "a\r\n";
            QByteArray send_data = str.toLatin1();
            serial[5]->write(send_data);
            lora_select = "CONFIG";
        }
    }
    else if(lora_select == "CONFIG")
    {
        if(str.contains("OK",Qt::CaseSensitive))//包含字符串
        {
            QString str = "AT+ADDR=" + QString::number(lora_config.point_addr,10) + "\r\n";
            QByteArray send_data = str.toLatin1();
            serial[5]->write(send_data);
            lora_select = "ADDR_OK";
        }
    }
    else if(lora_select == "ADDR_OK")
    {
        if(str.contains("OK",Qt::CaseSensitive))//包含字符串
        {
            QString str = "AT+SPD=" + QString::number(lora_config.fre,10) + "\r\n";
            QByteArray send_data = str.toLatin1();
            serial[5]->write(send_data);
            lora_select = "SPD_OK";
        }
    }
    else if(lora_select == "SPD_OK")
    {
        if(str.contains("OK",Qt::CaseSensitive))//包含字符串
        {
            QString str = "AT+CH=" + QString::number(lora_config.channel,10) + "\r\n";
            QByteArray send_data = str.toLatin1();
            serial[5]->write(send_data);
            lora_select = "CH_OK";
        }
    }
    else if(lora_select == "CH_OK")
    {
        if(str.contains("OK",Qt::CaseSensitive))//包含字符串
        {
            QString str = "AT+Z\r\n";
            QByteArray send_data = str.toLatin1();
            serial[5]->write(send_data);
            lora_select = "START";
        }
    }
    else if(lora_select == "START")//配置完成，收到传感器数据
    {
        if(str.contains("LoRa",Qt::CaseSensitive))//包含字符串
            return;//模块还没重启完成
    }
    else
    {
        ;
    }
}

void net_widget::on_pushButton_mobile_clicked()
{
    sim_select = "CNUM";
    QString str = "AT+CNUM\r\n";
    QByteArray send_data = str.toLatin1();
    com_4G->write(send_data);
}

void net_widget::on_pushButton_sim_flag_clicked()
{
    sim_select = "QCCID";
    QString str = "AT+QCCID\r\n";
    QByteArray send_data = str.toLatin1();
    com_4G->write(send_data);
}

void net_widget::on_pushButton_sim_signal_clicked()
{
    sim_select = "SIGNAL";
    QString str = "AT+CSQ\r\n";
    QByteArray send_data = str.toLatin1();
    com_4G->write(send_data);
}

void net_widget::on_pushButton_save_clicked()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("是否清空补传数据？"));
    m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

    int ret = m_box->exec();
    if (ret == QMessageBox::Yes)
    {
        qDebug()<<"ReSend Clear";
        emit ReSendclear(1);
    }
    else
    {
        ;
    }

    MainWindow::iniFile->setValue("/Server/IP1",ui->lineEdit_net_ip1->text());
    MainWindow::iniFile->setValue("/Server/IP2",ui->lineEdit_net_ip2->text());
    MainWindow::iniFile->setValue("/Server/IP3",ui->lineEdit_net_ip3->text());
    MainWindow::iniFile->setValue("/Server/IP4",ui->lineEdit_net_ip4->text());
    MainWindow::iniFile->setValue("/Server/IP5",ui->lineEdit_net_ip5->text());
    MainWindow::iniFile->setValue("/Server/PORT1",ui->lineEdit_net_port1->text());
    MainWindow::iniFile->setValue("/Server/PORT2",ui->lineEdit_net_port2->text());
    MainWindow::iniFile->setValue("/Server/PORT3",ui->lineEdit_net_port3->text());
    MainWindow::iniFile->setValue("/Server/PORT4",ui->lineEdit_net_port4->text());
    MainWindow::iniFile->setValue("/Server/PORT5",ui->lineEdit_net_port5->text());
    MainWindow::iniFile->setValue("/Server/Protocol1",ui->comboBox_1->currentIndex());
    MainWindow::iniFile->setValue("/Server/Protocol2",ui->comboBox_2->currentIndex());
    MainWindow::iniFile->setValue("/Server/Protocol3",ui->comboBox_3->currentIndex());
    MainWindow::iniFile->setValue("/Server/Protocol4",ui->comboBox_4->currentIndex());
    tcp_socket::socket_init();
}

void net_widget::on_save_Button_lora_clicked()
{
    MainWindow::iniFile->setValue("/LORA/Baud",ui->comboBox_lora_baud->currentText());
    MainWindow::iniFile->setValue("/LORA/ADDR_local",ui->lineEdit_lora_local_addr->text());
    MainWindow::iniFile->setValue("/LORA/ADDR_point",ui->lineEdit_lora_point_addr->text());
    MainWindow::iniFile->setValue("/LORA/ADDR_fre",ui->lineEdit_lora_fre->text());
    MainWindow::iniFile->setValue("/LORA/ADDR_channel",ui->lineEdit_lora_channel->text());

    //LORA功能暂时关闭
//    lora_config.point_addr = MainWindow::iniFile->value("/LORA/ADDR_point").toUInt();
//    lora_config.fre = MainWindow::iniFile->value("/LORA/ADDR_fre").toUInt();
//    lora_config.channel = MainWindow::iniFile->value("/LORA/ADDR_channel").toUInt() - 398;

//    lora_select = "a";
//    QString str = "+++\r\n";
//    QByteArray send_data = str.toLatin1();
//    serial[5]->write(send_data);
}
