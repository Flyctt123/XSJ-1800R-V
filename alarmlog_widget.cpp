#include "alarmlog_widget.h"
#include "ui_alarmlog_widget.h"

extern bool KeyBoard_Code,keyBoard_flag;
extern DATA_RES data_result;

alarmLog_widget::alarmLog_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alarmLog_widget)
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
    ui->lineEdit_upLimit->installEventFilter(this);
    ui->lineEdit_downLimit->installEventFilter(this);

    ui->lineEdit_upLimit->setText(MainWindow::iniFile->value("/ALARM/Water_upLimit").toString());//水位上限
    ui->lineEdit_downLimit->setText(MainWindow::iniFile->value("/ALARM/Water_downLimit").toString());//水位下限

    MainWindow::iniFile->setValue("/ALARM/Water_upLimit",ui->lineEdit_upLimit->text());
    MainWindow::iniFile->setValue("/ALARM/Water_downLimit",ui->lineEdit_downLimit->text());

    data_result.data_water_upper_limit_value = MainWindow::iniFile->value("/ALARM/Water_upLimit").toDouble();
    data_result.data_water_lower_limit_value = MainWindow::iniFile->value("/ALARM/Water_downLimit").toDouble();
    data_result.data_flow_upper_limit_value = MainWindow::iniFile->value("/ALARM/flow_upLimit").toDouble();
    data_result.data_flow_lower_limit_value = MainWindow::iniFile->value("/ALARM/flow_downLimit").toDouble();
    data_result.data_rain_upper_limit_value = MainWindow::iniFile->value("/ALARM/Rain_upLimit").toDouble();
    data_result.data_rain_lower_limit_value = MainWindow::iniFile->value("/ALARM/Rain_downLimit").toDouble();
    data_result.data_speed_upper_limit_value = MainWindow::iniFile->value("/ALARM/Speed_upLimit").toDouble();
    data_result.data_speed_lower_limit_value = MainWindow::iniFile->value("/ALARM/Speed_downLimit").toDouble();

    calendar = new QCalendarWidget(this); //日历
    QDate dateMax(2040,1,1);
    calendar->setMaximumDate(dateMax);
    QDate dateMin(2024,1,1);
    calendar->setMinimumDate(dateMin);

    calendar->setLocale(QLocale(QLocale::Chinese));//设置中文
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);//去掉列表头
    calendar->setFont(QFont("SimSun",10,QFont::Bold));
    calendar->setGeometry(0,0,380,210);
    calendar->setFirstDayOfWeek(Qt::Monday);
    calendar->hide();
    connect(calendar,SIGNAL(clicked(QDate)),this,SLOT(changedata()));

    alarmlog_button_init(ui->tab_button_timestart);
    alarmlog_button_init(ui->tab_button_determine);
    alarmlog_button_init(ui->pushButton_log);
    alarmlog_button_init(ui->pushButton_log_clear);
    alarmlog_button_init(ui->pushButton);

    alarm_data_base=QSqlDatabase::addDatabase("QSQLITE");//widget调用数据库不能添加connetc号，会找不到数据
    alarm_data_base.setDatabaseName(MainWindow::dbFile);
    alarm_data_base.open();
    QSqlQuery sqlQuery(alarm_data_base);
    model = new QSqlQueryModel(this);
}

alarmLog_widget::~alarmLog_widget()
{
    delete ui;
}

bool alarmLog_widget::eventFilter(QObject *watch, QEvent *evn)
{
    if((watch == ui->lineEdit_upLimit) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_upLimit);
    }
    if((watch == ui->lineEdit_downLimit) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard(ui->lineEdit_downLimit);
    }

    return QWidget::eventFilter(watch,evn);
}

void alarmLog_widget::callKeyBoard(QLineEdit *a)
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

void alarmLog_widget::alarmlog_button_init(QPushButton *button_init)
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

void alarmLog_widget::changedata()
{
    calendar->hide();
    ui->label_time->setText(calendar->selectedDate().toString("yyyy-MM-dd"));
}

void alarmLog_widget::excel_load_5min(QString tableName, QTableView *tableview, QString data_time1, QString data_time2)
{
    model->setQuery(("SELECT * FROM " +tableName+ " WHERE mark >= %1 and mark <= %2").arg(data_time1).arg(data_time2));

    while(model->canFetchMore())//解决问题：QT的QSqlQuery或QSqlQueryModel每次最多只能缓存查询结果的256条
    {
        model->fetchMore();
    }

    tableview->verticalHeader()->setVisible(false);//不显示行数
    tableview->setModel(model);
    //指定列宽
    tableview->setColumnWidth(0, 60);
    tableview->setColumnWidth(1, 160);
    tableview->setColumnWidth(2, 120);
    //自适应行高
    tableview->resizeRowsToContents();
    tableview->scrollToBottom();//显示最新
    tableview->show();
}

void alarmLog_widget::on_tab_button_timestart_clicked()
{
    calendar->show();
}

void alarmLog_widget::on_pushButton_log_clicked()
{
    ui->plainTextEdit->clear();
#ifdef ARM
    QFile file("/home/log.txt");
#else
    QString path = QDir::currentPath();
    QFile file(path + "/home/log.txt");
#endif

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"Open log file failed!";
        return;
    }

//    QTextStream text(&file);
//    while (!text.atEnd()) {
//        QString strLine = text.readLine();
//        ui->plainTextEdit->appendPlainText(QString::fromUtf8(strLine.toLocal8Bit()));
//    }
//    file.close();

    //使用内存映射，加快读取
    qint64 fileSize = file.size(); // 获取文件的大小
    uchar *data = file.map(0, fileSize); // 将文件的全部内容映射到内存中，返回一个指向该内容的指针
    file.close();//文件的关闭不会影响到我们后续的内存映射部分。
    if(data)
    { // 如果映射成功
        QElapsedTimer timer;
        timer.start();
        QString text = QString::fromUtf8((char *)data, fileSize);
        file.unmap(data); // 取消映射
        ui->plainTextEdit->appendPlainText(text);
        //QTextCursor cursor = ui->plainTextEdit->textCursor();
        //cursor.movePosition(QTextCursor::Start);
        //ui->plainTextEdit->setTextCursor(cursor);//是为了实现将鼠标对应的光标移动到第一行，也就是日志的最上面。
    }
    else
    { // 如果映射失败
        qDebug() << "日志查询失败"; // 打印错误信息
    }
}

void alarmLog_widget::on_tab_button_determine_clicked()
{
    if(ui->label_time->text() == "")
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("未设置查询日期！"));
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
    QString data_time1 = calendar->selectedDate().toString("yyyyMMdd");
    QString data_time2 = calendar->selectedDate().addDays(1).toString("yyyyMMdd");
    excel_load_5min("Alarm",ui->tableView_data,data_time1,data_time2);
}

void alarmLog_widget::on_pushButton_log_clear_clicked()
{
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("提示"),QString("确定清除日志？"));
    m_box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    QTimer::singleShot(5000,m_box,SLOT(accept()));//5秒自动关闭，防止卡界面

    int ret = m_box->exec();
    if (ret == QMessageBox::Yes)
    {
        system("rm /home/log.txt");
        ui->plainTextEdit->clear();
    }
    else
    {
        ;
    }
}

void alarmLog_widget::on_pushButton_clicked()
{
    if(ui->comboBox->currentText() == "水位")
    {
        MainWindow::iniFile->setValue("/ALARM/Water_upLimit",ui->lineEdit_upLimit->text());
        MainWindow::iniFile->setValue("/ALARM/Water_downLimit",ui->lineEdit_downLimit->text());

        data_result.data_water_upper_limit_value = MainWindow::iniFile->value("/ALARM/Water_upLimit").toDouble();
        data_result.data_water_lower_limit_value = MainWindow::iniFile->value("/ALARM/Water_downLimit").toDouble();
    }
    else if(ui->comboBox->currentText() == "流量")
    {
        MainWindow::iniFile->setValue("/ALARM/flow_upLimit",ui->lineEdit_upLimit->text());
        MainWindow::iniFile->setValue("/ALARM/flow_downLimit",ui->lineEdit_downLimit->text());

        data_result.data_flow_upper_limit_value = MainWindow::iniFile->value("/ALARM/flow_upLimit").toDouble();
        data_result.data_flow_lower_limit_value = MainWindow::iniFile->value("/ALARM/flow_downLimit").toDouble();
    }
    else if(ui->comboBox->currentText() == "雨量")
    {
        MainWindow::iniFile->setValue("/ALARM/Rain_upLimit",ui->lineEdit_upLimit->text());
        MainWindow::iniFile->setValue("/ALARM/Rain_downLimit",ui->lineEdit_downLimit->text());

        data_result.data_rain_upper_limit_value = MainWindow::iniFile->value("/ALARM/Rain_upLimit").toDouble();
        data_result.data_rain_lower_limit_value = MainWindow::iniFile->value("/ALARM/Rain_downLimit").toDouble();
    }
    else
    {
        MainWindow::iniFile->setValue("/ALARM/Speed_upLimit",ui->lineEdit_upLimit->text());
        MainWindow::iniFile->setValue("/ALARM/Speed_downLimit",ui->lineEdit_downLimit->text());

        data_result.data_speed_upper_limit_value = MainWindow::iniFile->value("/ALARM/Speed_upLimit").toDouble();
        data_result.data_speed_lower_limit_value = MainWindow::iniFile->value("/ALARM/Speed_downLimit").toDouble();
    }
}

void alarmLog_widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "水位")
    {
        ui->lineEdit_upLimit->setText(MainWindow::iniFile->value("/ALARM/Water_upLimit").toString());
        ui->lineEdit_downLimit->setText(MainWindow::iniFile->value("/ALARM/Water_downLimit").toString());
    }
    else if(arg1 == "流量")
    {
        ui->lineEdit_upLimit->setText(MainWindow::iniFile->value("/ALARM/flow_upLimit").toString());
        ui->lineEdit_downLimit->setText(MainWindow::iniFile->value("/ALARM/flow_downLimit").toString());
    }
    else if(arg1 == "雨量")
    {
        ui->lineEdit_upLimit->setText(MainWindow::iniFile->value("/ALARM/Rain_upLimit").toString());
        ui->lineEdit_downLimit->setText(MainWindow::iniFile->value("/ALARM/Rain_downLimit").toString());
    }
    else
    {
        ui->lineEdit_upLimit->setText(MainWindow::iniFile->value("/ALARM/Speed_upLimit").toString());
        ui->lineEdit_downLimit->setText(MainWindow::iniFile->value("/ALARM/Speed_downLimit").toString());
    }
}
