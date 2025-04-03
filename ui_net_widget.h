/********************************************************************************
** Form generated from reading UI file 'net_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NET_WIDGET_H
#define UI_NET_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_net_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_sim_flag;
    QLabel *label_sim_num;
    QPushButton *pushButton_sim_signal;
    QLabel *label_sim_signal;
    QPushButton *pushButton_mobile;
    QLabel *label_mobile_num;
    QWidget *tab_2;
    QPushButton *pushButton_net_check;
    QLabel *label_net_flag;
    QLabel *label_local_ip;
    QPushButton *pushButton_local_ip;
    QWidget *tab_wifi;
    QCheckBox *checkBox_wifi;
    QLabel *label_wifi_flag;
    QLabel *label_wifi_flag_2;
    QLabel *label_wifi_flag_3;
    QLineEdit *lineEdit_wifi_name;
    QLineEdit *lineEdit_wifi_password;
    QPushButton *pushButton_wifiname;
    QPushButton *pushButton_wifi_password;
    QWidget *tab_4;
    QLabel *label;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *lineEdit_lora_local_addr;
    QComboBox *comboBox_lora_baud;
    QLineEdit *lineEdit_lora_point_addr;
    QLineEdit *lineEdit_lora_fre;
    QLineEdit *lineEdit_lora_channel;
    QLabel *label_19;
    QLabel *label_20;
    QPushButton *save_Button_lora;
    QWidget *tab_3;
    QLabel *label_2;
    QLineEdit *lineEdit_net_ip1;
    QLabel *label_3;
    QLineEdit *lineEdit_net_port1;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_net_ip2;
    QLineEdit *lineEdit_net_port2;
    QLabel *label_6;
    QLineEdit *lineEdit_net_ip4;
    QLineEdit *lineEdit_net_port4;
    QLabel *label_7;
    QLineEdit *lineEdit_net_port3;
    QLabel *label_8;
    QLineEdit *lineEdit_net_ip3;
    QLabel *label_9;
    QLabel *label_10;
    QComboBox *comboBox_1;
    QPushButton *pushButton_save;
    QLineEdit *lineEdit_net_port5;
    QLabel *label_16;
    QLineEdit *lineEdit_net_ip5;
    QLabel *label_17;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;

    void setupUi(QWidget *net_widget)
    {
        if (net_widget->objectName().isEmpty())
            net_widget->setObjectName(QString::fromUtf8("net_widget"));
        net_widget->resize(623, 303);
        net_widget->setStyleSheet(QString::fromUtf8(""));
        tabWidget = new QTabWidget(net_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        pushButton_sim_flag = new QPushButton(tab);
        pushButton_sim_flag->setObjectName(QString::fromUtf8("pushButton_sim_flag"));
        pushButton_sim_flag->setGeometry(QRect(10, 63, 111, 31));
        pushButton_sim_flag->setFocusPolicy(Qt::NoFocus);
        pushButton_sim_flag->setLayoutDirection(Qt::LeftToRight);
        pushButton_sim_flag->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_sim_num = new QLabel(tab);
        label_sim_num->setObjectName(QString::fromUtf8("label_sim_num"));
        label_sim_num->setGeometry(QRect(130, 70, 231, 16));
        label_sim_num->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_sim_num->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_sim_signal = new QPushButton(tab);
        pushButton_sim_signal->setObjectName(QString::fromUtf8("pushButton_sim_signal"));
        pushButton_sim_signal->setGeometry(QRect(10, 101, 111, 31));
        pushButton_sim_signal->setFocusPolicy(Qt::NoFocus);
        pushButton_sim_signal->setLayoutDirection(Qt::LeftToRight);
        pushButton_sim_signal->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_sim_signal = new QLabel(tab);
        label_sim_signal->setObjectName(QString::fromUtf8("label_sim_signal"));
        label_sim_signal->setGeometry(QRect(130, 109, 231, 16));
        label_sim_signal->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_sim_signal->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_mobile = new QPushButton(tab);
        pushButton_mobile->setObjectName(QString::fromUtf8("pushButton_mobile"));
        pushButton_mobile->setGeometry(QRect(10, 23, 111, 31));
        pushButton_mobile->setFocusPolicy(Qt::NoFocus);
        pushButton_mobile->setLayoutDirection(Qt::LeftToRight);
        pushButton_mobile->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_mobile_num = new QLabel(tab);
        label_mobile_num->setObjectName(QString::fromUtf8("label_mobile_num"));
        label_mobile_num->setGeometry(QRect(130, 30, 231, 16));
        label_mobile_num->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_mobile_num->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        pushButton_net_check = new QPushButton(tab_2);
        pushButton_net_check->setObjectName(QString::fromUtf8("pushButton_net_check"));
        pushButton_net_check->setGeometry(QRect(62, 80, 101, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        pushButton_net_check->setFont(font);
        pushButton_net_check->setFocusPolicy(Qt::NoFocus);
        pushButton_net_check->setLayoutDirection(Qt::LeftToRight);
        pushButton_net_check->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_net_flag = new QLabel(tab_2);
        label_net_flag->setObjectName(QString::fromUtf8("label_net_flag"));
        label_net_flag->setGeometry(QRect(178, 85, 151, 21));
        label_net_flag->setFont(font);
        label_net_flag->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";\n"
"color: rgb(255, 0, 0);"));
        label_local_ip = new QLabel(tab_2);
        label_local_ip->setObjectName(QString::fromUtf8("label_local_ip"));
        label_local_ip->setGeometry(QRect(178, 47, 161, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(10);
        label_local_ip->setFont(font1);
        pushButton_local_ip = new QPushButton(tab_2);
        pushButton_local_ip->setObjectName(QString::fromUtf8("pushButton_local_ip"));
        pushButton_local_ip->setGeometry(QRect(62, 40, 101, 31));
        pushButton_local_ip->setFont(font);
        pushButton_local_ip->setFocusPolicy(Qt::NoFocus);
        pushButton_local_ip->setLayoutDirection(Qt::LeftToRight);
        pushButton_local_ip->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        tabWidget->addTab(tab_2, QString());
        tab_wifi = new QWidget();
        tab_wifi->setObjectName(QString::fromUtf8("tab_wifi"));
        checkBox_wifi = new QCheckBox(tab_wifi);
        checkBox_wifi->setObjectName(QString::fromUtf8("checkBox_wifi"));
        checkBox_wifi->setGeometry(QRect(80, 30, 80, 20));
        checkBox_wifi->setFocusPolicy(Qt::NoFocus);
        checkBox_wifi->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        checkBox_wifi->setChecked(true);
        label_wifi_flag = new QLabel(tab_wifi);
        label_wifi_flag->setObjectName(QString::fromUtf8("label_wifi_flag"));
        label_wifi_flag->setGeometry(QRect(180, 32, 141, 16));
        label_wifi_flag->setFont(font1);
        label_wifi_flag_2 = new QLabel(tab_wifi);
        label_wifi_flag_2->setObjectName(QString::fromUtf8("label_wifi_flag_2"));
        label_wifi_flag_2->setGeometry(QRect(10, 70, 91, 31));
        label_wifi_flag_2->setFont(font1);
        label_wifi_flag_3 = new QLabel(tab_wifi);
        label_wifi_flag_3->setObjectName(QString::fromUtf8("label_wifi_flag_3"));
        label_wifi_flag_3->setGeometry(QRect(10, 110, 91, 31));
        label_wifi_flag_3->setFont(font1);
        lineEdit_wifi_name = new QLineEdit(tab_wifi);
        lineEdit_wifi_name->setObjectName(QString::fromUtf8("lineEdit_wifi_name"));
        lineEdit_wifi_name->setGeometry(QRect(110, 70, 131, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(10);
        lineEdit_wifi_name->setFont(font2);
        lineEdit_wifi_name->setFocusPolicy(Qt::StrongFocus);
        lineEdit_wifi_password = new QLineEdit(tab_wifi);
        lineEdit_wifi_password->setObjectName(QString::fromUtf8("lineEdit_wifi_password"));
        lineEdit_wifi_password->setGeometry(QRect(110, 110, 131, 31));
        lineEdit_wifi_password->setFont(font2);
        pushButton_wifiname = new QPushButton(tab_wifi);
        pushButton_wifiname->setObjectName(QString::fromUtf8("pushButton_wifiname"));
        pushButton_wifiname->setGeometry(QRect(250, 70, 93, 31));
        pushButton_wifiname->setFont(font1);
        pushButton_wifiname->setFocusPolicy(Qt::NoFocus);
        pushButton_wifi_password = new QPushButton(tab_wifi);
        pushButton_wifi_password->setObjectName(QString::fromUtf8("pushButton_wifi_password"));
        pushButton_wifi_password->setGeometry(QRect(250, 110, 93, 31));
        pushButton_wifi_password->setFont(font1);
        pushButton_wifi_password->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_wifi, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(false);
        label->setGeometry(QRect(10, 40, 91, 20));
        QFont font3;
        font3.setPointSize(10);
        label->setFont(font3);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 100, 91, 20));
        label_11->setFont(font3);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(tab_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 130, 91, 20));
        label_12->setFont(font3);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 10, 81, 20));
        label_13->setFont(font3);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_14 = new QLabel(tab_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 70, 91, 21));
        label_14->setFont(font3);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_lora_local_addr = new QLineEdit(tab_4);
        lineEdit_lora_local_addr->setObjectName(QString::fromUtf8("lineEdit_lora_local_addr"));
        lineEdit_lora_local_addr->setEnabled(false);
        lineEdit_lora_local_addr->setGeometry(QRect(100, 40, 51, 21));
        comboBox_lora_baud = new QComboBox(tab_4);
        comboBox_lora_baud->addItem(QString());
        comboBox_lora_baud->addItem(QString());
        comboBox_lora_baud->setObjectName(QString::fromUtf8("comboBox_lora_baud"));
        comboBox_lora_baud->setGeometry(QRect(100, 10, 81, 22));
        comboBox_lora_baud->setFocusPolicy(Qt::NoFocus);
        lineEdit_lora_point_addr = new QLineEdit(tab_4);
        lineEdit_lora_point_addr->setObjectName(QString::fromUtf8("lineEdit_lora_point_addr"));
        lineEdit_lora_point_addr->setGeometry(QRect(100, 70, 51, 21));
        lineEdit_lora_fre = new QLineEdit(tab_4);
        lineEdit_lora_fre->setObjectName(QString::fromUtf8("lineEdit_lora_fre"));
        lineEdit_lora_fre->setGeometry(QRect(100, 100, 51, 21));
        lineEdit_lora_channel = new QLineEdit(tab_4);
        lineEdit_lora_channel->setObjectName(QString::fromUtf8("lineEdit_lora_channel"));
        lineEdit_lora_channel->setGeometry(QRect(100, 130, 51, 21));
        label_19 = new QLabel(tab_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(160, 130, 31, 20));
        label_19->setFont(font3);
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_20 = new QLabel(tab_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(160, 100, 41, 20));
        label_20->setFont(font3);
        label_20->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        save_Button_lora = new QPushButton(tab_4);
        save_Button_lora->setObjectName(QString::fromUtf8("save_Button_lora"));
        save_Button_lora->setGeometry(QRect(260, 140, 93, 28));
        save_Button_lora->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(68, 28, 51, 20));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        label_2->setFont(font4);
        label_2->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_ip1 = new QLineEdit(tab_3);
        lineEdit_net_ip1->setObjectName(QString::fromUtf8("lineEdit_net_ip1"));
        lineEdit_net_ip1->setGeometry(QRect(110, 29, 131, 22));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Times New Roman"));
        font5.setPointSize(9);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        lineEdit_net_ip1->setFont(font5);
        lineEdit_net_ip1->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_ip1->setStyleSheet(QString::fromUtf8("font: 9pt \"Times New Roman\";"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(247, 28, 71, 22));
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_port1 = new QLineEdit(tab_3);
        lineEdit_net_port1->setObjectName(QString::fromUtf8("lineEdit_net_port1"));
        lineEdit_net_port1->setGeometry(QRect(310, 27, 60, 22));
        lineEdit_net_port1->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_port1->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(68, 54, 51, 20));
        label_4->setFont(font4);
        label_4->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(247, 78, 71, 22));
        label_5->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_ip2 = new QLineEdit(tab_3);
        lineEdit_net_ip2->setObjectName(QString::fromUtf8("lineEdit_net_ip2"));
        lineEdit_net_ip2->setGeometry(QRect(110, 55, 131, 22));
        lineEdit_net_ip2->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_ip2->setStyleSheet(QString::fromUtf8("font: 9pt \"Times New Roman\";"));
        lineEdit_net_port2 = new QLineEdit(tab_3);
        lineEdit_net_port2->setObjectName(QString::fromUtf8("lineEdit_net_port2"));
        lineEdit_net_port2->setGeometry(QRect(310, 53, 60, 22));
        lineEdit_net_port2->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_port2->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(68, 78, 51, 20));
        label_6->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_ip4 = new QLineEdit(tab_3);
        lineEdit_net_ip4->setObjectName(QString::fromUtf8("lineEdit_net_ip4"));
        lineEdit_net_ip4->setGeometry(QRect(110, 106, 131, 22));
        lineEdit_net_ip4->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_ip4->setStyleSheet(QString::fromUtf8("font: 9pt \"Times New Roman\";"));
        lineEdit_net_port4 = new QLineEdit(tab_3);
        lineEdit_net_port4->setObjectName(QString::fromUtf8("lineEdit_net_port4"));
        lineEdit_net_port4->setGeometry(QRect(310, 104, 60, 22));
        lineEdit_net_port4->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_port4->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(247, 54, 71, 22));
        label_7->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_port3 = new QLineEdit(tab_3);
        lineEdit_net_port3->setObjectName(QString::fromUtf8("lineEdit_net_port3"));
        lineEdit_net_port3->setGeometry(QRect(310, 78, 60, 22));
        lineEdit_net_port3->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_port3->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(247, 104, 71, 22));
        label_8->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_ip3 = new QLineEdit(tab_3);
        lineEdit_net_ip3->setObjectName(QString::fromUtf8("lineEdit_net_ip3"));
        lineEdit_net_ip3->setGeometry(QRect(110, 80, 131, 22));
        lineEdit_net_ip3->setFont(font5);
        lineEdit_net_ip3->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_ip3->setStyleSheet(QString::fromUtf8("font: 9pt \"Times New Roman\";"));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(68, 104, 51, 20));
        label_9->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 3, 61, 20));
        label_10->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_1 = new QComboBox(tab_3);
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->setObjectName(QString::fromUtf8("comboBox_1"));
        comboBox_1->setGeometry(QRect(0, 28, 71, 22));
        comboBox_1->setFocusPolicy(Qt::NoFocus);
        comboBox_1->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\256\213\344\275\223\";"));
        pushButton_save = new QPushButton(tab_3);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(299, 157, 71, 26));
        pushButton_save->setFocusPolicy(Qt::NoFocus);
        pushButton_save->setLayoutDirection(Qt::LeftToRight);
        pushButton_save->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        lineEdit_net_port5 = new QLineEdit(tab_3);
        lineEdit_net_port5->setObjectName(QString::fromUtf8("lineEdit_net_port5"));
        lineEdit_net_port5->setGeometry(QRect(310, 130, 60, 22));
        lineEdit_net_port5->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_port5->setStyleSheet(QString::fromUtf8("font: 10pt \"Times New Roman\";"));
        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(-2, 132, 121, 20));
        label_16->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_net_ip5 = new QLineEdit(tab_3);
        lineEdit_net_ip5->setObjectName(QString::fromUtf8("lineEdit_net_ip5"));
        lineEdit_net_ip5->setGeometry(QRect(110, 132, 131, 22));
        lineEdit_net_ip5->setFocusPolicy(Qt::NoFocus);
        lineEdit_net_ip5->setStyleSheet(QString::fromUtf8("font: 9pt \"Times New Roman\";"));
        label_17 = new QLabel(tab_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(247, 130, 71, 22));
        label_17->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_2 = new QComboBox(tab_3);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(0, 55, 71, 22));
        comboBox_2->setFocusPolicy(Qt::NoFocus);
        comboBox_2->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\256\213\344\275\223\";"));
        comboBox_3 = new QComboBox(tab_3);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(0, 81, 71, 22));
        comboBox_3->setFocusPolicy(Qt::NoFocus);
        comboBox_3->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\256\213\344\275\223\";"));
        comboBox_4 = new QComboBox(tab_3);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(0, 106, 71, 22));
        comboBox_4->setFocusPolicy(Qt::NoFocus);
        comboBox_4->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\256\213\344\275\223\";"));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(net_widget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(net_widget);
    } // setupUi

    void retranslateUi(QWidget *net_widget)
    {
        net_widget->setWindowTitle(QApplication::translate("net_widget", "Form", nullptr));
        pushButton_sim_flag->setText(QApplication::translate("net_widget", "\346\237\245\350\257\242SIM\345\215\241\345\217\267", nullptr));
        label_sim_num->setText(QString());
        pushButton_sim_signal->setText(QApplication::translate("net_widget", "\346\243\200\346\265\213\344\277\241\345\217\267\345\274\272\345\272\246", nullptr));
        label_sim_signal->setText(QString());
        pushButton_mobile->setText(QApplication::translate("net_widget", "\346\237\245\350\257\242\346\211\213\346\234\272\345\217\267", nullptr));
        label_mobile_num->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("net_widget", "4G", nullptr));
        pushButton_net_check->setText(QApplication::translate("net_widget", "\346\243\200\346\265\213\347\275\221\347\273\234\350\277\236\346\216\245", nullptr));
        label_net_flag->setText(QApplication::translate("net_widget", "\347\275\221\347\273\234\350\277\236\346\216\245\345\244\261\350\264\245\357\274\201", nullptr));
        label_local_ip->setText(QApplication::translate("net_widget", "<html><head/><body><p>192.168.1.1</p></body></html>", nullptr));
        pushButton_local_ip->setText(QApplication::translate("net_widget", "\350\216\267\345\217\226\346\234\254\346\234\272IP", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("net_widget", "\344\273\245\345\244\252\347\275\221", nullptr));
        checkBox_wifi->setText(QString());
        label_wifi_flag->setText(QApplication::translate("net_widget", "WIFI\345\267\262\345\274\200\345\220\257", nullptr));
        label_wifi_flag_2->setText(QApplication::translate("net_widget", "WIFI\350\264\246\345\217\267\357\274\232", nullptr));
        label_wifi_flag_3->setText(QApplication::translate("net_widget", "WIFI\345\257\206\347\240\201\357\274\232", nullptr));
        lineEdit_wifi_name->setText(QApplication::translate("net_widget", "HI-LINK-668", nullptr));
        lineEdit_wifi_password->setText(QApplication::translate("net_widget", "12345678", nullptr));
        pushButton_wifiname->setText(QApplication::translate("net_widget", "\347\241\256\350\256\244\344\277\256\346\224\271", nullptr));
        pushButton_wifi_password->setText(QApplication::translate("net_widget", "\347\241\256\350\256\244\344\277\256\346\224\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_wifi), QApplication::translate("net_widget", "WIFI", nullptr));
        label->setText(QApplication::translate("net_widget", "\346\234\254\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        label_11->setText(QApplication::translate("net_widget", "\351\200\232\344\277\241\351\200\237\347\216\207\357\274\232", nullptr));
        label_12->setText(QApplication::translate("net_widget", "\351\200\232\344\277\241\344\277\241\351\201\223\357\274\232", nullptr));
        label_13->setText(QApplication::translate("net_widget", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        label_14->setText(QApplication::translate("net_widget", "\345\257\271\347\253\257\345\234\260\345\235\200\357\274\232", nullptr));
        comboBox_lora_baud->setItemText(0, QApplication::translate("net_widget", "9600", nullptr));
        comboBox_lora_baud->setItemText(1, QApplication::translate("net_widget", "115200", nullptr));

        label_19->setText(QApplication::translate("net_widget", "MHz", nullptr));
        label_20->setText(QApplication::translate("net_widget", "kbps", nullptr));
        save_Button_lora->setText(QApplication::translate("net_widget", "\344\277\235\345\255\230\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("net_widget", "LORA", nullptr));
        label_2->setText(QApplication::translate("net_widget", "IP1\357\274\232", nullptr));
        lineEdit_net_ip1->setText(QApplication::translate("net_widget", "www.baidu.com", nullptr));
        label_3->setText(QApplication::translate("net_widget", " \347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label_4->setText(QApplication::translate("net_widget", "IP2\357\274\232", nullptr));
        label_5->setText(QApplication::translate("net_widget", " \347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label_6->setText(QApplication::translate("net_widget", "IP3\357\274\232", nullptr));
        label_7->setText(QApplication::translate("net_widget", " \347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label_8->setText(QApplication::translate("net_widget", " \347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        lineEdit_net_ip3->setText(QApplication::translate("net_widget", "192.168.1.1", nullptr));
        label_9->setText(QApplication::translate("net_widget", "IP4\357\274\232", nullptr));
        label_10->setText(QApplication::translate("net_widget", "\345\215\217\350\256\256\357\274\232", nullptr));
        comboBox_1->setItemText(0, QApplication::translate("net_widget", "\346\260\264\346\226\207", nullptr));
        comboBox_1->setItemText(1, QApplication::translate("net_widget", "\346\260\264\350\265\204\346\272\220", nullptr));

        pushButton_save->setText(QApplication::translate("net_widget", "\344\277\235\345\255\230\346\233\264\346\224\271", nullptr));
        label_16->setText(QApplication::translate("net_widget", "\347\273\264\346\212\244\345\271\263\345\217\260IP5\357\274\232", nullptr));
        label_17->setText(QApplication::translate("net_widget", " \347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("net_widget", "\346\260\264\346\226\207", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("net_widget", "\346\260\264\350\265\204\346\272\220", nullptr));

        comboBox_3->setItemText(0, QApplication::translate("net_widget", "\346\260\264\346\226\207", nullptr));
        comboBox_3->setItemText(1, QApplication::translate("net_widget", "\346\260\264\350\265\204\346\272\220", nullptr));

        comboBox_4->setItemText(0, QApplication::translate("net_widget", "\346\260\264\346\226\207", nullptr));
        comboBox_4->setItemText(1, QApplication::translate("net_widget", "\346\260\264\350\265\204\346\272\220", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("net_widget", "\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class net_widget: public Ui_net_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NET_WIDGET_H
