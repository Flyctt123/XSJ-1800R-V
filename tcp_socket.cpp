#include "tcp_socket.h"
#include<QCoreApplication>
#include<QEventLoop>
#include<QtCore/qmath.h>

MAINTENANCE maintenance;
TCP_COMM tcp_comm[5];
REPORT_HEADHEX_SW *report_SW_headhex = (REPORT_HEADHEX_SW *)malloc(sizeof(REPORT_HEADHEX_SW));
REPORT_HEADHEX_SZY * report_SZY_headhex = (REPORT_HEADHEX_SZY *)malloc(sizeof(REPORT_HEADHEX_SZY));
extern DATA_RES data_result;
extern QSerialPort *serial[7];
extern OSD_flag osd_flag;
PIC_SEND pic_send;
extern KDY kdy;
extern QString SIM_CCID;
extern float Rain_ratio;
uint16_t file_comm_count = 0;//文件传输计时，长时间未完成就退出
DATA_RESEND data_reSend;

tcp_socket::tcp_socket(QWidget *parent) :
    QWidget(parent)
{
    Wifi_Server = new QTcpServer();
    //监听指定的端口
    if(!Wifi_Server->listen(QHostAddress::Any, 20002))
    {
        qDebug()<<Wifi_Server->errorString();
    }
    connect(Wifi_Server,&QTcpServer::newConnection,this,&tcp_socket::Wifi_Connected);

    tcp_comm[0].numTcp = 1;
    tcp_comm[0].ip = MainWindow::iniFile->value("/Server/IP1").toString();
    tcp_comm[0].port = MainWindow::iniFile->value("/Server/PORT1").toUInt();
    tcp_comm[0].socket_agreement = MainWindow::iniFile->value("/Server/Protocol1").toInt();;//通信协议
    tcp_comm[1].numTcp = 2;
    tcp_comm[1].ip = MainWindow::iniFile->value("/Server/IP2").toString();
    tcp_comm[1].port = MainWindow::iniFile->value("/Server/PORT2").toUInt();
    tcp_comm[1].socket_agreement = MainWindow::iniFile->value("/Server/Protocol2").toInt();;//通信协议
    tcp_comm[2].numTcp = 3;
    tcp_comm[2].ip = MainWindow::iniFile->value("/Server/IP3").toString();
    tcp_comm[2].port = MainWindow::iniFile->value("/Server/PORT3").toUInt();
    tcp_comm[2].socket_agreement = MainWindow::iniFile->value("/Server/Protocol3").toInt();;//通信协议
    tcp_comm[3].numTcp = 4;
    tcp_comm[3].ip = MainWindow::iniFile->value("/Server/IP4").toString();
    tcp_comm[3].port = MainWindow::iniFile->value("/Server/PORT4").toUInt();
    tcp_comm[3].socket_agreement = MainWindow::iniFile->value("/Server/Protocol4").toInt();;//通信协议
    tcp_comm[4].numTcp = 5;
    tcp_comm[4].ip = MainWindow::iniFile->value("/Server/IP5").toString();
    tcp_comm[4].port = MainWindow::iniFile->value("/Server/PORT5").toUInt();

    for(uint8_t i=0;i<5;i++)
    {
        tcp_comm[i].TCP_Socket = new QTcpSocket(this);
        if(tcp_comm[i].port == 0)
            tcp_comm[i].socket_select = false;
        else
            tcp_comm[i].socket_select = true;

        tcp_comm[i].send_num = 0;
        tcp_comm[i].tcp_onLine = true;
        tcp_comm[i].tcp_busy = false;
        tcp_comm[i].tcp_onLineTime = QDateTime::currentDateTime();//在线标志
    }

    QObject::connect(tcp_comm[0].TCP_Socket, &QTcpSocket::connected, this, &tcp_socket::socket1_Connected);
    QObject::connect(tcp_comm[1].TCP_Socket, &QTcpSocket::connected, this, &tcp_socket::socket2_Connected);
    QObject::connect(tcp_comm[2].TCP_Socket, &QTcpSocket::connected, this, &tcp_socket::socket3_Connected);
    QObject::connect(tcp_comm[3].TCP_Socket, &QTcpSocket::connected, this, &tcp_socket::socket4_Connected);
    QObject::connect(tcp_comm[4].TCP_Socket, &QTcpSocket::connected, this, &tcp_socket::socket5_Connected);

    QObject::connect(tcp_comm[0].TCP_Socket, &QTcpSocket::readyRead, this, &tcp_socket::socket1_Read_Data);
    QObject::connect(tcp_comm[1].TCP_Socket, &QTcpSocket::readyRead, this, &tcp_socket::socket2_Read_Data);
    QObject::connect(tcp_comm[2].TCP_Socket, &QTcpSocket::readyRead, this, &tcp_socket::socket3_Read_Data);
    QObject::connect(tcp_comm[3].TCP_Socket, &QTcpSocket::readyRead, this, &tcp_socket::socket4_Read_Data);
    QObject::connect(tcp_comm[4].TCP_Socket, &QTcpSocket::readyRead, this, &tcp_socket::socket5_Read_Data);

    QObject::connect(tcp_comm[0].TCP_Socket, &QTcpSocket::disconnected, this, &tcp_socket::socket1_Disconnected);
    QObject::connect(tcp_comm[1].TCP_Socket, &QTcpSocket::disconnected, this, &tcp_socket::socket2_Disconnected);
    QObject::connect(tcp_comm[2].TCP_Socket, &QTcpSocket::disconnected, this, &tcp_socket::socket3_Disconnected);
    QObject::connect(tcp_comm[3].TCP_Socket, &QTcpSocket::disconnected, this, &tcp_socket::socket4_Disconnected);
    QObject::connect(tcp_comm[4].TCP_Socket, &QTcpSocket::disconnected, this, &tcp_socket::socket5_Disconnected);

    QFile file("/home/Config.ini");
    maintenance = {0x5AA5,0xFF,0xA001,&file,"",0x00,0x00,0x00,{false,false,false,false,false,false}};

    timer =new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout_second()));//从0秒开始计时
    timer->start(1000);

    timer1 =new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(timerTimeout_receive()));
    timer1->start(200);

    timer2 =new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(timerTimeout_minute()));//1分钟处理

    timer3 =new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(Timeout_second_picture()));//图片循环发送处理

    timer4 =new QTimer(this);
    connect(timer4, SIGNAL(timeout()), this, SLOT(Timeout_send_maintenance_file()));//维护平台文件传输

    timer5 =new QTimer(this);
    connect(timer5, SIGNAL(timeout()), this, SLOT(timerTimeout_SZY_resend1()));//补传函数
    timer6 =new QTimer(this);
    connect(timer6, SIGNAL(timeout()), this, SLOT(timerTimeout_SZY_resend2()));//补传函数
    timer7 =new QTimer(this);
    connect(timer7, SIGNAL(timeout()), this, SLOT(timerTimeout_SZY_resend3()));//补传函数
    timer8 =new QTimer(this);
    connect(timer8, SIGNAL(timeout()), this, SLOT(timerTimeout_SZY_resend4()));//补传函数

    tcp_data_base=QSqlDatabase::addDatabase("QSQLITE","connect3");
    tcp_data_base.setDatabaseName(MainWindow::dbFile);
    tcp_data_base.open();

    report_SW_head_init();
    report_SZY_head_init();

    updata_label = new QLabel();
    updata_label->setGeometry(0,0,480,272);
    updata_label->setAlignment(Qt::AlignCenter);
    QFont font = QFont("宋体",15);
    updata_label->setFont(font);
    updata_label->setStyleSheet("background: rgb(244, 244, 244);color: rgb(55, 55, 165)");
    updata_label->hide();

    pProgressBar = new QProgressBar();//升级进度条
    pProgressBar->setAlignment(Qt::AlignHCenter);
    pProgressBar->setGeometry(10,200,460,25);
    pProgressBar->setOrientation(Qt::Horizontal);  // 水平方向
    pProgressBar->setValue(0);
    pProgressBar->setStyleSheet("QProgressBar{height:22px; text-align:center; font-size:14px; color:white; background:#1D5573;}"

                                "QProgressBar::chunk{background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #99ffff,stop:1 #41d6ff);}");
    pProgressBar->close();

#ifdef RESEND
    for(uint8_t i=0;i<4;i++)
    {
        if(reSendQuery(i+1))//开机检测是否需要补传
        {
            tcp_comm[i].reSend_flag[0] = true;
        }
        if(reSendQuery_SZY(i+1,1))//开机检测是否需要补传
        {
            tcp_comm[i].reSend_flag[1] = true;
        }
    }
#endif
}

tcp_socket::~tcp_socket()
{

}

void tcp_socket::Wifi_Connected()
{
    qDebug() << "Wifi_Connected!";
    //获取客户端连接
    Wifi_Socket = Wifi_Server->nextPendingConnection();

    QString test = "1234";
    Wifi_Socket->write(test.toLatin1());
    Wifi_Socket->flush();

    QObject::connect(Wifi_Socket, &QTcpSocket::readyRead, this, &tcp_socket::Wifi_Read_Data);
    QObject::connect(Wifi_Socket, &QTcpSocket::disconnected, this, &tcp_socket::Wifi_Disconnected);
}

void tcp_socket::Wifi_Disconnected()
{
    qDebug() << "Wifi_Disconnected!";
}

void tcp_socket::Wifi_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = Wifi_Socket->readAll();
    if(!buffer.isEmpty())
    {
        if((unsigned char)buffer.at(0) == 0xAA)
        {
            QString test = "5678";
            Wifi_Socket->write(test.toLatin1());
            Wifi_Socket->flush();
        }
    }
}

void tcp_socket::socket_Connect(TCP_COMM *Tcp_comm)
{
    //取消已有的连接
    Tcp_comm->TCP_Socket->abort();
    if(Tcp_comm->socket_agreement == 1)
        QThread::msleep(250);//武隆项目水资源重连需要延迟时间
    //连接服务器
    Tcp_comm->TCP_Socket->connectToHost(Tcp_comm->ip, Tcp_comm->port);
    if(Tcp_comm->socket_agreement == 1)
        QThread::msleep(250);
}

void tcp_socket::socket_init()
{
    tcp_comm[0].ip = MainWindow::iniFile->value("/Server/IP1").toString();
    tcp_comm[0].port = MainWindow::iniFile->value("/Server/PORT1").toUInt();
    tcp_comm[0].socket_agreement = MainWindow::iniFile->value("/Server/Protocol1").toInt();;//通信协议
    tcp_comm[1].ip = MainWindow::iniFile->value("/Server/IP2").toString();
    tcp_comm[1].port = MainWindow::iniFile->value("/Server/PORT2").toUInt();
    tcp_comm[1].socket_agreement = MainWindow::iniFile->value("/Server/Protocol2").toInt();;//通信协议
    tcp_comm[2].ip = MainWindow::iniFile->value("/Server/IP3").toString();
    tcp_comm[2].port = MainWindow::iniFile->value("/Server/PORT3").toUInt();
    tcp_comm[2].socket_agreement = MainWindow::iniFile->value("/Server/Protocol3").toInt();;//通信协议
    tcp_comm[3].ip = MainWindow::iniFile->value("/Server/IP4").toString();
    tcp_comm[3].port = MainWindow::iniFile->value("/Server/PORT4").toUInt();
    tcp_comm[3].socket_agreement = MainWindow::iniFile->value("/Server/Protocol4").toInt();;//通信协议
    tcp_comm[4].ip = MainWindow::iniFile->value("/Server/IP5").toString();
    tcp_comm[4].port = MainWindow::iniFile->value("/Server/PORT5").toUInt();

    for(uint8_t i=0;i<5;i++)
    {
        tcp_comm[i].send_num = 0;
        tcp_comm[i].tcp_busy = false;
        if(tcp_comm[i].port == 0)
            tcp_comm[i].socket_select = false;
        else
            tcp_comm[i].socket_select = true;

        //取消已有的连接
        tcp_comm[i].TCP_Socket->abort();
        tcp_comm[i].socket_flag = false;
    }
}

void tcp_socket::socket_Send(TCP_COMM *tcp_comm, QByteArray send_data,uint32_t len)
{
    if(tcp_comm->socket_flag)
    {
        tcp_comm->TCP_Socket->write(send_data,len);
        tcp_comm->TCP_Socket->flush();//刷新缓冲区
        qDebug()<< "tcp_send=" <<send_data.toHex();
    }
}

void tcp_socket::socket_Close(TCP_COMM *tcp_comm)
{
    //主动断开连接
    tcp_comm->TCP_Socket->disconnectFromHost();
}

void tcp_socket::socket1_Connected()
{
    tcp_comm[0].socket_flag = true;
    qDebug() << "socket1 connected!";
    report_SW_link(&tcp_comm[0]);
}

void tcp_socket::socket2_Connected()
{
    tcp_comm[1].socket_flag = true;
    qDebug() << "socket2 connected!";
    report_SW_link(&tcp_comm[1]);
}

void tcp_socket::socket3_Connected()
{
    tcp_comm[2].socket_flag = true;
    qDebug() << "socket3 connected!";
    report_SW_link(&tcp_comm[2]);
}

void tcp_socket::socket4_Connected()
{
    tcp_comm[3].socket_flag = true;
    qDebug() << "socket4 connected!";
    report_SW_link(&tcp_comm[3]);
}

void tcp_socket::socket5_Connected()
{
    tcp_comm[4].socket_flag = true;
    qDebug() << "socket5 connected!";

    QFile file("/home/Config.ini");
    maintenance = {0x5AA5,0xFF,0xA001,&file,"",0x00,0x00,0x00,{false,false,false,false,false,false}};
    QThread::msleep(500);
    maintenance_link();
}

void tcp_socket::socket1_Read_Data()
{
    tcp_comm[0].recive_buf = tcp_comm[0].TCP_Socket->readAll();
    tcp_comm[0].recive_buf_comm.append(tcp_comm[0].recive_buf);
    tcp_comm[0].recive_buf.clear();
}

void tcp_socket::socket2_Read_Data()
{
    tcp_comm[1].recive_buf = tcp_comm[1].TCP_Socket->readAll();
    tcp_comm[1].recive_buf_comm.append(tcp_comm[1].recive_buf);
    tcp_comm[1].recive_buf.clear();
}

void tcp_socket::socket3_Read_Data()
{
    tcp_comm[2].recive_buf = tcp_comm[2].TCP_Socket->readAll();
    tcp_comm[2].recive_buf_comm.append(tcp_comm[2].recive_buf);
    tcp_comm[2].recive_buf.clear();
}

void tcp_socket::socket4_Read_Data()
{
    tcp_comm[3].recive_buf = tcp_comm[3].TCP_Socket->readAll();
    tcp_comm[3].recive_buf_comm.append(tcp_comm[3].recive_buf);
    tcp_comm[3].recive_buf.clear();
}

void tcp_socket::socket5_Read_Data()
{
    tcp_comm[4].recive_buf = tcp_comm[4].TCP_Socket->readAll();
    tcp_comm[4].recive_buf_comm.append(tcp_comm[4].recive_buf);
    tcp_comm[4].recive_buf.clear();
}

uint32_t recive_file_size = 0;
void tcp_socket::socket_comm_fun(TCP_COMM *Tcp_comm)
{
    bool ok;
    QString file_len_str;

    if(!Tcp_comm->recive_buf_comm.isEmpty())
    {
        if((unsigned char)Tcp_comm->recive_buf_comm.at(0) == 0x7E && (unsigned char)Tcp_comm->recive_buf_comm.at(1) == 0x7E)//水文协议
        {
            uint8_t H_CRC_Data,L_CRC_Data;
            QByteArray CrcCheck = Tcp_comm->recive_buf_comm.left(Tcp_comm->recive_buf_comm.size()-2);
            uint16_t CRC_Data=ModBusCRC16(CrcCheck,CrcCheck.size());
            L_CRC_Data=CRC_Data & 0xff;
            H_CRC_Data=(CRC_Data>>8) & 0xff;
            if(H_CRC_Data==(unsigned char)Tcp_comm->recive_buf_comm[Tcp_comm->recive_buf_comm.size()-2] &&
               L_CRC_Data==(unsigned char)Tcp_comm->recive_buf_comm[Tcp_comm->recive_buf_comm.size()-1]
              )//RCR校验通过
            {
                Tcp_comm->socket_flag = true;
                data_result.event[17] = data_result.event[17] + 1;//收报记录
                if(data_result.event[17] > 65530)
                    data_result.event[17] = 0;

                switch((unsigned char)Tcp_comm->recive_buf_comm.at(10))//功能码
                {
                    case FC_REPORT_LINK_MT://链路报响应(无)
                    {
                        //qDebug()<<"TCP_RECEIVE_SW_Link = " << Tcp_comm->recive_buf_comm.toHex();
                        break;
                    }
                    case FC_REPORT_TEST://测试报响应
                    {
                        qDebug()<<"TCP_RECEIVE_SW_Tesk = " << Tcp_comm->recive_buf_comm.toHex();
                        check_time(Tcp_comm);
                        break;
                    }
                    case FC_REPORT_UNIFORM_TIME://均匀时段水文信息报响应
                    {
                        qDebug()<<"TCP_RECEIVE_Uniform_Time = " << Tcp_comm->recive_buf_comm.toHex();
                        break;
                    }
                    case FC_REPORT_ON_TIME://定时报响应
                    {
                        qDebug()<<"TCP_RECEIVE_SW_Fixed_Time = " << Tcp_comm->recive_buf_comm.toHex();
#ifdef RESEND
                        Tcp_comm->noReply_count --;
                        if(reSendQueryPoint(Tcp_comm->numTcp,QDateTime::currentDateTime().toString("yyyyMMddHHmm")))
                        {
                            Tcp_comm->reSend_type[0] = false;
                            reSendDeletePoint(Tcp_comm->numTcp,QDateTime::currentDateTime().toString("yyyyMMddHHmm"));
                            break;
                        }
                        if(Tcp_comm->reSend_flag[0])
                            reSendDelete(Tcp_comm->numTcp);
#endif
                        break;
                    }
                    case FC_REPORT_ADD_REPORT://加报报响应
                    {
                        qDebug()<<"TCP_RECEIVE_SW_Add = " << Tcp_comm->recive_buf_comm.toHex();
                        break;
                    }
                    case FC_REPORT_HOUR://小时报响应
                    {
                        qDebug()<<"TCP_RECEIVE_SW_Hour = " << Tcp_comm->recive_buf_comm.toHex();
                        break;
                    }
                    case FC_REPORT_MANUAL_WORK://人工置数报响应
                    {
                        qDebug()<<"TCP_RECEIVE_SW_Set_Number = " << Tcp_comm->recive_buf_comm.toHex();
                        break;
                    }
                    case FC_REPORT_QUERY_PIC://图片数据查询
                    {
                         if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询图片
                         {
                             qDebug()<<"TCP_RECEIVE_SW_PIC = " << Tcp_comm->recive_buf_comm.toHex();
                             QString camera_ip = MainWindow::iniFile->value("/Camera/IP1").toString();
                             QString camera_name = MainWindow::iniFile->value("/Camera/Name1").toString();
                             QString camera_password = MainWindow::iniFile->value("/Camera/Password1").toString();
                             report_SW_picture(Tcp_comm,camera_fun(camera_ip,camera_name,camera_password));//上传当前时间抓拍图片
                         }
                         else
                         {
                            //图片多帧传输应答
                         }
                        break;
                    }
                    case FC_QUERY_REALTIME_DATA://中心站查询遥测站实时数据
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询遥测站实时数据
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Query_RealTime_Data = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_QueryRealTime_Data(Tcp_comm);//水文协议 实时数据报
                        }
                        else
                        {
                            //平台实时数据应答
                        }
                        break;
                    }
                    case FC_QUERY_PERIOD_DATA://中心站查询遥测站均匀时段数据
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询遥测站均匀时段数据
                        {
                            if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 5) == ELEMENT_IDENTI_HOUR_RAIN)
                            {
                                qDebug()<<"TCP_RECEIVE_SW_Query_Uniform_Time_Rain = " << Tcp_comm->recive_buf_comm.toHex();
                                QString time1 = Tcp_comm->recive_buf_comm.toHex().mid(44,8);//年月日时
                                QString time2 = Tcp_comm->recive_buf_comm.toHex().mid(52,8);//年月日时
                                report_SW_QueryUniform_Time(Tcp_comm,ELEMENT_IDENTI_PRECIP_5MIN,time1,time2);//水文协议 均匀时段雨量数据
                            }
                            else if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 5) == ELEMENT_IDENTI_HOUR_WATER)
                            {
                                qDebug()<<"TCP_RECEIVE_SW_Query_Uniform_Time_Water = " << Tcp_comm->recive_buf_comm.toHex();
                                QString time1 = Tcp_comm->recive_buf_comm.toHex().mid(44,8);//年月日时
                                QString time2 = Tcp_comm->recive_buf_comm.toHex().mid(52,8);//年月日时
                                report_SW_QueryUniform_Time(Tcp_comm,ELEMENT_IDENTI_WATER_LEVEL,time1,time2);//水文协议 均匀时段水位数据
                            }
                            else
                            {
                                ;
                            }
                        }
                        else
                        {
                            //平台均匀时段数据应答
                        }
                        break;
                    }
                    case FC_QUERY_MANUAL_WORK://中心站查询遥测站人工置数
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询遥测站人工置数
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Query_Manual_Work = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_QueryManual_Work(Tcp_comm);
                        }
                        else
                        {
                            //人工置数应答
                        }
                        break;
                    }
                    case FC_QUERY_APPOINT_ELEMENT://中心站查询遥测站指定要素数
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//中心站查询遥测站指定要素数
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Query_Appoint_Element = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Query_APPOINT_ELEMENT(Tcp_comm);//水文协议 查询遥测站状态和报警信息
                        }
                        else
                        {
                            //平台查询遥测站指定要素数应答
                        }
                        break;
                    }
                    case FC_MODIFY_BASIC_SET://中心站修改遥测站基本配置表
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台修改遥测站基本配置表
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Modify_Basic_Set = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Modify_Basic_Set(Tcp_comm);//水文协议 修改遥测站基本配置表
                        }
                        else
                        {
                            //平台修改遥测站基本配置表应答
                        }
                        break;
                    }
                    case FC_REPORT_READ_BASIC_SET://中心站查询遥测站基本配置表
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询遥测站基本配置表
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Read_Basic_Set = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Query_Basic_Set(Tcp_comm);//水文协议 查询遥测站基本配置表
                        }
                        else
                        {
                            //平台查询遥测站基本配置表应答
                        }
                        break;
                    }
                    case FC_MODIFY_RUNNING_SET://中心站修改遥测站运行参数配置表
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台修改遥测站运行配置表
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Modify_Basic_Set = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Modify_Run_Set(Tcp_comm);//水文协议 修改遥测站运行配置表
                        }
                        else
                        {
                            //平台修改遥测站运行配置表应答
                        }
                        break;
                    }
                    case FC_REPORT_READ_RUNNING_SET://中心站查询遥测站运行参数配置表
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询遥测站运行配置表
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Read_Basic_Set = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Query_Run_Set(Tcp_comm);//水文协议 查询遥测站运行配置表
                        }
                        else
                        {
                            //平台查询遥测站运行配置表应答
                        }
                        break;
                    }
                    case FC_QUERY_PUMP_DATA://查询水泵电机实时工作数据
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(22) == ENQ){
                            qDebug()<<"TCP_RECEIVE_SW_Query_Fixed_Time = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Ask_Water_PumpPara(Tcp_comm);
                        }else {
                            //查询水泵电机实时工作数据传输应答
                        }

                         break;
                    }
                    case FC_QUERY_SOFT_VERSION://查询遥测终端软件版本
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(22) == ENQ){
                            qDebug()<<"TCP_RECEIVE_SW_Query_Soft_Version = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_QueryVersion(Tcp_comm);
                        }else {
                            //查询遥测终端软件版本据传输应答
                        }

                        break;
                    }
                    case FC_QUERY_STATUS://查询遥测站状态和报警信息
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)//平台查询遥测站实时数据
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Query_Alarm = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Query_Alarm(Tcp_comm);//水文协议 查询遥测站状态和报警信息
                        }
                        else
                        {
                            //平台遥测站状态和报警信息应答
                        }
                        break;
                    }
                    case FC_INIT_DATA://初始化固态存储数据
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Init_Data = " << Tcp_comm->recive_buf_comm.toHex();
                            Store_Data_Reset(Tcp_comm);
                        }
                        else
                        {
                             //中心站查询遥测站事件记录传输应答
                        }
                           break;
                    }
                    case FC_RESTORE_SETTING://恢复终端出厂设置
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Restore_Setting = " << Tcp_comm->recive_buf_comm.toHex();
                            Factory_Config_Reset(Tcp_comm);
                        }
                        else
                        {
                             //中心站查询遥测站事件记录传输应答
                        }
                           break;
                    }
                    case FC_SET_PASSWORD://修改密码
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ){

                             qDebug()<<"TCP_RECEIVE_SW_Set_Password = " << Tcp_comm->recive_buf_comm.toHex();
                             report_SW_Set_Password(Tcp_comm);
                        }else {
                                //修改密码传输应答
                        }
                        break;
                    }
                    case FC_SET_CLOCK://设置遥测站时钟
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Set_Clock = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Set_Clock(Tcp_comm);
                        }
                        else
                        {
                             //中心站设置遥测站时钟应答
                        }
                        break;
                    }
                    case FC_SET_IC_STATUS://设置遥测终端IC卡状态
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Set_IC_Status = " << Tcp_comm->recive_buf_comm.toHex();
                            QString IC_state = Tcp_comm->recive_buf_comm.toHex().mid(48,8);
                            report_SW_Set_ICstate(Tcp_comm,IC_state.toUInt(&ok,16));
                        }
                        else
                        {
                            //设置遥测终端IC卡状态传输应答
                        }
                        break;
                    }
                    case FC_REPORT_PUMP_SWITH_CMD://控制水泵开关命令
                    {
                    if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ){
                         qDebug()<<"TCP_RECEIVE_SW_Pump_Switch_Cmd = " << Tcp_comm->recive_buf_comm.toHex();
                         QByteArray data = Tcp_comm->recive_buf_comm.mid(22, 2);
                         QDataStream stream(data);
                         stream.setByteOrder(QDataStream::LittleEndian); // 设置字节序为小端序
                         uint16_t state;
                         stream >> state;
                         report_SW_Set_Water_Pumpstate(Tcp_comm,state);
                    } else {
                         //设置控制水泵开关命令传输应答
                    }
                       break;
                    }
                    case FC_REPORT_VALVE_SWITH_CMD://控制阀门开关命令
                    {    
                    if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ){
                        qDebug()<<"TCP_RECEIVE_SW_Valve_Switch_Cmd = " << Tcp_comm->recive_buf_comm.toHex();
                         QByteArray data = Tcp_comm->recive_buf_comm.mid(22, 2);
                         QDataStream stream(data);
                         stream.setByteOrder(QDataStream::BigEndian); // 设置字节序为小端序
                         uint16_t state;
                         stream >> state;
                         report_SW_Set_Valvestate(Tcp_comm,state);
                    } else {
                         //控制阀门开关命令传输应答
                    }
                       break;
                    }
                    case FC_REPORT_GATE_SWITH_CMD://控制闸门开关命令
                    {
                    if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ){
                        qDebug()<<"TCP_RECEIVE_SW_Gate_Switch_Cmd = " << Tcp_comm->recive_buf_comm.toHex();
                         QByteArray data = Tcp_comm->recive_buf_comm.mid(22, 4);
                         QDataStream stream(data);
                         stream.setByteOrder(QDataStream::BigEndian); // 设置字节序为小端序
                         uint32_t state;
                         stream >> state;
                         uint16_t value = BCDtoHalfword(((Tcp_comm->recive_buf_comm.at(24) << 8) & 0xFF00) + (Tcp_comm->recive_buf_comm.at(25) & 0x00FF));
                         report_SW_Set_gatestate(Tcp_comm,state,value);
                    } else {
                         //控制闸门开关命令传输应答
                    }
                       break;
                    }
                    case FC_WATER_YIELD_CMD://水量定值控制命令
                    {
                         if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ){
                             qDebug()<<"TCP_RECEIVE_SW_Water_Yield_Cmd = " << Tcp_comm->recive_buf_comm.toHex();
                              QByteArray data = Tcp_comm->recive_buf_comm.mid(22, 1);
                              QDataStream stream(data);
                              stream.setByteOrder(QDataStream::BigEndian); // 设置字节序为小端序
                              uint8_t state;
                              stream >> state;
                              report_SW_Set_Watersetting(Tcp_comm,state);
                         } else {
                              //水量定值控制命令传输应答
                         }
                            break;
                    }
                    case FC_QUERY_EVENT://中心站查询遥测站事件记录
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ)
                        {
                            qDebug()<<"TCP_RECEIVE_SW_Query_Event = " << Tcp_comm->recive_buf_comm.toHex();
                            report_SW_Query_Event(Tcp_comm);
                        }
                        else
                        {
                             //中心站查询遥测站事件记录传输应答
                        }
                           break;
                    }
                    case FC_QUERY_CLOCK://中心站查询遥测站时钟
                    {
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == ENQ){
                             qDebug()<<"TCP_RECEIVE_SW_Query_Clock = " << Tcp_comm->recive_buf_comm.toHex();
                             report_SW_Query_stationTime(Tcp_comm);
                        }else {
                             //中心站查询遥测站时钟传输应答
                        }

                        break;
                    }
                    default:
                        break;
                }
            }
        }
        else if((unsigned char)Tcp_comm->recive_buf_comm.at(0) == 0x68 && (unsigned char)Tcp_comm->recive_buf_comm.at(2) == 0x68)//水资源协议
        {
            uint8_t crc8;
            QByteArray CrcCheck = Tcp_comm->recive_buf_comm.left(Tcp_comm->recive_buf_comm.size()-2);
            crc8 = CRC8_SZY(CrcCheck,CrcCheck.size());
            if(crc8==(unsigned char)Tcp_comm->recive_buf_comm[Tcp_comm->recive_buf_comm.size()-2])//RCR校验通过
            {
                Tcp_comm->socket_flag = true;

                //CT 不检测地址
//                if((report_SZY_headhex->station_Addr_SZY[0] != (unsigned char)Tcp_comm->recive_buf_comm.at(4)) ||
//                   (report_SZY_headhex->station_Addr_SZY[1] != (unsigned char)Tcp_comm->recive_buf_comm.at(5)) ||
//                   (report_SZY_headhex->station_Addr_SZY[2] != (unsigned char)Tcp_comm->recive_buf_comm.at(6)) ||
//                   (report_SZY_headhex->station_Addr_SZY[3] != (unsigned char)Tcp_comm->recive_buf_comm.at(7)) ||
//                   (report_SZY_headhex->station_Addr_SZY[4] != (unsigned char)Tcp_comm->recive_buf_comm.at(8))
//                  )
//                    return;

                switch((unsigned char)Tcp_comm->recive_buf_comm.at(9))//AFN功能码
                {
                    case 0x02://链路报
                    {
                        //qDebug()<<"TCP_RECEIVE_SZY_LINK_DATA = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == 0xF0)
                        {
                            //登录
                            report_SZY_link(Tcp_comm,0xF0);
                        }
                        else if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 3) == 0xF2)
                        {
                            //保持在线
                            report_SZY_headhex->station_Addr_SZY[0] = (unsigned char)Tcp_comm->recive_buf_comm.at(4);
                            report_SZY_headhex->station_Addr_SZY[1] = (unsigned char)Tcp_comm->recive_buf_comm.at(5);
                            report_SZY_headhex->station_Addr_SZY[2] = (unsigned char)Tcp_comm->recive_buf_comm.at(6);
                            report_SZY_headhex->station_Addr_SZY[3] = (unsigned char)Tcp_comm->recive_buf_comm.at(7);
                            report_SZY_headhex->station_Addr_SZY[4] = (unsigned char)Tcp_comm->recive_buf_comm.at(8);
                            MainWindow::iniFile->setValue("/SZY_PROTOCOL/Station_addr",Tcp_comm->recive_buf_comm.toHex().mid(8,10));
                            report_SZY_link(Tcp_comm,0xF2);
                        }
                        else
                        {

                        }
                        break;
                    }
                    case 0x20://设置遥测终端雨量启报阈值及固态存储时间段间隔
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_THRESHOLD_STORETIME = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetThresholdStoreTime(Tcp_comm);
                        break;
                    }
                    case 0x1F://设置流量参数
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_FLOW = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetFlow(Tcp_comm);
                        break;
                    }
                    case 0x64://查询流量参数
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_FLOW = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryFlow(Tcp_comm);
                        break;
                    }
                    case 0x11://设置时钟
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_CLOCK = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetClock(Tcp_comm);
                        break;
                    }
                    case 0x51://查询时钟
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_CLOCK = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryClock(Tcp_comm);
                        break;
                    }
                    case 0x17://设置终端水位基值、水位上限
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_WATERL_LEVEL = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetWaterLevel(Tcp_comm);
                        break;
                    }
                    case 0x57://查询终端水位基值、水位上限
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_WATERL_LEVEL = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryWaterLevel(Tcp_comm);
                        break;
                    }
                    case 0x52://查询工作模式
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_WORKMODE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryWorkMode(Tcp_comm);
                        break;
                    }
                    case 0x12://设置工作模式
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_WORKMODE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetWorkMode(Tcp_comm);
                        break;
                    }
                    case 0x10://设置终端地址
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_ADDRESS = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetAddress(Tcp_comm);
                        break;
                    }
                    case 0x50://查询终端地址
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_ADDRESS = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryAddress(Tcp_comm);
                        break;
                    }
                    case 0xA1://设置遥测终端的数据自报种类及时间间隔
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_UPLOAD_TIME = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetUploadTime(Tcp_comm);
                        break;
                    }
                    case 0x53://查询遥测终端的数据自报种类及时间间隔
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_UPLOAD_TIME = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryUploadTime(Tcp_comm);
                        break;
                    }
                    case 0x5E://查询遥测终端状态和报警状态
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_ALL_STATE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryAllState(Tcp_comm);
                        break;
                    }
                    case 0x90://复位遥测终端参数和状态
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_ResetTerminal = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_ResetTerminal(Tcp_comm);
                        break;
                    }
                    case 0x91://清空遥测终端历史数据单元
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_DeleteHistoryData = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_DeleteHistoryData(Tcp_comm);
                        break;
                    }
                    case 0x92://遥控启动水泵或阀门/闸门
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_OpenKDY = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_OpenKDY(Tcp_comm);
                        break;
                    }
                    case 0x93://遥控关闭水泵或阀门/闸门
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_CloseKDY = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_CloseKDY(Tcp_comm);
                        break;
                    }
                    case 0x96://修改密码
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_SET_PASSWORD = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_SetPassword(Tcp_comm);
                        break;
                    }
                    case 0xB0://查询遥测终端实时值
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_REALTIME_VALUE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryRealTimeValue(Tcp_comm);
                        break;
                    }
                    case 0xB1://查询终端的固态存储数据
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_DATA = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryData(Tcp_comm);
                        break;
                    }
                    case 0xB2://查询内存自报数据
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_PICTURE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_QueryUploadData(Tcp_comm);
                        break;
                    }
                    case 0x61://查询遥测终端图像记录
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_PICTURE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        QString camera_ip = MainWindow::iniFile->value("/Camera/IP1").toString();
                        QString camera_name = MainWindow::iniFile->value("/Camera/Name1").toString();
                        QString camera_password = MainWindow::iniFile->value("/Camera/Password1").toString();
                        report_SZY_QueryPicture(Tcp_comm,camera_fun(camera_ip,camera_name,camera_password));
                        break;
                    }
					case 0x30:
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_PICTURE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_EnableIC(Tcp_comm);
                        break;
                    }
                    case 0x31:
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_QUERY_PICTURE = " << Tcp_comm->recive_buf_comm.toHex();
                        report_SZY_headhex->control_area = DIR_MASK | ((unsigned char)Tcp_comm->recive_buf_comm.at(3) & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
                        report_SZY_DisableIC(Tcp_comm);
                        break;
                    }
                    case 0xC0://自报数据响应
                    {
                        qDebug()<<"TCP_RECEIVE_SZY_FIXED_DATA = " << Tcp_comm->recive_buf_comm.toHex();
#ifdef RESEND
                        Tcp_comm->replytype_count --;
                        Tcp_comm->reSend_replytype_count --;
                        if(Tcp_comm->replytype_count <= 0)
                        {
                            if(reSendQueryPoint_SZY(Tcp_comm->numTcp,QDateTime::currentDateTime().toString("yyyyMMddHHmm")))
                            {
                                Tcp_comm->noReply_count --;
                                if(Tcp_comm->reSend_flag[1] == true)
                                    Tcp_comm->reSend_type[1] = true;
                                else
                                    Tcp_comm->reSend_type[1] = false;
                                reSendDeletePoint_SZY(Tcp_comm->numTcp,QDateTime::currentDateTime().toString("yyyyMMddHHmm"));
                                break;
                            }
                        }

                        if((Tcp_comm->reSend_flag[1]) && (Tcp_comm->reSend_replytype_count <= 0))
                        {
                            for(uint8_t i=0;i<report_SZY_headhex->uploadtype_count - 1;i++)
                                reSendDelete_SZY(Tcp_comm->numTcp);//删除第一行数据
                        }
#endif
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
        else if((unsigned char)Tcp_comm->recive_buf_comm.at(0) == 0x5A && (unsigned char)Tcp_comm->recive_buf_comm.at(1) == 0xA5)//维护平台新世杰协议
        {
            uint8_t H_CRC_Data,L_CRC_Data;
            QByteArray CrcCheck = Tcp_comm->recive_buf_comm.left(Tcp_comm->recive_buf_comm.size()-2);
            uint16_t CRC_Data=ModBusCRC16(CrcCheck,CrcCheck.size());
            L_CRC_Data=CRC_Data & 0xff;
            H_CRC_Data=(CRC_Data>>8) & 0xff;
            if(H_CRC_Data==(unsigned char)Tcp_comm->recive_buf_comm[Tcp_comm->recive_buf_comm.size()-2] &&
               L_CRC_Data==(unsigned char)Tcp_comm->recive_buf_comm[Tcp_comm->recive_buf_comm.size()-1]
              )//RCR校验通过
            {
                Tcp_comm->socket_flag = true;
                qDebug()<<"TCP_MAINTENANCE_Receive = " << Tcp_comm->recive_buf_comm.toHex();
                switch((unsigned char)Tcp_comm->recive_buf_comm.at(2))//功能码
                {
                    case 0xFF://握手响应
                         qDebug()<<"TCP_MAINTENANCE_CONNECT_OK";
                    break;

                    case 0x01://读配置文件
                    {
                        Tcp_comm->tcp_busy = true;
                        if(maintenance.fun_flag[0])//发文件数据
                        {
                            qDebug()<<"TCP_MAINTENANCE_Send_Config_file_data";
                            uint32_t send_size = 1024;//每包字节数
                            uint32_t load_size = 0;//已发送字节数
                            QFile file(maintenance.file_path);
                            if(!file.open(QIODevice::ReadOnly))//打开文件失败
                            {
                                qDebug()<<"open_file_error:" << maintenance.file_path;
                                return;
                            }
                            while(load_size < (maintenance.file_size))
                            {
                                QByteArray file_date;
                                if((maintenance.file_size - load_size) < send_size)
                                    file_date = file.read(maintenance.file_size - load_size);
                                else
                                    file_date = file.read(send_size);
                                uint32_t write_size = Tcp_comm->TCP_Socket->write(file_date);
                                QThread::msleep(100);
                                if(!Tcp_comm->TCP_Socket->waitForBytesWritten(2000))
                                {
                                    qDebug()<<"net_wait_error";
                                    updata_label->hide();
                                    QCoreApplication::processEvents();//强制刷新UI界面
                                    Tcp_comm->tcp_busy = false;
                                    maintenance.fun_flag[0] = false;
                                    return;
                                }
                                load_size += write_size;
                            }
                            file.close();
                            Tcp_comm->tcp_busy = false;
                            maintenance.fun_flag[0] = false;
                        }
                        else//发文件信息
                        {
                            qDebug()<<"TCP_MAINTENANCE_Send_Config_file_info";
                            updata_label->hide();
                            for(uint8_t  i=0;i<5;i++)
                                maintenance.fun_flag[i] = false;
                            maintenance.fun_flag[0] = true;
#ifdef ARM
                            maintenance.file_path = "/home/Config.ini";
#else
                            QString path = QDir::currentPath();
                            maintenance.file_path = path + "/home/Config.ini";
#endif
                            QFile FileData(maintenance.file_path);
                            maintenance.file_size = FileData.size();
                            maintenance = {0x5AA5,0x01,0xA001,&FileData,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                                           maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                            maintenance_link();
                        }
                    }
                    break;

                    case 0x02://写配置文件
                    {
                        Tcp_comm->tcp_busy = true;
                        for(uint8_t  i=0;i<5;i++)
                            maintenance.fun_flag[i] = false;
                        maintenance.fun_flag[1] = true;
                        //16进制转16进制字符串
                        file_len_str = Tcp_comm->recive_buf_comm.toHex().mid(10,8);
                        maintenance.file_size = file_len_str.toULongLong(&ok,16);//16进制字符串转10进制
                        qDebug()<<"TCP_config.ini_recive_start";
                        QFile file("/home/Config.ini");
                        maintenance = {0x5AA5,0x02,0xA001,&file,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                                       maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                        maintenance_link();
                        updata_label->setText("配置文件更新中...");
                        updata_label->raise();
                        updata_label->show();
                        file_comm_count = 0;
                        QCoreApplication::processEvents();//强制刷新UI界面
#ifdef ARM
                        system("rm /home/Config_backups.ini");
#endif
                    }
                    break;

                    case 0x03://远程升级
                    {
                        Tcp_comm->tcp_busy = true;
                        for(uint8_t  i=0;i<5;i++)
                            maintenance.fun_flag[i] = false;
                        maintenance.fun_flag[2] = true;
                        //16进制转16进制字符串
                        file_len_str = Tcp_comm->recive_buf_comm.toHex().mid(10,8);
                        maintenance.file_size = file_len_str.toULongLong(&ok,16);//16进制字符串转10进制
                        pProgressBar->setRange(0,maintenance.file_size);
                        qDebug()<<"TCP_updata_recive_start";
                        QFile file("/home/main_menu");
                        maintenance = {0x5AA5,0x03,0xA001,&file,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                                       maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                        maintenance_link();
                        updata_label->setText("版本更新中...");
                        updata_label->raise();
                        updata_label->show();
                        pProgressBar->raise();
                        pProgressBar->show();
                        file_comm_count = 0;
                        QCoreApplication::processEvents();//强制刷新UI界面
#ifdef ARM
                        system("rm /home/main_menu_backups");
#endif
                    }
                    break;

                    case 0x04://写EXCEL格式
                    {
                        Tcp_comm->tcp_busy = true;
                        for(uint8_t  i=0;i<5;i++)
                            maintenance.fun_flag[i] = false;
                        maintenance.fun_flag[3] = true;
                        //16进制转16进制字符串
                        file_len_str =Tcp_comm->recive_buf_comm.toHex().mid(10,8);
                        maintenance.file_size = file_len_str.toULongLong(&ok,16);//16进制字符串转10进制
                        qDebug()<<"TCP_EXCEL_recive_start";
                        QFile file("/home/formula.xlsx");
                        maintenance = {0x5AA5,0x04,0xA001,&file,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                                       maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                        maintenance_link();
                        updata_label->setText("EXCEL文件更新中...");
                        updata_label->raise();
                        updata_label->show();
                        file_comm_count = 0;
                        QCoreApplication::processEvents();//强制刷新UI界面
    #ifdef ARM
                        system("rm /home/formula_backups.xlsx");
    #endif
                    }
                    break;

                    case 0x05://读历史数据
                    {
                        Tcp_comm->tcp_busy = true;
                        if(maintenance.fun_flag[4])//发文件数据
                        {
                            qDebug()<<"TCP_MAINTENANCE_Send_DB_file_data";
                            updata_label->setText("历史数据上传中...");
                            updata_label->raise();
                            updata_label->show();

                            maintenance.send_size = 1024 * 4;//每包字节数
                            QFileInfo FileData(maintenance.file_path);
                            maintenance.file_info = new QFile(maintenance.file_path);
                            if(!maintenance.file_info->open(QIODevice::ReadOnly))//打开文件失败
                            {
                                qDebug()<<"open_file_error:" << maintenance.file_path;
                                return;
                            }
                            file_comm_count = 0;
                            maintenance.load_size = 0;
                            timer4->start(50);
                        }
                        else//发文件信息
                        {
                            qDebug()<<"TCP_MAINTENANCE_Send_DB_file_info";
                            for(uint8_t  i=0;i<5;i++)
                                maintenance.fun_flag[i] = false;
                            maintenance.fun_flag[4] = true;
                            maintenance.file_path = MainWindow::dbFile;
                            QFile FileData(maintenance.file_path);
                            maintenance.file_size = FileData.size();
                            maintenance = {0x5AA5,0x05,0xA001,&FileData,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                                           maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                            maintenance_link();
                        }
                    }
                    break;

                    case 0x06://读日志
                    {
                        Tcp_comm->tcp_busy = true;
                        if(maintenance.fun_flag[5])//发文件数据
                        {
                            updata_label->setText("日志上传中...");
                            updata_label->raise();
                            updata_label->show();

                            maintenance.send_size = 1024 * 4;//每包字节数
                            QFileInfo FileData(maintenance.file_path);
                            maintenance.file_info = new QFile(maintenance.file_path);
                            if(!maintenance.file_info->open(QIODevice::ReadOnly))//打开文件失败
                            {
                                qDebug()<<"open_file_error:" << maintenance.file_path;
                                return;
                            }
                            file_comm_count = 0;
                            maintenance.load_size = 0;
                            timer4->start(50);
                        }
                        else//发文件信息
                        {
                            for(uint8_t  i=0;i<5;i++)
                                maintenance.fun_flag[i] = false;
                            maintenance.fun_flag[5] = true;
                            maintenance.file_path = MainWindow::logFile;
                            QFile FileData(maintenance.file_path);
                            maintenance.file_size = FileData.size();
                            maintenance = {0x5AA5,0x06,0xA001,&FileData,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                                           maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                            maintenance_link();
                        }
                    }
                    break;

                    default:
                    break;
                }
                Tcp_comm->recive_buf_comm.clear();
            }
        }
        else if(maintenance.fun_flag[2] == true)//远程升级
        {
            QFile file("/home/main_menu_backups");
            if(!file.open(QIODevice::ReadWrite | QIODevice::Append))//打开文件失败
            {
                qDebug()<<"TCP_updata_open_error";
                return;
            }
            uint32_t len = file.write(Tcp_comm->recive_buf_comm);
            Tcp_comm->recive_buf_comm.clear();
            if(len > 0)
            {
                recive_file_size += len;
                fileComm_UIcount = fileComm_UIcount + len;
                pProgressBar->setValue(fileComm_UIcount);
            }
            if(recive_file_size >= maintenance.file_size)
            {
                recive_file_size = 0;
                file_comm_count = 0;
                qDebug()<<"TCP_updata_recive_ok";
                file.close();
                QThread::msleep(200);
                maintenance = {0x5AA5,0x03,0xA001,maintenance.file_info,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                               maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                maintenance_link();
                QThread::msleep(200);
                maintenance.fun_flag[2] = false;
#ifdef ARM
                serial_send_disconnect();
                system("killall XSJ1800RV");
                system("cp /home/main_menu_backups /home/XSJ1800RV");
                system("chmod 777 -R /home/XSJ1800RV");
                system("sync");
                system("reboot -f");
#endif
            }
        }
        else if(maintenance.fun_flag[1] == true)//写配置文件
        {
            QFile file("/home/Config_backups.ini");
            if(!file.open(QIODevice::ReadWrite | QIODevice::Append))//打开文件失败
            {
                qDebug()<<"TCP_Config.ini_open_error";
                return;
            }
            uint32_t len = file.write(Tcp_comm->recive_buf_comm);
            Tcp_comm->recive_buf_comm.clear();
            if(len > 0)
                recive_file_size += len;
            if(recive_file_size >= maintenance.file_size)
            {
                recive_file_size = 0;
                file_comm_count = 0;
                qDebug()<<"TCP_config_recive_ok";
                file.close();
                QThread::msleep(200);
                maintenance = {0x5AA5,0x02,0xA001,maintenance.file_info,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                               maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                maintenance_link();
                QThread::msleep(200);
                maintenance.fun_flag[1] = false;
                delete_ReSendData_Total();
#ifdef ARM
                serial_send_disconnect();
                system("mv /home/Config_backups.ini /home/Config.ini");
                system("chmod 777 -R /home/Config.ini");
                system("sync");
                system("reboot -f");
#endif
            }
        }
        else if(maintenance.fun_flag[3] == true)//写EXCEL文件
        {
            QFile file("/home/formula_backups.xlsx");
            if(!file.open(QIODevice::ReadWrite | QIODevice::Append))//打开文件失败
            {
                qDebug()<<"TCP_EXCEL_open_error";
                return;
            }
            uint32_t len = file.write(Tcp_comm->recive_buf_comm);
            Tcp_comm->recive_buf_comm.clear();
            if(len > 0)
                recive_file_size += len;
            if(recive_file_size >= maintenance.file_size)
            {
                recive_file_size = 0;
                file_comm_count = 0;
                qDebug()<<"TCP_updata_recive_ok";
                file.close();
                QThread::msleep(200);
                maintenance = {0x5AA5,0x04,0xA001,maintenance.file_info,maintenance.file_path,maintenance.file_size,maintenance.send_size,maintenance.load_size,{maintenance.fun_flag[0],maintenance.fun_flag[1],
                               maintenance.fun_flag[2],maintenance.fun_flag[3],maintenance.fun_flag[4],maintenance.fun_flag[5]}};
                maintenance_link();
                QThread::msleep(200);
                maintenance.fun_flag[3] = false;
#ifdef ARM
                serial_send_disconnect();
                system("mv /home/formula_backups.xlsx /home/formula.xlsx");
                system("chmod 777 -R /home/formula.xlsx");
                system("sync");
                system("reboot -f");
#endif
            }
        }
        else
            qDebug()<<"TCP_RECEIVE_ERROR";
    }
}

QString tcp_socket::floatToBCD(float number)
{
    int the_interger = (int)number;
    int the_float = (int)((number - (float)the_interger + 0.00001)*100);

    QString bcdString = QString("%1").arg(QString::number(the_interger),2,'0') +QString(" ") + QString("%1").arg(QString::number(the_float),2,'0');
    return bcdString;
}

void tcp_socket::socket1_Disconnected()
{
    tcp_comm[0].socket_flag = false;
    qDebug() << "socket1 disconnected!";

    QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
    DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
    singleInsertData("Alarm",DATA_BASE_Water,"TCP1 Disconnet");
}

void tcp_socket::socket2_Disconnected()
{
    tcp_comm[1].socket_flag = false;
    qDebug() << "socket2 disconnected!";

    QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
    DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
    singleInsertData("Alarm",DATA_BASE_Water,"TCP2 Disconnet");
}

void tcp_socket::socket3_Disconnected()
{
    tcp_comm[2].socket_flag = false;
    qDebug() << "socket3 disconnected!";

    QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
    DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
    singleInsertData("Alarm",DATA_BASE_Water,"TCP3 Disconnet");
}

void tcp_socket::socket4_Disconnected()
{
    tcp_comm[3].socket_flag = false;
    qDebug() << "socket4 disconnected!";

    QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
    DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
    singleInsertData("Alarm",DATA_BASE_Water,"TCP4 Disconnet");
}

void tcp_socket::socket5_Disconnected()
{
    tcp_comm[4].socket_flag = false;
    qDebug() << "socket5 disconnected!";

    QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
    DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
    singleInsertData("Alarm",DATA_BASE_Water,"TCP5 disconnet");
}


void tcp_socket::timerTimeout_second()
{
    if(QTime::currentTime().second() == 0)
    {
        timer->stop();
        timer2->start(60000);
    }
}

void tcp_socket::Timeout_second_picture()
{
    if(pic_send.socket_agreement == 0)//水文
    {
        if(pic_send.load_size < pic_send.pic_file_size)
        {
            uint16_t index = 0,count = 0;
            QByteArray send_data;
            uint16_t CRC_Data = 0;
            send_data.clear();
            index = 0;

            send_data[index++] = report_SW_headhex->frame_Begin >> 8;
            send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
            send_data[index++] = report_SW_headhex->station_centerAddr;
            send_data[index++] = report_SW_headhex->station_ycAddr[0];
            send_data[index++] = report_SW_headhex->station_ycAddr[1];
            send_data[index++] = report_SW_headhex->station_ycAddr[2];
            send_data[index++] = report_SW_headhex->station_ycAddr[3];
            send_data[index++] = report_SW_headhex->station_ycAddr[4];
            send_data[index++] = report_SW_headhex->password >> 8;
            send_data[index++] = report_SW_headhex->password & 0xff;

            send_data[index++] = FC_REPORT_QUERY_PIC;//功能码
            send_data[index++] = 0x00;//上行报文标识和数据长度
            send_data[index++] = 0x00;//上行报文标识和数据长度
            send_data[index++] = SYN;//多帧正文起始

            pic_send.pack_no = pic_send.pack_no + 1;
            send_data[index++] = pic_send.pack_total >> 4;//3个字节，12位总包数和12位当前包序号
            send_data[index++] = ((pic_send.pack_total & 0x0f) << 4) + ((pic_send.pack_no >> 8) & 0x0f);
            send_data[index++] = pic_send.pack_no & 0xff;

            if(pic_send.pack_no == 1)//新世杰规定，图片第一帧传文件信息，后面不传
            {
                tcp_comm->send_num = tcp_comm->send_num + 1;
                send_data[index++] = tcp_comm->send_num >> 8;//报文流水号
                send_data[index++] = tcp_comm->send_num & 0xff;//报文流水号

                QDate currentdate = QDate::currentDate();
                QTime currenttime = QTime::currentTime();
                send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
                send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
                send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
                send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
                send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
                send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

                send_data[index++] = 0xF1;//地址标识符
                send_data[index++] = 0xF1;

                send_data[index++] = report_SW_headhex->station_ycAddr[0];
                send_data[index++] = report_SW_headhex->station_ycAddr[1];
                send_data[index++] = report_SW_headhex->station_ycAddr[2];
                send_data[index++] = report_SW_headhex->station_ycAddr[3];
                send_data[index++] = report_SW_headhex->station_ycAddr[4];

                send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

                send_data[index++] = 0xF0;//观测时间标识符
                send_data[index++] = 0xF0;

                send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
                send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
                send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
                send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
                send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

                send_data[index++] = 0xF3;//图片标识符
                send_data[index++] = 0xF3;//图片标识符
            }

            count = index;
            QByteArray file_date;
            if((pic_send.pic_file_size - pic_send.load_size) <= pic_send.send_size)
            {
                file_date = pic_send.pic_file->read(pic_send.pic_file_size - pic_send.load_size);
                for(uint16_t i=0;i<(pic_send.pic_file_size - pic_send.load_size);i++)
                    send_data[index++] = file_date[i];
                send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
                send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度
                send_data[index++] = ETX;//传输正文结束,后续无报文
                pic_send.load_size += pic_send.pic_file_size - pic_send.load_size;
                CRC_Data = ModBusCRC16(send_data,count+file_date.size()+1);
                send_data[index++] = CRC_Data >> 8;
                send_data[index++] = CRC_Data & 0xff;
                send_data.resize(count+file_date.size()+3);//修改长度
                for(uint8_t i=0;i<4;i++)
                {
                    if(tcp_comm[i].tcp_busy)
                        socket_Send(&tcp_comm[i],send_data,send_data.size());
                }
            }
            else
            {
                file_date = pic_send.pic_file->read(pic_send.send_size);
                for(uint16_t i=0;i<pic_send.send_size;i++)
                    send_data[index++] = file_date[i];
                send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
                send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度
                send_data[index++] = ETB;//传输正文结束,后续有报文
                pic_send.load_size += pic_send.send_size;
                CRC_Data = ModBusCRC16(send_data,count+file_date.size()+1);
                send_data[index++] = CRC_Data >> 8;
                send_data[index++] = CRC_Data & 0xff;
                for(uint8_t i=0;i<4;i++)
                {
                    if(tcp_comm[i].tcp_busy)
                        socket_Send(&tcp_comm[i],send_data,send_data.size());
                }
            }
        }
        else
        {
            pic_send.pic_file->close();
            for(uint8_t i=0;i<4;i++)
            {
                if(tcp_comm[i].tcp_busy)
                    tcp_comm[i].tcp_busy = false;
            }
            timer3->stop();
        }
    }
    else//水资源
    {
        if(pic_send.load_size < pic_send.pic_file_size)
        {
            // 组包返回
            QByteArray send_data;
            uint16_t index = 0, crc8 = 0;
            send_data.clear();
            send_data[index++] = 0x68;//帧头
            send_data[index++] = 0x00;
            send_data[index++] = 0x68;
            send_data[index++] = report_SZY_headhex->control_area | DIV_FLAG;//控制域 + 拆分标志
            send_data[index++] = pic_send.pack_total;
            send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
            send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
            send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
            send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
            send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
            send_data[index++] = 0x61;

            // 读取图片信息
            QByteArray file_date;
            if((pic_send.pic_file_size - pic_send.load_size) <= pic_send.send_size)
            {
                file_date = pic_send.pic_file->read(pic_send.pic_file_size - pic_send.load_size);
                send_data[index++] = (pic_send.pic_file_size - pic_send.load_size) & 0xFF;//有效数据长度
                send_data[index++] = ((pic_send.pic_file_size - pic_send.load_size) >> 8) & 0xFF;
                for(uint16_t i=0;i<(pic_send.pic_file_size - pic_send.load_size);i++)
                    send_data[index++] = file_date[i];
                pic_send.load_size += pic_send.pic_file_size - pic_send.load_size;
                crc8 = CRC8_SZY(send_data,index);
                send_data[index++] = crc8;
                send_data[index++] = 0x16;//帧尾
                send_data[1] = pic_send.pack_total;//图片传输，数据长度为L * 1K

                for(uint8_t i=0;i<4;i++)
                {
                    if(tcp_comm[i].tcp_busy)
                        socket_Send(&tcp_comm[i],send_data,send_data.size());
                }
            }
            else
            {
                file_date = pic_send.pic_file->read(pic_send.send_size);
                send_data[index++] = pic_send.send_size & 0xFF;//有效数据长度
                send_data[index++] = (pic_send.send_size >> 8) & 0xFF;
                for(uint16_t i=0;i<pic_send.send_size;i++)
                    send_data[index++] = file_date[i];
                pic_send.load_size += pic_send.send_size;
                crc8 = CRC8_SZY(send_data,index);
                send_data[index++] = crc8;
                send_data[index++] = 0x16;//帧尾
                send_data[1] = pic_send.pack_total;//图片传输，数据长度为L * 1K

                for(uint8_t i=0;i<4;i++)
                {
                    if(tcp_comm[i].tcp_busy)
                        socket_Send(&tcp_comm[i],send_data,send_data.size());
                }
            }
            pic_send.pack_total = pic_send.pack_total - 1;
        }
        else
        {
            pic_send.pic_file->close();
            for(uint8_t i=0;i<4;i++)
            {
                if(tcp_comm[i].tcp_busy)
                    tcp_comm[i].tcp_busy = false;
            }
            timer3->stop();
        }
    }
}

void tcp_socket::Timeout_send_maintenance_file()
{
    file_comm_count ++;
    if(file_comm_count > (20 * 60 * 5))//5分钟
    {
        updata_label->hide();
        QCoreApplication::processEvents();//强制刷新UI界面
        maintenance.file_info->close();
        maintenance.load_size = 0;
        tcp_comm[4].tcp_busy = false;
        maintenance.fun_flag[4] = false;
        maintenance.fun_flag[5] = false;
        file_comm_count = 0;
        timer4->stop();
        return;
    }

    if((maintenance.load_size < maintenance.file_size))
    {
        QByteArray file_date;
        if((maintenance.file_size - maintenance.load_size) < maintenance.send_size)
            file_date = maintenance.file_info->read(maintenance.file_size - maintenance.load_size);
        else
            file_date = maintenance.file_info->read(maintenance.send_size);
        uint32_t write_size = tcp_comm[4].TCP_Socket->write(file_date);
        if(!tcp_comm[4].TCP_Socket->waitForBytesWritten(2000))
        {
            qDebug()<<"net_wait_error";
            updata_label->hide();
            QCoreApplication::processEvents();//强制刷新UI界面
            maintenance.file_info->close();
            maintenance.load_size = 0;
            tcp_comm[4].tcp_busy = false;
            maintenance.fun_flag[4] = false;
            maintenance.fun_flag[5] = false;
            file_comm_count = 0;
            timer4->stop();
            return;
        }
        maintenance.load_size += write_size;
        tcp_comm[4].tcp_onLine = true;//上传平台不回报文，避免认为掉线
    }
    else
    {
        updata_label->hide();
        QCoreApplication::processEvents();//强制刷新UI界面
        maintenance.file_info->close();
        maintenance.load_size = 0;
        tcp_comm[4].tcp_busy = false;
        maintenance.fun_flag[4] = false;
        maintenance.fun_flag[5] = false;
        file_comm_count = 0;
        timer4->stop();
    }
}

void tcp_socket::timerTimeout_minute()
{   
    for(uint8_t i=0;i<5;i++)
    {
        if(tcp_comm[i].socket_select == false)
            continue;
        if(tcp_comm[i].socket_flag == false)//未连接平台
            socket_Connect(&tcp_comm[i]);

        if(tcp_comm[i].tcp_onLine)
        {
            tcp_comm[i].tcp_onLine = false;//在线标志
            tcp_comm[i].tcp_onLineTime = QDateTime::currentDateTime();
        }

        int disconnect_sec = tcp_comm[i].tcp_onLineTime.secsTo(QDateTime::currentDateTime());
        if((disconnect_sec > 240) || (tcp_comm[i].noReply_count >= 3))//5分钟没有通信或定时报无响应超过3次
        {
            qDebug()<<"TCP" << i <<" ReConnect";
            //qDebug()<<"second=" << disconnect_sec <<" noReply count=" << tcp_comm[i].noReply_count;
            tcp_comm[i].socket_flag = false;
            tcp_comm[i].noReply_count = 0;

            QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
            DATA_BASE2 DATA_Alarm = {1,time_now_date,0};
            QString alarm_str = "TCP" + QString::number(i) + " ReConnect";
            singleInsertData("Alarm",DATA_Alarm,alarm_str);
            tcp_comm[i].tcp_onLineTime = QDateTime::currentDateTime();
            if(i == 4)//维护平台
            {
                updata_label->hide();
                QCoreApplication::processEvents();//强制刷新UI界面
                tcp_comm[4].tcp_busy = false;
                QFile file("/home/Config.ini");
                maintenance = {0x5AA5,0xFF,0xA001,&file,"",0x00,0x00,0x00,{false,false,false,false,false,false}};
                tcp_comm[4].recive_buf_comm.clear();
                recive_file_size = 0;
            }
        }
    }

    if(QTime::currentTime().minute() % report_SZY_headhex->fixed_report_minute == 0)
    {
        report_SZY_headhex->report_fixed_flag = true;//发送定时报标志
    }

    if(QTime::currentTime().minute() % report_SW_headhex->fixed_report_minute == 0)
    {
        report_SW_headhex->report_fixed_flag = true;//发送定时报标志
        return;//发送定时报就不发送链路报也不补传
    }

#ifdef RESEND
    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].socket_flag == false)//未连接平台
            continue;
        if(tcp_comm[i].tcp_busy == true)
            continue;
        if(report_SZY_headhex->report_fixed_flag == true)//发送定时报就不补传
            continue;
        if((tcp_comm[i].reSend_type[0] == true) || (tcp_comm[i].reSend_flag[0] == true))//水文补传
        {
            if(reSendQuery(i+1))//查询到补传数据
            {
                tcp_comm[i].reSend_flag[0] = true;
                QByteArray reSend_data;
                StringToHex(data_reSend.data,reSend_data);
                socket_Send(&tcp_comm[i],reSend_data,reSend_data.size());
            }
            else
                tcp_comm[i].reSend_flag[0] = false;
        }
        if((tcp_comm[i].reSend_type[1] == true) || (tcp_comm[i].reSend_flag[1] == true))//水资源补传
        {
            report_SZY_link(&tcp_comm[i],0xF2);//先发F2保持在线，再发定时报
            tcp_comm[i].reSend_flag[1] = true;
            tcp_comm[i].replytype_count = tcp_comm[i].reSend_replytype_count = report_SZY_headhex->uploadtype_count - 1;
            tcp_comm[i].reSend_send_count = 0;

            if(i == 0)
                timer5->start(200);
            if(i == 1)
                timer6->start(200);
            if(i == 2)
                timer7->start(200);
            if(i == 3)
                timer8->start(200);
        }
    }
#endif
    report_SW_link();
}

void tcp_socket::maintenance_link()
{
    uint16_t index = 0;
    QByteArray send_data;

    send_data[index++] = maintenance.frame_Begin >> 8;
    send_data[index++] = maintenance.frame_Begin & 0xff;
    send_data[index++] = maintenance.fun_code;
    send_data[index++] = maintenance.device_num >> 8;
    send_data[index++] = maintenance.device_num & 0xff;
    send_data[index++] = (maintenance.file_size >> 24) & 0xff;
    send_data[index++] = (maintenance.file_size >> 16) & 0xff;
    send_data[index++] = (maintenance.file_size >> 8) & 0xff;
    send_data[index++] = maintenance.file_size & 0xff;
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(&tcp_comm[4],send_data,send_data.size());
}

void tcp_socket::Factory_Config_Reset(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Store_Data_Reset";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_RESTORE_SETTING;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());

#ifdef ARM
    serial_send_disconnect();
    system("cp /home/Config_backup.ini /home/Config.ini");
    system("sync");
    system("reboot -f");
#endif
}

void tcp_socket::Store_Data_Reset(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Store_Data_Reset";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_INIT_DATA;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());

    data_result.event[0] = data_result.event[0] + 1;//历史数据初始化记录
    if(data_result.event[0] > 65530)
        data_result.event[0] = 0;

    delete_AllData_Total();
}

void tcp_socket::check_time(TCP_COMM *Tcp_comm)
{
    QString receive_time = "20" + Tcp_comm->recive_buf_comm.toHex().mid(32,12);
    QDateTime receiveDateTime;
    receiveDateTime = QDateTime::fromString(receive_time, "yyyyMMddhhmmss");
    if(receiveDateTime.secsTo(QDateTime::currentDateTime()) >= 180 || receiveDateTime.secsTo(QDateTime::currentDateTime()) <= -180)//时间误差超过3分钟
    {
        QString dateTime = "date -s \"" + receive_time.mid(0,4) + "-" + receive_time.mid(4,2) + "-" + receive_time.mid(6,2) + " " + receive_time.mid(8,2) + ":" + receive_time.mid(10,2) + ":" + receive_time.mid(12,2) + "\"";
        QString timetohw = "hwclock -w";
        QString hwtotime = "hwclock -s";
    #ifdef ARM
        system(dateTime.toLatin1());
        system(timetohw.toLatin1());
        system(hwtotime.toLatin1());
    #endif
    }
}

void tcp_socket::report_SW_link()
{
    uint16_t index = 0;
    QByteArray send_data;

    for(uint8_t i=0;i<4;i++)//维护平台不发报文
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(tcp_comm[i].reSend_flag[0])
            continue;
        if(tcp_comm[i].socket_flag == 0)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;
        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = FC_REPORT_LINK_MT;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        if(tcp_comm[i].send_num > 65500)
           tcp_comm[i].send_num = 0;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        socket_Send(&tcp_comm[i],send_data,send_data.size());
        tcp_comm[i].tcp_onLine = true;//在线标志
    }
}

void tcp_socket::report_SW_test()
{
    qDebug() << "tcp_SW_test_report";
    uint16_t index = 0;
    QByteArray send_data;
    uint32_t send_date_int = 0;

    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;

        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = FC_REPORT_TEST;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[index++] = 0xF1;//地址标识符
        send_data[index++] = 0xF1;

        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];

        send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

        send_data[index++] = 0xF0;//观测时间标识符
        send_data[index++] = 0xF0;

        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

        if((report_SW_headhex->uploadtype[2]  >> 1) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_FLOW_INST;//瞬时流量标识符
            send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_flow_inst = 0x123456;
            send_date_int = data_result.data_flow_inst * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_FLOW_TOTAL;//累计流量标识符
            send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
            send_date_int = data_result.data_flow_total;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

#ifdef FLOOD_FLOW
        send_data[index++] = 0x80;//泄洪流量标识符
        send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_flood_flow = 0x123456;
        send_date_int = data_result.data_flood_flow * 1000;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;
#endif

        if((report_SW_headhex->uploadtype[0]  >> 7) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_PRECIP_DAY;//日降雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_inst = 0x123456;
            send_date_int = data_result.data_rain_day * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_INST;//当前雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_inst = 0x123456;
            send_date_int = data_result.data_rain_inst * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_TOTAL;//累计雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_total * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_1H;//1h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_1h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_3H;//3h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_3h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_6H;//6h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_6h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_12H;//12h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_12h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_24H;//24h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_24h * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_48H;//48h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_48h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_72H;//72h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_72h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        if((report_SW_headhex->uploadtype[1]  >> 0) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_WATER_LEVEL;//水位标识符
            send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_water = 0x123456;
            send_date_int = data_result.data_water * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        if((report_SW_headhex->uploadtype[2]  >> 2) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_FLOW_SPEED;//流速标识符
            send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_flow_speed = 0x123456;
            send_date_int = data_result.data_flow_speed * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        if((report_SW_headhex->uploadtype[2]  >> 4) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_KDY;//开度值标识符
            send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_flow_speed = 0x123456;
            send_date_int = data_result.data_kdy_value;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
        send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.alarm_state_SW;
        QString str_alarm =  QString("%1").arg(send_date_int,8,16,QLatin1Char('0'));//固定字符串有8个
        QByteArray alarm;
        StringToHex(str_alarm,alarm);
        send_data[index++] = alarm[0];
        send_data[index++] = alarm[1];
        send_data[index++] = alarm[2];
        send_data[index++] = alarm[3];

        send_data[index++] = ELEMENT_IDENTI_VOL_LEVEL;//电压标识符
        send_data[index++] = 0x12;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.power_value * 100;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        if(tcp_comm[i].socket_flag == true)//连接成功才发送
        {
            socket_Send(&tcp_comm[i],send_data,send_data.size());
        }
        else
        {

        }
    }
}

void tcp_socket::report_SW_uniform_time(uint8_t fun_code,uint8_t type)
{
    uint16_t index = 0;
    QByteArray send_data;

    if(QTime::currentTime().minute() != 0)//整点报
        return;

    qDebug() << "tcp_SW_uniform_time_report";
    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(!tcp_comm[i].socket_flag)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;

        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = fun_code;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[index++] = 0xF1;//地址标识符
        send_data[index++] = 0xF1;

        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];

        send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

        send_data[index++] = 0xF0;//观测时间标识符
        send_data[index++] = 0xF0;

        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

        send_data[index++] = 0x04;//时间步长
        send_data[index++] = 0x18;//高5位表示数据字节数，低3位表示小数位数
        send_data[index++] = 0x00;
        send_data[index++] = 0x00;
        send_data[index++] = 0x05;

        QString min_0 = QDateTime::currentDateTime().addSecs(-60 * 60).toString("yyyyMMddHHmm");
        QString min_5 = QDateTime::currentDateTime().addSecs(-60 * 55).toString("yyyyMMddHHmm");
        QString min_10 = QDateTime::currentDateTime().addSecs(-60 * 50).toString("yyyyMMddHHmm");
        QString min_15 = QDateTime::currentDateTime().addSecs(-60 * 45).toString("yyyyMMddHHmm");
        QString min_20 = QDateTime::currentDateTime().addSecs(-60 * 40).toString("yyyyMMddHHmm");
        QString min_25 = QDateTime::currentDateTime().addSecs(-60 * 35).toString("yyyyMMddHHmm");
        QString min_30 = QDateTime::currentDateTime().addSecs(-60 * 30).toString("yyyyMMddHHmm");
        QString min_35 = QDateTime::currentDateTime().addSecs(-60 * 25).toString("yyyyMMddHHmm");
        QString min_40 = QDateTime::currentDateTime().addSecs(-60 * 20).toString("yyyyMMddHHmm");
        QString min_45 = QDateTime::currentDateTime().addSecs(-60 * 15).toString("yyyyMMddHHmm");
        QString min_50 = QDateTime::currentDateTime().addSecs(-60 * 10).toString("yyyyMMddHHmm");
        QString min_55 = QDateTime::currentDateTime().addSecs(-60 * 5).toString("yyyyMMddHHmm");
        QString min_60 = QDateTime::currentDateTime().toString("yyyyMMddHHmm");

        if(type == ELEMENT_IDENTI_PRECIP_5MIN)
        {
            send_data[index++] = ELEMENT_IDENTI_HOUR_RAIN; //1小时内每5分钟时段雨量
            send_data[index++] = 0x60;//高5位表示数据字节数，低3位表示小数位数

            send_data[index++] = (query_oneTable("Rain_Total",min_5).data - query_oneTable("Rain_Total",min_0).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_10).data - query_oneTable("Rain_Total",min_5).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_15).data - query_oneTable("Rain_Total",min_10).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_20).data - query_oneTable("Rain_Total",min_15).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_25).data - query_oneTable("Rain_Total",min_20).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_30).data - query_oneTable("Rain_Total",min_25).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_35).data - query_oneTable("Rain_Total",min_30).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_40).data - query_oneTable("Rain_Total",min_35).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_45).data - query_oneTable("Rain_Total",min_40).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_50).data - query_oneTable("Rain_Total",min_45).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_55).data - query_oneTable("Rain_Total",min_50).data) * 10;
            send_data[index++] = (query_oneTable("Rain_Total",min_60).data - query_oneTable("Rain_Total",min_55).data) * 10;
        }
        else
        {
            send_data[index++] = ELEMENT_IDENTI_HOUR_WATER;//1小时内每5分钟时段水位
            send_data[index++] = 0xC0;//高5位表示数据字节数，低3位表示小数位数

            uint16_t water_5min = (uint16_t)(query_oneTable("Water",min_5).data * 100);
            send_data[index++] = (water_5min >> 8 )& 0xff;
            send_data[index++] = water_5min & 0xff;
            uint16_t water_10min = (uint16_t)(query_oneTable("Water",min_10).data * 100);
            send_data[index++] = (water_10min >> 8 )& 0xff;
            send_data[index++] = water_10min & 0xff;
            uint16_t water_15min = (uint16_t)(query_oneTable("Water",min_15).data * 100);
            send_data[index++] = (water_15min >> 8 )& 0xff;
            send_data[index++] = water_15min & 0xff;
            uint16_t water_20min = (uint16_t)(query_oneTable("Water",min_20).data * 100);
            send_data[index++] = (water_20min >> 8 )& 0xff;
            send_data[index++] = water_20min & 0xff;
            uint16_t water_25min = (uint16_t)(query_oneTable("Water",min_25).data * 100);
            send_data[index++] = (water_25min >> 8 )& 0xff;
            send_data[index++] = water_25min & 0xff;
            uint16_t water_30min = (uint16_t)(query_oneTable("Water",min_30).data * 100);
            send_data[index++] = (water_30min >> 8 )& 0xff;
            send_data[index++] = water_30min & 0xff;
            uint16_t water_35min = (uint16_t)(query_oneTable("Water",min_35).data * 100);
            send_data[index++] = (water_35min >> 8 )& 0xff;
            send_data[index++] = water_35min & 0xff;
            uint16_t water_40min = (uint16_t)(query_oneTable("Water",min_40).data * 100);
            send_data[index++] = (water_40min >> 8 )& 0xff;
            send_data[index++] = water_40min & 0xff;
            uint16_t water_45min = (uint16_t)(query_oneTable("Water",min_45).data * 100);
            send_data[index++] = (water_45min >> 8 )& 0xff;
            send_data[index++] = water_45min & 0xff;
            uint16_t water_50min = (uint16_t)(query_oneTable("Water",min_50).data * 100);
            send_data[index++] = (water_50min >> 8 )& 0xff;
            send_data[index++] = water_50min & 0xff;
            uint16_t water_55min = (uint16_t)(query_oneTable("Water",min_55).data * 100);
            send_data[index++] = (water_55min >> 8 )& 0xff;
            send_data[index++] = water_55min & 0xff;
            uint16_t water_60min = (uint16_t)(query_oneTable("Water",min_60).data * 100);
            send_data[index++] = (water_60min >> 8 )& 0xff;
            send_data[index++] = water_60min & 0xff;
        }

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        socket_Send(&tcp_comm[i],send_data,send_data.size());
    }
}

void tcp_socket::report_SW_add()
{
    uint16_t index = 0;
    QByteArray send_data;
    uint32_t send_date_int = 0;

    if(report_SW_headhex->add_report_minute == 0)//加报时间为0就不报
        return;
    if(report_SW_headhex->report_send_add_time.addSecs(report_SW_headhex->add_report_minute * 60) > QTime::currentTime())
        return;

    data_result.event[12] = data_result.event[12] + 1;//水位超限记录
    qDebug() << "tcp_SW_add_report";
    report_SW_headhex->report_send_add_time = QTime::currentTime();

    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(!tcp_comm[i].socket_flag)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;

        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = FC_REPORT_ADD_REPORT;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[index++] = 0xF1;//地址标识符
        send_data[index++] = 0xF1;

        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];

        send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

        send_data[index++] = 0xF0;//观测时间标识符
        send_data[index++] = 0xF0;

        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

        send_data[index++] = ELEMENT_IDENTI_FLOW_INST;//瞬时流量标识符
        send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_flow_inst = 0x123456;
        send_date_int = data_result.data_flow_inst * 1000;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[index++] = ELEMENT_IDENTI_PRECIP_INST;//当前雨量标识符
        send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_rain_inst = 0x123456;
        send_date_int = data_result.data_rain_inst * 10;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[index++] = ELEMENT_IDENTI_WATER_LEVEL;//水位标识符
        send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_water = 0x123456;
        send_date_int = data_result.data_water * 1000;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[index++] = ELEMENT_IDENTI_FLOW_SPEED;//流速标识符
        send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_flow_speed = 0x123456;
        send_date_int = data_result.data_flow_speed * 1000;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
        send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.alarm_state_SW;
        QString str_alarm =  QString("%1").arg(send_date_int,8,16,QLatin1Char('0'));//10进制转16进制字符串 固定字符串有8个
        QByteArray alarm;
        StringToHex(str_alarm,alarm);
        send_data[index++] = alarm[0];
        send_data[index++] = alarm[1];
        send_data[index++] = alarm[2];
        send_data[index++] = alarm[3];

        send_data[index++] = ELEMENT_IDENTI_VOL_LEVEL;//电压标识符
        send_data[index++] = 0x12;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.power_value * 100;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        socket_Send(&tcp_comm[i],send_data,send_data.size());
    }
}

void tcp_socket::report_SW_hour()
{
    uint16_t index = 0;
    QByteArray send_data;
    uint32_t send_date_int = 0;

    if(QTime::currentTime().minute() != 0)//整点报
        return;

    qDebug() << "tcp_SW_hour_report";

    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(!tcp_comm[i].socket_flag)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;

        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = FC_REPORT_HOUR;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[index++] = 0xF1;//地址标识符
        send_data[index++] = 0xF1;

        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];

        send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

        send_data[index++] = 0xF0;//观测时间标识符
        send_data[index++] = 0xF0;

        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

        QString min_0 = QDateTime::currentDateTime().addSecs(-60 * 60).toString("yyyyMMddHHmm");
        QString min_5 = QDateTime::currentDateTime().addSecs(-60 * 55).toString("yyyyMMddHHmm");
        QString min_10 = QDateTime::currentDateTime().addSecs(-60 * 50).toString("yyyyMMddHHmm");
        QString min_15 = QDateTime::currentDateTime().addSecs(-60 * 45).toString("yyyyMMddHHmm");
        QString min_20 = QDateTime::currentDateTime().addSecs(-60 * 40).toString("yyyyMMddHHmm");
        QString min_25 = QDateTime::currentDateTime().addSecs(-60 * 35).toString("yyyyMMddHHmm");
        QString min_30 = QDateTime::currentDateTime().addSecs(-60 * 30).toString("yyyyMMddHHmm");
        QString min_35 = QDateTime::currentDateTime().addSecs(-60 * 25).toString("yyyyMMddHHmm");
        QString min_40 = QDateTime::currentDateTime().addSecs(-60 * 20).toString("yyyyMMddHHmm");
        QString min_45 = QDateTime::currentDateTime().addSecs(-60 * 15).toString("yyyyMMddHHmm");
        QString min_50 = QDateTime::currentDateTime().addSecs(-60 * 10).toString("yyyyMMddHHmm");
        QString min_55 = QDateTime::currentDateTime().addSecs(-60 * 5).toString("yyyyMMddHHmm");
        QString min_60 = QDateTime::currentDateTime().toString("yyyyMMddHHmm");

        send_data[index++] = ELEMENT_IDENTI_HOUR_RAIN;//1小时内每5分钟时段雨量标识符
        send_data[index++] = 0x60;//高5位表示数据字节数，低3位表示小数位数，12字节，每组雨量1个字节

        send_data[index++] = (query_oneTable("Rain_Total",min_5).data - query_oneTable("Rain_Total",min_0).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_10).data - query_oneTable("Rain_Total",min_5).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_15).data - query_oneTable("Rain_Total",min_10).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_20).data - query_oneTable("Rain_Total",min_15).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_25).data - query_oneTable("Rain_Total",min_20).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_30).data - query_oneTable("Rain_Total",min_25).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_35).data - query_oneTable("Rain_Total",min_30).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_40).data - query_oneTable("Rain_Total",min_35).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_45).data - query_oneTable("Rain_Total",min_40).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_50).data - query_oneTable("Rain_Total",min_45).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_55).data - query_oneTable("Rain_Total",min_50).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_60).data - query_oneTable("Rain_Total",min_55).data) * 10;

        send_data[index++] = ELEMENT_IDENTI_PRECIP_TOTAL;//累计雨量标识符
        send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_rain_total = 0x12345678;
        send_date_int = data_result.data_rain_total * 10;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[index++] = ELEMENT_IDENTI_HOUR_WATER;//1小时内每5分钟时段水位标识符
        send_data[index++] = 0xC0;//高5位表示数据字节数，低3位表示小数位数 24字节，每组水位2个字节

        uint16_t water_5min = (uint16_t)(query_oneTable("Water",min_5).data * 100);
        send_data[index++] = (water_5min >> 8 )& 0xff;
        send_data[index++] = water_5min & 0xff;
        uint16_t water_10min = (uint16_t)(query_oneTable("Water",min_10).data * 100);
        send_data[index++] = (water_10min >> 8 )& 0xff;
        send_data[index++] = water_10min & 0xff;
        uint16_t water_15min = (uint16_t)(query_oneTable("Water",min_15).data * 100);
        send_data[index++] = (water_15min >> 8 )& 0xff;
        send_data[index++] = water_15min & 0xff;
        uint16_t water_20min = (uint16_t)(query_oneTable("Water",min_20).data * 100);
        send_data[index++] = (water_20min >> 8 )& 0xff;
        send_data[index++] = water_20min & 0xff;
        uint16_t water_25min = (uint16_t)(query_oneTable("Water",min_25).data * 100);
        send_data[index++] = (water_25min >> 8 )& 0xff;
        send_data[index++] = water_25min & 0xff;
        uint16_t water_30min = (uint16_t)(query_oneTable("Water",min_30).data * 100);
        send_data[index++] = (water_30min >> 8 )& 0xff;
        send_data[index++] = water_30min & 0xff;
        uint16_t water_35min = (uint16_t)(query_oneTable("Water",min_35).data * 100);
        send_data[index++] = (water_35min >> 8 )& 0xff;
        send_data[index++] = water_35min & 0xff;
        uint16_t water_40min = (uint16_t)(query_oneTable("Water",min_40).data * 100);
        send_data[index++] = (water_40min >> 8 )& 0xff;
        send_data[index++] = water_40min & 0xff;
        uint16_t water_45min = (uint16_t)(query_oneTable("Water",min_45).data * 100);
        send_data[index++] = (water_45min >> 8 )& 0xff;
        send_data[index++] = water_45min & 0xff;
        uint16_t water_50min = (uint16_t)(query_oneTable("Water",min_50).data * 100);
        send_data[index++] = (water_50min >> 8 )& 0xff;
        send_data[index++] = water_50min & 0xff;
        uint16_t water_55min = (uint16_t)(query_oneTable("Water",min_55).data * 100);
        send_data[index++] = (water_55min >> 8 )& 0xff;
        send_data[index++] = water_55min & 0xff;
        uint16_t water_60min = (uint16_t)(query_oneTable("Water",min_60).data * 100);
        send_data[index++] = (water_60min >> 8 )& 0xff;
        send_data[index++] = water_60min & 0xff;

        send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
        send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.alarm_state_SW;
        QString str_alarm =  QString("%1").arg(send_date_int,8,16,QLatin1Char('0'));//固定字符串有8个
        QByteArray alarm;
        StringToHex(str_alarm,alarm);
        send_data[index++] = alarm[0];
        send_data[index++] = alarm[1];
        send_data[index++] = alarm[2];
        send_data[index++] = alarm[3];

        send_data[index++] = ELEMENT_IDENTI_VOL_LEVEL;//电压标识符
        send_data[index++] = 0x12;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.power_value * 100;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        socket_Send(&tcp_comm[i],send_data,send_data.size());
    }
}

void tcp_socket::report_SW_Manual_Work()
{
    uint32_t send_date_int = 0;
    uint16_t index = 0;
    QByteArray send_data;

    for(uint8_t i=0;i<4;i++)//维护平台不发报文
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(!tcp_comm[i].socket_flag)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;
        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = FC_REPORT_MANUAL_WORK;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[index++] = 0xF2;//人工置数标识符
        send_data[index++] = 0xF2;
        send_date_int = 0x04D2;//暂不开发，随便设个值

        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        socket_Send(&tcp_comm[i],send_data,send_data.size());
    }
}


void tcp_socket::report_SW_fixedPicture(QString dir_pic)
{
    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].socket_flag == false)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        if(tcp_comm[i].tcp_busy == true)
            continue;
        tcp_comm[i].tcp_busy = true;//传图片标志
    }

//    if(Tcp_comm->socket_flag == false)
//        return;
//    if(Tcp_comm->socket_agreement != 0)
//        return;
//    if(tcp_comm->tcp_busy == true)
//        return;
//    Tcp_comm->tcp_busy = true;

    QThread::msleep(500);
    qDebug()<<"Picture send start!";
#ifdef ARM
    //dir_pic = dir_pic;
#else
    QString path = QDir::currentPath();
    dir_pic = path + "/home/images/images1/2024-02-19-19-35-02.jpg";
#endif
    QFileInfo FileData(dir_pic);
    pic_send.pic_file_size = FileData.size();

    pic_send.send_size = 1024;//每包字节数
    pic_send.pack_total = (pic_send.pic_file_size + (pic_send.send_size - 1)) / pic_send.send_size;//总包数
    pic_send.pack_no = 0;//当前包序号
    pic_send.load_size = 0;//已发送字节数
    pic_send.pic_file = new QFile(dir_pic);

    if((!pic_send.pic_file->open(QIODevice::ReadOnly)) || (pic_send.pic_file_size == 0))//打开文件失败
    {
        qDebug()<<"open_file_error:" << dir_pic;
        QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
        DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
        singleInsertData("Alarm",DATA_BASE_Water,"Picture Error");
        return;
    }
    pic_send.socket_agreement = 0;
    timer3->start(1000);
}

void tcp_socket::report_SW_QueryRealTime_Data(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_RealTime_Data_report";
    uint32_t send_date_int = 0;


    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_REALTIME_DATA;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

    send_data[index++] = 0xF0;//观测时间标识符
    send_data[index++] = 0xF0;

    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

    send_data[index++] = ELEMENT_IDENTI_FLOW_INST;//瞬时流量标识符
    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_flow_inst = 0x123456;
    send_date_int = data_result.data_flow_inst * 1000;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_FLOW_TOTAL;//累计流量标识符
    send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
    send_date_int = data_result.data_flow_total;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_DAY;//日降雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_inst = 0x123456;
    send_date_int = data_result.data_rain_day * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_INST;//当前雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_inst = 0x123456;
    send_date_int = data_result.data_rain_inst * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_TOTAL;//累计雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_total * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_1H;//1h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_1h * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_3H;//3h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_3h * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_6H;//6h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_6h * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_12H;//12h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_12h * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_24H;//24h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_24h * 1000;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_48H;//48h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_48h * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_PRECIP_72H;//72h雨量标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_rain_total = 0x12345678;
    send_date_int = data_result.data_rain_72h * 10;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_WATER_LEVEL;//水位标识符
    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_water = 0x123456;
    send_date_int = data_result.data_water * 1000;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_FLOW_SPEED;//流速标识符
    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_flow_speed = 0x123456;
    send_date_int = data_result.data_flow_speed * 1000;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_KDY;//开度值标识符
    send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
    //data_result.data_flow_speed = 0x123456;
    send_date_int = data_result.data_kdy_value;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
    send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
    send_date_int = data_result.alarm_state_SW;
    QString str_alarm =  QString("%1").arg(send_date_int,8,16,QLatin1Char('0'));//固定字符串有8个
    QByteArray alarm;
    StringToHex(str_alarm,alarm);
    send_data[index++] = alarm[0];
    send_data[index++] = alarm[1];
    send_data[index++] = alarm[2];
    send_data[index++] = alarm[3];

    send_data[index++] = ELEMENT_IDENTI_VOL_LEVEL;//电压标识符
    send_data[index++] = 0x12;//高5位表示数据字节数，低3位表示小数位数
    send_date_int = data_result.power_value * 100;
    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_QueryUniform_Time(TCP_COMM *Tcp_comm,uint8_t type,QString time1,QString time2)
{
    uint16_t index = 0;
    QByteArray send_data;

    qDebug() << "tcp_SW_uniform_time_report";

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_PERIOD_DATA;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

    send_data[index++] = 0xF0;//观测时间标识符
    send_data[index++] = 0xF0;

    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

    send_data[index++] = 0x04;//时间步长
    send_data[index++] = 0x18;//高5位表示数据字节数，低3位表示小数位数
    send_data[index++] = 0x00;
    send_data[index++] = 0x00;
    send_data[index++] = 0x05;

    time1 = "";//备用
    QString Time= "20" + time2 + "00";//结束时间,插入年份和分钟
    QDateTime QueryDateTime;
    QueryDateTime = QDateTime::fromString(Time, "yyyyMMddhhmm");

    QString min_0 = QueryDateTime.addSecs(-60 * 60).toString("yyyyMMddHHmm");
    QString min_5 = QueryDateTime.addSecs(-60 * 55).toString("yyyyMMddHHmm");
    QString min_10 = QueryDateTime.addSecs(-60 * 50).toString("yyyyMMddHHmm");
    QString min_15 = QueryDateTime.addSecs(-60 * 45).toString("yyyyMMddHHmm");
    QString min_20 = QueryDateTime.addSecs(-60 * 40).toString("yyyyMMddHHmm");
    QString min_25 = QueryDateTime.addSecs(-60 * 35).toString("yyyyMMddHHmm");
    QString min_30 = QueryDateTime.addSecs(-60 * 30).toString("yyyyMMddHHmm");
    QString min_35 = QueryDateTime.addSecs(-60 * 25).toString("yyyyMMddHHmm");
    QString min_40 = QueryDateTime.addSecs(-60 * 20).toString("yyyyMMddHHmm");
    QString min_45 = QueryDateTime.addSecs(-60 * 15).toString("yyyyMMddHHmm");
    QString min_50 = QueryDateTime.addSecs(-60 * 10).toString("yyyyMMddHHmm");
    QString min_55 = QueryDateTime.addSecs(-60 * 5).toString("yyyyMMddHHmm");
    QString min_60 = QueryDateTime.toString("yyyyMMddHHmm");

    if(type == ELEMENT_IDENTI_PRECIP_5MIN)
    {
        send_data[index++] = ELEMENT_IDENTI_HOUR_RAIN; //1小时内每5分钟时段雨量
        send_data[index++] = 0x60;//高5位表示数据字节数，低3位表示小数位数

        send_data[index++] = (query_oneTable("Rain_Total",min_5).data - query_oneTable("Rain_Total",min_0).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_10).data - query_oneTable("Rain_Total",min_5).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_15).data - query_oneTable("Rain_Total",min_10).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_20).data - query_oneTable("Rain_Total",min_15).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_25).data - query_oneTable("Rain_Total",min_20).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_30).data - query_oneTable("Rain_Total",min_25).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_35).data - query_oneTable("Rain_Total",min_30).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_40).data - query_oneTable("Rain_Total",min_35).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_45).data - query_oneTable("Rain_Total",min_40).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_50).data - query_oneTable("Rain_Total",min_45).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_55).data - query_oneTable("Rain_Total",min_50).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_60).data - query_oneTable("Rain_Total",min_55).data) * 10;
    }
    else
    {
        send_data[index++] = ELEMENT_IDENTI_HOUR_WATER;//1小时内每5分钟时段水位
        send_data[index++] = 0xC0;//高5位表示数据字节数，低3位表示小数位数

        uint16_t water_5min = (uint16_t)(query_oneTable("Water",min_5).data * 100);
        send_data[index++] = (water_5min >> 8 )& 0xff;
        send_data[index++] = water_5min & 0xff;
        uint16_t water_10min = (uint16_t)(query_oneTable("Water",min_10).data * 100);
        send_data[index++] = (water_10min >> 8 )& 0xff;
        send_data[index++] = water_10min & 0xff;
        uint16_t water_15min = (uint16_t)(query_oneTable("Water",min_15).data * 100);
        send_data[index++] = (water_15min >> 8 )& 0xff;
        send_data[index++] = water_15min & 0xff;
        uint16_t water_20min = (uint16_t)(query_oneTable("Water",min_20).data * 100);
        send_data[index++] = (water_20min >> 8 )& 0xff;
        send_data[index++] = water_20min & 0xff;
        uint16_t water_25min = (uint16_t)(query_oneTable("Water",min_25).data * 100);
        send_data[index++] = (water_25min >> 8 )& 0xff;
        send_data[index++] = water_25min & 0xff;
        uint16_t water_30min = (uint16_t)(query_oneTable("Water",min_30).data * 100);
        send_data[index++] = (water_30min >> 8 )& 0xff;
        send_data[index++] = water_30min & 0xff;
        uint16_t water_35min = (uint16_t)(query_oneTable("Water",min_35).data * 100);
        send_data[index++] = (water_35min >> 8 )& 0xff;
        send_data[index++] = water_35min & 0xff;
        uint16_t water_40min = (uint16_t)(query_oneTable("Water",min_40).data * 100);
        send_data[index++] = (water_40min >> 8 )& 0xff;
        send_data[index++] = water_40min & 0xff;
        uint16_t water_45min = (uint16_t)(query_oneTable("Water",min_45).data * 100);
        send_data[index++] = (water_45min >> 8 )& 0xff;
        send_data[index++] = water_45min & 0xff;
        uint16_t water_50min = (uint16_t)(query_oneTable("Water",min_50).data * 100);
        send_data[index++] = (water_50min >> 8 )& 0xff;
        send_data[index++] = water_50min & 0xff;
        uint16_t water_55min = (uint16_t)(query_oneTable("Water",min_55).data * 100);
        send_data[index++] = (water_55min >> 8 )& 0xff;
        send_data[index++] = water_55min & 0xff;
        uint16_t water_60min = (uint16_t)(query_oneTable("Water",min_60).data * 100);
        send_data[index++] = (water_60min >> 8 )& 0xff;
        send_data[index++] = water_60min & 0xff;
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_QueryManual_Work(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_query_manual_work_report";
    uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_MANUAL_WORK;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF2;//人工置数标识符
    send_data[index++] = 0xF2;
    send_date_int = 0x04D2;//暂不开发，随便设个值

    send_date_int = uwordToBcd(send_date_int);
    send_data[index++] = (send_date_int >> 24 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = send_date_int & 0xff;

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_Query_Alarm(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Query_Alarm_report";
    uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_STATUS;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
    send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
    send_date_int = data_result.alarm_state_SW;
    QString str_alarm =  QString("%1").arg(send_date_int,8,16,QLatin1Char('0'));//固定字符串有8个
    QByteArray alarm;
    StringToHex(str_alarm,alarm);
    send_data[index++] = alarm[0];
    send_data[index++] = alarm[1];
    send_data[index++] = alarm[2];
    send_data[index++] = alarm[3];

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_Query_Event(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Query_Event_report";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_EVENT;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    for(uint8_t i=0;i<32;i++)
    {
        send_data[index++] = (data_result.event[i] >> 8) & 0xFF;
        send_data[index++] = data_result.event[i] & 0xFF;
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_Query_APPOINT_ELEMENT(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Query_Appoint_Element_report";
    uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_APPOINT_ELEMENT;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

    send_data[index++] = 0xF0;//观测时间标识符
    send_data[index++] = 0xF0;

    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

    if((unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 5) == 0xF5 ||
       (unsigned char)Tcp_comm->recive_buf_comm.at(Tcp_comm->recive_buf_comm.size() - 5) == 0xF4)//时段型数据
    {
        QString Time= QDateTime::currentDateTime().toString("yyyyMMddhh") + "00";//结束时间,分钟
        QDateTime QueryDateTime;
        QueryDateTime = QDateTime::fromString(Time, "yyyyMMddhhmm");

        QString min_0 = QueryDateTime.addSecs(-60 * 60).toString("yyyyMMddHHmm");
        QString min_5 = QueryDateTime.addSecs(-60 * 55).toString("yyyyMMddHHmm");
        QString min_10 = QueryDateTime.addSecs(-60 * 50).toString("yyyyMMddHHmm");
        QString min_15 = QueryDateTime.addSecs(-60 * 45).toString("yyyyMMddHHmm");
        QString min_20 = QueryDateTime.addSecs(-60 * 40).toString("yyyyMMddHHmm");
        QString min_25 = QueryDateTime.addSecs(-60 * 35).toString("yyyyMMddHHmm");
        QString min_30 = QueryDateTime.addSecs(-60 * 30).toString("yyyyMMddHHmm");
        QString min_35 = QueryDateTime.addSecs(-60 * 25).toString("yyyyMMddHHmm");
        QString min_40 = QueryDateTime.addSecs(-60 * 20).toString("yyyyMMddHHmm");
        QString min_45 = QueryDateTime.addSecs(-60 * 15).toString("yyyyMMddHHmm");
        QString min_50 = QueryDateTime.addSecs(-60 * 10).toString("yyyyMMddHHmm");
        QString min_55 = QueryDateTime.addSecs(-60 * 5).toString("yyyyMMddHHmm");
        QString min_60 = QueryDateTime.toString("yyyyMMddHHmm");

        send_data[index++] = ELEMENT_IDENTI_HOUR_RAIN; //1小时内每5分钟时段雨量
        send_data[index++] = 0x60;//高5位表示数据字节数，低3位表示小数位数

        send_data[index++] = (query_oneTable("Rain_Total",min_5).data - query_oneTable("Rain_Total",min_0).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_10).data - query_oneTable("Rain_Total",min_5).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_15).data - query_oneTable("Rain_Total",min_10).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_20).data - query_oneTable("Rain_Total",min_15).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_25).data - query_oneTable("Rain_Total",min_20).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_30).data - query_oneTable("Rain_Total",min_25).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_35).data - query_oneTable("Rain_Total",min_30).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_40).data - query_oneTable("Rain_Total",min_35).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_45).data - query_oneTable("Rain_Total",min_40).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_50).data - query_oneTable("Rain_Total",min_45).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_55).data - query_oneTable("Rain_Total",min_50).data) * 10;
        send_data[index++] = (query_oneTable("Rain_Total",min_60).data - query_oneTable("Rain_Total",min_55).data) * 10;

        send_data[index++] = ELEMENT_IDENTI_HOUR_WATER;//1小时内每5分钟时段水位
        send_data[index++] = 0xC0;//高5位表示数据字节数，低3位表示小数位数

        uint16_t water_5min = (uint16_t)(query_oneTable("Water",min_5).data * 100);
        send_data[index++] = (water_5min >> 8 )& 0xff;
        send_data[index++] = water_5min & 0xff;
        uint16_t water_10min = (uint16_t)(query_oneTable("Water",min_10).data * 100);
        send_data[index++] = (water_10min >> 8 )& 0xff;
        send_data[index++] = water_10min & 0xff;
        uint16_t water_15min = (uint16_t)(query_oneTable("Water",min_15).data * 100);
        send_data[index++] = (water_15min >> 8 )& 0xff;
        send_data[index++] = water_15min & 0xff;
        uint16_t water_20min = (uint16_t)(query_oneTable("Water",min_20).data * 100);
        send_data[index++] = (water_20min >> 8 )& 0xff;
        send_data[index++] = water_20min & 0xff;
        uint16_t water_25min = (uint16_t)(query_oneTable("Water",min_25).data * 100);
        send_data[index++] = (water_25min >> 8 )& 0xff;
        send_data[index++] = water_25min & 0xff;
        uint16_t water_30min = (uint16_t)(query_oneTable("Water",min_30).data * 100);
        send_data[index++] = (water_30min >> 8 )& 0xff;
        send_data[index++] = water_30min & 0xff;
        uint16_t water_35min = (uint16_t)(query_oneTable("Water",min_35).data * 100);
        send_data[index++] = (water_35min >> 8 )& 0xff;
        send_data[index++] = water_35min & 0xff;
        uint16_t water_40min = (uint16_t)(query_oneTable("Water",min_40).data * 100);
        send_data[index++] = (water_40min >> 8 )& 0xff;
        send_data[index++] = water_40min & 0xff;
        uint16_t water_45min = (uint16_t)(query_oneTable("Water",min_45).data * 100);
        send_data[index++] = (water_45min >> 8 )& 0xff;
        send_data[index++] = water_45min & 0xff;
        uint16_t water_50min = (uint16_t)(query_oneTable("Water",min_50).data * 100);
        send_data[index++] = (water_50min >> 8 )& 0xff;
        send_data[index++] = water_50min & 0xff;
        uint16_t water_55min = (uint16_t)(query_oneTable("Water",min_55).data * 100);
        send_data[index++] = (water_55min >> 8 )& 0xff;
        send_data[index++] = water_55min & 0xff;
        uint16_t water_60min = (uint16_t)(query_oneTable("Water",min_60).data * 100);
        send_data[index++] = (water_60min >> 8 )& 0xff;
        send_data[index++] = water_60min & 0xff;
    }
    else//实时类数据
    {
        uint8_t Query_count = (Tcp_comm->recive_buf_comm.size() - 25) / 2;//查询标识符个数
        for(uint8_t i=0;i<Query_count;i++)
        {
            switch((unsigned char)Tcp_comm->recive_buf_comm.at(22 + 2 * i))
            {
                case ELEMENT_IDENTI_FLOW_INST://瞬时流量标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_FLOW_INST;//瞬时流量标识符
                    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
                    send_date_int = data_result.data_flow_inst * 1000;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_FLOW_TOTAL://累计流量标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_FLOW_TOTAL;//累计流量标识符
                    send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
                    send_date_int = data_result.data_flow_total;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_PRECIP_DAY://日降雨量标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_PRECIP_DAY;//日降雨量标识符
                    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
                    //data_result.data_rain_inst = 0x123456;
                    send_date_int = data_result.data_rain_day * 10;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_PRECIP_INST://当前雨量标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_PRECIP_INST;//当前雨量标识符
                    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
                    //data_result.data_rain_inst = 0x123456;
                    send_date_int = data_result.data_rain_inst * 10;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_PRECIP_TOTAL://累计雨量标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_PRECIP_TOTAL;//累计雨量标识符
                    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
                    //data_result.data_rain_total = 0x12345678;
                    send_date_int = data_result.data_rain_total * 10;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_WATER_LEVEL://水位标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_WATER_LEVEL;//水位标识符
                    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
                    //data_result.data_water = 0x123456;
                    send_date_int = data_result.data_water * 1000;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_WATER_LEVEL_HEDAO://瞬时河道水位标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_WATER_LEVEL_HEDAO;//水位标识符
                    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
                    //data_result.data_water = 0x123456;
                    send_date_int = data_result.data_water * 1000;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_FLOW_SPEED://流速标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_FLOW_SPEED;//流速标识符
                    send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
                    //data_result.data_flow_speed = 0x123456;
                    send_date_int = data_result.data_flow_speed * 1000;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 24 )& 0xff;
                    send_data[index++] = (send_date_int >> 16 )& 0xff;
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                case ELEMENT_IDENTI_VOL_LEVEL://电压标识符
                {
                    send_data[index++] = ELEMENT_IDENTI_VOL_LEVEL;//电压标识符
                    send_data[index++] = 0x12;//高5位表示数据字节数，低3位表示小数位数
                    send_date_int = data_result.power_value * 100;
                    send_date_int = uwordToBcd(send_date_int);
                    send_data[index++] = (send_date_int >> 8 )& 0xff;
                    send_data[index++] = send_date_int & 0xff;
                    break;
                }
                default:
                    break;
            }
        }
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_Set_Clock(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Set_Clock_report";
    //uint32_t send_date_int = 0;

    uint8_t year = BCDtobyte(Tcp_comm->recive_buf_comm.at(16));
    uint8_t mon = BCDtobyte(Tcp_comm->recive_buf_comm.at(17));
    uint8_t day = BCDtobyte(Tcp_comm->recive_buf_comm.at(18));
    uint8_t hour = BCDtobyte(Tcp_comm->recive_buf_comm.at(19));
    uint8_t min = BCDtobyte(Tcp_comm->recive_buf_comm.at(20));
    uint8_t sec = BCDtobyte(Tcp_comm->recive_buf_comm.at(21));

    QString dateTime = "date -s \"" +  QString::number(year + 2000) + "-" + QString::number(mon) + "-" + QString::number(day) + " " + QString::number(hour) + ":" + QString::number(min) + ":" + QString::number(sec) + "\"";
    QString timetohw = "hwclock -w";
    QString hwtotime = "hwclock -s";
#ifdef ARM
    system(dateTime.toLatin1());
    system(timetohw.toLatin1());
    system(hwtotime.toLatin1());
#endif

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_SET_CLOCK;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

//去除字符串前面的0
static QString removefirst0(QString s)
{
    if(!s.left(1).operator ==("0"))
        return s;
    else
        return removefirst0(s.right(s.length()-1));
}

void tcp_socket::report_SW_Modify_Basic_Set(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Modify_Basic_Set_report";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_MODIFY_BASIC_SET;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    //配置解析
    bool ok;
    uint8_t count = 0;
    uint8_t cmd = 0;//参数配置标识符
    uint8_t byteN = 0;//字节数
    //uint8_t decimalN = 0;//小数位数
    while(count < (Tcp_comm->recive_buf_comm.size() - 25))
    {
        cmd = Tcp_comm->recive_buf_comm.at(22 + count);
        byteN = (Tcp_comm->recive_buf_comm.at(22 + count + 1) & 0xF8) >> 3;//高5位 字节数
        //decimalN = Tcp_comm->recive_buf_comm.at(22 + count + 1) & 0x07;//低3位 小数位数
        switch(cmd)
        {
            case 0x01://中心站地址
            {
                report_SW_headhex->station_centerAddr = Tcp_comm->recive_buf_comm.toHex().mid(48,2).toUInt(&ok,16);//16进制字符串转10进制
                MainWindow::iniFile->setValue("/SW_PROTOCOL/Central_addr",report_SW_headhex->station_centerAddr);

                send_data[index++] = 0x01;//基本配置标识符
                send_data[index++] = 0x20;//高5位 字节数 低3位 小数位数
                send_data[index++] = report_SW_headhex->station_centerAddr;
                send_data[index++] = 0x00;
                send_data[index++] = 0x00;
                send_data[index++] = 0x00;
                break;
            }
            case 0x02://遥测站地址
            {
                QString ycAddr = Tcp_comm->recive_buf_comm.toHex().mid(60,10);
                MainWindow::iniFile->setValue("/SW_PROTOCOL/Station_addr",ycAddr);

                QByteArray station_addr = 0;
                QString str_station_addr = MainWindow::iniFile->value("/SW_PROTOCOL/Station_addr").toString();
                StringToHex(str_station_addr,station_addr);
                report_SW_headhex->station_ycAddr[0] = station_addr[0];
                report_SW_headhex->station_ycAddr[1] = station_addr[1];
                report_SW_headhex->station_ycAddr[2] = station_addr[2];
                report_SW_headhex->station_ycAddr[3] = station_addr[3];
                report_SW_headhex->station_ycAddr[4] = station_addr[4];

                send_data[index++] = 0x02;//基本配置标识符
                send_data[index++] = 0x28;//高5位 字节数 低3位 小数位数
                send_data[index++] = report_SW_headhex->station_ycAddr[0];
                send_data[index++] = report_SW_headhex->station_ycAddr[1];
                send_data[index++] = report_SW_headhex->station_ycAddr[2];
                send_data[index++] = report_SW_headhex->station_ycAddr[3];
                send_data[index++] = report_SW_headhex->station_ycAddr[4];
                break;
            }
            case 0x03://密码
            {
                break;
            }
            case 0x04://中心站 1 主信道类型及地址
            {
                QString IP1_1 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(76,3));
                QString IP1_2 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(79,3));
                QString IP1_3 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(82,3));
                QString IP1_4 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(85,3));
                QString IP1 = IP1_1 + "." + IP1_2 + "." + IP1_3 + "." + IP1_4;
                tcp_comm[0].ip = IP1;
                MainWindow::iniFile->setValue("/Server/IP1",IP1);
                QString Port1 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(88,6));
                tcp_comm[0].port = Port1.toUInt();
                MainWindow::iniFile->setValue("/Server/PORT1",Port1);

                send_data[index++] = 0x04;//基本配置标识符
                send_data[index++] = 0x50;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(76,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(78,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(80,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(82,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(84,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(86,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(88,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(90,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(92,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(94,2).toUInt(&ok,16));
                break;
            }
            case 0x05://中心站 1 备用信道类型及地址
            {
                QString IP2_1 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(100,3));
                QString IP2_2 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(103,3));
                QString IP2_3 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(106,3));
                QString IP2_4 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(109,3));
                QString IP2 = IP2_1 + "." + IP2_2 + "." + IP2_3 + "." + IP2_4;
                tcp_comm[1].ip = IP2;
                MainWindow::iniFile->setValue("/Server/IP2",IP2);
                QString Port2 = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(112,6));
                tcp_comm[1].port = Port2.toUInt();
                MainWindow::iniFile->setValue("/Server/PORT2",Port2);

                send_data[index++] = 0x05;//基本配置标识符
                send_data[index++] = 0x50;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(76,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(78,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(80,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(82,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(84,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(86,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(88,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(90,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(92,2).toUInt(&ok,16));
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(94,2).toUInt(&ok,16));
                break;
            }
            case 0x06://中心站 2 主信道类型及地址
            {
                break;
            }
            case 0x07://中心站 2 备用信道类型及地址
            {
                break;
            }
            case 0x08://3
            {
                break;
            }
            case 0x09://3
            {
                break;
            }
            case 0x0A://4
            {
                break;
            }
            case 0x0B://4
            {
                break;
            }
            case 0x0C://工作方式
            {
                work_mode = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(122,2)).toUInt(&ok,16);

                send_data[index++] = 0x0C;//基本配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = work_mode;
                break;
            }
            case 0x0D://遥测站采集要素设置
            {
                report_SW_headhex->uploadtype[0] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(128,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[1] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(130,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[2] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(132,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[3] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(134,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[4] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(136,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[5] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(138,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[6] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(140,2)).toUInt(&ok,16);
                report_SW_headhex->uploadtype[7] = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(142,2)).toUInt(&ok,16);

                QString str_uploadtype0 = QString::number(report_SW_headhex->uploadtype[0],16);
                if(str_uploadtype0.length() < 2)
                    str_uploadtype0 = str_uploadtype0.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype1 = QString::number(report_SW_headhex->uploadtype[1],16);
                if(str_uploadtype1.length() < 2)
                    str_uploadtype1 = str_uploadtype1.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype2 = QString::number(report_SW_headhex->uploadtype[2],16);
                if(str_uploadtype2.length() < 2)
                    str_uploadtype2 = str_uploadtype2.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype3 = QString::number(report_SW_headhex->uploadtype[3],16);
                if(str_uploadtype3.length() < 2)
                    str_uploadtype3 = str_uploadtype3.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype4 = QString::number(report_SW_headhex->uploadtype[4],16);
                if(str_uploadtype4.length() < 2)
                    str_uploadtype4 = str_uploadtype4.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype5 = QString::number(report_SW_headhex->uploadtype[5],16);
                if(str_uploadtype5.length() < 2)
                    str_uploadtype5 = str_uploadtype5.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype6 = QString::number(report_SW_headhex->uploadtype[6],16);
                if(str_uploadtype6.length() < 2)
                    str_uploadtype6 = str_uploadtype6.rightJustified(2, '0');//字符串前面补0
                QString str_uploadtype7 = QString::number(report_SW_headhex->uploadtype[7],16);
                if(str_uploadtype7.length() < 2)
                    str_uploadtype7 = str_uploadtype7.rightJustified(2, '0');//字符串前面补0

                MainWindow::iniFile->setValue("/SW_PROTOCOL/Element",str_uploadtype0 + str_uploadtype1 + str_uploadtype2 + str_uploadtype3 +
                                              str_uploadtype4 + str_uploadtype5 + str_uploadtype6 + str_uploadtype7);

                send_data[index++] = 0x0D;//基本配置标识符
                send_data[index++] = 0x40;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(128,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(130,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(132,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(134,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(136,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(138,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(140,2).toUInt());
                send_data[index++] = byteToBcd(Tcp_comm->recive_buf_comm.toHex().mid(142,2).toUInt());
                break;
            }
            case 0x0E://中继站服务地址范围
            {
                break;
            }
            case 0x0F://遥测站通信设备识别号
            {
                //QString card_id = removefirst0(Tcp_comm->recive_buf_comm.toHex().mid(150,22));
                break;
            }
            default:
                break;
        }
        count = count + byteN + 2;
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
    emit uploadBaseSet(1);//更新ui配置
    socket_init();
    data_result.event[1] = data_result.event[1] + 1;//参数变更记录
    if(data_result.event[1] > 65530)
        data_result.event[1] = 0;
}

//IP地址转成4字节char
static void get_ip_array_form_QString(QString in,unsigned char *out)
{
    uint8_t next_ip_separate_symbol_index = 0;
    uint8_t now_ip_separate_symbol_index = 0;

    for(uint8_t i=0;i<4;i++){
        next_ip_separate_symbol_index = (i!=3)? (in.indexOf(".",next_ip_separate_symbol_index+1)):(in.length());
        if((next_ip_separate_symbol_index-now_ip_separate_symbol_index>0)&&(next_ip_separate_symbol_index-now_ip_separate_symbol_index<= 4)){
            *(out+i) = in.mid((i==0)? now_ip_separate_symbol_index:(now_ip_separate_symbol_index+1), \
                 (i==0)? next_ip_separate_symbol_index: \
                 (next_ip_separate_symbol_index-now_ip_separate_symbol_index-1)).toInt(0,10);
            now_ip_separate_symbol_index = next_ip_separate_symbol_index;
        }else{
            return;
        }
    }
}

void tcp_socket::report_SW_Query_Basic_Set(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Modify_Read_Set_report";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_REPORT_READ_BASIC_SET;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    //配置解析
    uint8_t count = 0;
    uint8_t cmd = 0;//参数配置标识符
    while(count < (Tcp_comm->recive_buf_comm.size() - 25))
    {
        cmd = Tcp_comm->recive_buf_comm.at(22 + count);
        switch(cmd)
        {
            case 0x01://中心站地址
            {
                send_data[index++] = 0x01;//基本配置标识符
                send_data[index++] = 0x20;//高5位 字节数 低3位 小数位数
                send_data[index++] = report_SW_headhex->station_centerAddr;
                send_data[index++] = 0x00;
                send_data[index++] = 0x00;
                send_data[index++] = 0x00;
                break;
            }
            case 0x02://遥测站地址
            {
                send_data[index++] = 0x02;//基本配置标识符
                send_data[index++] = 0x28;//高5位 字节数 低3位 小数位数
                send_data[index++] = report_SW_headhex->station_ycAddr[0];
                send_data[index++] = report_SW_headhex->station_ycAddr[1];
                send_data[index++] = report_SW_headhex->station_ycAddr[2];
                send_data[index++] = report_SW_headhex->station_ycAddr[3];
                send_data[index++] = report_SW_headhex->station_ycAddr[4];
                break;
            }
            case 0x03://密码
            {
                break;
            }
            case 0x04://中心站 1 主信道类型及地址
            {
                send_data[index++] = 0x04;//基本配置标识符
                send_data[index++] = 0x50;//高5位 字节数 低3位 小数位数
                send_data[index++] = 0x02;//IPV4
                unsigned char char_ip1[4] = {0,0,0,0};//192 168 110 112
                get_ip_array_form_QString(tcp_comm[0].ip,char_ip1);
                send_data[index++] = byteToBcd((char_ip1[0] / 10) & 0xff);
                send_data[index++] = byteToBcd((char_ip1[0] % 10 * 10 + char_ip1[1] / 100) & 0xff);
                send_data[index++] = byteToBcd((char_ip1[1] % 100) & 0xff);
                send_data[index++] = byteToBcd((char_ip1[2] / 10) & 0xff);
                send_data[index++] = byteToBcd((char_ip1[2] % 10 * 10 + char_ip1[3] / 100) & 0xff);
                send_data[index++] = byteToBcd((char_ip1[3] % 100) & 0xff);
                send_data[index++] = (wordTo3Bcd(tcp_comm[0].port) >> 16) & 0xff;
                send_data[index++] = (wordTo3Bcd(tcp_comm[0].port) >> 8) & 0xff;
                send_data[index++] = wordTo3Bcd(tcp_comm[0].port) & 0xff;
                break;
            }
            case 0x05://中心站 1 备用信道类型及地址
            {
                send_data[index++] = 0x05;//基本配置标识符
                send_data[index++] = 0x50;//高5位 字节数 低3位 小数位数
                send_data[index++] = 0x02;//IPV4
                unsigned char char_ip2[4] = {0,0,0,0};//192 168 110 112
                get_ip_array_form_QString(tcp_comm[1].ip,char_ip2);
                send_data[index++] = byteToBcd((char_ip2[0] / 10) & 0xff);
                send_data[index++] = byteToBcd((char_ip2[0] % 10 * 10 + char_ip2[1] / 100) & 0xff);
                send_data[index++] = byteToBcd((char_ip2[1] % 100) & 0xff);
                send_data[index++] = byteToBcd((char_ip2[2] / 10) & 0xff);
                send_data[index++] = byteToBcd((char_ip2[2] % 10 * 10 + char_ip2[3] / 100) & 0xff);
                send_data[index++] = byteToBcd((char_ip2[3] % 100) & 0xff);
                send_data[index++] = (wordTo3Bcd(tcp_comm[1].port) >> 16) & 0xff;
                send_data[index++] = (wordTo3Bcd(tcp_comm[1].port) >> 8) & 0xff;
                send_data[index++] = wordTo3Bcd(tcp_comm[1].port) & 0xff;
                break;
            }
            case 0x06://中心站 2 主信道类型及地址
            {
                break;
            }
            case 0x07://中心站 2 备用信道类型及地址
            {
                break;
            }
            case 0x08://3
            {
                break;
            }
            case 0x09://3
            {
                break;
            }
            case 0x0A://4
            {
                break;
            }
            case 0x0B://4
            {
                break;
            }
            case 0x0C://工作方式
            {
                send_data[index++] = 0x0C;//基本配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = work_mode;
                break;
            }
            case 0x0D://遥测站采集要素设置
            {
                send_data[index++] = 0x0D;//基本配置标识符
                send_data[index++] = 0x40;//高5位 字节数 低3位 小数位数
                send_data[index++] = report_SW_headhex->uploadtype[0];
                send_data[index++] = report_SW_headhex->uploadtype[1];
                send_data[index++] = report_SW_headhex->uploadtype[2];
                send_data[index++] = report_SW_headhex->uploadtype[3];
                send_data[index++] = report_SW_headhex->uploadtype[4];
                send_data[index++] = report_SW_headhex->uploadtype[5];
                send_data[index++] = report_SW_headhex->uploadtype[6];
                send_data[index++] = report_SW_headhex->uploadtype[7];
                break;
            }
            case 0x0E://中继站服务地址范围
            {
                break;
            }
            case 0x0F://遥测站通信设备识别号
            {
                send_data[index++] = 0x0F;
                send_data[index++] = 0x68;
                send_data[index++] = 0x01;//移动卡
                send_data[index++] = 0x00;//移动卡
                QByteArray array = SIM_CCID.toLatin1();
                for (int i = 0; i < array.size(); ++i)
                {
                    send_data[index++] = (int)array.at(i);
                }
                break;
            }
            default:
                break;
        }
        count = count + 2;
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_Modify_Run_Set(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Modify_Run_Set_report";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_MODIFY_RUNNING_SET;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    //配置解析
    bool ok;
    uint8_t count = 0;
    uint8_t cmd = 0;//参数配置标识符
    uint8_t byteN = 0;//字节数
    //uint8_t decimalN = 0;//小数位数
    while(count < (Tcp_comm->recive_buf_comm.size() - 25))
    {
        cmd = Tcp_comm->recive_buf_comm.at(22 + count);
        byteN = (Tcp_comm->recive_buf_comm.at(22 + count + 1) & 0xF8) >> 3;//高5位 字节数
        //decimalN = Tcp_comm->recive_buf_comm.at(22 + count + 1) & 0x07;//低3位 小数位数
        switch(cmd)
        {
            case 0x20://定时报时间间隔
            {
                report_SW_headhex->fixed_report_minute = BCDtobyte(Tcp_comm->recive_buf_comm.toHex().mid(48,2).toUInt(&ok,16));//16进制字符串转10进制
                MainWindow::iniFile->setValue("/SW_PROTOCOL/Fixed_time",report_SW_headhex->fixed_report_minute);

                send_data[index++] = 0x20;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(report_SW_headhex->fixed_report_minute);
                break;
            }
            case 0x21://加报报时间间隔
            {
                report_SW_headhex->add_report_minute = BCDtobyte(Tcp_comm->recive_buf_comm.toHex().mid(54,2).toUInt(&ok,16));//16进制字符串转10进制
                MainWindow::iniFile->setValue("/SW_PROTOCOL/Add_time",report_SW_headhex->add_report_minute);

                send_data[index++] = 0x21;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(report_SW_headhex->add_report_minute);
                break;
            }
            case 0x22://降雨量日起始时间
            {
                send_data[index++] = 0x22;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(8);//每天8点不变
                break;
            }
            case 0x23://采样间隔
            {
                send_data[index++] = 0x23;//运行配置标识符
                send_data[index++] = 0x10;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(0);//1秒钟采用间隔不变
                send_data[index++] = byteToBcd(1);//1秒钟采用间隔不变
                break;
            }
            case 0x24://水位数据存储时间间隔
            {
                send_data[index++] = 0x24;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(5);//5分钟数据存储时间间隔不变
                break;
            }
            case 0x25://雨量计分辨力
            {
                Rain_ratio = (float)BCDtobyte(Tcp_comm->recive_buf_comm.toHex().mid(80,2).toUInt(&ok,16)) / 10;//16进制字符串转10进制
                MainWindow::iniFile->setValue("/RAIN/Ratio1",QString::number(Rain_ratio,'f',2));

                send_data[index++] = 0x25;//运行配置标识符
                send_data[index++] = 0x09;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd((uint8_t)(Rain_ratio * 10));
                break;
            }
            case 0x26://水位计分辨力
            {
                send_data[index++] = 0x26;//运行配置标识符
                send_data[index++] = 0x09;//高5位 字节数 低3位 小数位数
                send_data[index++] = 1;//水位计分辨力为1不变
                break;
            }
            case 0x27://雨量加报阈值
            {
                data_result.data_rain_upper_limit_value = BCDtobyte(Tcp_comm->recive_buf_comm.toHex().mid(92,2).toUInt(&ok,16));//16进制字符串转10进制
                MainWindow::iniFile->setValue("/ALARM/Rain_upLimit",data_result.data_rain_upper_limit_value);
                send_data[index++] = 0x27;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd((uint8_t)data_result.data_rain_upper_limit_value);
                break;
            }
            case 0x28://水位基值
            {
                data_result.data_water_base_value = (double)Tcp_comm->recive_buf_comm.toHex().mid(98,8).toUInt(&ok,10) / 1000;
                MainWindow::iniFile->setValue("/ALARM/Water_base",data_result.data_water_base_value);
                send_data[index++] = 0x28;//运行配置标识符
                send_data[index++] = 0x23;//高5位 字节数 低3位 小数位数

                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000)) >> 24;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000)) >> 16;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000));
                break;
            }
            case 0x30://水位修正值
            {
                data_result.data_water_modify_value = (double)Tcp_comm->recive_buf_comm.toHex().mid(110,6).toUInt(&ok,10) / 1000;
                MainWindow::iniFile->setValue("/ALARM/Water_modify",data_result.data_water_modify_value);
                send_data[index++] = 0x30;//运行配置标识符
                send_data[index++] = 0x1B;//高5位 字节数 低3位 小数位数
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_modify_value * 1000)) >> 16;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_modify_value * 1000)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_modify_value * 1000));
                break;
            }
            case 0x38://加报水位
            {
//                data_result.data_water_modify_value = Tcp_comm->recive_buf_comm.toHex().mid(110,6).toDouble();
//                MainWindow::iniFile->setValue("/ALARM/Water_modify",data_result.data_water_modify_value);
                send_data[index++] = 0x38;//运行配置标识符
                send_data[index++] = 0x12;//高5位 字节数 低3位 小数位数
                send_data[index++] = 0x00;
                send_data[index++] = 0x00;
//                send_data[index++] = byteToBcd((uint8_t)(((uint32_t)(data_result.data_water_modify_value * 1000)) >> 16));
//                send_data[index++] = byteToBcd((uint8_t)(((uint32_t)(data_result.data_water_modify_value * 1000)) >> 8));
//                send_data[index++] = byteToBcd((uint8_t)((uint32_t)(data_result.data_water_modify_value * 1000)));
                break;
            }
            case 0x40://加报水位以上加报阈值
            {
                data_result.data_water_upper_limit_value = (double)Tcp_comm->recive_buf_comm.toHex().mid(128,4).toUInt(&ok,10) / 100;
                MainWindow::iniFile->setValue("/ALARM/Water_upLimit",data_result.data_water_upper_limit_value);
                send_data[index++] = 0x40;//运行配置标识符
                send_data[index++] = 0x12;//高5位 字节数 低3位 小数位数
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_upper_limit_value * 100)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_upper_limit_value * 100));
                break;
            }
            case 0x41://加报水位以下加报阈值
            {
                data_result.data_water_lower_limit_value = (double)Tcp_comm->recive_buf_comm.toHex().mid(136,4).toUInt(&ok,10) / 100;
                MainWindow::iniFile->setValue("/ALARM/Water_downLimit",data_result.data_water_lower_limit_value);
                send_data[index++] = 0x41;//运行配置标识符
                send_data[index++] = 0x12;//高5位 字节数 低3位 小数位数
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_lower_limit_value * 100)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_lower_limit_value * 100));
                break;
            }

            default:
                break;
        }
        count = count + byteN + 2;
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
    emit uploadRunSet(1);//更新ui配置
    data_result.event[1] = data_result.event[1] + 1;//参数变更记录
    if(data_result.event[1] > 65530)
        data_result.event[1] = 0;
}

void tcp_socket::report_SW_Query_Run_Set(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_Read_Run_Set_report";
    //uint32_t send_date_int = 0;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_REPORT_READ_RUNNING_SET;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    //配置解析
    uint8_t count = 0;
    uint8_t cmd = 0;//参数配置标识符
    while(count < (Tcp_comm->recive_buf_comm.size() - 25))
    {
        cmd = Tcp_comm->recive_buf_comm.at(22 + count);
        switch(cmd)
        {
            case 0x20://定时报时间间隔
            {
                send_data[index++] = 0x20;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(report_SW_headhex->fixed_report_minute);
                break;
            }
            case 0x21://加报报时间间隔
            {
                send_data[index++] = 0x21;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(report_SW_headhex->add_report_minute);
                break;
            }
            case 0x22://降雨量日起始时间
            {
                send_data[index++] = 0x22;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(8);//每天8点不变
                break;
            }
            case 0x23://采样间隔
            {
                send_data[index++] = 0x23;//运行配置标识符
                send_data[index++] = 0x10;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(0);//1秒钟采用间隔不变
                send_data[index++] = byteToBcd(1);//1秒钟采用间隔不变
                break;
            }
            case 0x24://水位数据存储时间间隔
            {
                send_data[index++] = 0x24;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd(5);//5分钟数据存储时间间隔不变
                break;
            }
            case 0x25://雨量计分辨力
            {
                send_data[index++] = 0x25;//运行配置标识符
                send_data[index++] = 0x09;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd((uint8_t)(Rain_ratio * 10));
                break;
            }
            case 0x26://水位计分辨力
            {
                send_data[index++] = 0x26;//运行配置标识符
                send_data[index++] = 0x09;//高5位 字节数 低3位 小数位数
                send_data[index++] = 1;//水位计分辨力为1不变
                break;
            }
            case 0x27://雨量加报阈值
            {
                send_data[index++] = 0x27;//运行配置标识符
                send_data[index++] = 0x08;//高5位 字节数 低3位 小数位数
                send_data[index++] = byteToBcd((uint8_t)data_result.data_rain_upper_limit_value);
                break;
            }
            case 0x28://水位基值
            {
                send_data[index++] = 0x28;//运行配置标识符
                send_data[index++] = 0x23;//高5位 字节数 低3位 小数位数

                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000)) >> 24;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000)) >> 16;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_base_value * 1000));
                break;
            }
            case 0x30://水位修正值
            {
                send_data[index++] = 0x30;//运行配置标识符
                send_data[index++] = 0x1B;//高5位 字节数 低3位 小数位数
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_modify_value * 1000)) >> 16;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_modify_value * 1000)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_modify_value * 1000));
                break;
            }
            case 0x38://加报水位
            {
//                data_result.data_water_modify_value = Tcp_comm->recive_buf_comm.toHex().mid(110,6).toDouble();
//                MainWindow::iniFile->setValue("/ALARM/Water_modify",data_result.data_water_modify_value);
                send_data[index++] = 0x38;//运行配置标识符
                send_data[index++] = 0x12;//高5位 字节数 低3位 小数位数
                send_data[index++] = 0x00;
                send_data[index++] = 0x00;
//                send_data[index++] = byteToBcd((uint8_t)(((uint32_t)(data_result.data_water_modify_value * 1000)) >> 16));
//                send_data[index++] = byteToBcd((uint8_t)(((uint32_t)(data_result.data_water_modify_value * 1000)) >> 8));
//                send_data[index++] = byteToBcd((uint8_t)((uint32_t)(data_result.data_water_modify_value * 1000)));
                break;
            }
            case 0x40://加报水位以上加报阈值
            {
                send_data[index++] = 0x40;//运行配置标识符
                send_data[index++] = 0x12;//高5位 字节数 低3位 小数位数
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_upper_limit_value * 100)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_upper_limit_value * 100));
                break;
            }
            case 0x41://加报水位以下加报阈值
            {
                send_data[index++] = 0x41;//运行配置标识符
                send_data[index++] = 0x12;//高5位 字节数 低3位 小数位数
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_lower_limit_value * 100)) >> 8;
                send_data[index++] = uwordToBcd((uint32_t)(data_result.data_water_lower_limit_value * 100));
                break;
            }

            default:
                break;
        }
        count = count + 2;
    }

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_fixed_time(uint8_t socket_agreement)
{
    if(socket_agreement == 0)//水文
    {
        report_SW_headhex->report_fixed_count++;

        if(report_SW_headhex->report_fixed_count == 1)
        {
            report_SW_fixed_time(FC_REPORT_ON_TIME);//水文协议 定时报
        }
        else if(report_SW_headhex->report_fixed_count == 2)
        {
            if(report_SW_headhex->report_type_select[0] == true)
                report_SW_uniform_time(FC_REPORT_UNIFORM_TIME,ELEMENT_IDENTI_PRECIP_5MIN);//水文协议 雨量均匀时段信息报
        }
        else if(report_SW_headhex->report_fixed_count == 3)
        {
            if(report_SW_headhex->report_type_select[0] == true)
                report_SW_uniform_time(FC_REPORT_UNIFORM_TIME,ELEMENT_IDENTI_WATER_LEVEL);//水文协议 水位均匀时段信息报
        }
        else if(report_SW_headhex->report_fixed_count == 4)
        {
            if(report_SW_headhex->report_type_select[1] == true)
                report_SW_hour();//水文协议 小时报
        }
        else if(report_SW_headhex->report_fixed_count == 5)
        {
            //if(report_SW_headhex->report_type_select[0] == true)
            //report_SW_Manual_Work();//水文协议 人工置数报
        }
        else if(report_SW_headhex->report_fixed_count == 6)
        {
            uint8_t time_min = QTime::currentTime().minute();
            if(time_min == 0)
            {
                //水文协议 图片报
                if(MainWindow::iniFile->value("/Camera/Open1").toUInt() == 1)
                {
                    QString camera_ip = MainWindow::iniFile->value("/Camera/IP1").toString();
                    QString camera_name = MainWindow::iniFile->value("/Camera/Name1").toString();
                    QString camera_password = MainWindow::iniFile->value("/Camera/Password1").toString();
                    report_SW_fixedPicture(camera_fun(camera_ip,camera_name,camera_password));//上传当前时间抓拍图片
                }
//                if(MainWindow::iniFile->value("/Camera/Open2").toUInt() == 1)
//                {
//                    QString camera_ip = MainWindow::iniFile->value("/Camera/IP2").toString();
//                    QString camera_name = MainWindow::iniFile->value("/Camera/Name2").toString();
//                    QString camera_password = MainWindow::iniFile->value("/Camera/Password2").toString();
//                    report_SW_fixedPicture(camera_fun(camera_ip,camera_name,camera_password));//上传当前时间抓拍图片
//                }
//                if(MainWindow::iniFile->value("/Camera/Open3").toUInt() == 1)
//                {
//                    QString camera_ip = MainWindow::iniFile->value("/Camera/IP3").toString();
//                    QString camera_name = MainWindow::iniFile->value("/Camera/Name3").toString();
//                    QString camera_password = MainWindow::iniFile->value("/Camera/Password3").toString();
//                    report_SW_fixedPicture(camera_fun(camera_ip,camera_name,camera_password));//上传当前时间抓拍图片
//                }
            }
        }
        else
        {
            report_SW_headhex->report_fixed_flag = false;
            report_SW_headhex->report_fixed_count = 0;
        }
    }

    else if(socket_agreement == 1)//水资源
    {
        report_SZY_headhex->report_fixed_count++;

        if(report_SZY_headhex->report_fixed_count == 1)
        {
            for(uint8_t i=0;i<4;i++)
            {
                report_SZY_link(&tcp_comm[i],0xF2);
            }
        }
        else if(report_SZY_headhex->report_fixed_count == 2)
        {
            if((report_SZY_headhex->uploadtype>>0)&0x01)
            {
                report_SZY_fixed_time(REPORT_RAINFALL);//水资源协议 雨量定时报
                //report_SZY_fixed_time(REPORT_COMPREHENSIVE);//水资源协议 统计雨量定时报 //水资源协议平台暂时不接收累计雨量数据
            }
        }
        else if(report_SZY_headhex->report_fixed_count == 3)
        {
            if((report_SZY_headhex->uploadtype>>1)&0x01)
            {
                report_SZY_fixed_time(REPORT_WATE_LEVEL);//水资源协议 水位定时报
            }
        }
        else if(report_SZY_headhex->report_fixed_count == 4)
        {
            if((report_SZY_headhex->uploadtype>>2)&0x01)
            {
                report_SZY_fixed_time(REPORT_FLOW_WATER);//水资源协议 流量定时报
            }
        }
        else if(report_SZY_headhex->report_fixed_count == 5)
        {
            if((report_SZY_headhex->uploadtype>>3)&0x01)
            {
                report_SZY_fixed_time(REPORT_VELOCITY_WATER);//水资源协议 流速定时报
            }
        }
//        else if(report_SZY_headhex->report_fixed_count == 6)
//        {
//            if((report_SZY_headhex->uploadtype>>4)&0x01)
//            {
//                report_SZY_fixed_time(REPORT_GATE_LOCATION);//水资源协议 闸门开度值定时报
//            }
//        }
//        else if(report_SZY_headhex->report_fixed_count == 7)
//        {
//            if((report_SZY_headhex->uploadtype>>12)&0x01)
//                report_SZY_fixed_time(REPORT_ALERT_OR_STATE);//水资源协议 报警或状态参数定时报
//        }
//        else if((report_SZY_headhex->report_fixed_count == 8) && (time_min == 0))
//        {
//            report_SZY_headhex->control_area = DIR_MASK | (0x30 & (FCB_MASK | FUNCTION_MASK)) | CONFIRM;
//            QString camera_ip = MainWindow::iniFile->value("/Camera/IP1").toString();
//            QString camera_name = MainWindow::iniFile->value("/Camera/Name1").toString();
//            QString camera_password = MainWindow::iniFile->value("/Camera/Password1").toString();
//            report_SZY_QueryPicture(&tcp_comm[0],camera_fun(camera_ip,camera_name,camera_password));
//        }
        else
        {
            for(uint8_t i=0;i<4;i++)
            {
                if(tcp_comm[i].socket_agreement == 1)
                    tcp_comm[i].noReply_count ++;
            }

            report_SZY_headhex->report_fixed_flag = false;//发送定时报标志
            report_SZY_headhex->report_fixed_count = 0;
        }
    }
    else//预警机
    {

    }
}

void tcp_socket::report_SW_link(TCP_COMM *Tcp_comm)
{
    uint16_t index = 0;
    QByteArray send_data;

    if(Tcp_comm->socket_agreement != 0)
        return;
    send_data.clear();
    index = 0;
    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_REPORT_LINK_MT;//功能码
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = STX;//传输正文起始
    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    if(Tcp_comm->send_num > 65500)
       Tcp_comm->send_num = 0;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
    Tcp_comm->tcp_onLine = true;//在线标志
}

void tcp_socket::report_SW_fixed_time(uint8_t fun_code)
{
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "tcp_SW_fixed_time_report";
    uint32_t send_date_int = 0;

    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(tcp_comm[i].socket_agreement != 0)
            continue;
        send_data.clear();
        index = 0;

        send_data[index++] = report_SW_headhex->frame_Begin >> 8;
        send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
        send_data[index++] = report_SW_headhex->station_centerAddr;
        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];
        send_data[index++] = report_SW_headhex->password >> 8;
        send_data[index++] = report_SW_headhex->password & 0xff;

        send_data[index++] = fun_code;//功能码
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = 0x00;//上行报文标识和数据长度
        send_data[index++] = STX;//传输正文起始
        tcp_comm[i].send_num = tcp_comm[i].send_num + 1;
        send_data[index++] = tcp_comm[i].send_num >> 8;//报文流水号
        send_data[index++] = tcp_comm[i].send_num & 0xff;//报文流水号

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

        send_data[index++] = 0xF1;//地址标识符
        send_data[index++] = 0xF1;

        send_data[index++] = report_SW_headhex->station_ycAddr[0];
        send_data[index++] = report_SW_headhex->station_ycAddr[1];
        send_data[index++] = report_SW_headhex->station_ycAddr[2];
        send_data[index++] = report_SW_headhex->station_ycAddr[3];
        send_data[index++] = report_SW_headhex->station_ycAddr[4];

        send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

        send_data[index++] = 0xF0;//观测时间标识符
        send_data[index++] = 0xF0;

        send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
        send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

        if((report_SW_headhex->uploadtype[2]  >> 1) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_FLOW_INST;//瞬时流量标识符
            send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_flow_inst = 0x123456;
            send_date_int = data_result.data_flow_inst * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_FLOW_TOTAL;//累计流量标识符
            send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
            send_date_int = data_result.data_flow_total;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

#ifdef FLOOD_FLOW
        send_data[index++] = 0x80;//泄洪流量标识符
        send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
        //data_result.data_flood_flow = 0x123456;
        send_date_int = data_result.data_flood_flow * 1000;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 24 )& 0xff;
        send_data[index++] = (send_date_int >> 16 )& 0xff;
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;
#endif

        if((report_SW_headhex->uploadtype[0]  >> 7) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_PRECIP_DAY;//日降雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_inst = 0x123456;
            send_date_int = data_result.data_rain_day * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_INST;//当前雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_inst = 0x123456;
            send_date_int = data_result.data_rain_inst * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_TOTAL;//累计雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_total * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_1H;//1h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_1h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_3H;//3h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_3h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_6H;//6h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_6h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_12H;//12h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_12h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_24H;//24h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_24h * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_48H;//48h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_48h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;

            send_data[index++] = ELEMENT_IDENTI_PRECIP_72H;//72h雨量标识符
            send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_rain_total = 0x12345678;
            send_date_int = data_result.data_rain_72h * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        if((report_SW_headhex->uploadtype[1]  >> 0) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_WATER_LEVEL;//水位标识符
            send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_water = 0x123456;
            send_date_int = data_result.data_water * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        if((report_SW_headhex->uploadtype[2]  >> 2) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_FLOW_SPEED;//流速标识符
            send_data[index++] = 0x23;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_flow_speed = 0x123456;
            send_date_int = data_result.data_flow_speed * 1000;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        if((report_SW_headhex->uploadtype[2]  >> 4) & 1)
        {
            send_data[index++] = ELEMENT_IDENTI_KDY;//开度值标识符
            send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
            //data_result.data_flow_speed = 0x123456;
            send_date_int = data_result.data_kdy_value;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (send_date_int >> 24 )& 0xff;
            send_data[index++] = (send_date_int >> 16 )& 0xff;
            send_data[index++] = (send_date_int >> 8 )& 0xff;
            send_data[index++] = send_date_int & 0xff;
        }

        send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
        send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.alarm_state_SW;
        QString str_alarm =  QString("%1").arg(send_date_int,8,16,QLatin1Char('0'));//固定字符串有8个
        QByteArray alarm;
        StringToHex(str_alarm,alarm);
        send_data[index++] = alarm[0];
        send_data[index++] = alarm[1];
        send_data[index++] = alarm[2];
        send_data[index++] = alarm[3];

        send_data[index++] = ELEMENT_IDENTI_VOL_LEVEL;//电压标识符
        send_data[index++] = 0x12;//高5位表示数据字节数，低3位表示小数位数
        send_date_int = data_result.power_value * 100;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = (send_date_int >> 8 )& 0xff;
        send_data[index++] = send_date_int & 0xff;

        send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
        send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

        send_data[index++] = ETX;//传输正文结束
        uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
        send_data[index++] = CRC_Data >> 8;
        send_data[index++] = CRC_Data & 0xff;

        tcp_comm[i].reSend_type[0] = true;//重传标志

        if(tcp_comm[i].socket_flag == true)//连接成功才发送，否则只保留数据待补传
        {
            socket_Send(&tcp_comm[i],send_data,send_data.size());
#ifdef RESEND
            tcp_comm[i].noReply_count ++;
#endif
        }
        else
        {

        }

#ifdef RESEND
        reSendInsertData(i+1,QDateTime::currentDateTime().toString("yyyyMMddHHmm"),send_data.toHex());
#endif
        data_result.event[16] = data_result.event[16] + 1;//发报记录
        if(data_result.event[16] > 65530)
            data_result.event[16] = 0;
    }
}

void tcp_socket::report_SW_Ask_Water_PumpPara(TCP_COMM *Tcp_comm){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "SW_Ask_Water_Pump";
    uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_PUMP_DATA;//功能码 OX44
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = STATION_TYPE_RESERVOIR;//测站分类码

    send_data[index++] = 0xF0;//观测时间标识符
    send_data[index++] = 0xF0;

    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);

    send_data[index++] = ELEMENT_IDENTI_A_Voltage;//交流A相电压标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    send_data_int = 2401;
    send_data_int = uwordToBcd(send_data_int);
    send_data[index++] = (send_data_int >> 24 )& 0xff;
    send_data[index++] = (send_data_int >> 16 )& 0xff;
    send_data[index++] = (send_data_int >> 8 )& 0xff;
    send_data[index++] = send_data_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_B_Voltage;//交流B相电压标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    send_data_int = 2402;
    send_data_int = uwordToBcd(send_data_int);
    send_data[index++] = (send_data_int >> 24 )& 0xff;
    send_data[index++] = (send_data_int >> 16 )& 0xff;
    send_data[index++] = (send_data_int >> 8 )& 0xff;
    send_data[index++] = send_data_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_C_Voltage;//交流C相电压标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    send_data_int = 2403;
    send_data_int = uwordToBcd(send_data_int);
    send_data[index++] = (send_data_int >> 24 )& 0xff;
    send_data[index++] = (send_data_int >> 16 )& 0xff;
    send_data[index++] = (send_data_int >> 8 )& 0xff;
    send_data[index++] = send_data_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_A_current;//交流A相电流标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    send_data_int = 551;
    send_data_int = uwordToBcd(send_data_int);
    send_data[index++] = (send_data_int >> 24 )& 0xff;
    send_data[index++] = (send_data_int >> 16 )& 0xff;
    send_data[index++] = (send_data_int >> 8 )& 0xff;
    send_data[index++] = send_data_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_B_current;//交流B相电流标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    send_data_int = 552;
    send_data_int = uwordToBcd(send_data_int);
    send_data[index++] = (send_data_int >> 24 )& 0xff;
    send_data[index++] = (send_data_int >> 16 )& 0xff;
    send_data[index++] = (send_data_int >> 8 )& 0xff;
    send_data[index++] = send_data_int & 0xff;

    send_data[index++] = ELEMENT_IDENTI_C_current;//交流C相电流标识符
    send_data[index++] = 0x21;//高5位表示数据字节数，低3位表示小数位数
    send_data_int = 553;
    send_data_int = uwordToBcd(send_data_int);
    send_data[index++] = (send_data_int >> 24 )& 0xff;
    send_data[index++] = (send_data_int >> 16 )& 0xff;
    send_data[index++] = (send_data_int >> 8 )& 0xff;
    send_data[index++] = send_data_int & 0xff;

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());

}
void tcp_socket::report_SW_Set_ICstate(TCP_COMM *Tcp_comm,uint32_t state){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Set_ICstate";
    uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_SET_IC_STATUS;//功能码 OX4B
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = ELEMENT_IDENTI_ALARM;//告警信息标识符
    send_data[index++] = 0x20;//高5位表示数据字节数，低3位表示小数位数
    if((state >> 9) & 1)
        data_result.alarm_state_SW = data_result.alarm_state_SW | state;
    else
        data_result.alarm_state_SW = data_result.alarm_state_SW & (~(1 << 9));

    send_data_int = data_result.alarm_state_SW;
    QString str_alarm =  QString("%1").arg(send_data_int,8,16,QLatin1Char('0'));//固定字符串有8个
    QByteArray alarm;
    StringToHex(str_alarm,alarm);
    send_data[index++] = alarm[0];
    send_data[index++] = alarm[1];
    send_data[index++] = alarm[2];
    send_data[index++] = alarm[3];

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}
void tcp_socket::report_SW_Set_Water_Pumpstate(TCP_COMM *Tcp_comm,uint16_t state){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Set_Water_Pumpstate";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_REPORT_PUMP_SWITH_CMD;//功能码 OX4C
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];


    send_data[index++] =  state & 0xFF;
    send_data[index++] = (state >> 8) & 0xFF;


    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());

}

void tcp_socket::report_SW_Set_Password(TCP_COMM *Tcp_comm){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Set_Password";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_SET_PASSWORD;//功能码 OX49
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    QByteArray data = Tcp_comm->recive_buf_comm.mid(24, 2);
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian); // 设置字节序为小端序
    uint16_t password;
    stream >> password;
    uint8_t high = password & 0xFF;
    uint8_t low = (password >> 8) & 0xFF;
    uint16_t result = ((high & 0xF0) >> 4) * 1000 + (high & 0x0F) * 100 + ((low & 0xF0) >> 4) * 10 + (low & 0x0F);
    QString result1 = QString::number(result); // 将整数值转换为十进制字符串
    MainWindow::iniFile->setValue("/SW_PROTOCOL/Password", result1);
    report_SW_headhex->password = MainWindow::iniFile->value("/SW_PROTOCOL/Password").toUInt();
    emit uploadPassword(result1);

    send_data[index++] = 0x03;//基本配置标识符 03H密码
    send_data[index++] = 0x10;//高5位表示数据字节数，低3位表示小数位数

    send_data[index++] =    password & 0xFF;
    send_data[index++] =   (password >> 8) & 0xFF;


    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
    data_result.event[4] = data_result.event[4] + 1;//密码修改记录
    if(data_result.event[4] > 65530)
        data_result.event[4] = 0;
}

void tcp_socket::report_SW_Query_stationTime(TCP_COMM *Tcp_comm){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Query_stationTime";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_CLOCK;//功能码 OX51
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];


    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_QueryVersion(TCP_COMM *Tcp_comm){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_QueryVersion";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_QUERY_SOFT_VERSION;//功能码 OX4F
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];


    QString version = MainWindow::Version;
    QByteArray versionb = version.toUtf8();
    int numBytes = versionb.size(); // 获取versionb中的字节数量

    QByteArray num(reinterpret_cast<const char*>(&numBytes), sizeof(numBytes));

    send_data[index++]  =  static_cast<uint8_t>(num.at(0));
    // 将versionb中的每个字节放入send_data中
    for (int i = 0; i < numBytes; ++i) {
        send_data[index++] = static_cast<uint8_t>(versionb.at(i));
    }




    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SW_Set_Valvestate(TCP_COMM *Tcp_comm,uint16_t state){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Set_Valvestate";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_REPORT_VALVE_SWITH_CMD;//功能码 OX4D
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];


    send_data[index++] =  state & 0xFF;
    send_data[index++] = (state >> 8) & 0xFF;


    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());

}

void tcp_socket::report_SW_Set_gatestate(TCP_COMM *Tcp_comm,uint32_t state,uint16_t value){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Set_gatestate";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_REPORT_GATE_SWITH_CMD;//功能码 OX4E
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] = (state >> 24) & 0xFF;
    send_data[index++] = (state >> 16) & 0xFF;
    send_data[index++] = (state >> 8) & 0xFF;
    send_data[index++] =  state & 0xFF;

    kdy.data = value;
    emit kdy_signal(3);//设置开度值
    qDebug()<<"KDY_Set_Value="<<kdy.data;
    MainWindow::iniFile->setValue("/KDY/Data",kdy.data);

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());

    Delay_MSec(1000 * (kdy.time + 1));
    if((state >> 16) & 0xFF)
        emit kdy_signal(5);//开闸门
    else
        emit kdy_signal(6);//关闸门
    qDebug()<<"KDY_Set_State";

    data_result.event[1] = data_result.event[1] + 1;//参数变更记录
    if(data_result.event[1] > 65530)
        data_result.event[1] = 0;
}
void tcp_socket::report_SW_Set_Watersetting(TCP_COMM *Tcp_comm,uint8_t state){
    uint16_t index = 0;
    QByteArray send_data;
    qDebug() << "report_SW_Set_Watersetting";
    //uint32_t send_data_int = 0 ;

    send_data[index++] = report_SW_headhex->frame_Begin >> 8;
    send_data[index++] = report_SW_headhex->frame_Begin & 0xff;
    send_data[index++] = report_SW_headhex->station_centerAddr;
    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];
    send_data[index++] = report_SW_headhex->password >> 8;
    send_data[index++] = report_SW_headhex->password & 0xff;

    send_data[index++] = FC_WATER_YIELD_CMD;//功能码 OX4F
    send_data[index++] = 0x00;//上行报文标识和数据长度
    send_data[index++] = 0x00;//上行报文标识和数据长度 在后文中将更新这二值
    send_data[index++] = STX;//传输正文起始

    Tcp_comm->send_num = Tcp_comm->send_num + 1;
    send_data[index++] = Tcp_comm->send_num >> 8;//报文流水号
    send_data[index++] = Tcp_comm->send_num & 0xff;//报文流水号

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = ((((currentdate.year()%100) / 10) & 0x0F) << 4) + (((currentdate.year() % 100) % 10) & 0x0f);
    send_data[index++] = (((currentdate.month() / 10) &0x0F) << 4) + ((currentdate.month() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);

    send_data[index++] = 0xF1;//地址标识符
    send_data[index++] = 0xF1;

    send_data[index++] = report_SW_headhex->station_ycAddr[0];
    send_data[index++] = report_SW_headhex->station_ycAddr[1];
    send_data[index++] = report_SW_headhex->station_ycAddr[2];
    send_data[index++] = report_SW_headhex->station_ycAddr[3];
    send_data[index++] = report_SW_headhex->station_ycAddr[4];

    send_data[index++] =  state & 0xFF;

    send_data[11] = ((index - 14) >> 8) & 0x0f;//修正上行报文标识和数据长度
    send_data[12] = (index - 14) & 0xff;//修正上行报文标识和数据长度

    send_data[index++] = ETX;//传输正文结束
    uint16_t CRC_Data=ModBusCRC16(send_data,send_data.size());
    send_data[index++] = CRC_Data >> 8;
    send_data[index++] = CRC_Data & 0xff;

    socket_Send(Tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_link(TCP_COMM *Tcp_comm,uint8_t fun_code)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!Tcp_comm->socket_flag)
        return;
    if(Tcp_comm->socket_agreement != 1)
        return;
    if(Tcp_comm->tcp_busy == true)
        return;
    send_data.clear();
    index = 0;

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x02;//AFN功能码，链路报
    send_data[index++] = fun_code;//保持在线
    crc8 = CRC8_SZY(send_data,index);//保持在线
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(Tcp_comm,send_data,send_data.size());
}


void tcp_socket::report_SZY_ResetTerminal(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,11))
        return;

    // 数据
    uint8_t data = tcp_comm->recive_buf_comm.at(10);

    // 先发送，再动作
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x90;
    send_data[index++] = data;
    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());

    if(data == 0x01)
    {
        serial_send_disconnect();
        system("reboot -f");//重启
    }
    else if(data == 0x02)
    {
#ifdef ARM
    serial_send_disconnect();
    system("cp /home/Config_backup.ini /home/Config.ini");
    system("sync");
    system("reboot -f");
#endif
    }else{

    }
}

void tcp_socket::report_SZY_DeleteHistoryData(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,11))
        return;

    // 数据
    uint8_t data = tcp_comm->recive_buf_comm.at(10);
    // 控制
    if(data&0x01)
    {
        deleteAllData("Rain");// 清除雨量
    }
    if(data&0x2)
    {
        deleteAllData("Water");// 清除水位
    }

    // 组包回传
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x91;
    send_data[index++] = data;
    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_OpenKDY(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,11))
        return;

    // 数据
    uint8_t data = tcp_comm->recive_buf_comm.at(10);
    //低四位是编号，此处忽略
    if((data&0xF0) == 0xF0)
    {
        // 控制
#ifdef ARM
        emit kdy_signal(5);
#endif

        // 组包回传
        QByteArray send_data;
        uint8_t index = 0, crc8 = 0;
        send_data.clear();
        send_data[index++] = 0x68;//帧头
        send_data[index++] = 0x00;
        send_data[index++] = 0x68;
        send_data[index++] = report_SZY_headhex->control_area;//控制域
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
        send_data[index++] = 0x92;
        send_data[index++] = data;
        crc8 = CRC8_SZY(send_data,index);
        send_data[index++] = crc8;
        send_data[index++] = 0x16;//帧尾

        send_data[1] = index - 5;//修正数据长度

        socket_Send(tcp_comm,send_data,send_data.size());
    }

    return;
}

void tcp_socket::report_SZY_CloseKDY(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,11))
        return;

    // 数据
    uint8_t data = tcp_comm->recive_buf_comm.at(10);
    //低四位是编号，此处忽略
    if((data&0xF0) == 0xF0)
    {
        // 控制
#ifdef ARM
        emit kdy_signal(6);
#endif

        // 组包回传
        QByteArray send_data;
        uint8_t index = 0, crc8 = 0;
        send_data.clear();
        send_data[index++] = 0x68;//帧头
        send_data[index++] = 0x00;
        send_data[index++] = 0x68;
        send_data[index++] = report_SZY_headhex->control_area;//控制域
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
        send_data[index++] = 0x93;
        send_data[index++] = data;
        crc8 = CRC8_SZY(send_data,index);
        send_data[index++] = crc8;
        send_data[index++] = 0x16;//帧尾

        send_data[1] = index - 5;//修正数据长度

        socket_Send(tcp_comm,send_data,send_data.size());
    }

    return;
}

void tcp_socket::report_SZY_SetThresholdStoreTime(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,tcp_comm->recive_buf_comm.size()-9))
        return;

    // TODO::取数据，目前不做该功能，暂不处理
    //uint8_t no = ((uint8_t)tcp_comm->recive_buf_comm.at(10))&0x0F;  // 编号（暂不使用）
    uint8_t type = (((uint8_t)tcp_comm->recive_buf_comm.at(10))&0xF0)>>4;
    //uint8_t timeInterval = (uint8_t)tcp_comm->recive_buf_comm.at(11);   // 时间间隔（暂不使用）

    switch (type) {
    case 0x00:
    {
        // 雨量1字节表示 范围0.1-9.9
        uint32_t tmp = bcdToUword(tcp_comm->recive_buf_comm,12,6);
        data_result.data_rain_upper_limit_value = ((double)tmp)/1000;
        MainWindow::iniFile->setValue("/ALARM/Rain_upLimit",QString::number(data_result.data_rain_upper_limit_value));
        break;
    }
    case 0x01:
    {
        // 水位
        uint32_t tmp = bcdToUword(tcp_comm->recive_buf_comm,12,7);
        data_result.data_water_upper_limit_value = ((double)tmp)/1000;
        MainWindow::iniFile->setValue("/ALARM/Water_upLimit",QString::number(data_result.data_water_upper_limit_value));
        break;
    }
    case 0x02:
    {
        //流量
        int32_t tmp = bcdToWord(tcp_comm->recive_buf_comm,12,10,true);
        data_result.data_flow_upper_limit_value = ((double)tmp)/1000;
        MainWindow::iniFile->setValue("/ALARM/flow_upLimit",QString::number(data_result.data_flow_upper_limit_value));
        break;
    }
    case 0x03:
    {
        //流速
        int32_t tmp = bcdToWord(tcp_comm->recive_buf_comm,12,6,true);
        data_result.data_speed_upper_limit_value = ((double)tmp)/1000;
        MainWindow::iniFile->setValue("/ALARM/Speed_upLimit",QString::number(data_result.data_speed_upper_limit_value));
        break;
    }
    default:
    {
        return;
    }
    }

    // 组包回传
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x20;

    // 截取数据
    for(int i=10;i<tcp_comm->recive_buf_comm.size()-9;i++)
         send_data[index++] = (uint8_t)tcp_comm->recive_buf_comm.at(i);

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryData(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 组包回传
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0xB1;

    for(int i=0;i<9;i++)
    {
        send_data[index++] = (uint8_t)tcp_comm->recive_buf_comm.at(10+i);
    }
    // TODO::载入数据（1小时以内的）

    QDateTime dateTime;
    dateTime.setDate(QDate(2000+bcdToUword(tcp_comm->recive_buf_comm,14,2), bcdToUword(tcp_comm->recive_buf_comm,13,2), bcdToUword(tcp_comm->recive_buf_comm,12,2)));
    dateTime.setTime(QTime(bcdToUword(tcp_comm->recive_buf_comm,11,2), 00, 0));

    uint8_t type = (uint8_t)tcp_comm->recive_buf_comm.at(10);
    switch (type) {
    case 0x00://雨量
    {
        for(int i=0;i<12;i++)//1小时12组数据（5分钟一组）
        {
            dateTime = dateTime.addSecs(300);   // 增加5分钟(查询是从05分开始的，所以放前面)
            QDate date = dateTime.date();
            QTime time = dateTime.time();
            QString mark = QString("%1%2%3%4%5")
                    .arg(date.year(),4,10,QChar('0'))
                    .arg(date.month(),2,10,QChar('0'))
                    .arg(date.day(),2,10,QChar('0'))
                    .arg(time.hour(),2,10,QChar('0'))
                    .arg(time.minute(),2,10,QChar('0'));
            DATA_BASE2 db=query_oneTable("Rain",mark);
            uint32_t send_date_int = uwordToBcd((int32_t)(db.data*10));// 没找到的填0
            send_data[index++] = send_date_int & 0xff;//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
        }
        break;
    }
    case 0x10://水位
    {
        for(int i=0;i<12;i++)//1小时12组数据（5分钟一组）
        {
            dateTime = dateTime.addSecs(300);   // 增加5分钟(查询是从05分开始的，所以放前面)
            QDate date = dateTime.date();
            QTime time = dateTime.time();
            QString mark = QString("%1%2%3%4%5")
                    .arg(date.year(),4,10,QChar('0'))
                    .arg(date.month(),2,10,QChar('0'))
                    .arg(date.day(),2,10,QChar('0'))
                    .arg(time.hour(),2,10,QChar('0'))
                    .arg(time.minute(),2,10,QChar('0'));
            DATA_BASE2 db=query_oneTable("Water",mark);
            uint64_t send_date_int = udwordToDBcd((uint32_t)abs(db.data*1000));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 24 )& 0xff);//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
            if(db.data<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;
        }
        break;
    }
    case 0x20://流量
    {
        for(int i=0;i<12;i++)//1小时12组数据（5分钟一组）
        {
            dateTime = dateTime.addSecs(300);   // 增加5分钟(查询是从05分开始的，所以放前面)
            QDate date = dateTime.date();
            QTime time = dateTime.time();
            QString mark = QString("%1%2%3%4%5")
                    .arg(date.year(),4,10,QChar('0'))
                    .arg(date.month(),2,10,QChar('0'))
                    .arg(date.day(),2,10,QChar('0'))
                    .arg(time.hour(),2,10,QChar('0'))
                    .arg(time.minute(),2,10,QChar('0'));
            DATA_BASE2 db=query_oneTable("Flow",mark);
            uint64_t send_date_int = udwordToDBcd((uint32_t)abs(db.data*1000));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 24 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 32 )& 0xff);;//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
            if(db.data<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;
        }
        break;
    }
    case 0x30://流速
    {
        for(int i=0;i<12;i++)//1小时12组数据（5分钟一组）
        {
            dateTime = dateTime.addSecs(300);   // 增加5分钟(查询是从05分开始的，所以放前面)
            QDate date = dateTime.date();
            QTime time = dateTime.time();
            QString mark = QString("%1%2%3%4%5")
                    .arg(date.year(),4,10,QChar('0'))
                    .arg(date.month(),2,10,QChar('0'))
                    .arg(date.day(),2,10,QChar('0'))
                    .arg(time.hour(),2,10,QChar('0'))
                    .arg(time.minute(),2,10,QChar('0'));
            DATA_BASE2 db=query_oneTable("Speed",mark);
            uint32_t send_date_int = uwordToBcd((uint32_t)abs(db.data*1000));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 16 )& 0xff);
            if(db.data<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;
        }
        break;
    }
    }

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());

}

void tcp_socket::report_SZY_QueryUploadData(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 组包回传
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0xB2;

    // TODO::不响应，载入空数据


    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryPicture(TCP_COMM *tcp_comm,QString dir_pic)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    if(tcp_comm->tcp_busy == true)
        return;
    tcp_comm->tcp_busy = true;

    QThread::msleep(500);

#ifdef ARM
    //dir_pic = dir_pic;
#else
    QString path = QDir::currentPath();
    dir_pic = path + "/home/images/images1/2024-02-19-19-35-02.jpg";
#endif
    QFileInfo FileData(dir_pic);
    pic_send.pic_file_size = FileData.size();

    pic_send.send_size = 1024;//每包字节数
    pic_send.pack_total = (pic_send.pic_file_size + (pic_send.send_size - 1)) / pic_send.send_size;//总包数
    pic_send.pack_no = 0;//当前包序号
    pic_send.load_size = 0;//已发送字节数
    pic_send.pic_file = new QFile(dir_pic);

    if(!pic_send.pic_file->open(QIODevice::ReadOnly))//打开文件失败
    {
        qDebug()<<"open_file_error:" << dir_pic;
        QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
        DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
        singleInsertData("Alarm",DATA_BASE_Water,"Picture Error");
        return;
    }
    pic_send.socket_agreement = 1;
    timer3->start(1000);
}

void tcp_socket::report_SZY_EnableIC(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,tcp_comm->recive_buf_comm.size()-9))
        return;

    // 组包返回
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x30;

    send_data[index++] = 0x5A;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_DisableIC(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,tcp_comm->recive_buf_comm.size()-9))
        return;

    // 组包返回
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x30;

    send_data[index++] = 0x5A;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryRealTimeValue(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 取数据类型
    uint8_t control = ((uint8_t)tcp_comm->recive_buf_comm.at(3))&0x0F;
    if(control != 0x0D && control != 0x03)  // 暂不支持其他参数
        return;

    // 组包返回
    QByteArray send_data;
    uint8_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0xB0;

    // 数据
    switch(control)
    {
    case 0x01:// 雨量参数(TODO::应该是累计雨量)
    {
        uint32_t send_date_int = 0;
        send_date_int = data_result.data_rain_total * 10;
        send_date_int = uwordToBcd(send_date_int);
        send_data[index++] = send_date_int & 0xff;//水资源协议，低字节在前
        send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
        send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
        break;
    }
    case 0x02:// 水位参数
    {
        uint64_t send_date_int = udwordToDBcd((uint32_t)abs(data_result.data_water*1000));
        send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
        send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
        send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
        send_data[index] = (uint8_t)((send_date_int >> 24 )& 0xff);//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
        if(data_result.data_water<0)
            send_data[index] = send_data[index] | 0xF0;
        index++;
        break;
    }
    case 0x03:// 流量(水量)参数
    {
        uint64_t send_date_int = udwordToDBcd((uint32_t)abs(data_result.data_flow_inst*1000));
        send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
        send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
        send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
        send_data[index++] = (uint8_t)((send_date_int >> 24 )& 0xff);
        send_data[index] = (uint8_t)((send_date_int >> 32 )& 0xff);;//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
        if(data_result.data_flow_inst<0)
            send_data[index] = send_data[index] | 0xF0;
        index++;

        send_date_int = udwordToDBcd((uint32_t)abs(data_result.data_flow_total));
        send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
        send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
        send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
        send_data[index++] = (uint8_t)((send_date_int >> 24 )& 0xff);
        send_data[index] = (uint8_t)((send_date_int >> 32 )& 0xff);;//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
        if(data_result.data_flow_total<0)
            send_data[index] = send_data[index] | 0xF0;
        index++;

        break;
    }
    case 0x04:// 流速参数
    {
        uint32_t send_date_int = uwordToBcd((uint32_t)abs(data_result.data_flow_speed*1000));
        send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
        send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
        send_data[index] = (uint8_t)((send_date_int >> 16 )& 0xff);
        if(data_result.data_flow_speed<0)
            send_data[index] = send_data[index] | 0xF0;
        index++;
        break;
    }
    case 0x0D:
    {
        // 此处是否只需要发4字节的报警参数，还是发两遍？
        send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF0000)>>16);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF000000)>>24);
        break;
    }
    }

    if(control != 0x0D)
    {
        send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF0000)>>16);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF000000)>>24);
    }

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetClock(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    //report_SZY_headhex->password = 0x5080;  //TODO::DEBUG
    if(!report_pwCheck(tcp_comm->recive_buf_comm,16))
        return;

    // 读取数据
    uint32_t sec = bcdToUword(tcp_comm->recive_buf_comm, 10, 2);
    uint32_t min = bcdToUword(tcp_comm->recive_buf_comm, 11, 2);
    uint32_t hour = bcdToUword(tcp_comm->recive_buf_comm, 12, 2);
    uint32_t day = bcdToUword(tcp_comm->recive_buf_comm, 13, 2);
    uint32_t month = (((uint8_t)tcp_comm->recive_buf_comm.at(14))&0x0F)+((((uint8_t)tcp_comm->recive_buf_comm.at(14))&0x10)>>4)*10;
    uint32_t dow = ((((uint8_t)tcp_comm->recive_buf_comm.at(14))&0xE0)>>5);
    uint32_t year = bcdToUword(tcp_comm->recive_buf_comm, 15, 2) + 2000;

    // 更新
#ifdef Q_OS_WIN
    SYSTEMTIME st;
    st.wYear = year;
    st.wMonth = month;
    st.wDay = day;
    st.wDayOfWeek = dow;
    st.wHour = hour;
    st.wMinute = min;
    st.wSecond = sec;
    SetSystemTime(&st);
#else
    std::system(QString("date -s '%.4u-%.2u-%.2u %.2u:%.2u:%.2u'").arg(year).arg(month).arg(day).arg(hour).arg(min).arg(sec).toLatin1());
    std::system(QString("hwclock -w").toLatin1());
    std::system(QString("hwclock -s").toLatin1());
#endif

    //CT
//    QString dateTime = "date -s \"" +  QString::number(year + 2000) + "-" + QString::number(month) + "-" + QString::number(day) + " " + QString::number(hour) + ":" + QString::number(min) + ":" + QString::number(sec) + "\"";
//    QString timetohw = "hwclock -w";
//#ifdef ARM
//    std::system(dateTime.toLatin1());
//    std::system(timetohw.toLatin1());
//#endif

    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x11;

    //数据
    uint32_t send_date_int = 0;
    send_date_int = uwordToBcd(sec);
    send_data[index++] = (uint8_t)(send_date_int & 0xFF);
    send_date_int = uwordToBcd(min);
    send_data[index++] = (uint8_t)(send_date_int & 0xFF);
    send_date_int = uwordToBcd(hour);
    send_data[index++] = (uint8_t)(send_date_int & 0xFF);
    send_date_int = uwordToBcd(day);
    send_data[index++] = (uint8_t)(send_date_int & 0xFF);
    send_date_int = uwordToBcd(month);
    send_data[index] = (uint8_t)(send_date_int & 0xFF);
    send_date_int = uwordToBcd(dow);
    send_data[index] = (send_data[index]|((uint8_t)((send_date_int<<5)&0xFF)));
    index++;
    send_date_int = uwordToBcd(year-2000);
    send_data[index++] = (uint8_t)(send_date_int & 0xFF);

    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = 0x00;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryClock(TCP_COMM *tcp_comm)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();
    index = 0;

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x51;//AFN功能码

    // 6字节BCD时间
    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = (((currentdate.dayOfWeek()&0x0F)<<5) + (((currentdate.month()/10)&0x0F)<<4) + ((currentdate.month()%10)&0x0F));
    send_data[index++] = ((((currentdate.year()%100)/10)&0x0F)<<4)+(((currentdate.year()%100)%10)&0x0F);

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetFlow(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    //report_SZY_headhex->password = 0x5080;  //TODO::DEBUG
    if(!report_pwCheck(tcp_comm->recive_buf_comm,15))
        return;

    // 读取数据
    double tmp = (double)bcdToWord(tcp_comm->recive_buf_comm,10,10,true);
    data_result.data_flow_upper_limit_value = (tmp)/1000;
    /*
    double tmp = (double)bcdToUword(tcp_comm->recive_buf_comm,10,9);
    if(tcp_comm->recive_buf_comm.at(14)&0xF0)
        tmp = -(tmp/1000);

    data_result.data_flow_upper_limit_value = tmp;
    */
    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x1F;
    //数据
    uint64_t send_date_int = 0;
    send_date_int = udwordToDBcd((uint64_t)(abs(data_result.data_flow_upper_limit_value)*1000));
    MainWindow::iniFile->setValue("/ALARM/flow_upLimit",data_result.data_flow_upper_limit_value);
    if(data_result.data_flow_upper_limit_value<0)
        send_date_int |= 0xF000000000;

    send_data[index++] = (uint8_t)(send_date_int&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>8)&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>16)&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>24)&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>32)&0xFF);

    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = 0x00;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryFlow(TCP_COMM *tcp_comm)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x64;//AFN功能码，链路报

    //数据
    uint64_t send_date_int = 0;
    send_date_int = udwordToDBcd((uint64_t)(abs(data_result.data_flow_upper_limit_value)*1000));
    if(data_result.data_flow_upper_limit_value<0)
        send_date_int |= 0xF000000000;

    send_data[index++] = (uint8_t)(send_date_int&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>8)&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>16)&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>24)&0xFF);
    send_data[index++] = (uint8_t)((send_date_int>>32)&0xFF);

    send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetWaterLevel(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    //report_SZY_headhex->password = 0x5080;  //TODO::DEBUG
    if(!report_pwCheck(tcp_comm->recive_buf_comm,17))
        return;

    // 读取数据
    double water_base=0, water_lower=0, water_upper=0;

    water_base = ((double)bcdToWord(tcp_comm->recive_buf_comm,10,6,false))/100;
    water_lower = ((double)bcdToUword(tcp_comm->recive_buf_comm,13,4))/100;
    water_upper = ((double)bcdToUword(tcp_comm->recive_buf_comm,15,4))/100;

    //范围判断
    /*
    if(water_base<-7999.0 || water_base>7999.99)
        return;
    if(water_lower>99.99 || water_upper>99.99)
        return;
    */

    // 更新
    data_result.data_water_base_value = water_base;
    data_result.data_water_lower_limit_value = water_lower;
    data_result.data_water_upper_limit_value = water_upper;

    MainWindow::iniFile->setValue("/ALARM/Water_base",QString::number(data_result.data_water_base_value, 'f', 2));//水位基值
    MainWindow::iniFile->setValue("/ALARM/Water_upLimit",QString::number(data_result.data_water_upper_limit_value, 'f', 2));
    MainWindow::iniFile->setValue("/ALARM/Water_downLimit",QString::number(data_result.data_water_lower_limit_value, 'f', 2));

    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x17;

    int32_t send_date_int = 0;
    send_date_int = (int32_t)(data_result.data_water_base_value * 100);
    send_date_int = wordTo3Bcd(send_date_int);
    send_data[index++] = send_date_int & 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;

    send_date_int = (int32_t)(data_result.data_water_lower_limit_value * 100);
    send_date_int = uwordToBcd((uint32_t)send_date_int);
    send_data[index++] = send_date_int & 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;

    send_date_int = (int32_t)(data_result.data_water_upper_limit_value * 100);
    send_date_int = uwordToBcd((uint32_t)send_date_int);
    send_data[index++] = send_date_int & 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;

    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = 0x00;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度
    emit uploadRunSet(1);//更新ui配置
    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryWaterLevel(TCP_COMM *tcp_comm)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();
    index = 0;

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x57;//AFN功能码，链路报

    // N*7(3基值+2下限+2上限)+2（报警状态）,暂时N=1
    //data_result.data_water_base_value = -777.77;        // TODO::DEBUG
    //data_result.data_water_lower_limit_value = 11.99 + data_result.data_water_base_value;   // TODO::DEBUG
    //data_result.data_water_upper_limit_value = 99.99 + data_result.data_water_base_value;   // TODO::DEBUG
    int32_t send_date_int = 0;
    send_date_int = (int32_t)(data_result.data_water_base_value * 100);
    send_date_int = wordTo3Bcd(send_date_int);
    send_data[index++] = send_date_int & 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;
    send_data[index++] = (send_date_int >> 16 )& 0xff;

    send_date_int = (int32_t)(data_result.data_water_lower_limit_value * 100);
    send_date_int = uwordToBcd((uint32_t)send_date_int);
    send_data[index++] = send_date_int & 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;

    send_date_int = (int32_t)(data_result.data_water_upper_limit_value * 100);
    send_date_int = uwordToBcd((uint32_t)send_date_int);
    send_data[index++] = send_date_int & 0xff;
    send_data[index++] = (send_date_int >> 8 )& 0xff;

    send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetWorkMode(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    //report_SZY_headhex->password = 0x5080;  //TODO::DEBUG
    if(!report_pwCheck(tcp_comm->recive_buf_comm,11))
        return;

    // 读取数据
    uint8_t tmp = (uint8_t)tcp_comm->recive_buf_comm.at(10);
    data_result.alarm_state_SZY &= 0xFFFCFFFF;
    data_result.alarm_state_SZY |= (((uint32_t)tmp)<<16);

    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x12;

    // 数据
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY & 0x030000) >> 16);

    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = 0x00;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryWorkMode(TCP_COMM *tcp_comm)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();
    index = 0;

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x52;//AFN功能码，链路报
    // 数据
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY & 0x030000) >> 16);
    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetAddress(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,15))
        return;

    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x10;
    //数据
    report_SZY_headhex->station_Addr_SZY[0] = (uint8_t)tcp_comm->recive_buf_comm.at(10);
    report_SZY_headhex->station_Addr_SZY[1] = (uint8_t)tcp_comm->recive_buf_comm.at(11);
    report_SZY_headhex->station_Addr_SZY[2] = (uint8_t)tcp_comm->recive_buf_comm.at(12);
    report_SZY_headhex->station_Addr_SZY[3] = (uint8_t)tcp_comm->recive_buf_comm.at(13);
    report_SZY_headhex->station_Addr_SZY[4] = (uint8_t)tcp_comm->recive_buf_comm.at(14);
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];

    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = 0x00;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
    MainWindow::iniFile->setValue("/SZY_PROTOCOL/Station_addr",tcp_comm->recive_buf_comm.toHex().mid(20,10));
}

void tcp_socket::report_SZY_QueryAddress(TCP_COMM *tcp_comm)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x50;
    // 数据
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetPassword(TCP_COMM *tcp_comm)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,12))
        return;

    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x96;
    //数据
    report_SZY_headhex->password = (((uint16_t)tcp_comm->recive_buf_comm.at(10))&0x00FF) + ((((uint16_t)tcp_comm->recive_buf_comm.at(11))&0x00FF)<<8);
    MainWindow::iniFile->setValue("/SZY_PROTOCOL/Password",QString::number(report_SZY_headhex->password));

    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryUploadTime(TCP_COMM *tcp_comm)
{
    // 只做上报时间，其他写死。上报时间统一
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x53;
    // 数据
    send_data[index++] = (uint8_t)(report_SZY_headhex->uploadtype&0xFF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->uploadtype>>8)&0xFF);

    uint32_t send_date_int = 0;
    send_date_int = uwordToBcd(report_SZY_headhex->fixed_report_minute);

    for(uint8_t i=0;i<14;i++)
    {
        if(((report_SZY_headhex->uploadtype>>i)&0x01))
        {
            // 需要上报
            send_data[index++] = (uint8_t)(send_date_int&0xFF);
            send_data[index++] = (uint8_t)((send_date_int>>8)&0xFF);

        }else{
            // 不需要上报
            send_data[index++] = 0x00;
            send_data[index++] = 0x00;
        }
    }

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_QueryAllState(TCP_COMM *tcp_comm)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;
    send_data.clear();

    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0x5E;

    // 数据
    send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF0000)>>16);
    send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF000000)>>24);

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_SetUploadTime(TCP_COMM *tcp_comm)
{
    // 只做上报时间，其他写死。上报时间统一
    // 暂定取非0的最小值

    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 1)
        return;

    // 先判断密码
    if(!report_pwCheck(tcp_comm->recive_buf_comm,40))
        return;

    // 数据
    uint16_t type = ((uint16_t)bcdToUword(tcp_comm->recive_buf_comm, 10, 4))&SZY_UPLOAD_TYPE_MASK;
    uint8_t min = 0;
    for(uint8_t i=0;i<14;i++)
    {
        if((type>>i)&0x01)
        {
            uint8_t t = (uint8_t)bcdToUword(tcp_comm->recive_buf_comm, 12+i*2, 4);
            if(t != 0)
            {
                if(min==0){
                    min = t;
                }else{
                    if(t<min)
                        min = t;
                }
            }
        }
    }
    if(min==0)
        return;

    // 更新数据
    report_SZY_headhex->uploadtype = type;
    report_SZY_headhex->uploadtype_count = 0;
    for(uint8_t i=0;i<16;i++)
    {
        if(report_SZY_headhex->uploadtype>>i&1)
            report_SZY_headhex->uploadtype_count ++;
    }
    report_SZY_headhex->fixed_report_minute = min;
    //更新ui
    emit uploadTime(report_SZY_headhex->fixed_report_minute);
    MainWindow::iniFile->setValue("/SZY_PROTOCOL/Fixed_time",report_SZY_headhex->fixed_report_minute);
    MainWindow::iniFile->setValue("/SZY_PROTOCOL/Element", QString::number(report_SZY_headhex->uploadtype));
    // 组包反馈
    QByteArray send_data;
    uint16_t index = 0, crc8 = 0;
    send_data.clear();
    send_data[index++] = 0x68;//帧头
    send_data[index++] = 0x00;
    send_data[index++] = 0x68;
    send_data[index++] = report_SZY_headhex->control_area;//控制域
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
    send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
    send_data[index++] = 0xA1;

    // 数据
    send_data[index++] = (uint8_t)(report_SZY_headhex->uploadtype&0xFF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->uploadtype>>8)&0xFF);
    uint32_t send_date_int = 0;
    send_date_int = uwordToBcd(report_SZY_headhex->fixed_report_minute);
    for(uint8_t i=0;i<14;i++)
    {
        if(((report_SZY_headhex->uploadtype>>i)&0x01))
        {
            // 需要上报
            send_data[index++] = (uint8_t)(send_date_int&0xFF);
            send_data[index++] = (uint8_t)((send_date_int>>8)&0xFF);

        }else{
            // 不需要上报
            send_data[index++] = 0x00;
            send_data[index++] = 0x00;
        }
    }


    send_data[index++] = (uint8_t)(report_SZY_headhex->password&0x00FF);
    send_data[index++] = (uint8_t)((report_SZY_headhex->password&0xFF00)>>8);

    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
    send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
    send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
    send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
    send_data[index++] = 0x00;

    crc8 = CRC8_SZY(send_data,index);
    send_data[index++] = crc8;
    send_data[index++] = 0x16;//帧尾

    send_data[1] = index - 5;//修正数据长度

    socket_Send(tcp_comm,send_data,send_data.size());
}

void tcp_socket::report_SZY_fixed_time(uint8_t fun_code)
{
    uint16_t index = 0,crc8 = 0;
    QByteArray send_data;
    //uint32_t bcd_code = 0;
    uint32_t send_date_int = 0;
    qDebug() << "tcp_SZY_fixed_time_report";
    for(uint8_t i=0;i<4;i++)
    {
        if(tcp_comm[i].tcp_busy)
            continue;
        if(tcp_comm[i].socket_agreement != 1)
            continue;
        send_data.clear();
        index = 0;

        send_data[index++] = 0x68;//帧头
        send_data[index++] = 0x00;
        send_data[index++] = 0x68;
        send_data[index++] = report_SZY_headhex->control_area | fun_code;//控制域
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[0];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[1];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[2];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[3];
        send_data[index++] = report_SZY_headhex->station_Addr_SZY[4];
        send_data[index++] = 0xC0;//AFN功能码，链路报

        if(fun_code == REPORT_RAINFALL) //瞬时雨量
        {
            //data_result.data_rain_inst = 10.00f;// TODO::DEBUG
            send_date_int = data_result.data_rain_inst * 10;
            send_date_int = uwordToBcd(send_date_int);
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);

            tcp_comm[i].reSend_type[1] = true;//重传标志
        }

        if(fun_code == REPORT_WATE_LEVEL)//水位
        {
            //data_result.data_water = 100.00f;// TODO::DEBUG
            uint64_t send_date_int = udwordToDBcd((uint32_t)abs(data_result.data_water*1000));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 24 )& 0xff);//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
            if(data_result.data_water<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;

            tcp_comm[i].reSend_type[1] = true;//重传标志
        }

        if(fun_code == REPORT_FLOW_WATER)//瞬时流量 + 累计流量
        {
            //data_result.data_flow_inst = 0.2f;// TODO::DEBUG
            uint64_t send_date_int = udwordToDBcd((uint32_t)abs(data_result.data_flow_inst*1000));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 24 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 32 )& 0xff);;//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
            if(data_result.data_flow_inst<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;

            send_date_int = udwordToDBcd((uint32_t)abs(data_result.data_flow_total));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
            send_data[index++] = (uint8_t)((send_date_int >> 24 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 32 )& 0xff);;//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
            if(data_result.data_flow_total<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;

            tcp_comm[i].reSend_type[1] = true;//重传标志
        }

        if(fun_code == REPORT_VELOCITY_WATER)//流速数据
        {
            //data_result.data_flow_speed = 0.3f;// TODO::DEBUG
            send_date_int = uwordToBcd((uint32_t)abs(data_result.data_flow_speed * 1000));
            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
            send_data[index] = (uint8_t)((send_date_int >> 16 )& 0xff);
            if(data_result.data_flow_speed<0)
                send_data[index] = send_data[index] | 0xF0;
            index++;

            tcp_comm[i].reSend_type[1] = true;//重传标志
        }

//        if(fun_code == REPORT_GATE_LOCATION)//闸门开度数据
//        {
//            //data_result.data_kdy_value = 12;// TODO::DEBUG
//            send_date_int = data_result.data_kdy_value;
//            send_date_int = uwordToBcd(send_date_int);
//            send_data[index++] = (uint8_t)(send_date_int & 0xff);//水资源协议，低字节在前
//            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
//            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);

//            tcp_comm[i].reSend_type[1] = true;//重传标志
//        }

//        if(fun_code == REPORT_ALERT_OR_STATE)//报警或状态参数
//        {
//            send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
//            send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);
//            send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF0000)>>16);
//            send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF000000)>>24);
//        }

//        if(fun_code == REPORT_COMPREHENSIVE)//统计雨量
//        {
//            //data_result.data_rain_total = 1000.0f;// TODO::DEBUG
//            send_data[index++] =  0xC1;
//            send_date_int = data_result.data_rain_total * 10;
//            send_date_int = uwordToBcd(send_date_int);
//            send_data[index++] = send_date_int & 0xff;//水资源协议，低字节在前
//            send_data[index++] = (uint8_t)((send_date_int >> 8 )& 0xff);
//            send_data[index++] = (uint8_t)((send_date_int >> 16 )& 0xff);
//            send_data[index++] = (uint8_t)((send_date_int >> 24 )& 0xff);
//            send_data[index++] = 0x00;//水资源协议流量数据有5个字节，最高位的高4位=0：正数，=F：负数
//        }

        //告警信息
        send_data[index++] = (uint8_t)(data_result.alarm_state_SZY&0xFF);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF00)>>8);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF0000)>>16);
        send_data[index++] = (uint8_t)((data_result.alarm_state_SZY&0xFF000000)>>24);

        QDate currentdate = QDate::currentDate();
        QTime currenttime = QTime::currentTime();
        send_data[index++] = (((currenttime.second() / 10) &0x0F) << 4) + ((currenttime.second() % 10) & 0x0F);
        send_data[index++] = (((currenttime.minute() / 10) &0x0F) << 4) + ((currenttime.minute() % 10) & 0x0F);
        send_data[index++] = (((currenttime.hour() / 10) &0x0F) << 4) + ((currenttime.hour() % 10) & 0x0F);
        send_data[index++] = (((currentdate.day() / 10) &0x0F) << 4) + ((currentdate.day() % 10) & 0x0F);
        send_data[index++] = 0x00;//允许发送延迟时间为0

        crc8 = CRC8_SZY(send_data,index);//保持在线
        send_data[index++] = crc8;
        send_data[index++] = 0x16;//帧尾

        send_data[1] = index - 5;//修正数据长度
        if(tcp_comm[i].socket_flag == true)//连接成功才发送，否则只保留数据待补传
        {
            socket_Send(&tcp_comm[i],send_data,send_data.size());
        }
        else
        {

        }

#ifdef RESEND
        reSendInsertData_SZY((i+1),QDateTime::currentDateTime().toString("yyyyMMddHHmm"),report_SZY_headhex->uploadtype_count - 1,send_data.toHex());
#endif
    }
}

void tcp_socket::report_SW_picture(TCP_COMM *tcp_comm,QString dir_pic)
{
    if(!tcp_comm->socket_flag)
        return;
    if(tcp_comm->socket_agreement != 0)
        return;
    if(tcp_comm->tcp_busy == true)
        return;
    tcp_comm->tcp_busy = true;

    QThread::msleep(500);

#ifdef ARM
    //dir_pic = dir_pic;
#else
    QString path = QDir::currentPath();
    dir_pic = path + "/home/images/images1/2024-02-19-19-35-02.jpg";
#endif
    QFileInfo FileData(dir_pic);
    pic_send.pic_file_size = FileData.size();

    pic_send.send_size = 1024;//每包字节数
    pic_send.pack_total = (pic_send.pic_file_size + (pic_send.send_size - 1)) / pic_send.send_size;//总包数
    pic_send.pack_no = 0;//当前包序号
    pic_send.load_size = 0;//已发送字节数
    pic_send.pic_file = new QFile(dir_pic);

    if((!pic_send.pic_file->open(QIODevice::ReadOnly)) || (pic_send.pic_file_size == 0))//打开文件失败
    {
        qDebug()<<"open_file_error:" << dir_pic;
        QString time_now_date = QDateTime::currentDateTime().toString("yyyyMMdd HH:mm:ss");
        DATA_BASE2 DATA_BASE_Water = {1,time_now_date,0};
        singleInsertData("Alarm",DATA_BASE_Water,"Picture Error");
        return;
    }
    pic_send.socket_agreement = 0;
    timer3->start(1000);
}

QString tcp_socket::camera_fun(QString camera_ip, QString camera_name, QString camera_password)
{
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
#ifdef ARM
    system(osd_cmd.toLatin1());
#endif

    //抓拍
    QString image_dir = "/home/images/images1/" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm") + ".jpg";
    QString takephoto_cmd = "curl --insecure --anyauth -u " + camera_name + ":" + camera_password + " -X GET http://" + camera_name + ":" + camera_password + "@" + camera_ip +"/ISAPI/Streaming/channels/1/picture > " + image_dir + " &";
#ifdef ARM
    system(takephoto_cmd.toLatin1());
#endif
    return image_dir;
}

bool tcp_socket::report_pwCheck(QByteArray array, uint32_t index)
{
//    uint16_t pw = (((uint16_t)array.at(index))&0x00FF) + ((((uint16_t)array.at(index+1))&0x00FF)<<8);
    uint16_t pw = (((uint16_t)array.at(index))&0x00FF) + ((((uint16_t)array.at(index+1))&0x00FF)<<8);

    if(pw!=report_SZY_headhex->password)
        return false;
    return true;
}

void tcp_socket::timerTimeout_receive()
{
    for(uint8_t i=0;i<5;i++)
    {
        if(!tcp_comm[i].recive_buf_comm.isEmpty())
        {
            tcp_comm[i].tcp_onLine = true;
            socket_comm_fun(&tcp_comm[i]);
            if(i != 4)//维护平台有大文件数据，不能频繁清理
                tcp_comm[i].recive_buf_comm.clear();
        }
    }

    if(report_SW_headhex->report_fixed_flag)
    {
        report_fixed_time(0);//定时报
    }

    if(report_SZY_headhex->report_fixed_flag)
    {
        report_fixed_time(1);//定时报
    }
}

uint16_t tcp_socket::ModBusCRC16(QByteArray data,uint32_t len)
{
    uint16_t crc=0xffff;
    uint16_t i, j;
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

uint8_t tcp_socket::CRC8_SZY(QByteArray buffer,uint16_t cLength)
{
    uint8_t crc = 0;
    int i,j;
    uint16_t temp=0;
    for (j = 3; j < cLength; j++)//水资源协议，前三个字节不参与CRC计数
    {
        temp = buffer.at(j);
        crc ^= temp;
        for (i = 0; i < 8; i++)
        {
            if ((crc & 0x80) == 0x80)
            {
                crc <<= 1;
                crc ^= 0xE5;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc & 0xFF;

//    uint8_t crc = 0;
//    int i,j;
//    uint8_t temp=0;
//    for (j = 3; j < cLength; j++)//水资源协议，前三个字节不参与CRC计数
//    {
//        temp = buffer.at(j);
//        crc ^= temp;
//        for (i = 0; i < 8; i++)
//        {
//            if ((crc & 0x80) == 0x80)
//            {
//                crc <<= 1;
//                crc ^= 0xE5;
//            }
//            else
//            {
//                crc <<= 1;
//            }
//        }
//    }
//    return crc & 0xFF;
}

void tcp_socket::serial_send_disconnect()
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

    crc16=ModBusCRC16(data_send,data_send.size());//计算CRC校验码
    data_crc[0]=crc16 & 0xff;
    data_crc[1]=crc16>>8 & 0xff;

    serial[2]->write(data_send);//串口发送头
    serial[2]->write(data_crc);//发送CRC校验码
}

//4字节十进制转BCD
uint32_t tcp_socket::uwordToBcd(uint32_t value)
{
    uint32_t A,B,C,D,E,F,G,H;
    uint32_t BCD = 0;

    A = B = C = D = E = F = G = H = 0;
    A = value/10000000%10 * pow(16,7);
    B = value/1000000%10 * pow(16,6);
    C = value/100000%10 * pow(16,5);
    D = value/10000%10 * pow(16,4);
    E = value/1000%10 * pow(16,3);
    F = value/100%10 * pow(16,2);
    G = value/10%10 * pow(16,1);
    H = value/1%10 * pow(16,0);
    BCD = A + B + C + D + E + F + G +H;
    return BCD;
}

uint64_t tcp_socket::udwordToDBcd(uint64_t value)
{
    uint64_t r=0,n=1;
    uint64_t a;
    while(value)
    {
        a=value %10;
        value=value/10;
        r=r+n*a;
        n=n<<4;
    }
    return r;
}

uint8_t tcp_socket::byteToBcd(uint8_t value)
{
    uint8_t A,B;
    uint8_t BCD = 0;

    A = B = 0;
    A = value/10%10 * pow(16,1);
    B = value/1%10 * pow(16,0);
    BCD = A + B;
    return BCD;
}

uint8_t tcp_socket::BCDtobyte(uint8_t bcd)
{
    uint8_t data = 0;
    data = ((bcd >> 4) & 0x0F) * 10 + (bcd & 0x0F);
    return data;
}

uint16_t tcp_socket::BCDtoHalfword(uint16_t bcd)
{
    uint16_t data = 0;
    data = ((bcd >> 12) & 0x0F) * 1000 + ((bcd >> 8) & 0x0F) * 100 + ((bcd >> 4) & 0x0F) * 10 + (bcd & 0x0F);
    return data;
}

uint32_t tcp_socket::wordToBcd(int32_t value)
{
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t BCD = 0;
    uint8_t f = (value > 0) ? 0 : 0x80;
    value = abs(value);
    A = B = C = D = E = F = G = H = 0;
    A = value / 10000000 % 10 * pow(16, 7);
    B = value / 1000000 % 10 * pow(16, 6);
    C = value / 100000 % 10 * pow(16, 5);
    D = value / 10000 % 10 * pow(16, 4);
    E = value / 1000 % 10 * pow(16, 3);
    F = value / 100 % 10 * pow(16, 2);
    G = value / 10 % 10 * pow(16, 1);
    H = value / 1 % 10 * pow(16, 0);
    BCD = A + B + C + D + E + F + G + H;

    BCD = BCD & 0x7FFFFFFF;
    BCD = BCD | (f << 24);
    return BCD;
}

uint32_t tcp_socket::wordTo3Bcd(int32_t value)
{
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t BCD = 0;
    uint8_t f = (value > 0) ? 0 : 0x80;
    value = abs(value);
    A = B = C = D = E = F = G = H = 0;
    A = value / 10000000 % 10 * pow(16, 7);
    B = value / 1000000 % 10 * pow(16, 6);
    C = value / 100000 % 10 * pow(16, 5);
    D = value / 10000 % 10 * pow(16, 4);
    E = value / 1000 % 10 * pow(16, 3);
    F = value / 100 % 10 * pow(16, 2);
    G = value / 10 % 10 * pow(16, 1);
    H = value / 1 % 10 * pow(16, 0);
    BCD = A + B + C + D + E + F + G + H;

    BCD = BCD & 0x00FFFFFF;
    BCD = BCD | (f << 16);

    return BCD;
}

uint32_t tcp_socket::uwordTo3Bcd(uint32_t value)
{
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t BCD = 0;
    A = B = C = D = E = F = G = H = 0;
    A = value / 10000000 % 10 * pow(16, 7);
    B = value / 1000000 % 10 * pow(16, 6);
    C = value / 100000 % 10 * pow(16, 5);
    D = value / 10000 % 10 * pow(16, 4);
    E = value / 1000 % 10 * pow(16, 3);
    F = value / 100 % 10 * pow(16, 2);
    G = value / 10 % 10 * pow(16, 1);
    H = value / 1 % 10 * pow(16, 0);
    BCD = A + B + C + D + E + F + G + H;
    BCD = 0x00FFFFFF;

    return BCD;
}

//len以半字节计数;plusMinus false表示最高字节最高位表示正负 true表示最高字节表示正负
int32_t tcp_socket::bcdToWord(QByteArray array, uint32_t index, uint8_t len, bool plusMinus)
{
    int32_t result = 0;
    uint32_t value;
    bool f = false;
    for (uint8_t i=0;i<len;i++) {
        if(i%2==0){
            value = ((uint8_t)array[index+i/2])&0x0F;
        }else{
            value = (((uint8_t)array[index+i/2])&0xF0)>>4;
        }

        if(i == len - 1){
            if(plusMinus){
                f = (value)?true:false;
                continue;
            }else{
                f = (value&0x08)?true:false;
                value &= 0x07;
            }
        }

        result += (value * pow(10, i));
    }

    return f?(-result):result;
}
//len以半字节计数;
uint32_t tcp_socket::bcdToUword(QByteArray array, uint32_t index, uint8_t len)
{
    uint32_t result = 0;
    uint32_t value;
    for (uint8_t i=0;i<len;i++) {
        if(i%2==0){
            value = ((uint8_t)array[index+i/2])&0x0F;
        }else{
            value = (((uint8_t)array[index+i/2])&0xF0)>>4;
        }

        result += (value * pow(10, i));
    }

    return result;
}

//非阻塞延迟，少用。。
void tcp_socket::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < _Timer )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

char tcp_socket::convertHexChart(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;  // 0x30 对应 ‘0’
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else
        return ch-ch;//不在0-f范围内的会发送成0
}

//数据转换 字符串转16进制
void tcp_socket::StringToHex(QString str, QByteArray &senddata)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = convertHexChart(hstr);
        lowhexdata = convertHexChart(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

void tcp_socket::report_SW_head_init()
{
    QByteArray station_addr = 0;
    report_SW_headhex->frame_Begin = 0x7E7E;
    report_SW_headhex->station_centerAddr = MainWindow::iniFile->value("/SW_PROTOCOL/Central_addr").toUInt();
    QString str_station_addr = MainWindow::iniFile->value("/SW_PROTOCOL/Station_addr").toString();
    StringToHex(str_station_addr,station_addr);
    report_SW_headhex->station_ycAddr[0] = station_addr[0];
    report_SW_headhex->station_ycAddr[1] = station_addr[1];
    report_SW_headhex->station_ycAddr[2] = station_addr[2];
    report_SW_headhex->station_ycAddr[3] = station_addr[3];
    report_SW_headhex->station_ycAddr[4] = station_addr[4];
    report_SW_headhex->password = MainWindow::iniFile->value("/SW_PROTOCOL/Password").toUInt();
    report_SW_headhex->fixed_report_minute = MainWindow::iniFile->value("/SW_PROTOCOL/Fixed_time").toUInt();
    report_SW_headhex->add_report_minute = MainWindow::iniFile->value("/SW_PROTOCOL/Add_time").toUInt();//加报时间间隔
    QString Element = MainWindow::iniFile->value("/SW_PROTOCOL/Element").toString();
    QByteArray upload_type;
    StringToHex(Element,upload_type);
    report_SW_headhex->uploadtype[0] = upload_type[0];
    report_SW_headhex->uploadtype[1] = upload_type[1];
    report_SW_headhex->uploadtype[2] = upload_type[2];
    report_SW_headhex->uploadtype[3] = upload_type[3];
    report_SW_headhex->uploadtype[4] = upload_type[4];
    report_SW_headhex->uploadtype[5] = upload_type[5];
    report_SW_headhex->uploadtype[6] = upload_type[6];
    report_SW_headhex->uploadtype[7] = upload_type[7];
    report_SW_headhex->report_send_add_time = QTime::currentTime();//上次发生加报报时间
    report_SW_headhex->report_fixed_flag = false;
    report_SW_headhex->report_fixed_count = 0;
    work_mode = 1;
    data_result.alarm_state_SW = 0;
}

void tcp_socket::report_SZY_head_init()
{
    QByteArray station_addr = 0;
    report_SZY_headhex->control_area = 0xB0;
    QString str_station_addr = MainWindow::iniFile->value("/SZY_PROTOCOL/Station_addr").toString();
    StringToHex(str_station_addr,station_addr);//水资源协议测站地址
    report_SZY_headhex->station_Addr_SZY[0] = station_addr[0];
    report_SZY_headhex->station_Addr_SZY[1] = station_addr[1];
    report_SZY_headhex->station_Addr_SZY[2] = station_addr[2];
    report_SZY_headhex->station_Addr_SZY[3] = station_addr[3];
    report_SZY_headhex->station_Addr_SZY[4] = station_addr[4];

    report_SZY_headhex->password = MainWindow::iniFile->value("/SZY_PROTOCOL/Password").toUInt();
    report_SZY_headhex->fixed_report_minute = MainWindow::iniFile->value("/SZY_PROTOCOL/Fixed_time").toUInt();
    report_SZY_headhex->uploadtype = MainWindow::iniFile->value("/SZY_PROTOCOL/Element").toUInt();
    report_SZY_headhex->uploadtype_count = 0;
    for(uint8_t i=0;i<16;i++)
    {
        if(report_SZY_headhex->uploadtype>>i&1)
            report_SZY_headhex->uploadtype_count ++;
    }
    for(uint8_t i=0;i<4;i++)
        tcp_comm[i].replytype_count = tcp_comm[i].reSend_replytype_count = report_SZY_headhex->uploadtype_count - 1;
    data_result.alarm_state_SZY = 0;
    report_SZY_headhex->report_fixed_flag =false;
    report_SZY_headhex->report_fixed_count = 0;
    data_result.alarm_state_SZY = data_result.alarm_state_SZY | 0x10000;//初始化工作模式为01自报模式
}

// 查询全部数据
void tcp_socket::queryTable(QString tableName)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec("SELECT * FROM " +tableName);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString mark = sqlQuery.value(1).toString();
            int data = sqlQuery.value(2).toInt();
            qDebug()<<QString("Bid:%1    mark:%2    data:%3").arg(id).arg(mark).arg(data);
        }
    }
}

// 查询指定数据
DATA_BASE2 tcp_socket::query_oneTable(QString tableName,QString data_time)
{
    DATA_BASE2 db_search;
    db_search.id = 0;
    db_search.data = 0;
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM " +tableName+ " WHERE mark = %1").arg(data_time));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            db_search.id = sqlQuery.value(0).toInt();
            db_search.mark = sqlQuery.value(1).toString();
            db_search.data = sqlQuery.value(2).toDouble();
            //qDebug()<<db_search.id<<db_search.mark<<db_search.data;
        }
    }
    return db_search;
}

// 插入单条数据
void tcp_socket::singleInsertData(QString table_name, DATA_BASE2 &singledb,QString alarmTXT)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.prepare("INSERT INTO " + table_name + " VALUES(:id,:mark,:data)");
    //sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":mark", singledb.mark);
    if(table_name == "Alarm")
        sqlQuery.bindValue(":data", alarmTXT);
    else
        sqlQuery.bindValue(":data", singledb.data);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

//插入补传数据
void tcp_socket::reSendInsertData(uint8_t tcpNum,QString mark,QString data)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.prepare(QString("INSERT INTO ReSendSW%1 VALUES(:id,:mark,:data)").arg(tcpNum));
    //sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":mark", mark);
    sqlQuery.bindValue(":data", data);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

//查询一行补传数据
bool tcp_socket::reSendQuery(uint8_t tcpNum)
{
    data_reSend.data = "";
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM ReSendSW%1 WHERE id = 1").arg(tcpNum));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            data_reSend.mark = sqlQuery.value(1).toString();
            data_reSend.data = sqlQuery.value(2).toString();
        }
    }
    if(data_reSend.data != "")
        return 1;
    else
        return 0;
}

bool tcp_socket::reSendQueryPoint(uint8_t tcpNum,QString mark)
{
    data_reSend.data = "";
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM ReSendSW%1 WHERE mark = %2").arg(tcpNum).arg(mark));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
//            data_reSend.mark = sqlQuery.value(1).toString();
            data_reSend.data = sqlQuery.value(2).toString();
        }
    }
    if(data_reSend.data != "")
        return 1;
    else
        return 0;
}

void tcp_socket::reSendDeletePoint(uint8_t tcpNum,QString mark)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM ReSendSW%1 WHERE mark = %2").arg(tcpNum).arg(mark));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            data_reSend.id = sqlQuery.value(0).toUInt();
//            data_reSend.mark = sqlQuery.value(1).toString();
//            data_reSend.data = sqlQuery.value(2).toString();
        }
    }

    sqlQuery.exec(QString("DELETE FROM ReSendSW%1 WHERE mark = %2").arg(tcpNum).arg(mark));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        //删除成功
    }
    if(data_reSend.id != 0)
    {
        sqlQuery.exec(QString("UPDATE ReSendSW%1 SET 'id'=(%2-1) WHERE id>%3").arg(tcpNum).arg(data_reSend.id).arg(data_reSend.id));
        sqlQuery.exec(QString("delete from sqlite_sequence where name = 'ReSendSW%1'").arg(tcpNum));//刷新
    }
}

void tcp_socket::reSendInsertData_SZY(uint8_t tcpNum,QString mark, uint8_t count, QString data)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.prepare(QString("INSERT INTO ReSendSZY%1 VALUES(:id,:mark,:count,:data)").arg(tcpNum));
    //sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":mark", mark);
    sqlQuery.bindValue(":count", count);
    sqlQuery.bindValue(":data", data);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

bool tcp_socket::reSendQuery_SZY(uint8_t tcpNum,uint8_t num)
{
    data_reSend.data = "";
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM ReSendSZY%1 WHERE id = %2").arg(tcpNum).arg(num));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            data_reSend.mark = sqlQuery.value(1).toString();
            for(uint8_t i=0;i<4;i++)
                tcp_comm[i].replytype_count = sqlQuery.value(2).toUInt();
            data_reSend.data = sqlQuery.value(3).toString();
        }
    }
    if(data_reSend.data != "")
        return 1;
    else
        return 0;
}

void tcp_socket::reSendDelete_SZY(uint8_t tcpNum)
{
    QSqlQuery sqlQuery(tcp_data_base);

    sqlQuery.exec(QString("DELETE FROM ReSendSZY%1 WHERE id = 1").arg(tcpNum));
    sqlQuery.exec(QString("UPDATE ReSendSZY%1 SET 'id'=(id-1) WHERE id>1").arg(tcpNum));
    sqlQuery.exec(QString("delete from sqlite_sequence where name = 'ReSendSZY%1'").arg(tcpNum));//刷新
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        //删除成功
    }
}

bool tcp_socket::reSendQueryPoint_SZY(uint8_t tcpNum,QString mark)
{
    data_reSend.data = "";
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM ReSendSZY%1 WHERE mark = %2").arg(tcpNum).arg(mark));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
//            data_reSend.mark = sqlQuery.value(1).toString();
            data_reSend.data = sqlQuery.value(3).toString();
        }
    }
    if(data_reSend.data != "")
        return 1;
    else
        return 0;
}

void tcp_socket::reSendDeletePoint_SZY(uint8_t tcpNum,QString mark)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("SELECT * FROM ReSendSZY%1 WHERE mark = %2").arg(tcpNum).arg(mark));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            data_reSend.id = sqlQuery.value(0).toUInt();
//            data_reSend.mark = sqlQuery.value(1).toString();
//            data_reSend.data = sqlQuery.value(3).toString();
        }
    }

    sqlQuery.exec(QString("DELETE FROM ReSendSZY%1 WHERE mark = %2").arg(tcpNum).arg(mark));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        //删除成功
    }
    if(data_reSend.id != 0)
    {
        sqlQuery.exec(QString("UPDATE ReSendSZY%1 SET 'id'=(%2-1) WHERE id>%3").arg(tcpNum).arg(data_reSend.id).arg(data_reSend.id));
        sqlQuery.exec(QString("delete from sqlite_sequence where name = 'ReSendSZY%1'").arg(tcpNum));//刷新
    }
}

void tcp_socket::timerTimeout_SZY_resend1()
{
    if(tcp_comm[0].tcp_busy == true)
        return;
    if((tcp_comm[0].reSend_type[1] == true) || (tcp_comm[0].reSend_flag[1] == true))//水资源补传
    {
        tcp_comm[0].reSend_send_count ++;
        if(reSendQuery_SZY(1,tcp_comm[0].reSend_send_count))//查询到补传数据
        {
            tcp_comm[0].reSend_flag[1] = true;
            QByteArray reSend_data;
            StringToHex(data_reSend.data,reSend_data);
            socket_Send(&tcp_comm[0],reSend_data,reSend_data.size());

            if(tcp_comm[0].reSend_send_count >= (report_SZY_headhex->uploadtype_count - 1))
            {
                tcp_comm[0].reSend_send_count = 0;
                timer5->stop();
            }
        }
        else
        {
            tcp_comm[0].reSend_flag[1] = false;
            timer5->stop();
        }
    }
}

void tcp_socket::timerTimeout_SZY_resend2()
{
    if(tcp_comm[1].tcp_busy == true)
        return;
    if((tcp_comm[1].reSend_type[1] == true) || (tcp_comm[1].reSend_flag[1] == true))//水资源补传
    {
        tcp_comm[1].reSend_send_count ++;
        if(reSendQuery_SZY(2,tcp_comm[1].reSend_send_count))//查询到补传数据
        {
            tcp_comm[1].reSend_flag[1] = true;
            QByteArray reSend_data;
            StringToHex(data_reSend.data,reSend_data);
            socket_Send(&tcp_comm[1],reSend_data,reSend_data.size());

            if(tcp_comm[1].reSend_send_count >= (report_SZY_headhex->uploadtype_count - 1))
            {
                tcp_comm[1].reSend_send_count = 0;
                timer6->stop();
            }
        }
        else
        {
            tcp_comm[1].reSend_flag[1] = false;
            timer6->stop();
        }
    }
}

void tcp_socket::timerTimeout_SZY_resend3()
{
    if(tcp_comm[2].tcp_busy == true)
        return;
    if((tcp_comm[2].reSend_type[1] == true) || (tcp_comm[2].reSend_flag[1] == true))//水资源补传
    {
        tcp_comm[2].reSend_send_count ++;
        if(reSendQuery_SZY(3,tcp_comm[2].reSend_send_count))//查询到补传数据
        {
            tcp_comm[2].reSend_flag[1] = true;
            QByteArray reSend_data;
            StringToHex(data_reSend.data,reSend_data);
            socket_Send(&tcp_comm[2],reSend_data,reSend_data.size());

            if(tcp_comm[2].reSend_send_count >= (report_SZY_headhex->uploadtype_count - 1))
            {
                tcp_comm[2].reSend_send_count = 0;
                timer7->stop();
            }
        }
        else
        {
            tcp_comm[2].reSend_flag[1] = false;
            timer7->stop();
        }
    }
}

void tcp_socket::timerTimeout_SZY_resend4()
{
    if(tcp_comm[3].tcp_busy == true)
        return;
    if((tcp_comm[3].reSend_type[1] == true) || (tcp_comm[3].reSend_flag[1] == true))//水资源补传
    {
        tcp_comm[3].reSend_send_count ++;
        if(reSendQuery_SZY(4,tcp_comm[3].reSend_send_count))//查询到补传数据
        {
            tcp_comm[3].reSend_flag[1] = true;
            QByteArray reSend_data;
            StringToHex(data_reSend.data,reSend_data);
            socket_Send(&tcp_comm[3],reSend_data,reSend_data.size());

            if(tcp_comm[3].reSend_send_count >= (report_SZY_headhex->uploadtype_count - 1))
            {
                tcp_comm[3].reSend_send_count = 0;
                timer8->stop();
            }
        }
        else
        {
            tcp_comm[3].reSend_flag[1] = false;
            timer8->stop();
        }
    }
}

//删除一行补传数据
void tcp_socket::reSendDelete(uint8_t tcpNum)
{
    QSqlQuery sqlQuery(tcp_data_base);

    sqlQuery.exec(QString("DELETE FROM ReSendSW%1 WHERE id = 1").arg(tcpNum));
    sqlQuery.exec(QString("UPDATE ReSendSW%1 SET 'id'=(id-1) WHERE id>1").arg(tcpNum));
    sqlQuery.exec(QString("delete from sqlite_sequence where name = 'ReSendSW%1'").arg(tcpNum));//刷新
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        //删除成功
    }
}

// 插入多条数据
void tcp_socket::moreInsertData(QString tableName,QList<DATA_BASE2>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.prepare("INSERT INTO " + tableName + " VALUES(?,?,?)");
    QVariantList idList,markList,dataList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        markList << moredb.at(i).mark;
        dataList << moredb.at(i).data;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(markList);
    sqlQuery.addBindValue(dataList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

// 修改数据
void tcp_socket::modifyData(QString tableName,DATA_BASE2 db)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.prepare("UPDATE " + tableName + " SET data=? WHERE mark=?");
    //sqlQuery.addBindValue(db.id);
    sqlQuery.addBindValue(db.data);
    sqlQuery.addBindValue(db.mark);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}


// 删除数据
void tcp_socket::deleteAllData(QString tableName)
{
    QSqlQuery sqlQuery(tcp_data_base);
    sqlQuery.exec(QString("DELETE FROM " +tableName));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

void tcp_socket::delete_AllData_Total(void)
{
    deleteAllData("Flow");
    deleteAllData("Water");
    deleteAllData("Rain");
    deleteAllData("Alarm");
    deleteAllData("Speed");
    deleteAllData("Rain_Total");
    deleteAllData("ReSendSW1");
    deleteAllData("ReSendSW2");
    deleteAllData("ReSendSW3");
    deleteAllData("ReSendSW4");
    deleteAllData("ReSendSZY1");
    deleteAllData("ReSendSZY2");
    deleteAllData("ReSendSZY3");
    deleteAllData("ReSendSZY4");
}

void tcp_socket::delete_ReSendData_Total()
{
    deleteAllData("ReSendSW1");
    deleteAllData("ReSendSW2");
    deleteAllData("ReSendSW3");
    deleteAllData("ReSendSW4");
    deleteAllData("ReSendSZY1");
    deleteAllData("ReSendSZY2");
    deleteAllData("ReSendSZY3");
    deleteAllData("ReSendSZY4");
}

// 删除数据
void tcp_socket::deleteData(QString tableName,int id)
{
    QSqlQuery sqlQuery(tcp_data_base);

    sqlQuery.exec(QString("DELETE FROM " +tableName+ " WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

//删除数据表
void tcp_socket::deleteTable(QString tableName)
{
    QSqlQuery sqlQuery(tcp_data_base);

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}
