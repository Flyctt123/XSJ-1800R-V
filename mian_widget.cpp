#include "mian_widget.h"
#include "ui_mian_widget.h"

uint8_t DO_Flag = 0;
extern uint8_t DI_Flag;//开入检测
extern uint16_t AI_data[6];
uint8_t AI_data_correct_count[6] = {0,0,0,0,0,0};//消抖计数
uint8_t AI_uint_select = 0;//模入电流电压选择
extern QSerialPort *serial[7];
extern COMM_CONFIG comm_config[5];
extern DATA_RES data_result;

mian_widget::mian_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mian_widget)
{
    ui->setupUi(this);
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
    ui->tabWidget->setFocusPolicy(Qt::NoFocus);//取消虚线框

    ui->label_DI1->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_DI2->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_DI3->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_DI4->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_DI5->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_kdy_open->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_kdy_off->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_kdy_raise->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_kdy_fall->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_kdy_error->setStyleSheet(m_grey_SheetStyle);//灰色
    ui->label_kdy_zidong->setStyleSheet(m_grey_SheetStyle);//灰色

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &mian_widget::refresh_timeout);

#ifdef BRUN
    //timer1->start(200)//烧录程序不刷新
#else
    timer1->start(200);
#endif
    AI_unit[0] = MainWindow::iniFile->value("/AI/AI1").toUInt();
    AI_unit[1] = MainWindow::iniFile->value("/AI/AI2").toUInt();
    AI_unit[2] = MainWindow::iniFile->value("/AI/AI3").toUInt();
    AI_unit[3] = MainWindow::iniFile->value("/AI/AI4").toUInt();
    AI_unit[4] = MainWindow::iniFile->value("/AI/AI5").toUInt();
    AI_unit[5] = MainWindow::iniFile->value("/AI/AI6").toUInt();
    for(uint8_t i=0;i<6;i++)
    {
        if(AI_unit[i])
            AI_uint_select = AI_uint_select | (1 << i);
    }

    if(MainWindow::iniFile->value("/DO/DO1").toUInt())
    {
        DO_Flag = DO_Flag | (1 << 0);
    }
    else
    {
        DO_Flag = DO_Flag & (~(1 << 0));
    }
    if(MainWindow::iniFile->value("/DO/DO2").toUInt())
    {
        DO_Flag = DO_Flag | (1 << 1);
    }
    else
    {
        DO_Flag = DO_Flag & (~(1 << 1));
    }
    if(MainWindow::iniFile->value("/DO/DO3").toUInt())
    {
        DO_Flag = DO_Flag | (1 << 2);
    }
    else
    {
        DO_Flag = DO_Flag & (~(1 << 2));
    }

#ifdef ARM
    if(MainWindow::iniFile->value("/DYC/DYC1").toUInt())
    {
        on_checkBox_DYC_1_stateChanged(1);
        ui->checkBox_DYC_1->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        on_checkBox_DYC_1_stateChanged(0);
        ui->checkBox_DYC_1->setCheckState(Qt::CheckState::Unchecked);
    }
    if(MainWindow::iniFile->value("/DYC/DYC2").toUInt())
    {
        on_checkBox_DYC_2_stateChanged(1);
        ui->checkBox_DYC_2->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        on_checkBox_DYC_2_stateChanged(0);
        ui->checkBox_DYC_2->setCheckState(Qt::CheckState::Unchecked);
    }
    if(MainWindow::iniFile->value("/DYC/DYC3").toUInt())
    {
        on_checkBox_DYC_3_stateChanged(1);
        ui->checkBox_DYC_3->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        on_checkBox_DYC_3_stateChanged(0);
        ui->checkBox_DYC_3->setCheckState(Qt::CheckState::Unchecked);
    }
    if(MainWindow::iniFile->value("/DYC/DYC4").toUInt())
    {
        on_checkBox_DYC_4_stateChanged(1);
        ui->checkBox_DYC_4->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        on_checkBox_DYC_4_stateChanged(0);
        ui->checkBox_DYC_4->setCheckState(Qt::CheckState::Unchecked);
    }
#endif
}

mian_widget::~mian_widget()
{
    delete ui;
}

uint16_t ModBusCRC16(QByteArray data)
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

void mian_widget::serial_send()
{
    QByteArray data_send,data_crc;//data1为数据，data2为CRC校验码
    uint16_t crc16;

    comm_config[1] = {0xAA,0x22,0x01,0x03,0x01,0x01,DO_Flag};//开出控制

    data_send[0]=comm_config[1].Head;
    data_send[1]=comm_config[1].Class;
    data_send[2]=comm_config[1].Operate;
    data_send[3]=comm_config[1].Type;
    data_send[4]=comm_config[1].Subtype;

    data_send[5]=(comm_config[1].len >> 8) & 0xff;
    data_send[6]=comm_config[1].len & 0xff;
    if(comm_config[1].Operate == 0)//读数据
    {
        data_send[7] = 0x00;
        data_send[8] = 0x00;
    }
    if(comm_config[1].Operate == 1)//写数据
        data_send[7] = comm_config[1].data;

    crc16=ModBusCRC16(data_send);//计算CRC校验码
    data_crc[0]=crc16 & 0xff;
    data_crc[1]=crc16>>8 & 0xff;

    serial[2]->write(data_send);//串口发送头
    serial[2]->write(data_crc);//发送CRC校验码
}

void mian_widget::refresh_timeout()
{
    float AI[6] = {0,0,0,0,0,0};

    if((DI_Flag >> 0) & 1)
        ui->label_DI1->setStyleSheet(m_green_SheetStyle);//绿色
    else
        ui->label_DI1->setStyleSheet(m_grey_SheetStyle);//灰色

    if((DI_Flag >> 1) & 1)
        ui->label_DI2->setStyleSheet(m_green_SheetStyle);//绿色
    else
        ui->label_DI2->setStyleSheet(m_grey_SheetStyle);//灰色

    if((DI_Flag >> 2) & 1)
        ui->label_DI3->setStyleSheet(m_green_SheetStyle);//绿色
    else
        ui->label_DI3->setStyleSheet(m_grey_SheetStyle);//灰色

    if((DI_Flag >> 3) & 1)
        ui->label_DI4->setStyleSheet(m_green_SheetStyle);//绿色
    else
        ui->label_DI4->setStyleSheet(m_grey_SheetStyle);//灰色

    if((DI_Flag >> 4) & 1)
        ui->label_DI5->setStyleSheet(m_green_SheetStyle);//绿色
    else
        ui->label_DI5->setStyleSheet(m_grey_SheetStyle);//灰色

    for(uint8_t i=0;i<6;i++)
    {
        if(AI_data[i] == 0)//采集值跳到0
        {
            AI_data_correct_count[i] ++;
            if(AI_data_correct_count[i] >= 15)//超过3秒
            {
                AI_data_correct_count[i] = 0;
                AI[i] = (float)AI_data[i];
            }
        }
        else
            AI[i] = (float)AI_data[i];
    }

    if(AI_unit[0] == 0)
        ui->label_AI1->setText(QString("%1").arg(AI[0] / 100) + "V");//电压原始值扩大了100倍
    else
        ui->label_AI1->setText(QString("%1").arg(AI[0]) + "mA");

    if(AI_unit[1] == 0)
        ui->label_AI2->setText(QString("%1").arg(AI[1] / 100) + "V");
    else
        ui->label_AI2->setText(QString("%1").arg(AI[1]) + "mA");

    if(AI_unit[2] == 0)
        ui->label_AI3->setText(QString("%1").arg(AI[2] / 100) + "V");
    else
        ui->label_AI3->setText(QString("%1").arg(AI[2]) + "mA");

    if(AI_unit[3] == 0)
        ui->label_AI4->setText(QString("%1").arg(AI[3] / 100) + "V");
    else
        ui->label_AI4->setText(QString("%1").arg(AI[3]) + "mA");

    if(AI_unit[4] == 0)
        ui->label_AI5->setText(QString("%1").arg(AI[4] / 100) + "V");
    else
        ui->label_AI5->setText(QString("%1").arg(AI[4]) + "mA");

    if(AI_unit[5] == 0)
        ui->label_AI6->setText(QString("%1").arg(AI[5] / 100) + "V");
    else
        ui->label_AI6->setText(QString("%1").arg(AI[5]) + "mA");

    ui->label_power_data->setText(QString::number(data_result.power_value,'f',2) + "V");
    ui->label_current_rain_data->setText(QString::number(data_result.data_rain_inst,'f',1) + "mm");
    ui->label_leiji_rain_data->setText(QString::number(data_result.data_rain_total,'f',1) + "mm");
    ui->label_current_flow_data->setText(QString::number(data_result.data_flow_inst,'f',3) + "m3/s");
    ui->label_leiji_flow_data->setText(QString::number(data_result.data_flow_total,'f',0) + "m3");
#ifdef FLOOD_FLOW
    ui->label_xiehong_flow_data->setText(QString::number(data_result.data_flood_flow,'f',2) + "m3/s");
#endif
    ui->label_shuiwei_data->setText(QString::number(data_result.data_water,'f',2) + "m");
    ui->label_liusu_data->setText(QString::number(data_result.data_flow_speed,'f',2) + "m/s");
    ui->label_kdy_data->setText(QString::number(data_result.data_kdy_value,'f',0) + "cm");

    if((data_result.data_kdy_state >> 0) & 1)//全开
    {
        ui->label_kdy_open->setStyleSheet(m_green_SheetStyle);//绿色
        data_result.alarm_state_SW = data_result.alarm_state_SW | (1 << 28);
    }
    else
    {
        ui->label_kdy_open->setStyleSheet(m_grey_SheetStyle);//灰色
        data_result.alarm_state_SW = data_result.alarm_state_SW & (~(1 << 28));
    }
    if((data_result.data_kdy_state >> 1) & 1)//全关
    {
        ui->label_kdy_off->setStyleSheet(m_green_SheetStyle);//绿色
        data_result.alarm_state_SW = data_result.alarm_state_SW | (1 << 29);
    }
    else
    {
        ui->label_kdy_off->setStyleSheet(m_grey_SheetStyle);//灰色
        data_result.alarm_state_SW = data_result.alarm_state_SW & (~(1 << 29));
    }
    if((data_result.data_kdy_state >> 2) & 1)//上升
    {
        ui->label_kdy_raise->setStyleSheet(m_green_SheetStyle);//绿色
    }
    else
    {
        ui->label_kdy_raise->setStyleSheet(m_grey_SheetStyle);//灰色
    }
    if((data_result.data_kdy_state >> 3) & 1)//下降
    {
        ui->label_kdy_fall->setStyleSheet(m_green_SheetStyle);//绿色
    }
    else
    {
        ui->label_kdy_fall->setStyleSheet(m_grey_SheetStyle);//灰色
    }
    if((data_result.data_kdy_state >> 8) & 1)//手动
    {
        ui->label_kdy_zidong->setStyleSheet(m_green_SheetStyle);//绿色
    }
    else
    {
        ui->label_kdy_zidong->setStyleSheet(m_grey_SheetStyle);//灰色
    }
    if((data_result.data_kdy_state >> 11) & 1)//故障
    {
        ui->label_kdy_error->setStyleSheet(m_green_SheetStyle);//绿色
        data_result.alarm_state_SW = data_result.alarm_state_SW | (1 << 30);
    }
    else
    {
        ui->label_kdy_error->setStyleSheet(m_grey_SheetStyle);//灰色
        data_result.alarm_state_SW = data_result.alarm_state_SW & (~(1 << 30));
    }
}

//可控电源
void mian_widget::on_checkBox_DYC_1_stateChanged(int arg1)
{
    if(arg1)
    {
        MainWindow::iniFile->setValue("/DYC/DYC1",1);
        system("echo 1 > /sys/class/leds/user-led-DY1/brightness");
    }
    else
    {
        MainWindow::iniFile->setValue("/DYC/DYC1",0);
        system("echo 0 > /sys/class/leds/user-led-DY1/brightness");
    }
}

void mian_widget::on_checkBox_DYC_2_stateChanged(int arg1)
{
    if(arg1)
    {
        MainWindow::iniFile->setValue("/DYC/DYC2",1);
        system("echo 1 > /sys/class/leds/user-led-DY2/brightness");
    }
    else
    {
        MainWindow::iniFile->setValue("/DYC/DYC2",0);
        system("echo 0 > /sys/class/leds/user-led-DY2/brightness");
    }
}

void mian_widget::on_checkBox_DYC_3_stateChanged(int arg1)
{
    if(arg1)
    {
        MainWindow::iniFile->setValue("/DYC/DYC3",1);
        system("echo 1 > /sys/class/leds/user-led-DY3/brightness");
    }
    else
    {
        MainWindow::iniFile->setValue("/DYC/DYC3",0);
        system("echo 0 > /sys/class/leds/user-led-DY3/brightness");
    }
}

void mian_widget::on_checkBox_DYC_4_stateChanged(int arg1)
{
    if(arg1)
    {
        MainWindow::iniFile->setValue("/DYC/DYC4",1);
        system("echo 1 > /sys/class/leds/user-led-DY4/brightness");
    }
    else
    {
        MainWindow::iniFile->setValue("/DYC/DYC4",0);
        system("echo 0 > /sys/class/leds/user-led-DY4/brightness");
    }
}

void mian_widget::on_checkBox_DO1_stateChanged(int arg1)
{
    if(arg1)
    {
        DO_Flag = DO_Flag | (1 << 0);
        MainWindow::iniFile->setValue("/DO/DO1",1);
    }
    else
    {
        DO_Flag = DO_Flag & (~(1 << 0));
        MainWindow::iniFile->setValue("/DO/DO1",0);
    }
#ifdef ARM
    serial_send();
#endif
}

void mian_widget::on_checkBox_DO2_stateChanged(int arg1)
{
    if(arg1)
    {
        DO_Flag = DO_Flag | (1 << 1);
        MainWindow::iniFile->setValue("/DO/DO2",1);
    }
    else
    {
        DO_Flag = DO_Flag & (~(1 << 1));
        MainWindow::iniFile->setValue("/DO/DO2",0);
    }
#ifdef ARM
    serial_send();
#endif
}

void mian_widget::on_checkBox_DO3_stateChanged(int arg1)
{
    if(arg1)
    {
        DO_Flag = DO_Flag | (1 << 2);
        MainWindow::iniFile->setValue("/DO/DO3",1);
    }
    else
    {
        DO_Flag = DO_Flag & (~(1 << 2));
        MainWindow::iniFile->setValue("/DO/DO3",0);
    }
#ifdef ARM
    serial_send();
#endif
}
