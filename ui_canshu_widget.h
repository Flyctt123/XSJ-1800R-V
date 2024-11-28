/********************************************************************************
** Form generated from reading UI file 'canshu_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANSHU_WIDGET_H
#define UI_CANSHU_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_canshu_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBox_485_identify;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *save_Button_485;
    QLabel *label_select2;
    QComboBox *BaudBox;
    QComboBox *PortBox;
    QLabel *label_19;
    QLineEdit *lineEdit_485_addr;
    QLabel *label_select4;
    QLineEdit *lineEdit_485_regAddr;
    QLabel *label_select5;
    QComboBox *comboBox_485_regNum;
    QLabel *label_select6;
    QComboBox *comboBox_485_type;
    QComboBox *comboBox_485_format;
    QLabel *label_select7;
    QLabel *label_select1;
    QComboBox *comboBox_485_num;
    QPushButton *clear_Button_485;
    QComboBox *comboBox_485_protocol;
    QLabel *label_42;
    QComboBox *comboBox_485_funcode;
    QLabel *label_select3;
    QWidget *tab_5;
    QLabel *label_23;
    QComboBox *BaudBox_kdy;
    QLineEdit *lineEdit_addr_kdy;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *lineEdit_kdy_upLimit;
    QLabel *label_26;
    QLineEdit *lineEdit_kdy_downLimit;
    QLabel *label_30;
    QLineEdit *lineEdit_kdy_data;
    QLabel *label_32;
    QLineEdit *lineEdit_kdy_time;
    QPushButton *pushButton_kdy_start;
    QLabel *label_33;
    QPushButton *pushButton_kdy_stop;
    QPushButton *pushButton_kdy_slave;
    QWidget *tab_3;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_7;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QRadioButton *radioButton1_vol;
    QRadioButton *radioButton1_cur;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QRadioButton *radioButton2_vol;
    QRadioButton *radioButton2_cur;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButton3_vol;
    QRadioButton *radioButton3_cur;
    QWidget *layoutWidget4;
    QGridLayout *gridLayout_4;
    QRadioButton *radioButton4_vol;
    QRadioButton *radioButton4_cur;
    QWidget *layoutWidget5;
    QGridLayout *gridLayout_5;
    QRadioButton *radioButton5_vol;
    QRadioButton *radioButton5_cur;
    QWidget *layoutWidget6;
    QGridLayout *gridLayout_6;
    QRadioButton *radioButton6_vol;
    QRadioButton *radioButton6_cur;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QLabel *label_13;
    QLineEdit *lineEdit_multipy;
    QLineEdit *lineEdit_divide;
    QLineEdit *lineEdit_add;
    QLineEdit *lineEdit_subtract;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_20;
    QComboBox *comboBox_485;
    QLabel *label_40;
    QLabel *label_41;
    QLineEdit *lineEdit_water_base;
    QLineEdit *lineEdit_water_modify;
    QGroupBox *groupBox_3;
    QLabel *label_12;
    QLineEdit *lineEdit_rain_ratio;
    QLabel *label_16;
    QPushButton *save_Button_sampling;
    QWidget *tab_4;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *save_Button_tcpTime;
    QLineEdit *lineEdit_fixed_reportTime;
    QComboBox *comboBox_report;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QLineEdit *lineEdit_add_reportTime;
    QLabel *label_39;
    QLineEdit *lineEdit_report_type;
    QLineEdit *lineEdit_report_password;
    QLineEdit *lineEdit_station_addr;
    QLineEdit *lineEdit_central_addr;
    QPushButton *pushButton_SW_test;
    QCheckBox *checkBox_SW_uniform_time;
    QCheckBox *checkBox_SW_hour;

    void setupUi(QWidget *canshu_widget)
    {
        if (canshu_widget->objectName().isEmpty())
            canshu_widget->setObjectName(QString::fromUtf8("canshu_widget"));
        canshu_widget->resize(540, 366);
        canshu_widget->setStyleSheet(QString::fromUtf8(""));
        tabWidget = new QTabWidget(canshu_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        QFont font;
        font.setPointSize(9);
        tabWidget->setFont(font);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        comboBox_485_identify = new QComboBox(tab);
        comboBox_485_identify->addItem(QString());
        comboBox_485_identify->addItem(QString());
        comboBox_485_identify->addItem(QString());
        comboBox_485_identify->addItem(QString());
        comboBox_485_identify->addItem(QString());
        comboBox_485_identify->setObjectName(QString::fromUtf8("comboBox_485_identify"));
        comboBox_485_identify->setGeometry(QRect(80, 150, 101, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(9);
        comboBox_485_identify->setFont(font1);
        comboBox_485_identify->setFocusPolicy(Qt::NoFocus);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 4, 81, 20));
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 30, 81, 20));
        QFont font2;
        font2.setPointSize(10);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        save_Button_485 = new QPushButton(tab);
        save_Button_485->setObjectName(QString::fromUtf8("save_Button_485"));
        save_Button_485->setGeometry(QRect(302, 150, 71, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        save_Button_485->setFont(font3);
        save_Button_485->setFocusPolicy(Qt::NoFocus);
        save_Button_485->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_select2 = new QLabel(tab);
        label_select2->setObjectName(QString::fromUtf8("label_select2"));
        label_select2->setGeometry(QRect(0, 150, 81, 20));
        label_select2->setFont(font2);
        label_select2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BaudBox = new QComboBox(tab);
        BaudBox->addItem(QString());
        BaudBox->addItem(QString());
        BaudBox->setObjectName(QString::fromUtf8("BaudBox"));
        BaudBox->setGeometry(QRect(80, 30, 101, 25));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Times New Roman"));
        font4.setPointSize(9);
        BaudBox->setFont(font4);
        BaudBox->setFocusPolicy(Qt::NoFocus);
        PortBox = new QComboBox(tab);
        PortBox->setObjectName(QString::fromUtf8("PortBox"));
        PortBox->setGeometry(QRect(80, 2, 101, 25));
        PortBox->setFont(font4);
        PortBox->setFocusPolicy(Qt::NoFocus);
        label_19 = new QLabel(tab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(0, 60, 81, 20));
        label_19->setFont(font2);
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_485_addr = new QLineEdit(tab);
        lineEdit_485_addr->setObjectName(QString::fromUtf8("lineEdit_485_addr"));
        lineEdit_485_addr->setGeometry(QRect(80, 60, 101, 21));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font5.setPointSize(8);
        lineEdit_485_addr->setFont(font5);
        label_select4 = new QLabel(tab);
        label_select4->setObjectName(QString::fromUtf8("label_select4"));
        label_select4->setGeometry(QRect(190, 30, 101, 20));
        label_select4->setFont(font2);
        label_select4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_485_regAddr = new QLineEdit(tab);
        lineEdit_485_regAddr->setObjectName(QString::fromUtf8("lineEdit_485_regAddr"));
        lineEdit_485_regAddr->setGeometry(QRect(290, 30, 81, 21));
        lineEdit_485_regAddr->setFont(font5);
        label_select5 = new QLabel(tab);
        label_select5->setObjectName(QString::fromUtf8("label_select5"));
        label_select5->setGeometry(QRect(190, 56, 101, 20));
        label_select5->setFont(font2);
        label_select5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_485_regNum = new QComboBox(tab);
        comboBox_485_regNum->addItem(QString());
        comboBox_485_regNum->addItem(QString());
        comboBox_485_regNum->addItem(QString());
        comboBox_485_regNum->addItem(QString());
        comboBox_485_regNum->setObjectName(QString::fromUtf8("comboBox_485_regNum"));
        comboBox_485_regNum->setGeometry(QRect(290, 56, 81, 25));
        comboBox_485_regNum->setFont(font1);
        comboBox_485_regNum->setFocusPolicy(Qt::NoFocus);
        label_select6 = new QLabel(tab);
        label_select6->setObjectName(QString::fromUtf8("label_select6"));
        label_select6->setGeometry(QRect(190, 86, 101, 20));
        label_select6->setFont(font2);
        label_select6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_485_type = new QComboBox(tab);
        comboBox_485_type->addItem(QString());
        comboBox_485_type->addItem(QString());
        comboBox_485_type->addItem(QString());
        comboBox_485_type->setObjectName(QString::fromUtf8("comboBox_485_type"));
        comboBox_485_type->setGeometry(QRect(290, 86, 81, 25));
        comboBox_485_type->setFont(font1);
        comboBox_485_type->setFocusPolicy(Qt::NoFocus);
        comboBox_485_format = new QComboBox(tab);
        comboBox_485_format->addItem(QString());
        comboBox_485_format->addItem(QString());
        comboBox_485_format->addItem(QString());
        comboBox_485_format->addItem(QString());
        comboBox_485_format->setObjectName(QString::fromUtf8("comboBox_485_format"));
        comboBox_485_format->setGeometry(QRect(270, 116, 101, 25));
        comboBox_485_format->setFont(font5);
        comboBox_485_format->setFocusPolicy(Qt::NoFocus);
        label_select7 = new QLabel(tab);
        label_select7->setObjectName(QString::fromUtf8("label_select7"));
        label_select7->setGeometry(QRect(190, 116, 81, 20));
        label_select7->setFont(font2);
        label_select7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_select1 = new QLabel(tab);
        label_select1->setObjectName(QString::fromUtf8("label_select1"));
        label_select1->setGeometry(QRect(0, 120, 81, 20));
        label_select1->setFont(font2);
        label_select1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_485_num = new QComboBox(tab);
        comboBox_485_num->addItem(QString());
        comboBox_485_num->addItem(QString());
        comboBox_485_num->addItem(QString());
        comboBox_485_num->addItem(QString());
        comboBox_485_num->setObjectName(QString::fromUtf8("comboBox_485_num"));
        comboBox_485_num->setGeometry(QRect(80, 120, 101, 25));
        comboBox_485_num->setFont(font1);
        comboBox_485_num->setFocusPolicy(Qt::NoFocus);
        clear_Button_485 = new QPushButton(tab);
        clear_Button_485->setObjectName(QString::fromUtf8("clear_Button_485"));
        clear_Button_485->setGeometry(QRect(220, 150, 71, 31));
        clear_Button_485->setFont(font3);
        clear_Button_485->setFocusPolicy(Qt::NoFocus);
        clear_Button_485->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        comboBox_485_protocol = new QComboBox(tab);
        comboBox_485_protocol->addItem(QString());
        comboBox_485_protocol->addItem(QString());
        comboBox_485_protocol->setObjectName(QString::fromUtf8("comboBox_485_protocol"));
        comboBox_485_protocol->setGeometry(QRect(80, 90, 101, 25));
        comboBox_485_protocol->setFont(font5);
        comboBox_485_protocol->setFocusPolicy(Qt::NoFocus);
        label_42 = new QLabel(tab);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setGeometry(QRect(0, 90, 81, 20));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font6.setPointSize(10);
        label_42->setFont(font6);
        label_42->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_485_funcode = new QComboBox(tab);
        comboBox_485_funcode->addItem(QString());
        comboBox_485_funcode->addItem(QString());
        comboBox_485_funcode->addItem(QString());
        comboBox_485_funcode->addItem(QString());
        comboBox_485_funcode->setObjectName(QString::fromUtf8("comboBox_485_funcode"));
        comboBox_485_funcode->setGeometry(QRect(290, 2, 81, 25));
        comboBox_485_funcode->setFont(font1);
        comboBox_485_funcode->setFocusPolicy(Qt::NoFocus);
        label_select3 = new QLabel(tab);
        label_select3->setObjectName(QString::fromUtf8("label_select3"));
        label_select3->setGeometry(QRect(190, 4, 101, 20));
        label_select3->setFont(font2);
        label_select3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        label_23 = new QLabel(tab_5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(0, 15, 101, 20));
        label_23->setFont(font2);
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BaudBox_kdy = new QComboBox(tab_5);
        BaudBox_kdy->addItem(QString());
        BaudBox_kdy->addItem(QString());
        BaudBox_kdy->setObjectName(QString::fromUtf8("BaudBox_kdy"));
        BaudBox_kdy->setGeometry(QRect(100, 15, 71, 25));
        BaudBox_kdy->setFont(font4);
        BaudBox_kdy->setFocusPolicy(Qt::NoFocus);
        lineEdit_addr_kdy = new QLineEdit(tab_5);
        lineEdit_addr_kdy->setObjectName(QString::fromUtf8("lineEdit_addr_kdy"));
        lineEdit_addr_kdy->setGeometry(QRect(100, 50, 71, 21));
        label_24 = new QLabel(tab_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(0, 50, 101, 20));
        label_24->setFont(font2);
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_25 = new QLabel(tab_5);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(0, 80, 101, 20));
        label_25->setFont(font2);
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_kdy_upLimit = new QLineEdit(tab_5);
        lineEdit_kdy_upLimit->setObjectName(QString::fromUtf8("lineEdit_kdy_upLimit"));
        lineEdit_kdy_upLimit->setGeometry(QRect(100, 80, 71, 21));
        label_26 = new QLabel(tab_5);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(0, 110, 101, 20));
        label_26->setFont(font2);
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_kdy_downLimit = new QLineEdit(tab_5);
        lineEdit_kdy_downLimit->setObjectName(QString::fromUtf8("lineEdit_kdy_downLimit"));
        lineEdit_kdy_downLimit->setGeometry(QRect(100, 110, 71, 21));
        label_30 = new QLabel(tab_5);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(190, 80, 81, 20));
        label_30->setFont(font2);
        label_30->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_kdy_data = new QLineEdit(tab_5);
        lineEdit_kdy_data->setObjectName(QString::fromUtf8("lineEdit_kdy_data"));
        lineEdit_kdy_data->setGeometry(QRect(270, 80, 71, 21));
        label_32 = new QLabel(tab_5);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(190, 110, 81, 20));
        label_32->setFont(font2);
        label_32->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_kdy_time = new QLineEdit(tab_5);
        lineEdit_kdy_time->setObjectName(QString::fromUtf8("lineEdit_kdy_time"));
        lineEdit_kdy_time->setGeometry(QRect(270, 110, 71, 21));
        pushButton_kdy_start = new QPushButton(tab_5);
        pushButton_kdy_start->setObjectName(QString::fromUtf8("pushButton_kdy_start"));
        pushButton_kdy_start->setGeometry(QRect(110, 150, 71, 28));
        pushButton_kdy_start->setFocusPolicy(Qt::NoFocus);
        label_33 = new QLabel(tab_5);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(346, 110, 21, 20));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Times New Roman"));
        font7.setPointSize(10);
        label_33->setFont(font7);
        label_33->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton_kdy_stop = new QPushButton(tab_5);
        pushButton_kdy_stop->setObjectName(QString::fromUtf8("pushButton_kdy_stop"));
        pushButton_kdy_stop->setGeometry(QRect(190, 150, 71, 28));
        pushButton_kdy_stop->setFocusPolicy(Qt::NoFocus);
        pushButton_kdy_slave = new QPushButton(tab_5);
        pushButton_kdy_slave->setObjectName(QString::fromUtf8("pushButton_kdy_slave"));
        pushButton_kdy_slave->setGeometry(QRect(290, 150, 71, 28));
        pushButton_kdy_slave->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_5, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        layoutWidget = new QWidget(tab_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 96, 161));
        gridLayout_7 = new QGridLayout(layoutWidget);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setVerticalSpacing(3);
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_7->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_7->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_7->addWidget(label_5, 2, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_7->addWidget(label_6, 3, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_7->addWidget(label_7, 4, 0, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_7->addWidget(label_9, 5, 0, 1, 1);

        layoutWidget1 = new QWidget(tab_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 23, 161, 21));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton1_vol = new QRadioButton(layoutWidget1);
        radioButton1_vol->setObjectName(QString::fromUtf8("radioButton1_vol"));
        radioButton1_vol->setChecked(true);

        gridLayout->addWidget(radioButton1_vol, 0, 0, 1, 1);

        radioButton1_cur = new QRadioButton(layoutWidget1);
        radioButton1_cur->setObjectName(QString::fromUtf8("radioButton1_cur"));
        radioButton1_cur->setEnabled(false);

        gridLayout->addWidget(radioButton1_cur, 0, 1, 1, 1);

        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(120, 50, 161, 21));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton2_vol = new QRadioButton(layoutWidget2);
        radioButton2_vol->setObjectName(QString::fromUtf8("radioButton2_vol"));
        radioButton2_vol->setChecked(true);

        gridLayout_2->addWidget(radioButton2_vol, 0, 0, 1, 1);

        radioButton2_cur = new QRadioButton(layoutWidget2);
        radioButton2_cur->setObjectName(QString::fromUtf8("radioButton2_cur"));
        radioButton2_cur->setEnabled(false);
        radioButton2_cur->setChecked(false);

        gridLayout_2->addWidget(radioButton2_cur, 0, 1, 1, 1);

        layoutWidget3 = new QWidget(tab_3);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(120, 77, 161, 21));
        gridLayout_3 = new QGridLayout(layoutWidget3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        radioButton3_vol = new QRadioButton(layoutWidget3);
        radioButton3_vol->setObjectName(QString::fromUtf8("radioButton3_vol"));
        radioButton3_vol->setChecked(true);

        gridLayout_3->addWidget(radioButton3_vol, 0, 0, 1, 1);

        radioButton3_cur = new QRadioButton(layoutWidget3);
        radioButton3_cur->setObjectName(QString::fromUtf8("radioButton3_cur"));
        radioButton3_cur->setEnabled(false);

        gridLayout_3->addWidget(radioButton3_cur, 0, 1, 1, 1);

        layoutWidget4 = new QWidget(tab_3);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(121, 102, 161, 21));
        gridLayout_4 = new QGridLayout(layoutWidget4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        radioButton4_vol = new QRadioButton(layoutWidget4);
        radioButton4_vol->setObjectName(QString::fromUtf8("radioButton4_vol"));
        radioButton4_vol->setChecked(true);

        gridLayout_4->addWidget(radioButton4_vol, 0, 0, 1, 1);

        radioButton4_cur = new QRadioButton(layoutWidget4);
        radioButton4_cur->setObjectName(QString::fromUtf8("radioButton4_cur"));
        radioButton4_cur->setEnabled(false);

        gridLayout_4->addWidget(radioButton4_cur, 0, 1, 1, 1);

        layoutWidget5 = new QWidget(tab_3);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(120, 131, 161, 21));
        gridLayout_5 = new QGridLayout(layoutWidget5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        radioButton5_vol = new QRadioButton(layoutWidget5);
        radioButton5_vol->setObjectName(QString::fromUtf8("radioButton5_vol"));
        radioButton5_vol->setEnabled(false);
        radioButton5_vol->setChecked(false);

        gridLayout_5->addWidget(radioButton5_vol, 0, 0, 1, 1);

        radioButton5_cur = new QRadioButton(layoutWidget5);
        radioButton5_cur->setObjectName(QString::fromUtf8("radioButton5_cur"));
        radioButton5_cur->setChecked(true);

        gridLayout_5->addWidget(radioButton5_cur, 0, 1, 1, 1);

        layoutWidget6 = new QWidget(tab_3);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(120, 158, 161, 21));
        gridLayout_6 = new QGridLayout(layoutWidget6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        radioButton6_vol = new QRadioButton(layoutWidget6);
        radioButton6_vol->setObjectName(QString::fromUtf8("radioButton6_vol"));
        radioButton6_vol->setEnabled(false);
        radioButton6_vol->setCheckable(true);
        radioButton6_vol->setChecked(false);

        gridLayout_6->addWidget(radioButton6_vol, 0, 0, 1, 1);

        radioButton6_cur = new QRadioButton(layoutWidget6);
        radioButton6_cur->setObjectName(QString::fromUtf8("radioButton6_cur"));
        radioButton6_cur->setChecked(true);

        gridLayout_6->addWidget(radioButton6_cur, 0, 1, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 351, 101));
        QFont font8;
        font8.setPointSize(8);
        groupBox->setFont(font8);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 70, 61, 20));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_multipy = new QLineEdit(groupBox);
        lineEdit_multipy->setObjectName(QString::fromUtf8("lineEdit_multipy"));
        lineEdit_multipy->setGeometry(QRect(137, 70, 41, 21));
        lineEdit_divide = new QLineEdit(groupBox);
        lineEdit_divide->setObjectName(QString::fromUtf8("lineEdit_divide"));
        lineEdit_divide->setGeometry(QRect(190, 70, 41, 21));
        lineEdit_add = new QLineEdit(groupBox);
        lineEdit_add->setObjectName(QString::fromUtf8("lineEdit_add"));
        lineEdit_add->setGeometry(QRect(245, 70, 41, 21));
        lineEdit_subtract = new QLineEdit(groupBox);
        lineEdit_subtract->setObjectName(QString::fromUtf8("lineEdit_subtract"));
        lineEdit_subtract->setGeometry(QRect(300, 70, 41, 21));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(75, 70, 47, 20));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(280, 67, 16, 20));
        label_15->setFont(font7);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(227, 70, 16, 20));
        label_17->setFont(font4);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(170, 70, 16, 20));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Times New Roman"));
        font9.setPointSize(10);
        font9.setBold(true);
        font9.setWeight(75);
        label_18->setFont(font9);
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(114, 70, 21, 20));
        label_20->setFont(font6);
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_485 = new QComboBox(groupBox);
        comboBox_485->addItem(QString());
        comboBox_485->addItem(QString());
        comboBox_485->addItem(QString());
        comboBox_485->addItem(QString());
        comboBox_485->setObjectName(QString::fromUtf8("comboBox_485"));
        comboBox_485->setGeometry(QRect(20, 20, 101, 25));
        comboBox_485->setFont(font);
        comboBox_485->setFocusPolicy(Qt::NoFocus);
        label_40 = new QLabel(groupBox);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(160, 39, 111, 20));
        label_40->setFont(font);
        label_40->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_41 = new QLabel(groupBox);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(160, 15, 111, 20));
        label_41->setFont(font);
        label_41->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_water_base = new QLineEdit(groupBox);
        lineEdit_water_base->setObjectName(QString::fromUtf8("lineEdit_water_base"));
        lineEdit_water_base->setGeometry(QRect(270, 12, 41, 21));
        lineEdit_water_modify = new QLineEdit(groupBox);
        lineEdit_water_modify->setObjectName(QString::fromUtf8("lineEdit_water_modify"));
        lineEdit_water_modify->setGeometry(QRect(270, 37, 41, 21));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 120, 171, 61));
        groupBox_3->setFont(font8);
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 30, 101, 20));
        label_12->setFont(font8);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_rain_ratio = new QLineEdit(groupBox_3);
        lineEdit_rain_ratio->setObjectName(QString::fromUtf8("lineEdit_rain_ratio"));
        lineEdit_rain_ratio->setGeometry(QRect(100, 30, 41, 21));
        lineEdit_rain_ratio->setFont(font);
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(150, 30, 21, 21));
        label_16->setFont(font);
        save_Button_sampling = new QPushButton(tab_2);
        save_Button_sampling->setObjectName(QString::fromUtf8("save_Button_sampling"));
        save_Button_sampling->setGeometry(QRect(260, 150, 93, 28));
        save_Button_sampling->setFont(font8);
        save_Button_sampling->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(6, 136, 131, 16));
        label_10->setFont(font2);
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(206, 137, 41, 16));
        label_11->setFont(font2);
        save_Button_tcpTime = new QPushButton(tab_4);
        save_Button_tcpTime->setObjectName(QString::fromUtf8("save_Button_tcpTime"));
        save_Button_tcpTime->setGeometry(QRect(270, 150, 93, 28));
        save_Button_tcpTime->setFocusPolicy(Qt::NoFocus);
        lineEdit_fixed_reportTime = new QLineEdit(tab_4);
        lineEdit_fixed_reportTime->setObjectName(QString::fromUtf8("lineEdit_fixed_reportTime"));
        lineEdit_fixed_reportTime->setGeometry(QRect(140, 134, 61, 21));
        lineEdit_fixed_reportTime->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        comboBox_report = new QComboBox(tab_4);
        comboBox_report->addItem(QString());
        comboBox_report->addItem(QString());
        comboBox_report->setObjectName(QString::fromUtf8("comboBox_report"));
        comboBox_report->setGeometry(QRect(25, 5, 111, 25));
        comboBox_report->setFocusPolicy(Qt::NoFocus);
        comboBox_report->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_34 = new QLabel(tab_4);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(6, 34, 131, 16));
        label_34->setFont(font2);
        label_34->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_35 = new QLabel(tab_4);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(6, 60, 131, 16));
        label_35->setFont(font2);
        label_35->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_36 = new QLabel(tab_4);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(6, 85, 131, 16));
        label_36->setFont(font2);
        label_36->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_37 = new QLabel(tab_4);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(6, 161, 131, 16));
        label_37->setFont(font2);
        label_38 = new QLabel(tab_4);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(206, 163, 41, 16));
        label_38->setFont(font2);
        lineEdit_add_reportTime = new QLineEdit(tab_4);
        lineEdit_add_reportTime->setObjectName(QString::fromUtf8("lineEdit_add_reportTime"));
        lineEdit_add_reportTime->setGeometry(QRect(140, 160, 61, 21));
        lineEdit_add_reportTime->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        label_39 = new QLabel(tab_4);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(6, 108, 131, 20));
        label_39->setFont(font2);
        label_39->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_report_type = new QLineEdit(tab_4);
        lineEdit_report_type->setObjectName(QString::fromUtf8("lineEdit_report_type"));
        lineEdit_report_type->setGeometry(QRect(140, 108, 121, 21));
        lineEdit_report_type->setFont(font8);
        lineEdit_report_password = new QLineEdit(tab_4);
        lineEdit_report_password->setObjectName(QString::fromUtf8("lineEdit_report_password"));
        lineEdit_report_password->setGeometry(QRect(140, 83, 61, 21));
        lineEdit_report_password->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        lineEdit_station_addr = new QLineEdit(tab_4);
        lineEdit_station_addr->setObjectName(QString::fromUtf8("lineEdit_station_addr"));
        lineEdit_station_addr->setGeometry(QRect(140, 58, 121, 21));
        lineEdit_station_addr->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        lineEdit_central_addr = new QLineEdit(tab_4);
        lineEdit_central_addr->setObjectName(QString::fromUtf8("lineEdit_central_addr"));
        lineEdit_central_addr->setGeometry(QRect(140, 32, 61, 21));
        lineEdit_central_addr->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        pushButton_SW_test = new QPushButton(tab_4);
        pushButton_SW_test->setObjectName(QString::fromUtf8("pushButton_SW_test"));
        pushButton_SW_test->setGeometry(QRect(270, 110, 93, 28));
        pushButton_SW_test->setFocusPolicy(Qt::NoFocus);
        checkBox_SW_uniform_time = new QCheckBox(tab_4);
        checkBox_SW_uniform_time->setObjectName(QString::fromUtf8("checkBox_SW_uniform_time"));
        checkBox_SW_uniform_time->setGeometry(QRect(270, 30, 101, 19));
        checkBox_SW_uniform_time->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\256\213\344\275\223\";"));
        checkBox_SW_hour = new QCheckBox(tab_4);
        checkBox_SW_hour->setObjectName(QString::fromUtf8("checkBox_SW_hour"));
        checkBox_SW_hour->setGeometry(QRect(270, 50, 101, 19));
        checkBox_SW_hour->setStyleSheet(QString::fromUtf8("font: 8pt \"\345\256\213\344\275\223\";"));
        tabWidget->addTab(tab_4, QString());

        retranslateUi(canshu_widget);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(canshu_widget);
    } // setupUi

    void retranslateUi(QWidget *canshu_widget)
    {
        canshu_widget->setWindowTitle(QApplication::translate("canshu_widget", "Form", nullptr));
        comboBox_485_identify->setItemText(0, QApplication::translate("canshu_widget", "\346\260\264\344\275\215", nullptr));
        comboBox_485_identify->setItemText(1, QApplication::translate("canshu_widget", "\347\236\254\346\227\266\346\265\201\351\207\217", nullptr));
        comboBox_485_identify->setItemText(2, QApplication::translate("canshu_widget", "\347\264\257\350\256\241\346\265\201\351\207\217", nullptr));
        comboBox_485_identify->setItemText(3, QApplication::translate("canshu_widget", "\346\265\201\351\200\237", nullptr));
        comboBox_485_identify->setItemText(4, QApplication::translate("canshu_widget", "\345\205\263\351\227\255", nullptr));

        label_3->setText(QApplication::translate("canshu_widget", "\344\270\262\345\217\243\345\217\267:", nullptr));
        label_4->setText(QApplication::translate("canshu_widget", "\346\263\242\347\211\271\347\216\207:", nullptr));
        save_Button_485->setText(QApplication::translate("canshu_widget", "\344\277\235\345\255\230", nullptr));
        label_select2->setText(QApplication::translate("canshu_widget", "\346\240\207\350\257\206\347\254\246:", nullptr));
        BaudBox->setItemText(0, QApplication::translate("canshu_widget", "9600", nullptr));
        BaudBox->setItemText(1, QApplication::translate("canshu_widget", "115200", nullptr));

        label_19->setText(QApplication::translate("canshu_widget", "\351\200\232\344\277\241\345\234\260\345\235\200:", nullptr));
        label_select4->setText(QApplication::translate("canshu_widget", "\345\257\204\345\255\230\345\231\250\345\234\260\345\235\200:", nullptr));
        label_select5->setText(QApplication::translate("canshu_widget", "\345\257\204\345\255\230\345\231\250\346\225\260\351\207\217:", nullptr));
        comboBox_485_regNum->setItemText(0, QApplication::translate("canshu_widget", "1", nullptr));
        comboBox_485_regNum->setItemText(1, QApplication::translate("canshu_widget", "2", nullptr));
        comboBox_485_regNum->setItemText(2, QApplication::translate("canshu_widget", "3", nullptr));
        comboBox_485_regNum->setItemText(3, QApplication::translate("canshu_widget", "4", nullptr));

        label_select6->setText(QApplication::translate("canshu_widget", "\346\225\260\346\215\256\347\261\273\345\236\213:", nullptr));
        comboBox_485_type->setItemText(0, QApplication::translate("canshu_widget", "\346\225\264\345\236\213", nullptr));
        comboBox_485_type->setItemText(1, QApplication::translate("canshu_widget", "\346\265\256\347\202\271\345\236\213", nullptr));
        comboBox_485_type->setItemText(2, QApplication::translate("canshu_widget", "BCD\347\240\201", nullptr));

        comboBox_485_format->setItemText(0, QApplication::translate("canshu_widget", "\351\253\230\345\211\215\344\275\216\345\220\216\346\255\243", nullptr));
        comboBox_485_format->setItemText(1, QApplication::translate("canshu_widget", "\351\253\230\345\211\215\344\275\216\345\220\216\345\217\215", nullptr));
        comboBox_485_format->setItemText(2, QApplication::translate("canshu_widget", "\344\275\216\345\211\215\351\253\230\345\220\216\346\255\243", nullptr));
        comboBox_485_format->setItemText(3, QApplication::translate("canshu_widget", "\344\275\216\345\211\215\351\253\230\345\220\216\345\217\215", nullptr));

        label_select7->setText(QApplication::translate("canshu_widget", "\346\225\260\346\215\256\346\240\274\345\274\217:", nullptr));
        label_select1->setText(QApplication::translate("canshu_widget", "\351\207\207\346\240\267\345\272\217\345\217\267:", nullptr));
        comboBox_485_num->setItemText(0, QApplication::translate("canshu_widget", "1", nullptr));
        comboBox_485_num->setItemText(1, QApplication::translate("canshu_widget", "2", nullptr));
        comboBox_485_num->setItemText(2, QApplication::translate("canshu_widget", "3", nullptr));
        comboBox_485_num->setItemText(3, QApplication::translate("canshu_widget", "4", nullptr));

        clear_Button_485->setText(QApplication::translate("canshu_widget", "\346\270\205\351\231\244", nullptr));
        comboBox_485_protocol->setItemText(0, QApplication::translate("canshu_widget", "Modbus\344\270\273\347\253\231", nullptr));
        comboBox_485_protocol->setItemText(1, QApplication::translate("canshu_widget", "Modbus\344\273\216\347\253\231", nullptr));

        label_42->setText(QApplication::translate("canshu_widget", "\351\200\232\344\277\241\345\215\217\350\256\256:", nullptr));
        comboBox_485_funcode->setItemText(0, QApplication::translate("canshu_widget", "03", nullptr));
        comboBox_485_funcode->setItemText(1, QApplication::translate("canshu_widget", "04", nullptr));
        comboBox_485_funcode->setItemText(2, QApplication::translate("canshu_widget", "06", nullptr));
        comboBox_485_funcode->setItemText(3, QApplication::translate("canshu_widget", "16", nullptr));

        label_select3->setText(QApplication::translate("canshu_widget", "\345\212\237\350\203\275\347\240\201:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("canshu_widget", "485\351\200\232\344\277\241", nullptr));
        label_23->setText(QApplication::translate("canshu_widget", "COM4\346\263\242\347\211\271\347\216\207:", nullptr));
        BaudBox_kdy->setItemText(0, QApplication::translate("canshu_widget", "9600", nullptr));
        BaudBox_kdy->setItemText(1, QApplication::translate("canshu_widget", "115200", nullptr));

        label_24->setText(QApplication::translate("canshu_widget", "\351\200\232\344\277\241\345\234\260\345\235\200:", nullptr));
        label_25->setText(QApplication::translate("canshu_widget", "\345\274\200\345\272\246\345\200\274\344\270\212\351\231\220:", nullptr));
        label_26->setText(QApplication::translate("canshu_widget", "\345\274\200\345\272\246\345\200\274\344\270\213\351\231\220:", nullptr));
        label_30->setText(QApplication::translate("canshu_widget", "\345\274\200\345\272\246\345\200\274:", nullptr));
        label_32->setText(QApplication::translate("canshu_widget", "\351\242\204\350\255\246\346\227\266\351\227\264:", nullptr));
        pushButton_kdy_start->setText(QApplication::translate("canshu_widget", "\345\220\257\345\212\250", nullptr));
        label_33->setText(QApplication::translate("canshu_widget", "s", nullptr));
        pushButton_kdy_stop->setText(QApplication::translate("canshu_widget", "\346\200\245\345\201\234", nullptr));
        pushButton_kdy_slave->setText(QApplication::translate("canshu_widget", "\344\277\235\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("canshu_widget", "\345\274\200\345\272\246\346\216\247\345\210\266", nullptr));
        label->setText(QApplication::translate("canshu_widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\346\250\241\345\205\245\351\200\232\351\201\2231\357\274\232</span></p></body></html>", nullptr));
        label_2->setText(QApplication::translate("canshu_widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\346\250\241\345\205\245\351\200\232\351\201\2232\357\274\232</span></p></body></html>", nullptr));
        label_5->setText(QApplication::translate("canshu_widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\346\250\241\345\205\245\351\200\232\351\201\2233\357\274\232</span></p></body></html>", nullptr));
        label_6->setText(QApplication::translate("canshu_widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\346\250\241\345\205\245\351\200\232\351\201\2234\357\274\232</span></p></body></html>", nullptr));
        label_7->setText(QApplication::translate("canshu_widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\346\250\241\345\205\245\351\200\232\351\201\2235\357\274\232</span></p></body></html>", nullptr));
        label_9->setText(QApplication::translate("canshu_widget", "<html><head/><body><p><span style=\" font-size:10pt;\">\346\250\241\345\205\245\351\200\232\351\201\2236\357\274\232</span></p></body></html>", nullptr));
        radioButton1_vol->setText(QApplication::translate("canshu_widget", "\347\224\265\345\216\213", nullptr));
        radioButton1_cur->setText(QApplication::translate("canshu_widget", "\347\224\265\346\265\201", nullptr));
        radioButton2_vol->setText(QApplication::translate("canshu_widget", "\347\224\265\345\216\213", nullptr));
        radioButton2_cur->setText(QApplication::translate("canshu_widget", "\347\224\265\346\265\201", nullptr));
        radioButton3_vol->setText(QApplication::translate("canshu_widget", "\347\224\265\345\216\213", nullptr));
        radioButton3_cur->setText(QApplication::translate("canshu_widget", "\347\224\265\346\265\201", nullptr));
        radioButton4_vol->setText(QApplication::translate("canshu_widget", "\347\224\265\345\216\213", nullptr));
        radioButton4_cur->setText(QApplication::translate("canshu_widget", "\347\224\265\346\265\201", nullptr));
        radioButton5_vol->setText(QApplication::translate("canshu_widget", "\347\224\265\345\216\213", nullptr));
        radioButton5_cur->setText(QApplication::translate("canshu_widget", "\347\224\265\346\265\201", nullptr));
        radioButton6_vol->setText(QApplication::translate("canshu_widget", "\347\224\265\345\216\213", nullptr));
        radioButton6_cur->setText(QApplication::translate("canshu_widget", "\347\224\265\346\265\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("canshu_widget", "\346\250\241\345\205\245\351\205\215\347\275\256", nullptr));
        groupBox->setTitle(QApplication::translate("canshu_widget", "485\351\207\207\346\240\267", nullptr));
        label_13->setText(QApplication::translate("canshu_widget", "\350\256\241\347\256\227\345\200\274=", nullptr));
        lineEdit_multipy->setText(QApplication::translate("canshu_widget", "1", nullptr));
        lineEdit_divide->setText(QApplication::translate("canshu_widget", "1", nullptr));
        lineEdit_add->setText(QApplication::translate("canshu_widget", "0", nullptr));
        lineEdit_subtract->setText(QApplication::translate("canshu_widget", "0", nullptr));
        label_14->setText(QApplication::translate("canshu_widget", "\351\207\207\346\240\267\345\200\274", nullptr));
        label_15->setText(QApplication::translate("canshu_widget", "-", nullptr));
        label_17->setText(QApplication::translate("canshu_widget", "+", nullptr));
        label_18->setText(QApplication::translate("canshu_widget", "/", nullptr));
        label_20->setText(QApplication::translate("canshu_widget", "*", nullptr));
        comboBox_485->setItemText(0, QApplication::translate("canshu_widget", "\346\260\264\344\275\215", nullptr));
        comboBox_485->setItemText(1, QApplication::translate("canshu_widget", "\347\236\254\346\227\266\346\265\201\351\207\217", nullptr));
        comboBox_485->setItemText(2, QApplication::translate("canshu_widget", "\347\264\257\350\256\241\346\265\201\351\207\217", nullptr));
        comboBox_485->setItemText(3, QApplication::translate("canshu_widget", "\346\265\201\351\200\237", nullptr));

        label_40->setText(QApplication::translate("canshu_widget", "\346\260\264\344\275\215\344\277\256\346\255\243\345\200\274\357\274\232", nullptr));
        label_41->setText(QApplication::translate("canshu_widget", "\346\260\264\344\275\215\345\237\272\345\200\274\357\274\232", nullptr));
        lineEdit_water_base->setText(QApplication::translate("canshu_widget", "0", nullptr));
        lineEdit_water_modify->setText(QApplication::translate("canshu_widget", "0", nullptr));
        groupBox_3->setTitle(QApplication::translate("canshu_widget", "\351\231\215\351\233\250\351\207\217\351\207\207\346\240\267", nullptr));
        label_12->setText(QApplication::translate("canshu_widget", "\351\233\250\351\207\217\345\210\206\350\276\250\345\212\233\357\274\232", nullptr));
        label_16->setText(QApplication::translate("canshu_widget", "mm", nullptr));
        save_Button_sampling->setText(QApplication::translate("canshu_widget", "\344\277\235\345\255\230\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("canshu_widget", "\351\207\207\346\240\267\344\277\256\346\255\243", nullptr));
        label_10->setText(QApplication::translate("canshu_widget", "\345\256\232\346\227\266\346\212\245\346\227\266\351\227\264\351\227\264\351\232\224\357\274\232", nullptr));
        label_11->setText(QApplication::translate("canshu_widget", "\345\210\206\351\222\237", nullptr));
        save_Button_tcpTime->setText(QApplication::translate("canshu_widget", "\344\277\235\345\255\230\345\217\202\346\225\260", nullptr));
        comboBox_report->setItemText(0, QApplication::translate("canshu_widget", "\346\260\264\346\226\207", nullptr));
        comboBox_report->setItemText(1, QApplication::translate("canshu_widget", "\346\260\264\350\265\204\346\272\220", nullptr));

        label_34->setText(QApplication::translate("canshu_widget", "\344\270\255\345\277\203\347\253\231\345\234\260\345\235\200\357\274\232", nullptr));
        label_35->setText(QApplication::translate("canshu_widget", "\351\201\245\346\265\213\347\253\231\345\234\260\345\235\200\357\274\232", nullptr));
        label_36->setText(QApplication::translate("canshu_widget", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_37->setText(QApplication::translate("canshu_widget", "\345\212\240\346\212\245\346\212\245\346\227\266\351\227\264\351\227\264\351\232\224\357\274\232", nullptr));
        label_38->setText(QApplication::translate("canshu_widget", "\345\210\206\351\222\237", nullptr));
        label_39->setText(QApplication::translate("canshu_widget", "\347\233\221\346\265\213\346\225\260\346\215\256\347\247\215\347\261\273\357\274\232", nullptr));
        pushButton_SW_test->setText(QApplication::translate("canshu_widget", "\346\260\264\346\226\207\346\265\213\350\257\225\346\212\245", nullptr));
        checkBox_SW_uniform_time->setText(QApplication::translate("canshu_widget", "\345\235\207\345\214\200\346\227\266\346\256\265\346\212\245", nullptr));
        checkBox_SW_hour->setText(QApplication::translate("canshu_widget", "\345\260\217\346\227\266\346\212\245", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("canshu_widget", "\350\277\234\344\274\240\345\217\202\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class canshu_widget: public Ui_canshu_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANSHU_WIDGET_H
