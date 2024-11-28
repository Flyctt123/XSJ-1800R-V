#include "camera_widget.h"
#include "ui_camera_widget.h"

extern DATA_RES data_result;
extern bool KeyBoard_Code,KeyBoard_ABC_Code,keyBoard_flag,keyBoard_ABC_flag;
OSD_flag osd_flag;

camera_widget::camera_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera_widget)
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
    camera_button_init(ui->pushButton_takephoto);
    camera_button_init(ui->pushButton_save);
    camera_button_init(ui->pushButton_osd_save);
    ui->lineEdit_ip->installEventFilter(this);
    ui->lineEdit_name->installEventFilter(this);
    ui->lineEdit_password->installEventFilter(this);

    ui->lineEdit_ip->setText(MainWindow::iniFile->value("/Camera/IP1").toString());
    ui->lineEdit_name->setText(MainWindow::iniFile->value("/Camera/Name1").toString());
    ui->lineEdit_password->setText(MainWindow::iniFile->value("/Camera/Password1").toString());
    ui->checkBox_open->setChecked(MainWindow::iniFile->value("/Camera/Open1").toUInt());
    ui->checkBox_water->setChecked(MainWindow::iniFile->value("/OSD/Water").toUInt());
    ui->checkBox_flow_current->setChecked(MainWindow::iniFile->value("/OSD/Flow_current").toUInt());

    osd_flag.osd_water = MainWindow::iniFile->value("/OSD/Water").toUInt();
    osd_flag.osd_flow_inst = MainWindow::iniFile->value("/OSD/Flow_current").toUInt();

    timer =new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(time_out()));//抓拍等待1秒
}

camera_widget::~camera_widget()
{
    delete ui;
}

bool camera_widget::eventFilter(QObject *watch, QEvent *evn)
{
    if ((watch == ui->lineEdit_ip) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_ip);
    }
    if ((watch == ui->lineEdit_name) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_name);
    }
    if ((watch == ui->lineEdit_password) && evn->type() == QEvent::MouseButtonPress)
    {
        callKeyBoard_ABC(ui->lineEdit_password);
    }

    return QWidget::eventFilter(watch,evn);
}

void camera_widget::callKeyBoard(QLineEdit *a)
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

void camera_widget::callKeyBoard_ABC(QLineEdit *a)
{
    if(KeyBoard_ABC_Code==false)
    {
        keyBoard_ABC = new KeyBoard_ABC(0, a);
        keyBoard_ABC->setGeometry(2, 120, 476, 150);
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

void camera_widget::camera_button_init(QPushButton *button_init)
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

void camera_widget::on_pushButton_takephoto_clicked()
{
    ui->label_image->setText("抓拍图片中...");
    timer->start(800);
    if(ui->comboBox_takephoto->currentIndex() == 0)
    {
        QString camera_ip = MainWindow::iniFile->value("/Camera/IP1").toString();
        QString camera_name = MainWindow::iniFile->value("/Camera/Name1").toString();
        QString camera_password = MainWindow::iniFile->value("/Camera/Password1").toString();

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
                          "-d '<TextOverlayList>" + osd_code + "</TextOverlayList>' http://" + camera_name + ":" + camera_password + "@" + camera_ip +"/ISAPI/System/Video/inputs/channels/1/overlays/text" + " &";
        system(osd_cmd.toLatin1());

        //抓拍
        QString takephoto_cmd = "curl --insecure --anyauth -u " + camera_name + ":" + camera_password + " -X GET http://" + camera_name + ":" + camera_password + "@" + camera_ip +"/ISAPI/Streaming/channels/1/picture >/home/images/test.jpg" + " &";
        system(takephoto_cmd.toLatin1());
    }
    else if(ui->comboBox_takephoto->currentIndex() == 1)
    {
        QString camera_ip = MainWindow::iniFile->value("/Camera/IP2").toString();
        QString camera_name = MainWindow::iniFile->value("/Camera/Name2").toString();
        QString camera_password = MainWindow::iniFile->value("/Camera/Password2").toString();

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
        system(osd_cmd.toLatin1());

        //抓拍
        QString takephoto_cmd = "curl --insecure --anyauth -u " + camera_name + ":" + camera_password + " -X GET http://" + camera_name + ":" + camera_password + "@" + camera_ip +"/ISAPI/Streaming/channels/1/picture >/home/images/test.jpg" + " &";
        system(takephoto_cmd.toLatin1());
    }
    else
    {
        QString camera_ip = MainWindow::iniFile->value("/Camera/IP3").toString();
        QString camera_name = MainWindow::iniFile->value("/Camera/Name3").toString();
        QString camera_password = MainWindow::iniFile->value("/Camera/Password3").toString();

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
        system(osd_cmd.toLatin1());

        //抓拍
        QString takephoto_cmd = "curl --insecure --anyauth -u " + camera_name + ":" + camera_password + " -X GET http://" + camera_name + ":" + camera_password + "@" + camera_ip +"/ISAPI/Streaming/channels/1/picture >/home/images/test.jpg" + " &";
        system(takephoto_cmd.toLatin1());
    }
}

void camera_widget::on_checkBox_water_stateChanged(int arg1)
{
    if(arg1)
    {
        osd_flag.osd_water = 1;
    }
    else
    {
        osd_flag.osd_water = 0;
    }
}

void camera_widget::on_checkBox_flow_current_stateChanged(int arg1)
{
    if(arg1)
    {
        osd_flag.osd_flow_inst = 1;
    }
    else
    {
        osd_flag.osd_flow_inst = 0;
    }
}

void camera_widget::on_pushButton_save_clicked()
{
    if(ui->comboBox_init->currentIndex() == 0)
    {
        MainWindow::iniFile->setValue("/Camera/IP1",ui->lineEdit_ip->text());
        MainWindow::iniFile->setValue("/Camera/Name1",ui->lineEdit_name->text());
        MainWindow::iniFile->setValue("/Camera/Password1",ui->lineEdit_password->text());
    }
    else if(ui->comboBox_init->currentIndex() == 1)
    {
        MainWindow::iniFile->setValue("/Camera/IP2",ui->lineEdit_ip->text());
        MainWindow::iniFile->setValue("/Camera/Name2",ui->lineEdit_name->text());
        MainWindow::iniFile->setValue("/Camera/Password2",ui->lineEdit_password->text());
    }
    else
    {
        MainWindow::iniFile->setValue("/Camera/IP3",ui->lineEdit_ip->text());
        MainWindow::iniFile->setValue("/Camera/Name3",ui->lineEdit_name->text());
        MainWindow::iniFile->setValue("/Camera/Password3",ui->lineEdit_password->text());
    }
}

void camera_widget::on_comboBox_init_currentIndexChanged(int index)
{
    if(index == 0)
    {
        ui->lineEdit_ip->setText(MainWindow::iniFile->value("/Camera/IP1").toString());
        ui->lineEdit_name->setText(MainWindow::iniFile->value("/Camera/Name1").toString());
        ui->lineEdit_password->setText(MainWindow::iniFile->value("/Camera/Password1").toString());
        ui->checkBox_open->setChecked(MainWindow::iniFile->value("/Camera/Open1").toUInt());
    }
    else if(index == 1)
    {
        ui->lineEdit_ip->setText(MainWindow::iniFile->value("/Camera/IP2").toString());
        ui->lineEdit_name->setText(MainWindow::iniFile->value("/Camera/Name2").toString());
        ui->lineEdit_password->setText(MainWindow::iniFile->value("/Camera/Password2").toString());
        ui->checkBox_open->setChecked(MainWindow::iniFile->value("/Camera/Open2").toUInt());
    }
    else
    {
        ui->lineEdit_ip->setText(MainWindow::iniFile->value("/Camera/IP3").toString());
        ui->lineEdit_name->setText(MainWindow::iniFile->value("/Camera/Name3").toString());
        ui->lineEdit_password->setText(MainWindow::iniFile->value("/Camera/Password3").toString());
        ui->checkBox_open->setChecked(MainWindow::iniFile->value("/Camera/Open3").toUInt());
    }
}

void camera_widget::on_checkBox_open_stateChanged(int arg1)
{
    if(arg1)
    {
        if(ui->comboBox_init->currentIndex() == 0)
        {
            MainWindow::iniFile->setValue("/Camera/Open1",1);
        }
        else if(ui->comboBox_init->currentIndex() == 1)
        {
            MainWindow::iniFile->setValue("/Camera/Open2",1);
        }
        else
        {
            MainWindow::iniFile->setValue("/Camera/Open3",1);
        }
    }
    else
    {
        if(ui->comboBox_init->currentIndex() == 0)
        {
            MainWindow::iniFile->setValue("/Camera/Open1",0);
        }
        else if(ui->comboBox_init->currentIndex() == 1)
        {
            MainWindow::iniFile->setValue("/Camera/Open2",0);
        }
        else
        {
            MainWindow::iniFile->setValue("/Camera/Open3",0);
        }
    }
}

void camera_widget::time_out()
{
    timer->stop();
    QString fileFullName = "/home/images/test.jpg";
    QFileInfo fileInfo(fileFullName);
    if(fileInfo.isFile() && (fileInfo.size() > 0))//文件存在
    {
        QPixmap *pixmap = new QPixmap("/home/images/test.jpg");
        pixmap->scaled(ui->label_image->size(), Qt::KeepAspectRatio);//设置图片适应lable大小
        ui->label_image->setScaledContents(true);
        ui->label_image->setPixmap(*pixmap);
        QFile("/home/images/test.jpg").remove();
        return;
    }
    else
        ui->label_image->setText("抓拍图片失败！");
}

void camera_widget::on_pushButton_osd_save_clicked()
{
    if(osd_flag.osd_water == 1)
        MainWindow::iniFile->setValue("/OSD/Water",1);
    else
        MainWindow::iniFile->setValue("/OSD/Water",0);
    if(osd_flag.osd_flow_inst == 1)
        MainWindow::iniFile->setValue("/OSD/Flow_current",1);
    else
        MainWindow::iniFile->setValue("/OSD/Flow_current",0);
}
