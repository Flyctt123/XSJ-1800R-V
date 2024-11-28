#include "history_widget.h"
#include "ui_history_widget.h"

history_widget::history_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history_widget)
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

    //chart = ui->QChartView_shuiwei->chart();
    history_button_init(ui->button_water_timestart);
    history_button_init(ui->button_water_determine);
    history_button_init(ui->button_flow_speed_timestart);
    history_button_init(ui->button_flow_speed_determine);
    history_button_init(ui->button_flow_now_timestart);
    history_button_init(ui->button_flow_now_determine);
    history_button_init(ui->button_rain_now_timestart);
    history_button_init(ui->button_rain_now_determine);

    //model = new QStandardItemModel();
//    series = new QSplineSeries();//创建一个样条曲线对象

    history_data_base=QSqlDatabase::addDatabase("QSQLITE");//widget调用数据库不能添加connetc号，会找不到数据
    history_data_base.setDatabaseName(MainWindow::dbFile);
    history_data_base.open();
    model = new QSqlQueryModel(this);
}

history_widget::~history_widget()
{
    delete ui;
}

void history_widget::history_button_init(QPushButton *button_init)
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

void history_widget::changedata()
{
    calendar->hide();
    ui->label_date_water->setText(calendar->selectedDate().toString("yyyy-MM-dd"));
    ui->label_date_flow_speed->setText(calendar->selectedDate().toString("yyyy-MM-dd"));
    ui->label_date_flow_now->setText(calendar->selectedDate().toString("yyyy-MM-dd"));
    ui->label_date_rain_now->setText(calendar->selectedDate().toString("yyyy-MM-dd"));
}

void history_widget::excel_load_5min(QString tableName,QTableView *tableview,QString data_time1,QString data_time2)
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
    tableview->hideColumn(3);//隐藏第n列
    tableview->hideColumn(4);//隐藏第n列
    tableview->hideColumn(5);//隐藏第n列
    tableview->show();

//    uint16_t line_num = 0;
//    delete model;
//    model = new QStandardItemModel();

//    QString path = QDir::currentPath();//获取当前工程目录
//    /* 加载数据 */
//    QString strAll;
//    QStringList strList;    //创建字符串列表
//    QFile file(path + "/date/date_shuiwei_15min_20230713.txt");
//    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        //把文件所有信息读出来
//        QTextCodec *codec = QTextCodec::codecForName("utf8");//支持读取中文
//        QTextStream stream(&file);
//        stream.setCodec(codec);//输出流的设置
//        strAll = stream.readAll();
//    }
//    file.close();
//    strList = strAll.split("\n");//换行符来分割.txt文本

//    tableview->setStyleSheet("background: rgb(255, 255, 255);font: 9pt 黑体 bold;color: rgb(0, 0, 0)");

//    model->setItem(0, 0, new QStandardItem("时间"));
//    for(uint8_t i=0;i<32;i++)
//    {
//        model->setItem(0, i+1, new QStandardItem(strList.at(line_num)));
//        line_num = line_num + 2;
//    }
//    line_num = 0;
//    model->setItem(1, 0, new QStandardItem("数据(mm)"));
//    for(uint8_t i=0;i<32;i++)
//    {
//        model->setItem(1, i+1, new QStandardItem(strList.at(line_num+1)));
//        line_num = line_num + 2;
//    }

//    line_num = 64;
//    model->setItem(2, 0, new QStandardItem("时间"));
//    for(uint8_t i=0;i<32;i++)
//    {
//        model->setItem(2, i+1, new QStandardItem(strList.at(line_num)));
//        line_num = line_num + 2;
//    }
//    line_num = 64;
//    model->setItem(3, 0, new QStandardItem("数据(mm)"));
//    for(uint8_t i=0;i<32;i++)
//    {
//        model->setItem(3, i+1, new QStandardItem(strList.at(line_num+1)));
//        line_num = line_num + 2;
//    }

//    line_num = 128;
//    model->setItem(4, 0, new QStandardItem("时间"));
//    for(uint8_t i=0;i<32;i++)
//    {
//        model->setItem(4, i+1, new QStandardItem(strList.at(line_num)));
//        line_num = line_num + 2;
//    }
//    line_num = 128;
//    model->setItem(5, 0, new QStandardItem("数据(mm)"));
//    for(uint8_t i=0;i<32;i++)
//    {
//        model->setItem(5, i+1, new QStandardItem(strList.at(line_num+1)));
//        line_num = line_num + 2;
//    }

//    for(uint8_t i=0;i<33;i++)
//    {
//        for(uint8_t j=0;j<6;j=j+2)
//            model->item(j, i)->setBackground(QColor(198,198,198));
//    }

//    /* 自适应所有列，让它布满空间 */
//    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    tableview->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

//    /* 不显示行数列数 */
//    tableview->horizontalHeader()->setVisible(false);
//    tableview->verticalHeader()->setVisible(false);

//    /* 合并单元格 */
//    tableview->setSpan(0,2,2,1);
//    tableview->setSpan(0,3,2,1);

//    /* 设置表格视图数据 */
//    tableview->setModel(model);
//    tableview->hide();
//    /* 指定行宽 */
//    //tableview->setColumnWidth(1, 180);
}

void history_widget::on_button_water_timestart_clicked()
{
    calendar->show();
}

void history_widget::on_button_flow_speed_timestart_clicked()
{
    calendar->show();
}

void history_widget::on_button_flow_now_timestart_clicked()
{
    calendar->show();
}

void history_widget::on_button_rain_now_timestart_clicked()
{
    calendar->show();
}

void history_widget::on_button_water_determine_clicked()
{
    if(ui->label_date_water->text() == "")
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
    excel_load_5min("Water",ui->tableView_water,data_time1,data_time2);
}

void history_widget::on_button_rain_now_determine_clicked()
{
    if(ui->label_date_rain_now->text() == "")
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
    excel_load_5min("Rain",ui->tableView_rain_now,data_time1,data_time2);
}

void history_widget::on_button_flow_speed_determine_clicked()
{
    if(ui->label_date_flow_speed->text() == "")
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
    excel_load_5min("Speed",ui->tableView_flow_speed,data_time1,data_time2);
}

void history_widget::on_button_flow_now_determine_clicked()
{
    if(ui->label_date_flow_now->text() == "")
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
    excel_load_5min("Flow",ui->tableView_flow_now,data_time1,data_time2);
}
