#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QLabel>

//取消，linux编译不了<Windows.h>
//#if ARM
//#else
//    #include <Windows.h>
//#endif

#include "sqlite.h"
#include "mainwindow.h"

//水文协议报文帧控制字字符定义
#define SOHA  0x01     //ASCII字符编码报文帧起始
#define SOHH  0x7E7E   //HEX/BCD编码报文帧起始
#define STX   0x02     //传输正文起始
#define SYN   0x16     //多包传输正文起始
#define ETX   0x03     //报文结束，后续无报文
#define ETB   0x17     //报文结束，后续有报文
#define ENQ   0x05     //询问
#define EOT   0x04     //传输结束，退出
#define ACK   0x06     //肯定确认，继续发送
#define ACKQ  0x16     //肯定确认，继续发送
#define NAK   0x15     //否定应答，反馈重发
#define ESC   0x1B     //传输结束，终端保持在线

//水文协议功能码定义
#define FC_REPORT_LINK_MT             0x2F     //链路维持报
#define FC_REPORT_TEST                0x30     //测试报
#define FC_REPORT_UNIFORM_TIME        0x31     //均匀时段水文信息报
#define FC_REPORT_ON_TIME             0x32     //遥测站定时报
#define FC_REPORT_ADD_REPORT          0x33     //遥测站加报报
#define FC_REPORT_HOUR                0x34     //遥测站小时报
#define FC_REPORT_MANUAL_WORK         0x35     //遥测站人工置数报
#define FC_REPORT_QUERY_PIC	          0x36     //遥测站图片报/中心站查询遥测站图片采集信息
#define FC_QUERY_REALTIME_DATA        0x37     //中心站查询遥测站实时数据
#define FC_QUERY_PERIOD_DATA          0x38     //中心站查询遥测站时段数据
#define FC_QUERY_MANUAL_WORK          0x39     //中心站查询遥测站人工置数
#define FC_QUERY_APPOINT_ELEMENT      0x3A     //中心站查询遥测站指定要素数
#define FC_MODIFY_BASIC_SET           0x40     //中心站修改遥测站基本配置表
#define FC_REPORT_READ_BASIC_SET      0x41     //中心站查询遥测站基本配置表/遥测站自报基本配置表
#define FC_MODIFY_RUNNING_SET         0x42     //中心站修改遥测站运行参数配置表
#define FC_REPORT_READ_RUNNING_SET    0x43     //中心站查询遥测站运行参数配置表/遥测站自报运行参数配置表
#define FC_QUERY_PUMP_DATA            0x44     //查询水泵电机实时工作数据
#define FC_QUERY_SOFT_VERSION         0x45     //查询遥测终端软件版本
#define FC_QUERY_STATUS	              0x46	   //查询遥测站状态和报警信息
#define FC_INIT_DATA                  0x47	   //初始化固态存储数据
#define FC_RESTORE_SETTING            0x48	   //恢复终端出厂设置
#define FC_SET_PASSWORD               0x49	   //修改密码
#define FC_SET_CLOCK                  0x4A	   //设置遥测站时钟
#define FC_SET_IC_STATUS              0x4B	   //设置遥测终端IC卡状态
#define FC_REPORT_PUMP_SWITH_CMD      0x4C	   //控制水泵开关命令/水泵状态信息自报
#define FC_REPORT_VALVE_SWITH_CMD     0x4D	   //控制阀门开关命令/阀门状态信息自报
#define FC_REPORT_GATE_SWITH_CMD      0x4E	   //控制闸门开关命令/闸门状态信息自报
#define FC_WATER_YIELD_CMD            0x4F	   //水量定值控制命令
#define FC_QUERY_EVENT                0x50	   //中心站查询遥测站事件记录
#define FC_QUERY_CLOCK	              0x51	   //中心站查询遥测站时钟
#define FC_WELL_REPORT_FIXED          0xE0	   //机井定点报
#define FC_WELL_REPORT_OPENPUMP       0xE1     //机井开泵报
#define FC_WELL_REPORT_CLOSEPUMP      0xE2	   //机井开关报
#define FC_REPORT_GATE_STOP_CMD       0xE3	   //控制闸门停止命令
#define FC_WATER_LEVEL_T0_FLOW		  0xE5	   //水位/有功功率变为流量的5个定值命令

//水文协议遥测站分类码
#define STATION_TYPE_RAIN_FALL        0x50     //降水
#define STATION_TYPE_RESERVOIR        0x4B     //水库
#define STATION_TYPE_GATE_DAM         0x5A     //闸坝

//水文协议要素标识符定义
#define ELEMENT_IDENTI_VOL_LEVEL	  0x38			//电压
#define ELEMENT_IDENTI_WATER_LEVEL_HEDAO	0x39	//瞬时河道水位
#define ELEMENT_IDENTI_WATER_LEVEL    0x3B			//水位
#define ELEMENT_IDENTI_FLOW_SPEED	  0x37			//流速
#define ELEMENT_IDENTI_FLOW_INST	  0x27			//瞬时流量
#define ELEMENT_IDENTI_FLOW_TOTAL     0x76			//累计流量
#define ELEMENT_IDENTI_PRECIP_DAY	  0x1F			//日降水量
#define ELEMENT_IDENTI_PRECIP_INST	  0x20			//当前降水量
#define ELEMENT_IDENTI_PRECIP_TOTAL   0x26			//累计降水量
#define ELEMENT_IDENTI_PRECIP_5MIN    0x22			//5分钟降水量
#define ELEMENT_IDENTI_PRECIP_1H      0x1A			//1小时降水量
#define ELEMENT_IDENTI_PRECIP_3H      0x1C			//3小时降水量
#define ELEMENT_IDENTI_PRECIP_6H      0x1D			//6小时降水量
#define ELEMENT_IDENTI_PRECIP_12H     0x1E			//12小时降水量
#define ELEMENT_IDENTI_PRECIP_24H     0x90			//24小时降水量
#define ELEMENT_IDENTI_PRECIP_48H     0x91			//48小时降水量
#define ELEMENT_IDENTI_PRECIP_72H     0x92			//72小时降水量
#define ELEMENT_IDENTI_ALARM          0x45			//告警信息
#define ELEMENT_IDENTI_A_Voltage      0x70          //交流A相电压
#define ELEMENT_IDENTI_B_Voltage      0x71          //交流B相电压
#define ELEMENT_IDENTI_C_Voltage      0x72          //交流C相电压
#define ELEMENT_IDENTI_A_current      0x73          //交流A相电流
#define ELEMENT_IDENTI_B_current      0x74          //交流B相电流
#define ELEMENT_IDENTI_C_current      0x75          //交流C相电流
#define ELEMENT_IDENTI_KDY            0x79			//新世杰自定义开度值
#define ELEMENT_IDENTI_HOUR_RAIN      0xF4			//1小时内每5分钟时段雨量
#define ELEMENT_IDENTI_HOUR_WATER     0xF5			//1小时内每5分钟时段水位

//水资源协议功能码
#define  CONFIRM                0x00     //确认
#define  REPORT_RAINFALL        0x01     //雨量参数
#define  REPORT_WATE_LEVEL      0x02     //水位参数
#define  REPORT_FLOW_WATER	    0x03     //流量参数
#define  REPORT_VELOCITY_WATER  0x04     //流速参数
#define  REPORT_GATE_LOCATION   0x05     //闸位参数
#define  REPORT_POWER           0x06     //功率参数
#define  REPORT_AIR_PRESSURE    0x07     //气压参数
#define  REPORT_WIND_SPEED      0x08     //风速参数
#define  REPORT_WATER_TEMP      0x09     //水温参数
#define  REPORT_WATER_QUALITY   0x0A     //水质参数
#define  REPORT_SIOIL_WATER     0x0B     //土壤含水率参数
#define  REPORT_EVAPORATION     0x0C     //蒸发量参数
#define  REPORT_ALERT_OR_STATE  0x0D     //报警或状态参数
#define  REPORT_COMPREHENSIVE   0x0E     //统计雨量
#define  REPORT_HYDRAULIC       0X0F     //水压参数

//水资源协议控制域
#define  DIR_MASK               0x80     //上行帧
#define  DIV_FLAG               0x40     //拆分标志
#define  FCB_MASK               0x30     //帧计数
#define  FUNCTION_MASK          0x0F     //功能码

//维护平台新世杰协议
typedef struct
{
    uint16_t frame_Begin; //帧起始符
    uint8_t fun_code;     //功能码
    uint16_t device_num;  //设备编号
    QFile *file_info;   //文件信息
    QString file_path;   //文件路径
    uint32_t file_size;  //文件大小
    uint32_t send_size;//每包字节数
    uint32_t load_size;//已发送字节数
    bool fun_flag[6];     //功能标志位
}MAINTENANCE;

//水文协议配置
typedef struct
{
    uint16_t frame_Begin;       //帧起始符
    uint8_t station_centerAddr;     //中心站地址
    uint8_t station_ycAddr[5];      //遥测站地址
    uint16_t password;             //密码
    uint8_t uploadtype[8];            //上报种类 要素配置
    /*监测流量：20000000000
    监测水位、流量：1020000000000
    监测雨量、水位、流量：8001020000000000
    监测雨量、水位、闸门开度、流量：8001120000000000
    监测雨量、水位、闸门开度、流速、流量：8001160000000000*/

    uint8_t fixed_report_minute;//定时报时间间隔
    uint8_t add_report_minute;//加报报时间间隔
    bool report_fixed_flag = false;//发送定时报标志
    QTime report_send_add_time;//发送加报报时间
    uint8_t report_fixed_count = 0;//定时报循环计数
    bool report_type_select[2];//均匀时段报和小时报是否上报选择
}REPORT_HEADHEX_SW;

//ASCII编码帧头
typedef struct
{
    uint8_t frameBeginFlag;           //帧起始符
    uint8_t stationCenterAddr[2];     //中心站地址
    uint8_t stationYCAddr[10];        //遥测站地址
    char password[4];                 //密码
}REPORT_HEAD_ASCII;

//水资源协议配置
typedef struct
{
    uint8_t control_area;//控制域
    uint8_t station_Addr_SZY[5];    //水资源协议地址域
    uint16_t password;              //密码
    uint16_t uploadtype;            //上报种类
    uint8_t uploadtype_count = 0;//上报种类计数
#define SZY_UPLOAD_TYPE_MASK    0x100F  //上报种类掩码，bit15-0：备用 备用 水压 报警信息 蒸发量 土壤含水率 水质 水温 风速 气压 功率 闸门 流速 流量 水位 雨量
                                        //4111 = 0x100F = 0001 0000 0000 1111（雨量、水位、流量、流速、报警信息）
                                        //4100 = 0x1004 = 0001 0000 0000 0100（流量、报警信息）
    uint8_t fixed_report_minute;//定时报时间间隔
    bool report_fixed_flag = false;//发送定时报标志
    uint8_t report_fixed_count = 0;//定时报循环计数
}REPORT_HEADHEX_SZY;

typedef struct
{
    int id;
    QString mark;
    double data;
}DATA_BASE2;

typedef struct
{
    int id;
    QString mark;
    QString data;
}DATA_RESEND;

typedef struct
{
    uint8_t numTcp;//编号1-5
    QString ip;
    int port;
    QTcpSocket *TCP_Socket;
    QByteArray recive_buf;
    QByteArray recive_buf_comm;
    uint8_t socket_agreement;//协议选择 0水文 1水资源
    bool socket_flag;
    bool socket_select;//是否需要连
    uint16_t send_num;//报文流水号
    bool tcp_busy;
    bool tcp_onLine;//在线标志
    int8_t noReply_count = 0;//定时报无回复计数
    QDateTime tcp_onLineTime;//在线时间

    bool reSend_flag[2] = {false,false};//补传状态[水文定时报、水资源定时报]（true=补传中）
    bool reSend_type[2] = {false,false};//报文补传类型[水文定时报、水资源定时报]

    int8_t replytype_count = 0;//水资源定时报响应计数
    int8_t reSend_replytype_count = 0;//水资源补传定时报响应计数
    int8_t reSend_send_count = 0;//水资源补传定时报发送计数
}TCP_COMM;

//图片发送
typedef struct
{
    uint8_t socket_agreement;//水文水资源协议选择
    uint32_t pic_file_size;
    uint32_t send_size;//每包字节数
    uint16_t pack_total;//总包数
    uint16_t pack_no;//当前包序号
    uint32_t load_size;//已发送字节数
    QFile *pic_file;
}PIC_SEND;

class tcp_socket : public QWidget
{
    Q_OBJECT

public:
    explicit tcp_socket(QWidget *parent = nullptr);
    ~tcp_socket();
signals:
    //水文协议信号
    void uploadTime(uint8_t);
    void uploadPassword(QString);
    void kdy_signal(int);
    void uploadBaseSet(int);
    void uploadRunSet(int);

public slots:

    void Wifi_Connected();
    void Wifi_Disconnected();
    void Wifi_Read_Data();
    void socket_Connect(TCP_COMM *tcp_comm);
    static void socket_init();
    void socket_Send(TCP_COMM *tcp_comm, QByteArray send_data,uint32_t len);
    void socket_Close(TCP_COMM *tcp_comm);
    void socket1_Connected();
    void socket2_Connected();
    void socket3_Connected();
    void socket4_Connected();
    void socket5_Connected();
    void socket1_Disconnected();
    void socket2_Disconnected();
    void socket3_Disconnected();
    void socket4_Disconnected();
    void socket5_Disconnected();
    void socket1_Read_Data();
    void socket2_Read_Data();
    void socket3_Read_Data();
    void socket4_Read_Data();
    void socket5_Read_Data();
    void socket_comm_fun(TCP_COMM *tcp_comm);
    QString floatToBCD(float number);//float转为BCD码
    // 查询全部数据
    void queryTable(QString tableName);
    // 查询指定数据
    DATA_BASE2 query_oneTable(QString tableName,QString data_time);
    // 插入数据
    void singleInsertData(QString table_name,DATA_BASE2 &singleData,QString alarmTXT); // 插入单条数据
    void moreInsertData(QString tableName,QList<DATA_BASE2> &moreData); // 插入多条数据
    // 修改数据
    void modifyData(QString tableName,DATA_BASE2 db);
    // 删除数据
    void deleteAllData(QString tableName);
    // 删除所有数据
    void delete_AllData_Total(void);
    // 删除补传数据
    void delete_ReSendData_Total(void);
    // 删除数据
    void deleteData(QString tableName,int id);
    //删除数据表
    void deleteTable(QString tableName);

    void reSendInsertData(uint8_t tcpNum,QString mark,QString data);//插入补传数据
    bool reSendQuery(uint8_t tcpNum);//查询第一行补传数据
    void reSendDelete(uint8_t tcpNum);//删除第一行补传数据
    bool reSendQueryPoint(uint8_t tcpNum,QString mark);//查询指定行补传数据
    void reSendDeletePoint(uint8_t tcpNum,QString mark);//删除指定行补传数据

    void reSendInsertData_SZY(uint8_t tcpNum,QString mark,uint8_t count,QString data);//插入水资源补传数据
    bool reSendQuery_SZY(uint8_t tcpNum,uint8_t num);//查询指定行补传数据
    void reSendDelete_SZY(uint8_t tcpNum);//删除第一行补传数据
    bool reSendQueryPoint_SZY(uint8_t tcpNum,QString mark);//查询指定时间补传数据
    void reSendDeletePoint_SZY(uint8_t tcpNum,QString mark);//删除指定行补传数据
    void timerTimeout_SZY_resend1();//水资源补传函数
    void timerTimeout_SZY_resend2();//水资源补传函数
    void timerTimeout_SZY_resend3();//水资源补传函数
    void timerTimeout_SZY_resend4();//水资源补传函数
private:
    QSqlDatabase tcp_data_base;// 用于建立和数据库的连接
    QLabel *updata_label;
    QTimer *timer,*timer1,*timer2,*timer3,*timer4,*timer5,*timer6,*timer7,*timer8;
    uint8_t work_mode;
    uint32_t fileComm_UIcount = 0;//用于远程升级进度条
    QProgressBar *pProgressBar;//升级进度条

    QTcpSocket *Wifi_Socket;
    QTcpServer* Wifi_Server;

private slots:
    void report_SW_head_init();
    void report_SZY_head_init();
    void timerTimeout_second();
    void Timeout_second_picture();
    void Timeout_send_maintenance_file();
    void timerTimeout_minute();
    void maintenance_link();//维护平台
    void Factory_Config_Reset(TCP_COMM *Tcp_comm);//恢复出厂设置
    void Store_Data_Reset(TCP_COMM *Tcp_comm);//初始化固态数据
    void check_time(TCP_COMM *Tcp_comm);//校时
    void report_fixed_time(uint8_t socket_agreement);//定时报

    void report_SW_link(TCP_COMM *Tcp_comm);//水文协议 连接成功时自报链路报
    void report_SW_link();//水文协议 自报链路报
    void report_SW_test();//水文协议 自报测试报
    void report_SW_uniform_time(uint8_t fun_code,uint8_t type);//水文协议 自报均匀时段水文信息报
    void report_SW_fixed_time(uint8_t fun_code);//水文协议 自报定时报
    void report_SW_add();//水文协议 自报加报报
    void report_SW_hour();//水文协议 自报小时报
    void report_SW_Manual_Work();//水文协议 自报人工置数报
    void report_SW_fixedPicture(QString dir_pic);//水文协议 图片定时报

    void report_SW_Ask_Water_PumpPara(TCP_COMM *Tcp_comm);//查询水泵电机数据
    void report_SW_Set_ICstate(TCP_COMM *Tcp_comm,uint32_t state);//设置遥测站IC卡状态
    void report_SW_Set_Water_Pumpstate(TCP_COMM *Tcp_comm,uint16_t state);//控制水泵开关
    void report_SW_Set_Valvestate(TCP_COMM *Tcp_comm,uint16_t state);//控制阀门开关
    void report_SW_Set_gatestate(TCP_COMM *Tcp_comm,uint32_t state,uint16_t value);//控制闸门开关
    void report_SW_Set_Watersetting(TCP_COMM *Tcp_comm,uint8_t state);//水量定值控制
    void report_SW_QueryVersion(TCP_COMM *Tcp_comm);//水文协议 查询软件版本
    void report_SW_Set_Password(TCP_COMM *Tcp_comm);//水文协议 修改密码
    void report_SW_Query_stationTime(TCP_COMM *Tcp_comm);//水文协议 查询遥测站时钟

    void report_SW_QueryRealTime_Data(TCP_COMM *Tcp_comm);//水文协议 查询实时数据报
    void report_SW_QueryUniform_Time(TCP_COMM *Tcp_comm,uint8_t type,QString time1,QString time2);//水文协议 查询均匀时段数据报
    void report_SW_QueryManual_Work(TCP_COMM *Tcp_comm);//水文协议 查询人工置数报
    void report_SW_Query_Alarm(TCP_COMM *Tcp_comm);//水文协议 查询遥测站告警信息
    void report_SW_Query_Event(TCP_COMM *Tcp_comm);//水文协议 查询遥测站事件记录
    void report_SW_Query_APPOINT_ELEMENT(TCP_COMM *Tcp_comm);//水文协议 查询指定要素数据
    void report_SW_Set_Clock(TCP_COMM *Tcp_comm);//水文协议 设置遥测站时钟
    void report_SW_Modify_Basic_Set(TCP_COMM *Tcp_comm);//水文协议 修改遥测站基本参数配置表
    void report_SW_Query_Basic_Set(TCP_COMM *Tcp_comm);//水文协议 查询遥测站基本参数配置表
    void report_SW_Modify_Run_Set(TCP_COMM *Tcp_comm);//水文协议 修改遥测站运行参数配置表
    void report_SW_Query_Run_Set(TCP_COMM *Tcp_comm);//水文协议 查询遥测站运行参数配置表
    void report_SW_picture(TCP_COMM *Tcp_comm,QString dir_pic);//水文协议 查询图片报

    void report_SZY_link(TCP_COMM *tcp_comm,uint8_t fun_code);//水资源协议链路报 AFN 0x02
    void report_SZY_SetWaterLevel(TCP_COMM *tcp_comm);      // AFN 0x17
    void report_SZY_QueryWaterLevel(TCP_COMM *tcp_comm);    // AFN 0x57
    void report_SZY_SetFlow(TCP_COMM *tcp_comm);            // AFN 0x1F
    void report_SZY_QueryFlow(TCP_COMM *tcp_comm);          // AFN 0x64
    void report_SZY_SetClock(TCP_COMM *tcp_comm);           // AFN 0x11
    void report_SZY_QueryClock(TCP_COMM *tcp_comm);         // AFN 0x51
    void report_SZY_SetWorkMode(TCP_COMM *tcp_comm);        // AFN 0x12
    void report_SZY_QueryWorkMode(TCP_COMM *tcp_comm);      // AFN 0X52
    void report_SZY_SetAddress(TCP_COMM *tcp_comm);         // AFN 0X10
    void report_SZY_QueryAddress(TCP_COMM *tcp_comm);       // AFN 0X50
    void report_SZY_SetPassword(TCP_COMM *tcp_comm);        // AFN 0X96
    void report_SZY_QueryUploadTime(TCP_COMM *tcp_comm);    // AFN 0X53
    void report_SZY_SetUploadTime(TCP_COMM *tcp_comm);      // AFN 0XA1
    void report_SZY_QueryAllState(TCP_COMM *tcp_comm);      // AFN 0x5E
    void report_SZY_ResetTerminal(TCP_COMM *tcp_comm);      // AFN 0x90
    void report_SZY_DeleteHistoryData(TCP_COMM *tcp_comm);  // AFN 0X91
    void report_SZY_OpenKDY(TCP_COMM *tcp_comm);            // AFN 0x92
    void report_SZY_CloseKDY(TCP_COMM *tcp_comm);           // AFN 0x93
    void report_SZY_SetThresholdStoreTime(TCP_COMM *tcp_comm);// AFN 0x20
    void report_SZY_QueryRealTimeValue(TCP_COMM *tcp_comm); // AFN 0xB0
    void report_SZY_QueryData(TCP_COMM *tcp_comm);          // AFN 0XB1
    void report_SZY_QueryUploadData(TCP_COMM *tcp_comm);    // AFN 0XB2
    void report_SZY_QueryPicture(TCP_COMM *tcp_comm,QString dir_pic);    // AFN 0X61
	void report_SZY_EnableIC(TCP_COMM *tcp_comm);           // AFN 0x30
    void report_SZY_DisableIC(TCP_COMM *tcp_comm);          // AFN 0x31
    void report_SZY_fixed_time(uint8_t fun_code);//水资源协议定时报 AFN 0xC0

    QString camera_fun(QString camera_ip,QString camera_name,QString camera_password);
    bool report_pwCheck(QByteArray array, uint32_t index);//密码检验
    void timerTimeout_receive();
    /*CRC校验函数*/
    uint16_t ModBusCRC16(QByteArray data,uint32_t len);
    uint8_t CRC8_SZY(QByteArray buffer,uint16_t cLength);
    void serial_send_disconnect();
    //4字节十进制转BCD
    uint32_t uwordToBcd(uint32_t value);
    uint32_t wordToBcd(int32_t value);
    uint32_t wordTo3Bcd(int32_t value);
    uint32_t uwordTo3Bcd(uint32_t value);

    uint64_t udwordToDBcd(uint64_t value);
    uint8_t byteToBcd(uint8_t value);
    uint8_t BCDtobyte(uint8_t bcd);
    uint16_t BCDtoHalfword(uint16_t bcd);
    int32_t bcdToWord(QByteArray array, uint32_t index, uint8_t len, bool plusMinus);
    uint32_t bcdToUword(QByteArray array, uint32_t index, uint8_t len);
    void Delay_MSec(unsigned int msec);//毫秒延迟，不阻塞
    static char convertHexChart(char ch);//数据转换 字符串转16进制数据处理
    static void StringToHex(QString str, QByteArray &senddata);//数据转换 字符串转16进制
};

#endif // TCP_SOCKET_H
