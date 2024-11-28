#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QThread>
#include <mainwindow.h>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <canshu_widget.h>

typedef struct
{
    uint8_t Head;//头
    uint8_t Class;//类
    uint8_t Operate;//操作码
    uint8_t Type;//类型码
    uint8_t Subtype;//子类型
    uint16_t len;//数据长度
    uint8_t data;//数据
}COMM_CONFIG;

typedef struct
{
    int id;
    QString mark;
    double data;
}DATA_BASE1;

typedef struct
{
    uint8_t serial_num;//串口号(1-4)
    uint8_t device_addr;//设备地址
    uint8_t protocol;//Modbus主/从协议（0：主站 1：从站）
    uint8_t identify[4];//数据标识符（水位0x3B、瞬时流量0x27、累计流量0x76、流速0x89、开度值A1、开度仪状态A2）
    uint8_t fun_code[4];//功能码（03读保持寄存器，04读输入寄存器，06写单个寄存器，16写多个寄存器）
    uint16_t reg_addr[4];//寄存器地址
    uint16_t reg_count[4];//寄存器数量
    uint8_t data_type[4];//数据类型（整型、4字节单精度浮点型、BCD码）
    uint8_t data_format[4];//数据格式（低前高后正序1234、高前低后正序3412）
    bool send_flag[4];//发送标记，由于接收判断
    QByteArray recive_buf;//接收数据
    QByteArray recive_buf_com;//待通信处理数据
}Modbus;

typedef struct
{
    double power_value;//电源电压
    double data_water;//水位数据
    double data_flow_speed;//流速数据
    double data_flow_inst;//瞬时流量数据
    double data_flow_total;//累计流量数据
    double data_rain_day;//日降雨量数据
    double data_rain_inst;//当前降雨量数据
    double data_rain_total;//累计雨量数据
    double data_rain_1h;//1h雨量数据
    double data_rain_3h;//3h雨量数据
    double data_rain_6h;//6h雨量数据
    double data_rain_12h;//12h雨量数据
    double data_rain_24h;//24h雨量数据
    double data_rain_48h;//48h雨量数据
    double data_rain_72h;//72h雨量数据
    double data_rain_history;//每次开机调取数据库存储的累积雨量

    double data_water_base_value;        // 水位基值
    double data_water_modify_value;      // 水位修正值
    double data_water_lower_limit_value; // 水位下限值=相对+基值
    double data_water_upper_limit_value; // 水位上限值=相对+基值

    double data_flow_lower_limit_value; // 流量下限值
    double data_flow_upper_limit_value; // 流量上限值

    double data_rain_lower_limit_value; // 雨量下限值
    double data_rain_upper_limit_value; // 雨量上限值

    double data_speed_lower_limit_value; // 流速下限值
    double data_speed_upper_limit_value; // 流速上限值

    uint16_t event[32];//事件记录
    //1 ERC1 历史数据初始化记录 2字节(事件触发的次数)
    //2 ERC2 参数变更记录 2字节
    //3 ERC3 状态量变位记录 2字节
    //4 ERC4 传感器及仪表故障记录 2字节
    //5 ERC5 密码修改记录 2字节
    //6 ERC6 终端故障记录 2字节
    //7 ERC7 交流失电记录 2字节
    //8 ERC8 蓄电池电压低告警记录 2字节
    //9 ERC9 终端箱非法打开记录 2字节
    //10 ERC10 水泵故障记录 2字节
    //11 ERC11 剩余水量超限告警记录 2字节
    //12 ERC12 水位超限告警记录 2字节
    //13 ERC13 水压超限告警记录 2字节
    //14 ERC14 水质参数超限告警记录 2字节
    //15 ERC15 数据出错记录 2字节
    //16 ERC16 发报文记录 2字节
    //17 ERC17 收报文记录 2字节
    //18 ERC18 发报文出错记录 2字节
    //19 ERC19～32 备用 2

    uint32_t alarm_state_SZY;// 报警种类和报警状态
    //水资源协议:
    // 前两字节（低字节） 报警种类和报警状态 各位0表示不报警，1报警
    // D0-工作交流电停电告警；D1-蓄电池电压报警；D2-水位超限报警；D3-流量超限报警；
    // D4-水质超限报警；D5-流量仪表故障报警；D6—水泵开停状态；D7—水位仪表故障报警；
    // D8—水压超限报警；D9—备用；D10—终端 IC 卡功能报警；D11—定值控制报警；
    // D12—剩余水量的下限报警；D13—终端箱门状态报警；D14—D15 备用。

    // 后两字节（高字节） 遥测终端状态
    // D0，D1—终端的工作模式。00H，终端在自报、遥测工作状态(对应上位机“兼容工作状态”)；
    //                      01H，终端在自报确认工作状态(对应上位机“自报工作状态”)；
    //                      02H，终端在遥测工作状态(对应上位机“查询/应答工作状态”)；
    //                      03H，终端在调试或维修状态(对应上位机“调试/维修状态”)。
    // D2—终端 IC 卡功能是否有效。0：无效；1：有效。
    // D3—定值控制是否投入。0：退出；1：投入。
    // D4—水泵工作状态。 0：启动；1：停止。
    // D5—终端箱门状态。0：开启；1：关闭。
    // D6—电源工作状态。0：AC220V 供电；1：蓄电池供电。
    // D7—D15 备用。

    uint32_t alarm_state_SW;// 报警种类和报警状态
    //水文协议:
    //交流电充电状态 BIT0 0：正常；1：停电
    //蓄电池电压状态 BIT1 0：正常；1：电压低
    //水位超限报警状态 BIT2 0：正常；1：报警
    //流量超限报警状态 BIT3 0：正常；1：报警
    //水质超限报警状态 BIT4 0：正常；1：报警
    //流量仪表状态 BIT5 0：正常；1：故障
    //水位仪表状态 BIT6 0：正常；1：故障
    //终端箱门状态 BIT7 0：开启；1：关闭
    //存储器状态 BIT8 0：正常；1：异常
    //IC 卡功能有效 BIT9 0：关闭；1：IC 卡有效
    //水泵工作状态 BIT10 0：水泵工作；1：水泵停机
    //剩余水量报警 BIT11 0：未超限；1：水量超限
    //保留 BIT12～31

    double data_kdy_value;//开度仪数据
    uint16_t data_kdy_state;//开度仪状态//bit0:全开、bit1:全关、bit2:上升、bit3:下降、bit8:自动、bit11:故障

    double data_flood_flow;//泄洪流量数据
}DATA_RES;

class serialport : public QThread
{
    Q_OBJECT
public:
    explicit serialport(QObject *parent = 0);

    uint8_t time_count = 0;//time计数
    DATA_BASE1 db2;

public slots:
    void timerTimeout_second();
    /*CRC校验函数*/
    uint16_t ModBusCRC16(QByteArray data);
    float Int2Float(uint16_t x1, uint16_t x2);//4字节Modbus转浮点数
    void kdy_send_Modbus(int);
    void kdy_set_upLimit();
    void kdy_set_downLimit();
    void kdy_set_data();
    void kdy_set_time();
    void kdy_set_start();
    void kdy_set_stop();

    void serial_send_Modbus(uint8_t number,Modbus COM_Modbus);
    void serial_send_LPC1778(COMM_CONFIG comm_config);
    void serial_send_connect();
    void serialport_recive_COM1();
    void serialport_recive_COM2();
    void serialport_recive_COM3();
    void serialport_recive_COM4();
    void serialport_recive_COM_LPC1778();
    void serialport_recive_Fun(Modbus modbus);//serial_num=0~5(COM1~4、COM_1778)
    void serialport_receive_timeout();
    void data_save_timeout();
    void serialport_send_COM_timeout();
    // 查询全部数据
    void queryTable(QString tableName);
    // 查询指定行数据
    DATA_BASE1 query_oneTable(QString tableName,QString data_time);
    //查询最新数据
    DATA_BASE1 query_NewestTable(QString tableName);
    // 插入数据
    void singleInsertData(QString table_name,DATA_BASE1 &singleData); // 插入单条数据
    void moreInsertData(QString tableName,QList<DATA_BASE1> &moreData); // 插入多条数据
    // 修改数据
    void modifyData(QString tableName,DATA_BASE1 db);
    // 删除数据
    void deleteData(QString tableName,int id);
    //删除数据表
    void deleteTable(QString tableName);

private:
    virtual void run();//任务处理线程
    QSqlDatabase thread_serial_base;// 用于建立和数据库的连接
    QTimer *timer,*timer1,*timer2,*timer3;
    bool comm_receive_flag = false;
    bool led_comm_flag = true;
    QString time_now_date = "";//日期时间
    uint8_t modbus_count[4] = {0,0,0,0};
    QString Rain_time_day1,Rain_time_day2,Rain_time_1h,Rain_time_3h,Rain_time_6h,Rain_time_12h,Rain_time_24h,Rain_time_48h,Rain_time_72h;//降雨量计算时间
    uint8_t comm_error_count[7];//通信异常计数，由于处理通信异常清零[水位、瞬时流量、累计流量、流速、开度值、开度仪状态、泄洪流量]
signals:
    void tcp_alarm_signal(int);//超阈值告警信号
};

#endif // DATA_THREAD_H
