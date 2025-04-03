#include "serialport.h"

//EXCEL操作
//#include "xlsxdocument.h"
//#include "xlsxchartsheet.h"
//#include "xlsxcellrange.h"
//#include "xlsxchart.h"
//#include "xlsxrichstring.h"
//#include "xlsxworkbook.h"

//引入JavaScript计算公式
//#include <QJSEngine>
#include <QMutex>
#include <QtMath>

extern KDY kdy;
extern CALCULATE_485 calculate_485[4];//水位、瞬时流量、累计流量、流速
extern QSerialPort *serial[7];
extern QMutex g_mutex;
uint8_t DI_Flag;//开入检测
extern uint8_t DO_Flag;//开出控制
uint16_t AI_data[6] = {0,0,0,0,0,0};//模入值
extern uint8_t AI_uint_select;//开入电流电压选择
extern float Rain_ratio;//雨量分辨力
COMM_CONFIG comm_config[5];//0:握手 1：开出 2：雨量 3：电流电压选择 4：雨量分辨力
Modbus modbus[5];//COM1~4 + LPC1778串口
DATA_RES data_result;
int rain_data_reset = 0;//LPC1778复位后的雨量计数保留

serialport::serialport(QObject *parent) :
    QThread(parent)
{
    QMutexLocker locker(&g_mutex);
    thread_serial_base=QSqlDatabase::addDatabase("QSQLITE","connect2");
    thread_serial_base.setDatabaseName(MainWindow::dbFile);
    thread_serial_base.open();

//    QXlsx::Document xlsx(QDir::currentPath() + "/home/test.xlsx");
//    QString A1 = xlsx.read("A1").toString();
//    qDebug() << "A1 = " << A1;
//    QString A2 = xlsx.read("A2").toString();
//    QString formula = xlsx.read("A3").toString();
//    QXlsx::Document xlsx1;
//    xlsx1.write("A1",45);
//    xlsx1.write("A2",A2.toUInt());
//    xlsx1.write("A3",formula);
//#ifdef ARM
//    xlsx.saveAs("/home/test.xlsx");
//#else
//    xlsx1.saveAs(QDir::currentPath() + "/home/test.xlsx");
//#endif
//    qDebug() << "NUM=" << xlsx1.cellAt("A3")->value().toString();

//    QJSEngine engine;
//    QJSValue value;
//    engine.evaluate("A1=1;A2=2");
//    value = engine.evaluate(xlsx.read("A3").toString().replace("=",""));
//    qDebug() << value.toString();

//    DATA_BASE1 DATA_BASE_Test1 = {1, "Uart_Addr1", 01};
//    DATA_BASE1 DATA_BASE_Test2 = {1, "20240102154530", 3305};
//    DATA_BASE1 DATA_BASE_Test3 = {1, "20240102154530", 82305};
//    DATA_BASE DATA_BASE_Test5 = {3, "20240102153830", 8888};
//    singleInsertData("Config",DATA_BASE_Test1);
//    singleInsertData("Flow",DATA_BASE_Test2);
//    singleInsertData("Water",DATA_BASE_Test3);

    timer =new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout_second()));//从0秒开始计时
    timer->start(1000);

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &serialport::serialport_receive_timeout);//串口接受处理
    timer1->start(100);

    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, &serialport::data_save_timeout);//5分钟数据存储

    timer3 = new QTimer(this);
    connect(timer3, &QTimer::timeout, this, &serialport::serialport_send_COM_timeout);//串口发送处理
    timer3->start(1000);

    modbus[4] = {0x02,//IO扩展板串口号，与1778通信不用Modbus，此处便于串口接收代码统一
                 0x00,//设备地址
                 0,//主从协议
                 {0x00,0x00},//数据标识符
                 {0x00,0x00},//功能码
                 {0x0000,0x0000},//寄存器地址
                 {0x0000,0x0000},//寄存器数量
                 {0x00,0x00},//数据类型
                 {0x00,0x00},//数据格式
                 {false,false},
                 0x00,//接收数据
                 0x00};//待通信处理数据

    QObject::connect(serial[1], &QSerialPort::readyRead, this, &serialport::serialport_recive_COM1);

    QObject::connect(serial[6], &QSerialPort::readyRead, this, &serialport::serialport_recive_COM2);
    QObject::connect(serial[3], &QSerialPort::readyRead, this, &serialport::serialport_recive_COM3);
    QObject::connect(serial[4], &QSerialPort::readyRead, this, &serialport::serialport_recive_COM4);
    QObject::connect(serial[2], &QSerialPort::readyRead, this, &serialport::serialport_recive_COM_LPC1778);
#ifdef ARM
    serial_send_connect();//与1778握手
#endif

    data_result.data_rain_history = query_NewestTable("Rain_Total").data;//开机查询累积雨量，便于数据叠加
    if(data_result.data_rain_history <= 0)
        data_result.data_rain_history = 0;
}

void serialport::timerTimeout_second()
{
    if(QTime::currentTime().second() == 0)
    {
        timer->stop();
        timer2->start(60000);
    }
}

void serialport::run()
{
    while(1)
    {
//        QApplication::processEvents();//防止死循环
//        //serial_send_test();
////        modifyData("student",2, "zhaoliu", 27);
////        queryTable("student");

//        QThread::sleep(1);
    }
}

void serialport::serialport_recive_COM1()
{
    modbus[0].recive_buf = serial[1]->readAll();
    modbus[0].recive_buf_com.append(modbus[0].recive_buf);
    modbus[0].recive_buf.clear();
}

void serialport::serialport_recive_COM2()
{
    modbus[1].recive_buf = serial[6]->readAll();
    modbus[1].recive_buf_com.append(modbus[1].recive_buf);
    modbus[1].recive_buf.clear();
}

void serialport::serialport_recive_COM3()
{
    modbus[2].recive_buf = serial[3]->readAll();
    modbus[2].recive_buf_com.append(modbus[2].recive_buf);
    modbus[2].recive_buf.clear();
}

void serialport::serialport_recive_COM4()
{
    modbus[3].recive_buf = serial[4]->readAll();
    modbus[3].recive_buf_com.append(modbus[3].recive_buf);
    modbus[3].recive_buf.clear();
}

void serialport::serialport_recive_COM_LPC1778()
{
    modbus[4].recive_buf = serial[2]->readAll();
    modbus[4].recive_buf_com.append(modbus[4].recive_buf);
    modbus[4].recive_buf.clear();
}

void serialport::serialport_receive_timeout()
{
    for(uint8_t i=0;i<5;i++)
    {
        if(modbus[i].recive_buf_com.size() >= 7)//Modbus通信单帧数据大于等于7个字节)
        {
            serialport_recive_Fun(modbus[i]);//COM1-4 + UART_LPC1778
            modbus[i].recive_buf_com.clear();
        }
    }
}

void serialport::data_save_timeout()
{
    if(QTime::currentTime().minute() % 5 == 0)//每5分钟记录一次数据
    {
        time_now_date = QDateTime::currentDateTime().toString("yyyyMMddHHmm");
        DATA_BASE1 DATA_BASE_Water = {1, time_now_date, data_result.data_water};
        singleInsertData("Water",DATA_BASE_Water);
        DATA_BASE1 DATA_BASE_Flow_Inst = {1, time_now_date, data_result.data_flow_inst};
        singleInsertData("Flow",DATA_BASE_Flow_Inst);
        DATA_BASE1 DATA_BASE_Flow_Speed = {1, time_now_date, data_result.data_flow_speed};
        singleInsertData("Speed",DATA_BASE_Flow_Speed);
        DATA_BASE1 DATA_BASE_Rain_Total = {1, time_now_date, data_result.data_rain_total};
        singleInsertData("Rain_Total",DATA_BASE_Rain_Total);

        //每天8点开始计算日降雨量
        Rain_time_day1 = QDateTime::currentDateTime().addSecs(-60 * 60 * 24).toString("yyyyMMdd") + "0800";//昨日8点
        Rain_time_day2 = QDateTime::currentDateTime().toString("yyyyMMdd") + "0800";//今日8点
        Rain_time_1h = QDateTime::currentDateTime().addSecs(-60 * 60 * 1).toString("yyyyMMddHHmm");
        Rain_time_3h = QDateTime::currentDateTime().addSecs(-60 * 60 * 3).toString("yyyyMMddHHmm");
        Rain_time_6h = QDateTime::currentDateTime().addSecs(-60 * 60 * 6).toString("yyyyMMddHHmm");
        Rain_time_12h = QDateTime::currentDateTime().addSecs(-60 * 60 * 12).toString("yyyyMMddHHmm");
        Rain_time_24h = QDateTime::currentDateTime().addSecs(-60 * 60 * 24).toString("yyyyMMddHHmm");
        Rain_time_48h = QDateTime::currentDateTime().addSecs(-60 * 60 * 48).toString("yyyyMMddHHmm");
        Rain_time_72h = QDateTime::currentDateTime().addSecs(-60 * 60 * 72).toString("yyyyMMddHHmm");

        //每天8点开始计算日降雨量
        if(QTime::currentTime().hour() >= 8)
        {
            data_result.data_rain_day = query_oneTable("Rain_Total",Rain_time_day2).data - query_oneTable("Rain_Total",Rain_time_day1).data;//日降雨量
            data_result.data_rain_inst = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_day2).data;//当前降雨量
        }
        else
        {
            data_result.data_rain_day = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_day1).data;//日降雨量
            data_result.data_rain_inst = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_day1).data;//当前降雨量
        }

        data_result.data_rain_1h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_1h).data;//1h降雨量
        data_result.data_rain_3h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_3h).data;
        data_result.data_rain_6h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_6h).data;
        data_result.data_rain_12h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_12h).data;
        data_result.data_rain_24h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_24h).data;
        data_result.data_rain_48h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_48h).data;
        data_result.data_rain_72h = data_result.data_rain_total - query_oneTable("Rain_Total",Rain_time_72h).data;

        if(data_result.data_rain_inst > data_result.data_rain_upper_limit_value)
        {
            emit tcp_alarm_signal(3);
        }
        //当前降雨量存数据库
        if(data_result.data_rain_inst < 0)
            data_result.data_rain_inst = 0;
        DATA_BASE1 DATA_BASE_Rain = {1, time_now_date, data_result.data_rain_inst};
        singleInsertData("Rain",DATA_BASE_Rain);
    }
}

void serialport::serialport_send_COM_timeout()
{
#ifdef ARM
    for(uint8_t i=0;i<4;i++)//COM1-3 + 开度仪
        serial_send_Modbus(i,modbus[i]);

    if(comm_receive_flag)//通信灯
    {
        if(led_comm_flag)
            system("echo 1 > /sys/class/leds/user-led-comm/brightness");
        else
        {
            system("echo 0 > /sys/class/leds/user-led-comm/brightness");
            comm_receive_flag = false;
        }
        led_comm_flag = !led_comm_flag;
    }
#else
    serial_send_Modbus(0,modbus[0]);
#endif
}

uint16_t BCDtoHalfword(uint16_t bcd)
{
    uint16_t data = 0;
    data = ((bcd >> 12) & 0x0F) * 1000 + ((bcd >> 8) & 0x0F) * 100 + ((bcd >> 4) & 0x0F) * 10 + (bcd & 0x0F);
    return data;
}

uint32_t BCDtoWord(uint32_t bcd)
{
    uint32_t data = 0;
    data = ((bcd >> 28) & 0x0F) * 10000000 + ((bcd >> 24) & 0x0F) * 1000000 + ((bcd >> 20) & 0x0F) * 100000 + ((bcd >> 16) & 0x0F) * 10000 + ((bcd >> 12) & 0x0F) * 1000 + ((bcd >> 8) & 0x0F) * 100 + ((bcd >> 4) & 0x0F) * 10 + (bcd & 0x0F);
    return data;
}

void serialport::serialport_recive_Fun(Modbus comm_modbus)
{
    uint8_t data_len = 0;
    int32_t data_res_int = 0;
    double data_res_float = 0;

    bool ok;
    if(!comm_modbus.recive_buf_com.isEmpty())
    {
        uint8_t H_CRC_Data,L_CRC_Data;
        QByteArray CrcCheck = comm_modbus.recive_buf_com.left(comm_modbus.recive_buf_com.size()-2);
        uint16_t CRC_Data=ModBusCRC16(CrcCheck);
        L_CRC_Data=CRC_Data & 0xff;
        H_CRC_Data=(CRC_Data>>8) & 0xff;
        if(L_CRC_Data == (unsigned char)comm_modbus.recive_buf_com[comm_modbus.recive_buf_com.size()-2] &&
           H_CRC_Data == (unsigned char)comm_modbus.recive_buf_com[comm_modbus.recive_buf_com.size()-1])//RCR校验通过
        {
            //与1778通信
            if(((unsigned char)comm_modbus.recive_buf_com.at(0) == comm_config[0].Head) && ((unsigned char)comm_modbus.recive_buf_com.at(1) == comm_config[0].Class))
            {
                switch (comm_modbus.recive_buf_com.at(3))
                {
                    //握手
                    case 0x00:
                        qDebug()<<"Receive LPC1778 Connect";
                        rain_data_reset = data_result.data_rain_total - data_result.data_rain_history;
                        if(rain_data_reset < 0)
                            rain_data_reset = 0;
                        serial_send_connect();//1778复位后，需要T113重新去握手
                    break;
                    //开入
                    case 0x01:
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x01)
                        {
                            if((comm_modbus.recive_buf_com.at(7) >> 0) & 1)
                                DI_Flag = DI_Flag | (1 << 0);
                            else
                                DI_Flag = DI_Flag & (~(1 << 0));

                            if((comm_modbus.recive_buf_com.at(7) >> 1) & 1)
                                DI_Flag = DI_Flag | (1 << 1);
                            else
                                DI_Flag = DI_Flag & (~(1 << 1));

                            if((comm_modbus.recive_buf_com.at(7) >> 2) & 1)
                                DI_Flag = DI_Flag | (1 << 2);
                            else
                                DI_Flag = DI_Flag & (~(1 << 2));

                            if((comm_modbus.recive_buf_com.at(7) >> 3) & 1)
                                DI_Flag = DI_Flag | (1 << 3);
                            else
                                DI_Flag = DI_Flag & (~(1 << 3));

                            if((comm_modbus.recive_buf_com.at(7) >> 4) & 1)
                                DI_Flag = DI_Flag | (1 << 4);
                            else
                                DI_Flag = DI_Flag & (~(1 << 4));
                        }
                    break;
                    //模入
                    case 0x02:
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x01)
                        {
                            AI_data[0] = BCDtoHalfword(((comm_modbus.recive_buf_com.at(7) << 8) & 0xFF00) + (comm_modbus.recive_buf_com.at(8) & 0x00FF));
                        }
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x02)
                        {
                            AI_data[1] = BCDtoHalfword(((comm_modbus.recive_buf_com.at(7) << 8) & 0xFF00) + (comm_modbus.recive_buf_com.at(8) & 0x00FF));
                        }
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x03)
                        {
                            AI_data[2] = BCDtoHalfword(((comm_modbus.recive_buf_com.at(7) << 8) & 0xFF00) + (comm_modbus.recive_buf_com.at(8) & 0x00FF));
                        }
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x04)
                        {
                            AI_data[3] = BCDtoHalfword(((comm_modbus.recive_buf_com.at(7) << 8) & 0xFF00) + (comm_modbus.recive_buf_com.at(8) & 0x00FF));
                        }
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x05)
                        {
                            AI_data[4] = BCDtoHalfword(((comm_modbus.recive_buf_com.at(7) << 8) & 0xFF00) + (comm_modbus.recive_buf_com.at(8) & 0x00FF));
                        }
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x06)
                        {
                            AI_data[5] = BCDtoHalfword(((comm_modbus.recive_buf_com.at(7) << 8) & 0xFF00) + (comm_modbus.recive_buf_com.at(8) & 0x00FF));
                        }
                    break;
                    //开出响应
                    case 0x03:
//                        qDebug()<<"AO Recive";
//                        if(recive_buf.at(4)==0x01)
//                        {
//                            qDebug()<<"AO OK";
//                        }
                    break;
                    //降雨量
                    case 0x04:
                        if((unsigned char)comm_modbus.recive_buf_com.at(4)==0x01)
                        {
                            QString str_res = comm_modbus.recive_buf_com.toHex().mid(14,8);
                            uint32_t Rain_data = str_res.toInt(&ok,16);
                            data_result.data_rain_total = data_result.data_rain_history + (float)(Rain_data * Rain_ratio) + rain_data_reset;//累计降雨量
                        }
                    break;
                    //模入电流电压选择
                    case 0x05:
//                        if(recive_buf.at(4)==0x01)
//                        {
//                            qDebug()<<"AI Select OK";
//                        }
                    break;
                    //雨量分辨力
//                    case 0x06:
//                        if(recive_buf.at(4)==0x01)
//                        {
//                            qDebug()<<"Rain Select OK";
//                        }
                    break;
                    default:
                    break;
                }
            }
            else//485通信
            {
                if(comm_receive_flag == false)
                    comm_receive_flag = true;
                if((unsigned char)comm_modbus.recive_buf_com.at(0) == comm_modbus.device_addr)
                {
                    if((unsigned char)comm_modbus.protocol == 0)//comm_modbus主站协议
                    {
                        for(uint8_t i=0;i<sizeof(comm_modbus.fun_code)/sizeof(comm_modbus.fun_code[0]);i++)
                        {
                            if(!comm_modbus.send_flag[i])//发送状态判断
                                continue;
                            if((unsigned char)comm_modbus.recive_buf_com.at(1) != comm_modbus.fun_code[i])//功能码
                                continue;
                            data_len = comm_modbus.recive_buf_com.at(2);//返回数据长度
                            if(comm_modbus.data_format[i] == 0)//高字节在前，低字节在后，正序（1234->1234）
                            {
                                if(comm_modbus.data_type[i] == 0)//整型
                                {
                                    if(data_len == 2)//短整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);
                                        QString str_res = str_res1 + str_res2;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                    if(data_len == 4)//长整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//1
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//2
                                        QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//3
                                        QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//4
                                        QString str_res = str_res1 + str_res2 + str_res3 + str_res4;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                }
                                else if(comm_modbus.data_type[i] == 1)//单精度浮点型
                                {
                                    QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//1
                                    QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//2
                                    QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//3
                                    QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//4

                                    QString str_res = str_res1 + str_res2 + str_res3 + str_res4;
                                    uint16_t res1 = str_res.mid(0,4).toUShort(&ok,16);
                                    uint16_t res2 = str_res.mid(4,4).toUShort(&ok,16);
                                    data_res_float = Int2Float(res1,res2);
                                }
                                else//BCD码
                                {
                                    QString str_res = comm_modbus.recive_buf_com.toHex().mid(6,data_len * 2);
                                    data_res_float = str_res.toFloat();
                                }
                            }
                            else if(comm_modbus.data_format[i] == 1)//高字节在前，低字节在后，反序（1234->2143）
                            {
                                if(comm_modbus.data_type[i] == 0)//整型
                                {
                                    if(data_len == 2)//短整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);
                                        QString str_res = str_res1 + str_res2;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                    if(data_len == 4)//长整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//2
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//1
                                        QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//4
                                        QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//3
                                        QString str_res = str_res2 + str_res1 + str_res4 + str_res3;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                }
                                else if(comm_modbus.data_type[i] == 1)//单精度浮点型
                                {
                                    QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//2
                                    QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//1
                                    QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//4
                                    QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//3

                                    QString str_res = str_res2 + str_res1 + str_res4 + str_res3;
                                    uint16_t res1 = str_res.mid(0,4).toUShort(&ok,16);
                                    uint16_t res2 = str_res.mid(4,4).toUShort(&ok,16);
                                    data_res_float = Int2Float(res1,res2);
                                }
                                else//BCD码
                                {
                                    QString str_res = comm_modbus.recive_buf_com.toHex().mid(6,data_len * 2);
                                    data_res_float = str_res.toFloat();
                                }
                            }
                            else if(comm_modbus.data_format[i] == 2)//低字节在前，高字节在后，正序（1234->3412）
                            {
                                if(comm_modbus.data_type[i] == 0)//整型
                                {
                                    if(data_len == 2)//短整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);
                                        QString str_res = str_res2 + str_res1;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                    if(data_len == 4)//长整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//3
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//4
                                        QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//1
                                        QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//2
                                        QString str_res = str_res3 + str_res4 + str_res1 + str_res2;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                }
                                else if(comm_modbus.data_type[i] == 1)//单精度浮点型
                                {
                                    QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//3
                                    QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//4
                                    QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//1
                                    QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//2
                                    QString str_res = str_res3 + str_res4 + str_res1 + str_res2;
                                    uint16_t res1 = str_res.mid(0,4).toUShort(&ok,16);
                                    uint16_t res2 = str_res.mid(4,4).toUShort(&ok,16);
                                    data_res_float = Int2Float(res1,res2);
                                }
                                else//BCD码
                                {
                                    QString str_res = comm_modbus.recive_buf_com.toHex().mid(6,data_len * 2);
                                    data_res_float = str_res.toFloat();
                                }
                            }
                            else//低字节在前，高字节在后，反序（1234->4321）
                            {
                                if(comm_modbus.data_type[i] == 0)//整型
                                {
                                    if(data_len == 2)//短整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);
                                        QString str_res = str_res2 + str_res1;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                    if(data_len == 4)//长整型
                                    {
                                        QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//4
                                        QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//3
                                        QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//2
                                        QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//1
                                        QString str_res = str_res4 + str_res3 + str_res2 + str_res1;
                                        data_res_int = str_res.toInt(&ok,16);
                                        if(!(str_res.at(0) >= '0' && str_res.at(0) <= '7'))//负数
                                        {
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除符号位
                                            data_res_int = ~ data_res_int;           //反码
                                            data_res_int = data_res_int & 0x7FFFFFFF;   //清除左边多余位
                                            data_res_int = data_res_int + 1;        //加1
                                            data_res_int = data_res_int * -1;         //符号位
                                        }
                                        data_res_float = data_res_int;
                                    }
                                }
                                else if(comm_modbus.data_type[i] == 1)//单精度浮点型
                                {
                                    QString str_res1 = comm_modbus.recive_buf_com.toHex().mid(6,2);//4
                                    QString str_res2 = comm_modbus.recive_buf_com.toHex().mid(8,2);//3
                                    QString str_res3 = comm_modbus.recive_buf_com.toHex().mid(10,2);//2
                                    QString str_res4 = comm_modbus.recive_buf_com.toHex().mid(12,2);//1
                                    QString str_res = str_res4 + str_res3 + str_res2 + str_res1;
                                    uint16_t res1 = str_res.mid(0,4).toUShort(&ok,16);
                                    uint16_t res2 = str_res.mid(4,4).toUShort(&ok,16);
                                    data_res_float = Int2Float(res1,res2);
                                }
                                else//BCD码
                                {
                                    QString str_res = comm_modbus.recive_buf_com.toHex().mid(6,data_len * 2);
                                    data_res_float = str_res.toFloat();
                                }
                            }

                            switch((unsigned char)comm_modbus.identify[i])
                            {
                                case 0x3B://水位
                                {
                                    comm_error_count[0] = 0;

                                    data_result.data_water = (data_res_float * calculate_485[0].multipy / calculate_485[0].divide + calculate_485[0].add - calculate_485[0].subtract) + data_result.data_water_base_value + data_result.data_water_modify_value;
#ifdef FLOOD_FLOW
                                    //泄洪流量计算公式：Q=σs * μ0 * e * n * b * sqrt(2gH0)

                                    if(kdy.unit == "mm")
                                        data_result.data_flood_flow = ((0.97-0.81*acos((6.5-data_result.data_kdy_value/1000)/9)/PI) - (0.56-0.81*acos((6.5-data_result.data_kdy_value/1000)/9)/PI) * data_result.data_kdy_value/1000/50) * data_result.data_kdy_value/1000 * 1 * 5 * sqrt(2 * 9.8 * (data_result.data_water-360));
                                    else
                                        data_result.data_flood_flow = ((0.97-0.81*acos((6.5-data_result.data_kdy_value/100)/9)/PI) - (0.56-0.81*acos((6.5-data_result.data_kdy_value/100)/9)/PI) * data_result.data_kdy_value/100/50) * data_result.data_kdy_value/100 * 1 * 5 * sqrt(2 * 9.8 * (data_result.data_water-360));
                                    if(qIsNaN(data_result.data_flood_flow))//计数错误
                                    {
                                        comm_error_count[6] ++;
                                        if(comm_error_count[6] > 3)
                                        {
                                            comm_error_count[6] = 0;
                                            data_result.data_flood_flow = 0;
                                        }
                                    }
#endif
                                    if(data_result.data_water > data_result.data_water_upper_limit_value)
                                    {
                                        data_result.alarm_state_SW = data_result.alarm_state_SW | (1 << 2);//水位超限告警
                                        data_result.alarm_state_SZY = data_result.alarm_state_SZY | (1 << 2);//水位超限告警
                                        emit tcp_alarm_signal(1);
                                    }
                                    else
                                    {
                                        data_result.alarm_state_SW = data_result.alarm_state_SW & (~(1 << 2));//水位超限告警取消
                                        data_result.alarm_state_SZY = data_result.alarm_state_SZY & (~(1 << 2));//水位超限告警取消
                                    }
                                    break;
                                }
                                case 0x27://瞬时流量
                                {
                                    comm_error_count[1] = 0;

                                    data_result.data_flow_inst = data_res_float * calculate_485[1].multipy / calculate_485[1].divide + calculate_485[1].add - calculate_485[1].subtract;
                                    if(data_result.data_flow_inst > data_result.data_flow_upper_limit_value)
                                    {
                                        data_result.alarm_state_SW = data_result.alarm_state_SW | (1 << 3);//流量超限告警
                                        data_result.alarm_state_SZY = data_result.alarm_state_SZY | (1 << 3);//流量超限告警
                                        emit tcp_alarm_signal(2);
                                    }
                                    else
                                    {
                                        data_result.alarm_state_SW = data_result.alarm_state_SW & (~(1 << 3));//水位超限告警取消
                                        data_result.alarm_state_SZY = data_result.alarm_state_SZY & (~(1 << 3));//水位超限告警取消
                                    }
                                    break;
                                }
                                case 0x76://累计流量
                                {
                                    comm_error_count[2] = 0;

                                    data_result.data_flow_total = data_res_float * calculate_485[2].multipy / calculate_485[2].divide + calculate_485[2].add - calculate_485[2].subtract;
                                    break;
                                }
                                case 0x37://流速
                                {
                                    comm_error_count[3] = 0;

                                    data_result.data_flow_speed = data_res_float * calculate_485[3].multipy / calculate_485[3].divide + calculate_485[3].add - calculate_485[3].subtract;
                                    if(data_result.data_flow_speed > data_result.data_speed_upper_limit_value)
                                        emit tcp_alarm_signal(4);
                                    break;
                                }
                                case 0xA1://开度值
                                    comm_error_count[4] = 0;

                                    data_result.data_kdy_value = data_res_float;
                                break;

                                case 0xA2://开度仪状态
                                    comm_error_count[5] = 0;

                                    data_result.data_kdy_state = data_res_float;
                                break;

                                default:
                                break;
                            }
                            if(((data_result.alarm_state_SW >> 2) & 1) || ((data_result.alarm_state_SW >> 3) & 1))
                                system("echo 1 > /sys/class/leds/user-led-alarm/brightness");
                            else
                                system("echo 0 > /sys/class/leds/user-led-alarm/brightness");
                            comm_modbus.send_flag[i] = false;//发送状态清除
                        }
                    }
                    else//从站协议
                    {
                        if((unsigned char)comm_modbus.recive_buf_com.at(1) == 0x03)//读数据功能码
                        {
                            QByteArray data_send,data_crc;
                            uint16_t crc16;

                            uint16_t regAddr = ((unsigned char)comm_modbus.recive_buf_com.at(2) << 8 & 0xffff) + (unsigned char)comm_modbus.recive_buf_com.at(3);
                            switch(regAddr)
                            {
                                case 0x01://电压
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = data_result.power_value * 100;
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                case 0x03://温度
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = 2650;//温度假值26.5℃
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                case 0x05://累计雨量
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = data_result.data_rain_total * 100;
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                case 0x07://日降雨量
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = data_result.data_rain_day * 100;
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                case 0x09://水位
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = data_result.data_water * 100;
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                case 0x0C://瞬时流量
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = data_result.data_flow_inst * 100;
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                case 0x0D://累计流量
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;
                                    uint32_t data = data_result.data_flow_total;
                                    data_send[3] = (data >> 8) & 0xff;
                                    data_send[4] = data  & 0xff;
                                    data_send[5] = (data >> 24) & 0xff;
                                    data_send[6] = (data >> 16) & 0xff;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//comm_modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;

                                default:
                                {
                                    data_send[0] = comm_modbus.device_addr;
                                    data_send[1] = (unsigned char)comm_modbus.recive_buf_com.at(1);
                                    data_send[2] = (unsigned char)comm_modbus.recive_buf_com.at(5) * 2;

                                    for(uint8_t i=0;i<data_send[2];i++)
                                        data_send[3 + i] = 0;

                                    crc16=ModBusCRC16(data_send);//计算CRC校验码
                                    data_crc[0] = crc16 & 0xff;//Modbus规定CRC低字节在前
                                    data_crc[1] = crc16>>8 & 0xff;

                                    serial[comm_modbus.serial_num]->write(data_send);//串口发送
                                    serial[comm_modbus.serial_num]->write(data_crc);//发送CRC校验码
                                }
                                break;
                            }
                        }
                    }

                }
            }
        }
    }
}

uint16_t serialport::ModBusCRC16(QByteArray data)
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

float serialport::Int2Float(uint16_t x1, uint16_t x2)
{
    int f, fRest, exponent, exponentRest;
    float value, weishu;
    f = x1 / 32768;
    fRest = x1 % 32768;
    exponent = fRest / 128;
    exponentRest = fRest % 128;
    weishu = (float)(exponentRest * 65536 + x2) / 8388608;
    value = (float)pow(-1, f) * (float)pow(2, exponent - 127) * (weishu + 1);
    return value;
}

void serialport::kdy_send_Modbus(int count)
{
    if(count == 1)//slave
        kdy_set_upLimit();
    else if(count == 2)//
        kdy_set_downLimit();
    else if(count == 3)//
        kdy_set_data();
    else if(count == 4)//
        kdy_set_time();
    else if(count == 5)//start
    {
        kdy_set_start();
    }
    else//stop
    {
        kdy_set_stop();
    }
}

void serialport::kdy_set_upLimit()
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    uint8_t fun_code = 0x06;
    uint16_t reg_addr =0x0005;
    uint16_t reg_count = kdy.upLimit;

    data_send[0]= modbus[3].device_addr;
    data_send[1]= fun_code;
    data_send[2]= (reg_addr >> 8) & 0xff;
    data_send[3]= reg_addr & 0xff;
    data_send[4]= (reg_count >> 8) & 0xff;
    data_send[5]= reg_count & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;

#ifdef ARM
    serial[modbus[3].serial_num]->write(data_send);//串口发送
    serial[modbus[3].serial_num]->write(data_crc);//发送CRC校验码
#endif
    qDebug()<<"dky="<<data_send.toHex();
}

void serialport::kdy_set_downLimit()
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    uint8_t fun_code = 0x06;
    uint16_t reg_addr =0x0006;
    uint16_t reg_count = kdy.downLimit;

    data_send[0]= modbus[3].device_addr;
    data_send[1]= fun_code;
    data_send[2]= (reg_addr >> 8) & 0xff;
    data_send[3]= reg_addr & 0xff;
    data_send[4]= (reg_count >> 8) & 0xff;
    data_send[5]= reg_count & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;
#ifdef ARM
    serial[modbus[3].serial_num]->write(data_send);//串口发送
    serial[modbus[3].serial_num]->write(data_crc);//发送CRC校验码
#endif
    qDebug()<<"dky="<<data_send.toHex();
}

void serialport::kdy_set_data()
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    uint8_t fun_code = 0x06;
    uint16_t reg_addr =0x0007;
    uint16_t reg_count = kdy.data;

    data_send[0]= modbus[3].device_addr;
    data_send[1]= fun_code;
    data_send[2]= (reg_addr >> 8) & 0xff;
    data_send[3]= reg_addr & 0xff;
    data_send[4]= (reg_count >> 8) & 0xff;
    data_send[5]= reg_count & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;
#ifdef ARM
    serial[modbus[3].serial_num]->write(data_send);//串口发送
    serial[modbus[3].serial_num]->write(data_crc);//发送CRC校验码
#endif
    qDebug()<<"dky="<<data_send.toHex();
    MainWindow::iniFile->setValue("/KDY/Data",kdy.data);
}

void serialport::kdy_set_time()
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    uint8_t fun_code = 0x06;
    uint16_t reg_addr =0x0008;
    uint16_t reg_count = kdy.time;

    data_send[0]= modbus[3].device_addr;
    data_send[1]= fun_code;
    data_send[2]= (reg_addr >> 8) & 0xff;
    data_send[3]= reg_addr & 0xff;
    data_send[4]= (reg_count >> 8) & 0xff;
    data_send[5]= reg_count & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;
#ifdef ARM
    serial[modbus[3].serial_num]->write(data_send);//串口发送
    serial[modbus[3].serial_num]->write(data_crc);//发送CRC校验码
#endif
    qDebug()<<"dky="<<data_send.toHex();
}

void serialport::kdy_set_start()
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    uint8_t fun_code = 0x06;
    uint16_t reg_addr =0x0004;
    uint16_t reg_count = 0x0100;

    data_send[0]= modbus[3].device_addr;
    data_send[1]= fun_code;
    data_send[2]= (reg_addr >> 8) & 0xff;
    data_send[3]= reg_addr & 0xff;
    data_send[4]= (reg_count >> 8) & 0xff;
    data_send[5]= reg_count & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;
#ifdef ARM
    serial[modbus[3].serial_num]->write(data_send);//串口发送
    serial[modbus[3].serial_num]->write(data_crc);//发送CRC校验码
#endif
    qDebug()<<"dky="<<data_send.toHex();
}

void serialport::kdy_set_stop()
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    uint8_t fun_code = 0x06;
    uint16_t reg_addr =0x0004;
    uint16_t reg_count = 0x0000;

    data_send[0]= modbus[3].device_addr;
    data_send[1]= fun_code;
    data_send[2]= (reg_addr >> 8) & 0xff;
    data_send[3]= reg_addr & 0xff;
    data_send[4]= (reg_count >> 8) & 0xff;
    data_send[5]= reg_count & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;
#ifdef ARM
    serial[modbus[3].serial_num]->write(data_send);//串口发送
    serial[modbus[3].serial_num]->write(data_crc);//发送CRC校验码
#endif
    qDebug()<<"dky="<<data_send.toHex();
}

void serialport::serial_send_Modbus(uint8_t number,Modbus COM_Modbus)
{
    QByteArray data_send,data_crc;
    uint16_t crc16;

    if(!(COM_Modbus.identify[modbus_count[number]] - 255))//Modbus.identify = 0xFF表示通道关闭
    {
        modbus_count[number] ++;
        if(modbus_count[number] >= sizeof(COM_Modbus.fun_code)/sizeof(COM_Modbus.fun_code[0]))
        {
            modbus_count[number] = 0;
            return;
        }
        return;
    }

    if(modbus_count[number] >= sizeof(COM_Modbus.fun_code)/sizeof(COM_Modbus.fun_code[0]))
        modbus_count[number] = 0;

    data_send[0]=COM_Modbus.device_addr;
    data_send[1]=COM_Modbus.fun_code[modbus_count[number]];
    data_send[2]=(COM_Modbus.reg_addr[modbus_count[number]] >> 8) & 0xff;
    data_send[3]=COM_Modbus.reg_addr[modbus_count[number]] & 0xff;
    data_send[4]=(COM_Modbus.reg_count[modbus_count[number]] >> 8) & 0xff;
    data_send[5]=COM_Modbus.reg_count[modbus_count[number]] & 0xff;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;//Modbus规定CRC低字节在前
    data_crc[1]=crc16>>8 & 0xff;

    serial[COM_Modbus.serial_num]->write(data_send);//串口发送
    serial[COM_Modbus.serial_num]->write(data_crc);//发送CRC校验码

    if(COM_Modbus.serial_num == 0x01)//此处不能直接用COM_Modbus.send_flag去处理,因为此函数会执行4次,导致重复叠加
    {
        modbus[0].send_flag[0] = false;
        modbus[0].send_flag[1] = false;
        modbus[0].send_flag[2] = false;
        modbus[0].send_flag[3] = false;
        modbus[0].send_flag[modbus_count[number]] = true;
    }
    else if(COM_Modbus.serial_num == 0x06)
    {
        modbus[1].send_flag[0] = false;
        modbus[1].send_flag[1] = false;
        modbus[1].send_flag[2] = false;
        modbus[1].send_flag[3] = false;
        modbus[1].send_flag[modbus_count[number]] = true;
    }
    else if(COM_Modbus.serial_num == 0x03)
    {
        modbus[2].send_flag[0] = false;
        modbus[2].send_flag[1] = false;
        modbus[2].send_flag[2] = false;
        modbus[2].send_flag[3] = false;
        modbus[2].send_flag[modbus_count[number]] = true;
    }
    else
    {
        modbus[3].send_flag[0] = false;
        modbus[3].send_flag[1] = false;
        modbus[3].send_flag[2] = false;
        modbus[3].send_flag[3] = false;
        modbus[3].send_flag[modbus_count[number]] = true;
    }

    //判断通信状态,通信异常将数据清零
    switch((unsigned char)COM_Modbus.identify[modbus_count[number]])
    {
        case 0x3B://水位
        {
            comm_error_count[0] ++;
            if(comm_error_count[0] > 3)
            {
                comm_error_count[0] = 0;
                data_result.data_water = 0;
#ifdef FLOOD_FLOW
                data_result.data_flood_flow = 0;
#endif
            }
            break;
        }
        case 0x27://瞬时流量
        {
            comm_error_count[1] ++;
            if(comm_error_count[1] > 3)
            {
                comm_error_count[1] = 0;
                data_result.data_flow_inst = 0;
            }
            break;
        }
        case 0x76://累计流量
        {
            comm_error_count[2] ++;
            if(comm_error_count[2] > 3)
            {
                comm_error_count[2] = 0;
                data_result.data_flow_total = 0;
            }
            break;
        }
        case 0x37://流速
        {
            comm_error_count[3] ++;
            if(comm_error_count[3] > 3)
            {
                comm_error_count[3] = 0;
                data_result.data_flow_speed = 0;
            }
            break;
        }
        case 0xA1://开度值
        {
            comm_error_count[4] ++;
            if(comm_error_count[4] > 3)
            {
                comm_error_count[4] = 0;
                data_result.data_kdy_value = 0;
            }
            break;
        }
        case 0xA2://开度仪状态
        {
            comm_error_count[5] ++;
            if(comm_error_count[5] > 3)
            {
                comm_error_count[5] = 0;
                data_result.data_kdy_state = 0;
            }
            break;
        }
        default:
            break;
    }

    modbus_count[number] ++;
}

void serialport::serial_send_connect()
{
    comm_config[0] = {0xAA,0x22,0x01,0x00,0x01,0x00,0x00};//握手
    serial_send_LPC1778(comm_config[0]);
    qDebug()<<"T113 Send Connect LPC1778";
    QThread::msleep(200);

    comm_config[1] = {0xAA,0x22,0x01,0x03,0x01,0x01,DO_Flag};//开出控制
    serial_send_LPC1778(comm_config[1]);
    QThread::msleep(200);

    comm_config[3] = {0xAA,0x22,0x01,0x05,0x01,0x01,AI_uint_select};//模入电压电流选择
    serial_send_LPC1778(comm_config[3]);
    QThread::msleep(200);
}

void serialport::serial_send_LPC1778(COMM_CONFIG comm_config)
{
    QByteArray data_send,data_crc;//data1为数据，data2为CRC校验码
    uint16_t crc16;

    data_send[0]=comm_config.Head;
    data_send[1]=comm_config.Class;
    data_send[2]=comm_config.Operate;
    data_send[3]=comm_config.Type;
    data_send[4]=comm_config.Subtype;

    data_send[5]=(comm_config.len >> 8) & 0xff;
    data_send[6]=comm_config.len & 0xff;
    if(comm_config.Operate == 0)//读数据
    {
        data_send[7] = 0x00;
        data_send[8] = 0x00;
    }
    if(comm_config.Operate == 1)//写数据
        data_send[7] = comm_config.data;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;
    data_crc[1]=crc16>>8 & 0xff;

    serial[2]->write(data_send);//串口发送头
    serial[2]->write(data_crc);//发送CRC校验码
    qDebug()<<"send_1778="<<data_send.toHex()<<data_crc.toHex();
}

// 查询全部数据
void serialport::queryTable(QString tableName)
{
    QSqlQuery sqlQuery(thread_serial_base);
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
            qDebug()<<QString("Cid:%1    mark:%2    data:%3").arg(id).arg(mark).arg(data);
        }
    }
}

// 查询指定行数据
DATA_BASE1 serialport::query_oneTable(QString tableName,QString data_time)
{
    DATA_BASE1 db_search;
    QSqlQuery sqlQuery(thread_serial_base);
    sqlQuery.exec(QString("SELECT * FROM " +tableName+ " WHERE mark = %1").arg(data_time));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
        if(tableName == "Rain_Total")
            db_search.data = data_result.data_rain_total;
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

DATA_BASE1 serialport::query_NewestTable(QString tableName)
{
    DATA_BASE1 db_search;

    QSqlQuery sqlQuery(thread_serial_base);
    //查询当前最大ID
    QString select_max_sql = "select max(id) from " + tableName;
    int max_id = 0;
    sqlQuery.prepare(select_max_sql);
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            max_id = sqlQuery.value(0).toInt();
        }
    }

    sqlQuery.exec(QString("SELECT * FROM " +tableName+ " WHERE id = %1").arg(max_id));
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
        }
    }
    return db_search;
}

// 插入单条数据
void serialport::singleInsertData(QString table_name, DATA_BASE1 &singledb)
{
    QSqlQuery sqlQuery(thread_serial_base);
    sqlQuery.prepare("INSERT INTO " + table_name + " VALUES(:id,:mark,:data)");
    //sqlQuery.bindValue(":id", NULL);
    sqlQuery.bindValue(":mark", singledb.mark);
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

// 插入多条数据
void serialport::moreInsertData(QString tableName,QList<DATA_BASE1>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery(thread_serial_base);
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
void serialport::modifyData(QString tableName,DATA_BASE1 db)
{
    QSqlQuery sqlQuery(thread_serial_base);
    sqlQuery.prepare("UPDATE " + tableName + " SET mark=?,data=? WHERE id=?");
    sqlQuery.addBindValue(db.mark);
    sqlQuery.addBindValue(db.data);
    sqlQuery.addBindValue(db.id);
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
void serialport::deleteData(QString tableName,int id)
{
    QSqlQuery sqlQuery(thread_serial_base);

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
void serialport::deleteTable(QString tableName)
{
    QSqlQuery sqlQuery(thread_serial_base);

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
