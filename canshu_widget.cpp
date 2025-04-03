#include "canshu_widget.h"
#include "ui_canshu_widget.h"
#include "serialport.h"

extern bool KeyBoard_Code,keyBoard_flag;
QSerialPort *serial[7];
float Rain_ratio = 0;//雨量分辨力
extern REPORT_HEADHEX_SW *report_SW_headhex;
extern REPORT_HEADHEX_SZY * report_SZY_headhex;
extern DATA_RES data_result;

extern Modbus modbus[5];//COM1~3 + 开度仪 + LPC1778串口
CALCULATE_485 calculate_485[4];//水位、瞬时流量、累计流量、流速
KDY kdy;

/*
"serial[0] --- ttyAS1" --- 路由模块调试口
"serial[1] --- ttyAS2" --- 第1路485
"serial[2] --- ttyAS3" --- IO扩展板
"serial[3] --- ttyCH343USB0" --- 第3路485
"serial[4] --- ttyCH343USB1" --- 第4路485
"serial[5] --- ttyCH343USB2" --- LORA
"serial[6] --- ttyCH343USB3" --- 第2路485
*/

canshu_widget::canshu_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::canshu_widget)
{
    ui->setupUi(this);
    ui->tabWidget->setStyleSheet(
        "QTabBar::tab{font-size:15px;}"
        "QTabWidget::pane{border: 2px solid rgb(210, 210, 210);\
        background:rgb(246, 246, 246);\
        border-top-color:transparent;}\
        QTabWidget::tab-bar{background:rgb(0, 0, 0);subcontrol-position:left;}\
        QTabBar::tab{width:65px;/*宽度根据实际需要进行调整*/"
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

    ui->lineEdit_water_base->installEventFilter(this);
    ui->lineEdit_water_modify->installEventFilter(this);
    ui->lineEdit_multipy->installEventFilter(this);
    ui->lineEdit_divide->installEventFilter(this);
    ui->lineEdit_add->installEventFilter(this);
    ui->lineEdit_subtract->installEventFilter(this);
    ui->lineEdit_485_addr->installEventFilter(this);
    ui->lineEdit_485_regAddr->installEventFilter(this);
    ui->lineEdit_addr_kdy->installEventFilter(this);
    ui->lineEdit_kdy_upLimit->installEventFilter(this);
    ui->lineEdit_kdy_downLimit->installEventFilter(this);
    ui->lineEdit_kdy_data->installEventFilter(this);
    ui->lineEdit_kdy_time->installEventFilter(this);
    ui->lineEdit_rain_ratio->installEventFilter(this);
    ui->lineEdit_central_addr->installEventFilter(this);
    ui->lineEdit_station_addr->installEventFilter(this);
    ui->lineEdit_report_password->installEventFilter(this);
    ui->lineEdit_report_type->installEventFilter(this);
    ui->lineEdit_add_reportTime->installEventFilter(this);
    ui->lineEdit_fixed_reportTime->installEventFilter(this);

    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) //扫描可用串口
    {
        if((info.portName() == "ttyAS0") || (info.portName() == "ttyAS4") || (info.portName() == "ttyAS5"))
            ;
        else
            portStringList += info.portName();
    }

#ifdef ARM
    for(uint8_t i = 0;i < portStringList.size();i ++)
    {
        serial[i] = new QSerialPort;
        if(portStringList[i] == "ttyAS2")
            serial_init(serial[i],portStringList[i],MainWindow::iniFile->value("/UART1/Baud").toUInt());//开机初始化串口
        else if(portStringList[i] == "ttyCH343USB3")
            serial_init(serial[i],portStringList[i],MainWindow::iniFile->value("/UART2/Baud").toUInt());
        else if(portStringList[i] == "ttyCH343USB0")
            serial_init(serial[i],portStringList[i],MainWindow::iniFile->value("/UART3/Baud").toUInt());
        else if(portStringList[i] == "ttyCH343USB1")
            serial_init(serial[i],portStringList[i],MainWindow::iniFile->value("/KDY/Baud").toUInt());
        else if(portStringList[i] == "ttyCH343USB2")
            serial_init(serial[i],portStringList[i],MainWindow::iniFile->value("/LORA/Baud").toUInt());
        else
            serial_init(serial[i],portStringList[i],9600);
    }
#else
    serial[1] = new QSerialPort;
    serial_init(serial[1],"COM3",9600);//开机初始化串口
#endif

    portCOM += "COM1";
    portCOM += "COM2";
    portCOM += "COM3";
    ui->PortBox->addItems(portCOM);
    //设置波特率下拉菜单默认显示第三项9600
    ui->BaudBox->setCurrentIndex(0);

    qDebug()<<"serial_port =" << portStringList;

    canshu_button_init(ui->clear_Button_485);
    canshu_button_init(ui->save_Button_485);
    canshu_button_init(ui->save_Button_sampling);
    canshu_button_init(ui->pushButton_kdy_stop);
    canshu_button_init(ui->pushButton_kdy_start);
    canshu_button_init(ui->pushButton_kdy_slave);
    canshu_button_init(ui->pushButton_SW_test);
    canshu_button_init(ui->save_Button_tcpTime);

    serial_change = new QSerialPort;

    ui->BaudBox->setCurrentText(MainWindow::iniFile->value("/UART1/Baud").toString());
    ui->lineEdit_485_addr->setText(MainWindow::iniFile->value("/UART1/ADDR").toString());
    ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value("/UART1/Identify1").toUInt());
    ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value("/UART1/Fun_code1").toUInt());
    ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value("/UART1/Reg_addr1").toString());
    ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value("/UART1/Reg_count1").toUInt());
    ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value("/UART1/Data_type1").toUInt());
    ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value("/UART1/Data_format1").toUInt());

    if(MainWindow::iniFile->value("/UART1/Protocol").toUInt() == 0)
    {
        ui->comboBox_485_protocol->setCurrentIndex(0);
        modbus[0].protocol = 0;
        ui->label_select1->show();
        ui->label_select2->show();
        ui->label_select3->show();
        ui->label_select4->show();
        ui->label_select5->show();
        ui->label_select6->show();
        ui->label_select7->show();
        ui->comboBox_485_num->show();
        ui->comboBox_485_identify->show();
        ui->comboBox_485_funcode->show();
        ui->lineEdit_485_regAddr->show();
        ui->comboBox_485_regNum->show();
        ui->comboBox_485_type->show();
        ui->comboBox_485_format->show();
    }
    else
    {
        ui->comboBox_485_protocol->setCurrentIndex(1);
        modbus[0].protocol = 1;
        MainWindow::iniFile->setValue("/UART1/Identify1",4);//采集通道关闭
        MainWindow::iniFile->setValue("/UART1/Identify2",4);
        MainWindow::iniFile->setValue("/UART1/Identify3",4);
        MainWindow::iniFile->setValue("/UART1/Identify4",4);
        ui->label_select1->hide();
        ui->label_select2->hide();
        ui->label_select3->hide();
        ui->label_select4->hide();
        ui->label_select5->hide();
        ui->label_select6->hide();
        ui->label_select7->hide();
        ui->comboBox_485_num->hide();
        ui->comboBox_485_identify->hide();
        ui->comboBox_485_funcode->hide();
        ui->lineEdit_485_regAddr->hide();
        ui->comboBox_485_regNum->hide();
        ui->comboBox_485_type->hide();
        ui->comboBox_485_format->hide();
    }

    if(MainWindow::iniFile->value("/UART2/Protocol").toUInt() == 0)
    {
        modbus[1].protocol = 0;
    }
    else
    {
        modbus[1].protocol = 1;
        MainWindow::iniFile->setValue("/UART2/Identify1",4);//采集通道关闭
        MainWindow::iniFile->setValue("/UART2/Identify2",4);
        MainWindow::iniFile->setValue("/UART2/Identify3",4);
        MainWindow::iniFile->setValue("/UART2/Identify4",4);
    }

    if(MainWindow::iniFile->value("/UART3/Protocol").toUInt() == 0)
    {
        modbus[2].protocol = 0;
    }
    else
    {
        modbus[2].protocol = 1;
        MainWindow::iniFile->setValue("/UART3/Identify1",4);//采集通道关闭
        MainWindow::iniFile->setValue("/UART3/Identify2",4);
        MainWindow::iniFile->setValue("/UART3/Identify3",4);
        MainWindow::iniFile->setValue("/UART3/Identify4",4);
    }

    ui->BaudBox_kdy->setCurrentText(MainWindow::iniFile->value("/KDY/Baud").toString());
    ui->lineEdit_addr_kdy->setText(MainWindow::iniFile->value("/KDY/ADDR").toString());
    ui->lineEdit_kdy_upLimit->setText(MainWindow::iniFile->value("/KDY/UpLimit").toString());
    ui->lineEdit_kdy_downLimit->setText(MainWindow::iniFile->value("/KDY/DownLimit").toString());
    ui->lineEdit_kdy_data->setText(MainWindow::iniFile->value("/KDY/Data").toString());
    ui->lineEdit_kdy_time->setText(MainWindow::iniFile->value("/KDY/Time").toString());
    ui->lineEdit_rain_ratio->setText(MainWindow::iniFile->value("/RAIN/Ratio1").toString());

    QFile file0("/home/kd_unit.txt");
    if(file0.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
         while(!file0.atEnd())
         {
           line = file0.readLine();
         }
         if(line == "0")
         {
             ui->comboBox_kdUnit->setCurrentIndex(0);
             kdy.unit = "mm";
         }
         else
         {
             ui->comboBox_kdUnit->setCurrentIndex(1);
             kdy.unit = "cm";
         }
         file0.close();
    }
    else
    {
        ui->comboBox_kdUnit->setCurrentIndex(0);
        kdy.unit = "mm";
    }

    modbus_comm_init();//Modbus点表配置初始化
    timer =new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout_second()));//从0秒开始计时
    on_pushButton_kdy_slave_clicked();//开度仪配置初始化

    QFile file1("/home/SW_report_uniform_time.txt");
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
         while(!file1.atEnd())
         {
           line = file1.readLine();
         }
         if(line == "0")
         {
             ui->checkBox_SW_uniform_time->setChecked(false);
             report_SW_headhex->report_type_select[0] = false;
         }
         else
         {
             ui->checkBox_SW_uniform_time->setChecked(true);
             report_SW_headhex->report_type_select[0] = true;
         }
         file1.close();
    }
    else
        report_SW_headhex->report_type_select[0] = false;

    QFile file2("/home/SW_report_hour.txt");
    if(file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
         while(!file2.atEnd())
         {
           line = file2.readLine();
         }
         if(line == "0")
         {
             ui->checkBox_SW_hour->setChecked(false);
             report_SW_headhex->report_type_select[1] = false;
         }
         else
         {
             ui->checkBox_SW_hour->setChecked(true);
             report_SW_headhex->report_type_select[1] = true;
         }
         file2.close();
    }
    else
        report_SW_headhex->report_type_select[1] = false;

    ui->lineEdit_central_addr->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Central_addr").toString());
    ui->lineEdit_station_addr->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Station_addr").toString());
    ui->lineEdit_report_password->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Password").toString());
    ui->lineEdit_fixed_reportTime->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Fixed_time").toString());
    ui->lineEdit_add_reportTime->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Add_time").toString());
    ui->lineEdit_report_type->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Element").toString());
    ui->lineEdit_water_base->setText(MainWindow::iniFile->value("/ALARM/Water_base").toString());
    ui->lineEdit_water_modify->setText(MainWindow::iniFile->value("/ALARM/Water_modify").toString());
    ui->lineEdit_rain_ratio->setText(MainWindow::iniFile->value("/RAIN/Ratio1").toString());
    Rain_ratio = MainWindow::iniFile->value("/RAIN/Ratio1").toFloat();

    if(MainWindow::iniFile->value("/AI/AI1").toUInt())
        ui->radioButton1_cur->setChecked(true);
    else
        ui->radioButton1_vol->setChecked(true);
    if(MainWindow::iniFile->value("/AI/AI2").toUInt())
        ui->radioButton2_cur->setChecked(true);
    else
        ui->radioButton2_vol->setChecked(true);
    if(MainWindow::iniFile->value("/AI/AI3").toUInt())
        ui->radioButton3_cur->setChecked(true);
    else
        ui->radioButton3_vol->setChecked(true);
    if(MainWindow::iniFile->value("/AI/AI4").toUInt())
        ui->radioButton4_cur->setChecked(true);
    else
        ui->radioButton4_vol->setChecked(true);
    if(MainWindow::iniFile->value("/AI/AI5").toUInt())
        ui->radioButton5_cur->setChecked(true);
    else
        ui->radioButton5_vol->setChecked(true);
    if(MainWindow::iniFile->value("/AI/AI6").toUInt())
        ui->radioButton6_cur->setChecked(true);
    else
        ui->radioButton6_vol->setChecked(true);

    ui->radioButton1_cur->hide();
    ui->radioButton2_cur->hide();
    ui->radioButton3_cur->hide();
    ui->radioButton4_cur->hide();
    ui->radioButton5_vol->hide();
    ui->radioButton6_vol->hide();

    calculate_485[0].multipy = MainWindow::iniFile->value("/SAMPLING_Water/Multipy").toUInt();
    calculate_485[0].divide = MainWindow::iniFile->value("/SAMPLING_Water/Divide").toUInt();
    calculate_485[0].add = MainWindow::iniFile->value("/SAMPLING_Water/Add").toUInt();
    calculate_485[0].subtract = MainWindow::iniFile->value("/SAMPLING_Water/Subtract").toUInt();
    calculate_485[1].multipy = MainWindow::iniFile->value("/SAMPLING_flow_inst/Multipy").toUInt();
    calculate_485[1].divide = MainWindow::iniFile->value("/SAMPLING_flow_inst/Divide").toUInt();
    calculate_485[1].add = MainWindow::iniFile->value("/SAMPLING_flow_inst/Add").toUInt();
    calculate_485[1].subtract = MainWindow::iniFile->value("/SAMPLING_flow_inst/Subtract").toUInt();
    calculate_485[2].multipy = MainWindow::iniFile->value("/SAMPLING_flow_total/Multipy").toUInt();
    calculate_485[2].divide = MainWindow::iniFile->value("/SAMPLING_flow_total/Divide").toUInt();
    calculate_485[2].add = MainWindow::iniFile->value("/SAMPLING_flow_total/Add").toUInt();
    calculate_485[2].subtract = MainWindow::iniFile->value("/SAMPLING_flow_total/Subtract").toUInt();
    calculate_485[3].multipy = MainWindow::iniFile->value("/SAMPLING_flow_speed/Multipy").toUInt();
    calculate_485[3].divide = MainWindow::iniFile->value("/SAMPLING_flow_speed/Divide").toUInt();
    calculate_485[3].add = MainWindow::iniFile->value("/SAMPLING_flow_speed/Add").toUInt();
    calculate_485[3].subtract = MainWindow::iniFile->value("/SAMPLING_flow_speed/Subtract").toUInt();

    data_result.data_water_base_value = MainWindow::iniFile->value("/ALARM/Water_base").toDouble();//水位基值
    data_result.data_water_modify_value = MainWindow::iniFile->value("/ALARM/Water_modify").toDouble();//水位修正值
}

canshu_widget::~canshu_widget()
{
    delete ui;
}

void canshu_widget::setUploadTimeToUI(uint8_t t)
{
    ui->lineEdit_fixed_reportTime->setText(QString::number(t));
}

void canshu_widget::setUploadPasswordToUI(QString p)
{
    ui->lineEdit_report_password->setText(p);
}

void canshu_widget::setUploadBaseSet(void)
{
    ui->lineEdit_central_addr->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Central_addr").toString());
    ui->lineEdit_station_addr->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Station_addr").toString());
    ui->lineEdit_report_type->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Element").toString());
}

void canshu_widget::setUploadRunSet(void)
{
    ui->lineEdit_fixed_reportTime->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Fixed_time").toString());
    ui->lineEdit_add_reportTime->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Add_time").toString());
    ui->lineEdit_rain_ratio->setText(MainWindow::iniFile->value("/RAIN/Ratio1").toString());
    ui->lineEdit_water_base->setText(MainWindow::iniFile->value("/ALARM/Water_base").toString());
    ui->lineEdit_water_modify->setText(MainWindow::iniFile->value("/ALARM/Water_modify").toString());
}

bool canshu_widget::eventFilter(QObject *watch, QEvent *evn)
{
    if ((watch == ui->lineEdit_water_base) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_water_base);
    }
    if ((watch == ui->lineEdit_water_modify) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_water_modify);
    }
    if ((watch == ui->lineEdit_multipy) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_multipy);
    }
    if ((watch == ui->lineEdit_divide) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_divide);
    }
    if ((watch == ui->lineEdit_add) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_add);
    }
    if ((watch == ui->lineEdit_subtract) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_subtract);
    }
    if ((watch == ui->lineEdit_rain_ratio) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_rain_ratio);
    }
    if ((watch == ui->lineEdit_central_addr) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_central_addr);
    }
    if ((watch == ui->lineEdit_station_addr) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_station_addr);
    }
    if ((watch == ui->lineEdit_report_password) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_report_password);
    }
    if ((watch == ui->lineEdit_report_type) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_report_type);
    }
    if ((watch == ui->lineEdit_add_reportTime) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_add_reportTime);
    }
    if ((watch == ui->lineEdit_fixed_reportTime) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_fixed_reportTime);
    }
    if ((watch == ui->lineEdit_485_addr) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_485_addr);
    }
    if ((watch == ui->lineEdit_485_regAddr) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_485_regAddr);
    }
    if ((watch == ui->lineEdit_addr_kdy) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_addr_kdy);
    }
    if ((watch == ui->lineEdit_kdy_upLimit) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_kdy_upLimit);
    }
    if ((watch == ui->lineEdit_kdy_downLimit) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_kdy_downLimit);
    }
    if ((watch == ui->lineEdit_kdy_data) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_kdy_data);
    }
    if ((watch == ui->lineEdit_kdy_time) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_kdy_time);
    }
    if ((watch == ui->lineEdit_rain_ratio) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_rain_ratio);
    }

    return QWidget::eventFilter(watch,evn);
}

void canshu_widget::callKeyBoard(QLineEdit *a)
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

void canshu_widget::timerTimeout_second()
{
    time_count ++;
    if(time_count == 1)
        emit kdy_signal(1);
    else if(time_count == 2)
        emit kdy_signal(2);
    else if(time_count == 3)
        emit kdy_signal(3);
    else if(time_count == 4)
        emit kdy_signal(4);
    else if(time_count == (5 + kdy.time))
        emit kdy_signal(5);
    else if(time_count > (5 + kdy.time))
    {
        time_count = 0;
        timer->stop();
    }
    else
    {
        ;
    }
}

void canshu_widget::canshu_button_init(QPushButton *button_init)
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

void canshu_widget::serial_init(QSerialPort *serial, QString portname, int bundrate)
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

void canshu_widget::on_save_Button_485_clicked()
{
    if(ui->PortBox->currentText() == "COM1")
    {
#ifdef ARM
        serial_change = serial[1];
        serial_change->close();
        serial_change->setPortName("ttyAS2");
        //打开串口
        serial_change->open(QIODevice::ReadWrite);
        //设置波特率
        serial_change->setBaudRate(ui->BaudBox->currentText().toInt());
#endif
        MainWindow::iniFile->setValue("/UART1/Baud",ui->BaudBox->currentText());
        MainWindow::iniFile->setValue("/UART1/ADDR",ui->lineEdit_485_addr->text());
        MainWindow::iniFile->setValue("/UART1/Protocol",ui->comboBox_485_protocol->currentIndex());
        if(ui->comboBox_485_protocol->currentIndex() == 0)
        {
            modbus[0].protocol = 0;
            if(ui->comboBox_485_num->currentText() == "1")
            {
                MainWindow::iniFile->setValue("/UART1/Identify1",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Fun_code1",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Reg_addr1",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART1/Reg_count1",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_type1",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_format1",ui->comboBox_485_format->currentIndex());
            }
            else if(ui->comboBox_485_num->currentText() == "2")
            {
                MainWindow::iniFile->setValue("/UART1/Identify2",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Fun_code2",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Reg_addr2",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART1/Reg_count2",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_type2",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_format2",ui->comboBox_485_format->currentIndex());
            }
            else if(ui->comboBox_485_num->currentText() == "3")
            {
                MainWindow::iniFile->setValue("/UART1/Identify3",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Fun_code3",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Reg_addr3",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART1/Reg_count3",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_type3",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_format3",ui->comboBox_485_format->currentIndex());
            }
            else
            {
                MainWindow::iniFile->setValue("/UART1/Identify4",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Fun_code4",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Reg_addr4",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART1/Reg_count4",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_type4",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART1/Data_format4",ui->comboBox_485_format->currentIndex());
            }
        }
        else//Modbus从站
        {
            modbus[0].protocol = 1;
            MainWindow::iniFile->setValue("/UART1/Identify1",4);//采集通道关闭
            MainWindow::iniFile->setValue("/UART1/Identify2",4);
            MainWindow::iniFile->setValue("/UART1/Identify3",4);
            MainWindow::iniFile->setValue("/UART1/Identify4",4);
        }
    }
    else if(ui->PortBox->currentText() == "COM2")
    {
#ifdef ARM
        serial_change = serial[6];
        serial_change->close();
        serial_change->setPortName("ttyCH343USB3");
        //打开串口
        serial_change->open(QIODevice::ReadWrite);
        //设置波特率
        serial_change->setBaudRate(ui->BaudBox->currentText().toInt());
#endif
        MainWindow::iniFile->setValue("/UART2/Baud",ui->BaudBox->currentText());
        MainWindow::iniFile->setValue("/UART2/ADDR",ui->lineEdit_485_addr->text());
        MainWindow::iniFile->setValue("/UART2/Protocol",ui->comboBox_485_protocol->currentIndex());
        if(ui->comboBox_485_protocol->currentIndex() == 0)
        {
            modbus[1].protocol = 0;
            if(ui->comboBox_485_num->currentText() == "1")
            {
                MainWindow::iniFile->setValue("/UART2/Identify1",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Fun_code1",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Reg_addr1",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART2/Reg_count1",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_type1",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_format1",ui->comboBox_485_format->currentIndex());
            }
            else if(ui->comboBox_485_num->currentText() == "2")
            {
                MainWindow::iniFile->setValue("/UART2/Identify2",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Fun_code2",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Reg_addr2",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART2/Reg_count2",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_type2",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_format2",ui->comboBox_485_format->currentIndex());
            }
            else if(ui->comboBox_485_num->currentText() == "3")
            {
                MainWindow::iniFile->setValue("/UART2/Identify3",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Fun_code3",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Reg_addr3",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART2/Reg_count3",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_type3",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_format3",ui->comboBox_485_format->currentIndex());
            }
            else
            {
                MainWindow::iniFile->setValue("/UART2/Identify4",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Fun_code4",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Reg_addr4",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART2/Reg_count4",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_type4",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART2/Data_format4",ui->comboBox_485_format->currentIndex());
            }
        }
        else//Modbus从站
        {
            modbus[1].protocol = 1;
            MainWindow::iniFile->setValue("/UART2/Identify1",4);//采集通道关闭
            MainWindow::iniFile->setValue("/UART2/Identify2",4);
            MainWindow::iniFile->setValue("/UART2/Identify3",4);
            MainWindow::iniFile->setValue("/UART2/Identify4",4);
        }
    }
    else if(ui->PortBox->currentText() == "COM3")
    {
#ifdef ARM
        serial_change = serial[3];
        serial_change->close();
        serial_change->setPortName("ttyCH343USB0");
        //打开串口
        serial_change->open(QIODevice::ReadWrite);
        //设置波特率
        serial_change->setBaudRate(ui->BaudBox->currentText().toInt());
#endif
        MainWindow::iniFile->setValue("/UART3/Baud",ui->BaudBox->currentText());
        MainWindow::iniFile->setValue("/UART3/ADDR",ui->lineEdit_485_addr->text());
        MainWindow::iniFile->setValue("/UART3/Protocol",ui->comboBox_485_protocol->currentIndex());
        if(ui->comboBox_485_protocol->currentIndex() == 0)
        {
            modbus[2].protocol = 0;
            if(ui->comboBox_485_num->currentText() == "1")
            {
                MainWindow::iniFile->setValue("/UART3/Identify1",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Fun_code1",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Reg_addr1",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART3/Reg_count1",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_type1",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_format1",ui->comboBox_485_format->currentIndex());
            }
            else if(ui->comboBox_485_num->currentText() == "2")
            {
                MainWindow::iniFile->setValue("/UART3/Identify2",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Fun_code2",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Reg_addr2",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART3/Reg_count2",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_type2",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_format2",ui->comboBox_485_format->currentIndex());
            }
            else if(ui->comboBox_485_num->currentText() == "3")
            {
                MainWindow::iniFile->setValue("/UART3/Identify3",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Fun_code3",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Reg_addr3",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART3/Reg_count3",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_type3",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_format3",ui->comboBox_485_format->currentIndex());
            }
            else
            {
                MainWindow::iniFile->setValue("/UART3/Identify4",ui->comboBox_485_identify->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Fun_code4",ui->comboBox_485_funcode->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Reg_addr4",ui->lineEdit_485_regAddr->text());
                MainWindow::iniFile->setValue("/UART3/Reg_count4",ui->comboBox_485_regNum->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_type4",ui->comboBox_485_type->currentIndex());
                MainWindow::iniFile->setValue("/UART3/Data_format4",ui->comboBox_485_format->currentIndex());
            }
        }
        else//Modbus从站
        {
            modbus[2].protocol = 1;
            MainWindow::iniFile->setValue("/UART3/Identify1",4);//采集通道关闭
            MainWindow::iniFile->setValue("/UART3/Identify2",4);
            MainWindow::iniFile->setValue("/UART3/Identify3",4);
            MainWindow::iniFile->setValue("/UART3/Identify4",4);
        }
    }
    else
    {

    }

#ifdef ARM
    //设置数据位数
    serial_change->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial_change->setParity(QSerialPort::NoParity);
    //设置停止位
    serial_change->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial_change->setFlowControl(QSerialPort::NoFlowControl);
#endif

    modbus_comm_init();
}

void canshu_widget::on_PortBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_485_num->setCurrentIndex(0);
    if(arg1 == "COM1")
    {
        ui->BaudBox->setCurrentText(MainWindow::iniFile->value("/UART1/Baud").toString());
        ui->lineEdit_485_addr->setText(MainWindow::iniFile->value("/UART1/ADDR").toString());
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value("/UART1/Identify1").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value("/UART1/Fun_code1").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value("/UART1/Reg_addr1").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value("/UART1/Reg_count1").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value("/UART1/Data_type1").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value("/UART1/Data_format1").toUInt());
        if(MainWindow::iniFile->value("/UART1/Protocol").toUInt() == 0)
        {
            ui->comboBox_485_protocol->setCurrentIndex(0);
            ui->label_select1->show();
            ui->label_select2->show();
            ui->label_select3->show();
            ui->label_select4->show();
            ui->label_select5->show();
            ui->label_select6->show();
            ui->label_select7->show();
            ui->comboBox_485_num->show();
            ui->comboBox_485_identify->show();
            ui->comboBox_485_funcode->show();
            ui->lineEdit_485_regAddr->show();
            ui->comboBox_485_regNum->show();
            ui->comboBox_485_type->show();
            ui->comboBox_485_format->show();
        }
        else
        {
            ui->comboBox_485_protocol->setCurrentIndex(1);
            ui->label_select1->hide();
            ui->label_select2->hide();
            ui->label_select3->hide();
            ui->label_select4->hide();
            ui->label_select5->hide();
            ui->label_select6->hide();
            ui->label_select7->hide();
            ui->comboBox_485_num->hide();
            ui->comboBox_485_identify->hide();
            ui->comboBox_485_funcode->hide();
            ui->lineEdit_485_regAddr->hide();
            ui->comboBox_485_regNum->hide();
            ui->comboBox_485_type->hide();
            ui->comboBox_485_format->hide();
        }
    }
    if(arg1 == "COM2")
    {
        ui->BaudBox->setCurrentText(MainWindow::iniFile->value("/UART2/Baud").toString());
        ui->lineEdit_485_addr->setText(MainWindow::iniFile->value("/UART2/ADDR").toString());
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value("/UART2/Identify1").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value("/UART2/Fun_code1").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value("/UART2/Reg_addr1").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value("/UART2/Reg_count1").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value("/UART2/Data_type1").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value("/UART2/Data_format1").toUInt());

        if(MainWindow::iniFile->value("/UART2/Protocol").toUInt() == 0)
        {
            ui->comboBox_485_protocol->setCurrentIndex(0);
            ui->label_select1->show();
            ui->label_select2->show();
            ui->label_select3->show();
            ui->label_select4->show();
            ui->label_select5->show();
            ui->label_select6->show();
            ui->label_select7->show();
            ui->comboBox_485_num->show();
            ui->comboBox_485_identify->show();
            ui->comboBox_485_funcode->show();
            ui->lineEdit_485_regAddr->show();
            ui->comboBox_485_regNum->show();
            ui->comboBox_485_type->show();
            ui->comboBox_485_format->show();
        }
        else
        {
            ui->comboBox_485_protocol->setCurrentIndex(1);
            ui->label_select1->hide();
            ui->label_select2->hide();
            ui->label_select3->hide();
            ui->label_select4->hide();
            ui->label_select5->hide();
            ui->label_select6->hide();
            ui->label_select7->hide();
            ui->comboBox_485_num->hide();
            ui->comboBox_485_identify->hide();
            ui->comboBox_485_funcode->hide();
            ui->lineEdit_485_regAddr->hide();
            ui->comboBox_485_regNum->hide();
            ui->comboBox_485_type->hide();
            ui->comboBox_485_format->hide();
        }
    }
    if(arg1 == "COM3")
    {
        ui->BaudBox->setCurrentText(MainWindow::iniFile->value("/UART3/Baud").toString());
        ui->lineEdit_485_addr->setText(MainWindow::iniFile->value("/UART3/ADDR").toString());
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value("/UART3/Identify1").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value("/UART3/Fun_code1").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value("/UART3/Reg_addr1").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value("/UART3/Reg_count1").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value("/UART3/Data_type1").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value("/UART3/Data_format1").toUInt());

        if(MainWindow::iniFile->value("/UART3/Protocol").toUInt() == 0)
        {
            ui->comboBox_485_protocol->setCurrentIndex(0);
            ui->label_select1->show();
            ui->label_select2->show();
            ui->label_select3->show();
            ui->label_select4->show();
            ui->label_select5->show();
            ui->label_select6->show();
            ui->label_select7->show();
            ui->comboBox_485_num->show();
            ui->comboBox_485_identify->show();
            ui->comboBox_485_funcode->show();
            ui->lineEdit_485_regAddr->show();
            ui->comboBox_485_regNum->show();
            ui->comboBox_485_type->show();
            ui->comboBox_485_format->show();
        }
        else
        {
            ui->comboBox_485_protocol->setCurrentIndex(1);
            ui->label_select1->hide();
            ui->label_select2->hide();
            ui->label_select3->hide();
            ui->label_select4->hide();
            ui->label_select5->hide();
            ui->label_select6->hide();
            ui->label_select7->hide();
            ui->comboBox_485_num->hide();
            ui->comboBox_485_identify->hide();
            ui->comboBox_485_funcode->hide();
            ui->lineEdit_485_regAddr->hide();
            ui->comboBox_485_regNum->hide();
            ui->comboBox_485_type->hide();
            ui->comboBox_485_format->hide();
        }
    }
}

void canshu_widget::on_radioButton1_vol_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI1",0);
}

void canshu_widget::on_radioButton1_cur_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI1",1);
}

void canshu_widget::on_radioButton2_vol_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI2",0);
}

void canshu_widget::on_radioButton2_cur_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI2",1);
}

void canshu_widget::on_radioButton3_vol_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI3",0);
}

void canshu_widget::on_radioButton3_cur_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI3",1);
}

void canshu_widget::on_radioButton4_vol_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI4",0);
}

void canshu_widget::on_radioButton4_cur_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI4",1);
}

void canshu_widget::on_radioButton5_vol_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI5",0);
}

void canshu_widget::on_radioButton5_cur_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI5",1);
}

void canshu_widget::on_radioButton6_vol_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI6",0);
}

void canshu_widget::on_radioButton6_cur_clicked()
{
    MainWindow::iniFile->setValue("/AI/AI6",1);
}

void canshu_widget::on_save_Button_sampling_clicked()
{
    if(ui->lineEdit_divide->text() == "0")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("除数不能为0!"));
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

    if(ui->comboBox_485->currentText() == "水位")
    {
        MainWindow::iniFile->setValue("/SAMPLING_Water/Multipy",ui->lineEdit_multipy->text());
        MainWindow::iniFile->setValue("/SAMPLING_Water/Divide",ui->lineEdit_divide->text());
        MainWindow::iniFile->setValue("/SAMPLING_Water/Add",ui->lineEdit_add->text());
        MainWindow::iniFile->setValue("/SAMPLING_Water/Subtract",ui->lineEdit_subtract->text());
        calculate_485[0].multipy = ui->lineEdit_multipy->text().toUShort();
        calculate_485[0].divide = ui->lineEdit_divide->text().toUShort();
        calculate_485[0].add = ui->lineEdit_add->text().toUShort();
        calculate_485[0].subtract = ui->lineEdit_subtract->text().toUShort();

        MainWindow::iniFile->setValue("/ALARM/Water_base",ui->lineEdit_water_base->text());//水位基值
        MainWindow::iniFile->setValue("/ALARM/Water_modify",ui->lineEdit_water_modify->text());//水位修正值
        data_result.data_water_base_value = MainWindow::iniFile->value("/ALARM/Water_base").toDouble();
        data_result.data_water_modify_value = MainWindow::iniFile->value("/ALARM/Water_modify").toDouble();
    }
    else if(ui->comboBox_485->currentText() == "瞬时流量")
    {
        MainWindow::iniFile->setValue("/SAMPLING_flow_inst/Multipy",ui->lineEdit_multipy->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_inst/Divide",ui->lineEdit_divide->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_inst/Add",ui->lineEdit_add->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_inst/Subtract",ui->lineEdit_subtract->text());
        calculate_485[1].multipy = ui->lineEdit_multipy->text().toUShort();
        calculate_485[1].divide = ui->lineEdit_divide->text().toUShort();
        calculate_485[1].add = ui->lineEdit_add->text().toUShort();
        calculate_485[1].subtract = ui->lineEdit_subtract->text().toUShort();
    }
    else if(ui->comboBox_485->currentText() == "累计流量")
    {
        MainWindow::iniFile->setValue("/SAMPLING_flow_total/Multipy",ui->lineEdit_multipy->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_total/Divide",ui->lineEdit_divide->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_total/Add",ui->lineEdit_add->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_total/Subtract",ui->lineEdit_subtract->text());
        calculate_485[2].multipy = ui->lineEdit_multipy->text().toUShort();
        calculate_485[2].divide = ui->lineEdit_divide->text().toUShort();
        calculate_485[2].add = ui->lineEdit_add->text().toUShort();
        calculate_485[2].subtract = ui->lineEdit_subtract->text().toUShort();
    }
    else
    {
        MainWindow::iniFile->setValue("/SAMPLING_flow_speed/Multipy",ui->lineEdit_multipy->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_speed/Divide",ui->lineEdit_divide->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_speed/Add",ui->lineEdit_add->text());
        MainWindow::iniFile->setValue("/SAMPLING_flow_speed/Subtract",ui->lineEdit_subtract->text());
        calculate_485[3].multipy = ui->lineEdit_multipy->text().toUShort();
        calculate_485[3].divide = ui->lineEdit_divide->text().toUShort();
        calculate_485[3].add = ui->lineEdit_add->text().toUShort();
        calculate_485[3].subtract = ui->lineEdit_subtract->text().toUShort();
    }

    MainWindow::iniFile->setValue("/RAIN/Ratio1",ui->lineEdit_rain_ratio->text());
    Rain_ratio = MainWindow::iniFile->value("/RAIN/Ratio1").toFloat();
}

void canshu_widget::on_comboBox_485_num_currentIndexChanged(const QString &arg1)
{
    QString uart_com = "";
    if(ui->PortBox->currentText() == "COM1")
        uart_com = "/UART1/";
    if(ui->PortBox->currentText() == "COM2")
        uart_com = "/UART2/";
    if(ui->PortBox->currentText() == "COM3")
        uart_com = "/UART3/";

    if(arg1 == "1")
    {
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Identify1").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Fun_code1").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value(uart_com + "Reg_addr1").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Reg_count1").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_type1").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_format1").toUInt());
    }
    else if(arg1 == "2")
    {
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Identify2").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Fun_code2").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value(uart_com + "Reg_addr2").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Reg_count2").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_type2").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_format2").toUInt());
    }
    else if(arg1 == "3")
    {
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Identify3").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Fun_code3").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value(uart_com + "Reg_addr3").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Reg_count3").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_type3").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_format3").toUInt());
    }
    else
    {
        ui->comboBox_485_identify->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Identify4").toUInt());
        ui->comboBox_485_funcode->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Fun_code4").toUInt());
        ui->lineEdit_485_regAddr->setText(MainWindow::iniFile->value(uart_com + "Reg_addr4").toString());
        ui->comboBox_485_regNum->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Reg_count4").toUInt());
        ui->comboBox_485_type->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_type4").toUInt());
        ui->comboBox_485_format->setCurrentIndex(MainWindow::iniFile->value(uart_com + "Data_format4").toUInt());
    }
}

void canshu_widget::on_clear_Button_485_clicked()
{
    QString uart_com = "";
    if(ui->PortBox->currentText() == "COM1")
        uart_com = "/UART1/";
    if(ui->PortBox->currentText() == "COM2")
        uart_com = "/UART2/";
    if(ui->PortBox->currentText() == "COM3")
        uart_com = "/UART3/";

    if(ui->comboBox_485_num->currentText() == "1")
    {
        MainWindow::iniFile->setValue(uart_com + "Identify1",0);
        MainWindow::iniFile->setValue(uart_com + "Fun_code1",0);
        MainWindow::iniFile->setValue(uart_com + "Reg_addr1","");
        MainWindow::iniFile->setValue(uart_com + "Reg_count1",0);
        MainWindow::iniFile->setValue(uart_com + "Data_type1",0);
        MainWindow::iniFile->setValue(uart_com + "Data_format1",0);
    }
    else if(ui->comboBox_485_num->currentText() == "2")
    {
        MainWindow::iniFile->setValue(uart_com + "Identify2",0);
        MainWindow::iniFile->setValue(uart_com + "Fun_code2",0);
        MainWindow::iniFile->setValue(uart_com + "Reg_addr2","");
        MainWindow::iniFile->setValue(uart_com + "Reg_count2",0);
        MainWindow::iniFile->setValue(uart_com + "Data_type2",0);
        MainWindow::iniFile->setValue(uart_com + "Data_format2",0);
    }
    else if(ui->comboBox_485_num->currentText() == "3")
    {
        MainWindow::iniFile->setValue(uart_com + "Identify3",0);
        MainWindow::iniFile->setValue(uart_com + "Fun_code3",0);
        MainWindow::iniFile->setValue(uart_com + "Reg_addr3","");
        MainWindow::iniFile->setValue(uart_com + "Reg_count3",0);
        MainWindow::iniFile->setValue(uart_com + "Data_type3",0);
        MainWindow::iniFile->setValue(uart_com + "Data_format3",0);
    }
    else
    {
    }

    ui->comboBox_485_identify->setCurrentIndex(0);
    ui->comboBox_485_funcode->setCurrentIndex(0);
    ui->lineEdit_485_regAddr->setText("");
    ui->comboBox_485_regNum->setCurrentIndex(0);
    ui->comboBox_485_type->setCurrentIndex(0);
    ui->comboBox_485_format->setCurrentIndex(0);
}

void canshu_widget::modbus_comm_init()
{
    bool ok;
    modbus[0] = {0x01,//COM1串口号
                 (uint8_t)MainWindow::iniFile->value("/UART1/ADDR").toString().toInt(&ok,16),//设备地址
                 (uint8_t)MainWindow::iniFile->value("/UART1/Protocol").toUInt(),//主从协议
                 {comm_485_identify[MainWindow::iniFile->value("/UART1/Identify1").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART1/Identify2").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART1/Identify3").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART1/Identify4").toUInt()]},//数据标识符
                 {comm_485_fun_code[MainWindow::iniFile->value("/UART1/Fun_code1").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART1/Fun_code2").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART1/Fun_code3").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART1/Fun_code4").toUInt()]},//功能码
                 {(uint16_t)MainWindow::iniFile->value("/UART1/Reg_addr1").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART1/Reg_addr2").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART1/Reg_addr3").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART1/Reg_addr4").toString().toInt(&ok,16)},//寄存器地址
                 {comm_485_reg_count[MainWindow::iniFile->value("/UART1/Reg_count1").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART1/Reg_count2").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART1/Reg_count3").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART1/Reg_count4").toUInt()]},//寄存器数量
                 {(uint8_t)MainWindow::iniFile->value("/UART1/Data_type1").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART1/Data_type2").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART1/Data_type3").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART1/Data_type4").toUInt()},//数据类型
                 {(uint8_t)MainWindow::iniFile->value("/UART1/Data_format1").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART1/Data_format2").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART1/Data_format3").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART1/Data_format4").toUInt()},//数据格式
                 {false,false,false,false},//发送标记
                 0x00,//接收的数据
                 0x00};//待通信处理的数据

    modbus[1] = {0x06,//COM2串口号
                 (uint8_t)MainWindow::iniFile->value("/UART2/ADDR").toString().toInt(&ok,16),//设备地址
                 (uint8_t)MainWindow::iniFile->value("/UART2/Protocol").toUInt(),//主从协议
                 {comm_485_identify[MainWindow::iniFile->value("/UART2/Identify1").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART2/Identify2").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART2/Identify3").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART2/Identify4").toUInt()]},//数据标识符
                 {comm_485_fun_code[MainWindow::iniFile->value("/UART2/Fun_code1").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART2/Fun_code2").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART2/Fun_code3").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART2/Fun_code4").toUInt()]},//功能码
                 {(uint16_t)MainWindow::iniFile->value("/UART2/Reg_addr1").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART2/Reg_addr2").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART2/Reg_addr3").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART2/Reg_addr4").toString().toInt(&ok,16)},//寄存器地址
                 {comm_485_reg_count[MainWindow::iniFile->value("/UART2/Reg_count1").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART2/Reg_count2").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART2/Reg_count3").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART2/Reg_count4").toUInt()]},//寄存器数量
                 {(uint8_t)MainWindow::iniFile->value("/UART2/Data_type1").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART2/Data_type2").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART2/Data_type3").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART2/Data_type4").toUInt()},//数据类型
                 {(uint8_t)MainWindow::iniFile->value("/UART2/Data_format1").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART2/Data_format2").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART2/Data_format3").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART2/Data_format4").toUInt()},//数据格式
                 {false,false,false,false},//发送标记
                 0x00,//接收的数据
                 0x00};//待通信处理的数据

    modbus[2] = {0x03,//COM3串口号
                 (uint8_t)MainWindow::iniFile->value("/UART3/ADDR").toString().toInt(&ok,16),//设备地址
                 (uint8_t)MainWindow::iniFile->value("/UART3/Protocol").toUInt(),//主从协议
                 {comm_485_identify[MainWindow::iniFile->value("/UART3/Identify1").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART3/Identify2").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART3/Identify3").toUInt()],comm_485_identify[MainWindow::iniFile->value("/UART3/Identify4").toUInt()]},//数据标识符
                 {comm_485_fun_code[MainWindow::iniFile->value("/UART3/Fun_code1").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART3/Fun_code2").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART3/Fun_code3").toUInt()],comm_485_fun_code[MainWindow::iniFile->value("/UART3/Fun_code4").toUInt()]},//功能码
                 {(uint16_t)MainWindow::iniFile->value("/UART3/Reg_addr1").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART3/Reg_addr2").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART3/Reg_addr3").toString().toInt(&ok,16),(uint16_t)MainWindow::iniFile->value("/UART3/Reg_addr4").toString().toInt(&ok,16)},//寄存器地址
                 {comm_485_reg_count[MainWindow::iniFile->value("/UART3/Reg_count1").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART3/Reg_count2").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART3/Reg_count3").toUInt()],comm_485_reg_count[MainWindow::iniFile->value("/UART3/Reg_count4").toUInt()]},//寄存器数量
                 {(uint8_t)MainWindow::iniFile->value("/UART3/Data_type1").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART3/Data_type2").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART3/Data_type3").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART3/Data_type4").toUInt()},//数据类型
                 {(uint8_t)MainWindow::iniFile->value("/UART3/Data_format1").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART3/Data_format2").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART3/Data_format3").toUInt(),(uint8_t)MainWindow::iniFile->value("/UART3/Data_format4").toUInt()},//数据格式
                 {false,false,false,false},//发送标记
                 0x00,//接收的数据
                 0x00};//待通信处理的数据

    modbus[3] = {0x04,//COM4串口号-开度仪
                 (uint8_t)MainWindow::iniFile->value("/KDY/ADDR").toString().toInt(&ok,16),//设备地址
                 0,//主站协议
                 {0xA1,0xA2,0xFF,0xFF},//数据标识符（A1：开度值  A2：开度仪状态）
                 {0x03,0x03,0,0},//功能码
                 {0x00,0x03,0,0},//寄存器地址
                 {0x01,0x01,0,0},//寄存器数量
                 {0,0,0,0},//数据类型
                 {0,0,0,0},//数据格式
                 {false,false,false,false},//发送标记
                 0x00,//接收的数据
                 0x00};//待通信处理的数据
    data_result.data_flow_inst = 0;
    data_result.data_flow_total = 0;
    data_result.data_water = 0;
    data_result.data_flow_speed = 0;
}

void canshu_widget::on_comboBox_485_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "水位")
    {
        ui->lineEdit_multipy->setText(MainWindow::iniFile->value("/SAMPLING_Water/Multipy").toString());
        ui->lineEdit_divide->setText(MainWindow::iniFile->value("/SAMPLING_Water/Divide").toString());
        ui->lineEdit_add->setText(MainWindow::iniFile->value("/SAMPLING_Water/Add").toString());
        ui->lineEdit_subtract->setText(MainWindow::iniFile->value("/SAMPLING_Water/Subtract").toString());
    }
    else if(arg1 == "瞬时流量")
    {
        ui->lineEdit_multipy->setText(MainWindow::iniFile->value("/SAMPLING_flow_inst/Multipy").toString());
        ui->lineEdit_divide->setText(MainWindow::iniFile->value("/SAMPLING_flow_inst/Divide").toString());
        ui->lineEdit_add->setText(MainWindow::iniFile->value("/SAMPLING_flow_inst/Add").toString());
        ui->lineEdit_subtract->setText(MainWindow::iniFile->value("/SAMPLING_flow_inst/Subtract").toString());
    }
    else if(arg1 == "累计流量")
    {
        ui->lineEdit_multipy->setText(MainWindow::iniFile->value("/SAMPLING_flow_total/Multipy").toString());
        ui->lineEdit_divide->setText(MainWindow::iniFile->value("/SAMPLING_flow_total/Divide").toString());
        ui->lineEdit_add->setText(MainWindow::iniFile->value("/SAMPLING_flow_total/Add").toString());
        ui->lineEdit_subtract->setText(MainWindow::iniFile->value("/SAMPLING_flow_total/Subtract").toString());
    }
    else
    {
        ui->lineEdit_multipy->setText(MainWindow::iniFile->value("/SAMPLING_flow_speed/Multipy").toString());
        ui->lineEdit_divide->setText(MainWindow::iniFile->value("/SAMPLING_flow_speed/Divide").toString());
        ui->lineEdit_add->setText(MainWindow::iniFile->value("/SAMPLING_flow_speed/Add").toString());
        ui->lineEdit_subtract->setText(MainWindow::iniFile->value("/SAMPLING_flow_speed/Subtract").toString());
    }
}

void canshu_widget::on_pushButton_kdy_start_clicked()
{
    emit kdy_signal(5);
}

void canshu_widget::on_pushButton_kdy_stop_clicked()
{
    emit kdy_signal(6);
}

void canshu_widget::on_pushButton_kdy_slave_clicked()
{
    if(ui->lineEdit_kdy_time->text().toUInt() >= 10)
        ui->lineEdit_kdy_time->setText("10");
#ifdef ARM
    serial_init(serial[4],"ttyCH343USB1",ui->BaudBox_kdy->currentText().toInt());
#endif

    MainWindow::iniFile->setValue("/KDY/Baud",ui->BaudBox_kdy->currentText());
    MainWindow::iniFile->setValue("/KDY/ADDR",ui->lineEdit_addr_kdy->text());
    MainWindow::iniFile->setValue("/KDY/UpLimit",ui->lineEdit_kdy_upLimit->text());
    MainWindow::iniFile->setValue("/KDY/DownLimit",ui->lineEdit_kdy_downLimit->text());
    MainWindow::iniFile->setValue("/KDY/Data",ui->lineEdit_kdy_data->text());
    MainWindow::iniFile->setValue("/KDY/Time",ui->lineEdit_kdy_time->text());

    modbus[3].device_addr = MainWindow::iniFile->value("/KDY/ADDR").toInt();
    kdy.upLimit = MainWindow::iniFile->value("/KDY/UpLimit").toInt();
    kdy.downLimit = MainWindow::iniFile->value("/KDY/DownLimit").toInt();
    kdy.data = MainWindow::iniFile->value("/KDY/Data").toInt();
    kdy.time = MainWindow::iniFile->value("/KDY/Time").toInt();

    QFile file("/home/kd_unit.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        if(ui->comboBox_kdUnit->currentText() == "mm")
        {
            file.write("0");
            kdy.unit = "mm";
        }
        else
        {
            file.write("1");
            kdy.unit = "cm";
        }
        file.flush();
        file.close();
    }
    else
        ;

#ifdef ARM
    timer->start(1000);
#endif
}

//数据转换 字符串转16进制数据处理
static char convertHexChart(char ch)
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

//数据转换 字符串转十六进制
static void StringToHex(QString str, QByteArray &senddata)
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

void canshu_widget::on_save_Button_tcpTime_clicked()
{
    QByteArray station_addr = 0;

    if(ui->lineEdit_fixed_reportTime->text().toUInt() <= 5)
        ui->lineEdit_fixed_reportTime->setText("5");
    if(ui->lineEdit_add_reportTime->text().toUInt() <= 5)
        ui->lineEdit_add_reportTime->setText("5");

    if(ui->comboBox_report->currentText() == "水文")
    {
        MainWindow::iniFile->setValue("/SW_PROTOCOL/Central_addr",ui->lineEdit_central_addr->text());
        MainWindow::iniFile->setValue("/SW_PROTOCOL/Station_addr",ui->lineEdit_station_addr->text());
        MainWindow::iniFile->setValue("/SW_PROTOCOL/Password",ui->lineEdit_report_password->text());
        MainWindow::iniFile->setValue("/SW_PROTOCOL/Fixed_time",ui->lineEdit_fixed_reportTime->text());
        MainWindow::iniFile->setValue("/SW_PROTOCOL/Add_time",ui->lineEdit_add_reportTime->text());
        MainWindow::iniFile->setValue("/SW_PROTOCOL/Element",ui->lineEdit_report_type->text());

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
        report_SW_headhex->add_report_minute = MainWindow::iniFile->value("/SW_PROTOCOL/Add_time").toUInt();
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
    }
    else
    {
        MainWindow::iniFile->setValue("/SZY_PROTOCOL/Station_addr",ui->lineEdit_station_addr->text());
        MainWindow::iniFile->setValue("/SZY_PROTOCOL/Password",ui->lineEdit_report_password->text());
        MainWindow::iniFile->setValue("/SZY_PROTOCOL/Fixed_time",ui->lineEdit_fixed_reportTime->text());
        MainWindow::iniFile->setValue("/SZY_PROTOCOL/Element",ui->lineEdit_report_type->text());

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
    }
    emit ReSendClear(1);
}

void canshu_widget::on_comboBox_report_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "水文")
    {
        ui->lineEdit_central_addr->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Central_addr").toString());
        ui->lineEdit_station_addr->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Station_addr").toString());
        ui->lineEdit_report_password->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Password").toString());
        ui->lineEdit_fixed_reportTime->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Fixed_time").toString());
        ui->lineEdit_add_reportTime->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Add_time").toString());
        ui->lineEdit_report_type->setText(MainWindow::iniFile->value("/SW_PROTOCOL/Element").toString());

        ui->checkBox_SW_uniform_time->show();
        ui->checkBox_SW_hour->show();
        ui->pushButton_SW_test->show();
        ui->label_37->show();
        ui->label_38->show();
        ui->lineEdit_add_reportTime->show();
    }
    else
    {
        ui->lineEdit_station_addr->setText(MainWindow::iniFile->value("/SZY_PROTOCOL/Station_addr").toString());
        ui->lineEdit_report_password->setText(MainWindow::iniFile->value("/SZY_PROTOCOL/Password").toString());
        ui->lineEdit_fixed_reportTime->setText(MainWindow::iniFile->value("/SZY_PROTOCOL/Fixed_time").toString());
        ui->lineEdit_report_type->setText(MainWindow::iniFile->value("/SZY_PROTOCOL/Element").toString());

        ui->checkBox_SW_uniform_time->hide();
        ui->checkBox_SW_hour->hide();
        ui->pushButton_SW_test->hide();
        ui->label_37->hide();
        ui->label_38->hide();
        ui->lineEdit_add_reportTime->hide();
    }
}

void canshu_widget::on_pushButton_SW_test_clicked()
{
    emit SW_test_signal(1);
}

void canshu_widget::on_checkBox_SW_uniform_time_stateChanged(int arg1)
{
    QFile file("/home/SW_report_uniform_time.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        if(arg1)
        {
            file.write("1");
            report_SW_headhex->report_type_select[0] = true;
        }
        else
        {
            file.write("0");
            report_SW_headhex->report_type_select[0] = false;
        }
        file.flush();
        file.close();
    }
    else
        return;
}

void canshu_widget::on_checkBox_SW_hour_stateChanged(int arg1)
{
    QFile file("/home/SW_report_hour.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        if(arg1)
        {
            file.write("1");
            report_SW_headhex->report_type_select[1] = true;
        }
        else
        {
            file.write("0");
            report_SW_headhex->report_type_select[1] = false;
        }
        file.flush();
        file.close();
    }
    else
        return;
}

void canshu_widget::on_comboBox_485_protocol_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Modbus主站")
    {
        ui->label_select1->show();
        ui->label_select2->show();
        ui->label_select3->show();
        ui->label_select4->show();
        ui->label_select5->show();
        ui->label_select6->show();
        ui->label_select7->show();
        ui->comboBox_485_num->show();
        ui->comboBox_485_identify->show();
        ui->comboBox_485_funcode->show();
        ui->lineEdit_485_regAddr->show();
        ui->comboBox_485_regNum->show();
        ui->comboBox_485_type->show();
        ui->comboBox_485_format->show();
    }
    else
    {
        ui->label_select1->hide();
        ui->label_select2->hide();
        ui->label_select3->hide();
        ui->label_select4->hide();
        ui->label_select5->hide();
        ui->label_select6->hide();
        ui->label_select7->hide();
        ui->comboBox_485_num->hide();
        ui->comboBox_485_identify->hide();
        ui->comboBox_485_funcode->hide();
        ui->lineEdit_485_regAddr->hide();
        ui->comboBox_485_regNum->hide();
        ui->comboBox_485_type->hide();
        ui->comboBox_485_format->hide();
    }
}
