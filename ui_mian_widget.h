/********************************************************************************
** Form generated from reading UI file 'mian_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIAN_WIDGET_H
#define UI_MIAN_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mian_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_picture;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_liusu_data;
    QLabel *label_current_flow_data;
    QLabel *label_power;
    QLabel *label_power_data;
    QLabel *label_shuiwei_data;
    QLabel *label_leiji_rain_data;
    QLabel *label_leiji_flow;
    QLabel *label_leiji_rain;
    QLabel *label_current_rain;
    QLabel *label_liusu;
    QLabel *label_leiji_flow_data;
    QLabel *label_current_flow;
    QLabel *label_current_rain_data;
    QLabel *label_shuiwei;
    QLabel *label_xiehong_flow;
    QLabel *label_xiehong_flow_data;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_DI1;
    QLabel *label_2;
    QLabel *label_DI2;
    QLabel *label_DI3;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_DI4;
    QLabel *label_DI5;
    QGroupBox *groupBox_2;
    QLabel *label_6;
    QLabel *label_AI1;
    QLabel *label_7;
    QLabel *label_AI2;
    QLabel *label_AI3;
    QLabel *label_8;
    QLabel *label_AI4;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_AI5;
    QLabel *label_AI6;
    QLabel *label_11;
    QGroupBox *groupBox_5;
    QLabel *label_19;
    QLabel *label_kdy_open;
    QLabel *label_20;
    QLabel *label_kdy_off;
    QLabel *label_kdy_raise;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_kdy_fall;
    QLabel *label_kdy_error;
    QLabel *label_kdy_data;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_kdy_zidong;
    QWidget *tab_3;
    QGroupBox *groupBox_3;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QCheckBox *checkBox_DO1;
    QCheckBox *checkBox_DO2;
    QCheckBox *checkBox_DO3;
    QGroupBox *groupBox_4;
    QCheckBox *checkBox_DYC_3;
    QCheckBox *checkBox_DYC_2;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QCheckBox *checkBox_DYC_1;
    QLabel *label_18;
    QCheckBox *checkBox_DYC_4;

    void setupUi(QWidget *mian_widget)
    {
        if (mian_widget->objectName().isEmpty())
            mian_widget->setObjectName(QString::fromUtf8("mian_widget"));
        mian_widget->resize(381, 219);
        mian_widget->setStyleSheet(QString::fromUtf8(""));
        tabWidget = new QTabWidget(mian_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_picture = new QLabel(tab);
        label_picture->setObjectName(QString::fromUtf8("label_picture"));
        label_picture->setGeometry(QRect(3, 3, 161, 181));
        label_picture->setStyleSheet(QString::fromUtf8("border-image: url(:/back/image/main.jpg);"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(165, 3, 201, 181));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(1);
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_liusu_data = new QLabel(layoutWidget);
        label_liusu_data->setObjectName(QString::fromUtf8("label_liusu_data"));
        QFont font;
        font.setPointSize(8);
        label_liusu_data->setFont(font);
        label_liusu_data->setStyleSheet(QString::fromUtf8(""));
        label_liusu_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_liusu_data, 2, 1, 1, 1);

        label_current_flow_data = new QLabel(layoutWidget);
        label_current_flow_data->setObjectName(QString::fromUtf8("label_current_flow_data"));
        label_current_flow_data->setFont(font);
        label_current_flow_data->setStyleSheet(QString::fromUtf8(""));
        label_current_flow_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_current_flow_data, 3, 1, 1, 1);

        label_power = new QLabel(layoutWidget);
        label_power->setObjectName(QString::fromUtf8("label_power"));
        label_power->setFont(font);
        label_power->setStyleSheet(QString::fromUtf8(""));
        label_power->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_power, 0, 0, 1, 1);

        label_power_data = new QLabel(layoutWidget);
        label_power_data->setObjectName(QString::fromUtf8("label_power_data"));
        label_power_data->setFont(font);
        label_power_data->setStyleSheet(QString::fromUtf8(""));
        label_power_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_power_data, 0, 1, 1, 1);

        label_shuiwei_data = new QLabel(layoutWidget);
        label_shuiwei_data->setObjectName(QString::fromUtf8("label_shuiwei_data"));
        label_shuiwei_data->setFont(font);
        label_shuiwei_data->setStyleSheet(QString::fromUtf8(""));
        label_shuiwei_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_shuiwei_data, 1, 1, 1, 1);

        label_leiji_rain_data = new QLabel(layoutWidget);
        label_leiji_rain_data->setObjectName(QString::fromUtf8("label_leiji_rain_data"));
        label_leiji_rain_data->setFont(font);
        label_leiji_rain_data->setStyleSheet(QString::fromUtf8(""));
        label_leiji_rain_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_leiji_rain_data, 7, 1, 1, 1);

        label_leiji_flow = new QLabel(layoutWidget);
        label_leiji_flow->setObjectName(QString::fromUtf8("label_leiji_flow"));
        label_leiji_flow->setFont(font);
        label_leiji_flow->setStyleSheet(QString::fromUtf8(""));
        label_leiji_flow->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_leiji_flow, 4, 0, 1, 1);

        label_leiji_rain = new QLabel(layoutWidget);
        label_leiji_rain->setObjectName(QString::fromUtf8("label_leiji_rain"));
        label_leiji_rain->setFont(font);
        label_leiji_rain->setStyleSheet(QString::fromUtf8(""));
        label_leiji_rain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_leiji_rain, 7, 0, 1, 1);

        label_current_rain = new QLabel(layoutWidget);
        label_current_rain->setObjectName(QString::fromUtf8("label_current_rain"));
        label_current_rain->setFont(font);
        label_current_rain->setStyleSheet(QString::fromUtf8(""));
        label_current_rain->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_current_rain, 6, 0, 1, 1);

        label_liusu = new QLabel(layoutWidget);
        label_liusu->setObjectName(QString::fromUtf8("label_liusu"));
        label_liusu->setFont(font);
        label_liusu->setStyleSheet(QString::fromUtf8(""));
        label_liusu->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_liusu, 2, 0, 1, 1);

        label_leiji_flow_data = new QLabel(layoutWidget);
        label_leiji_flow_data->setObjectName(QString::fromUtf8("label_leiji_flow_data"));
        label_leiji_flow_data->setFont(font);
        label_leiji_flow_data->setStyleSheet(QString::fromUtf8(""));
        label_leiji_flow_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_leiji_flow_data, 4, 1, 1, 1);

        label_current_flow = new QLabel(layoutWidget);
        label_current_flow->setObjectName(QString::fromUtf8("label_current_flow"));
        label_current_flow->setFont(font);
        label_current_flow->setStyleSheet(QString::fromUtf8(""));
        label_current_flow->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_current_flow, 3, 0, 1, 1);

        label_current_rain_data = new QLabel(layoutWidget);
        label_current_rain_data->setObjectName(QString::fromUtf8("label_current_rain_data"));
        label_current_rain_data->setFont(font);
        label_current_rain_data->setStyleSheet(QString::fromUtf8(""));
        label_current_rain_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_current_rain_data, 6, 1, 1, 1);

        label_shuiwei = new QLabel(layoutWidget);
        label_shuiwei->setObjectName(QString::fromUtf8("label_shuiwei"));
        label_shuiwei->setFont(font);
        label_shuiwei->setStyleSheet(QString::fromUtf8(""));
        label_shuiwei->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_shuiwei, 1, 0, 1, 1);

        label_xiehong_flow = new QLabel(layoutWidget);
        label_xiehong_flow->setObjectName(QString::fromUtf8("label_xiehong_flow"));
        label_xiehong_flow->setFont(font);
        label_xiehong_flow->setStyleSheet(QString::fromUtf8(""));
        label_xiehong_flow->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_xiehong_flow, 5, 0, 1, 1);

        label_xiehong_flow_data = new QLabel(layoutWidget);
        label_xiehong_flow_data->setObjectName(QString::fromUtf8("label_xiehong_flow_data"));
        label_xiehong_flow_data->setFont(font);
        label_xiehong_flow_data->setStyleSheet(QString::fromUtf8(""));
        label_xiehong_flow_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_xiehong_flow_data, 5, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        layoutWidget->raise();
        label_picture->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 71, 171));
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 31, 28, 16));
        label_DI1 = new QLabel(groupBox);
        label_DI1->setObjectName(QString::fromUtf8("label_DI1"));
        label_DI1->setGeometry(QRect(40, 31, 16, 17));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(11, 58, 28, 16));
        label_DI2 = new QLabel(groupBox);
        label_DI2->setObjectName(QString::fromUtf8("label_DI2"));
        label_DI2->setGeometry(QRect(40, 58, 16, 17));
        label_DI3 = new QLabel(groupBox);
        label_DI3->setObjectName(QString::fromUtf8("label_DI3"));
        label_DI3->setGeometry(QRect(40, 85, 16, 17));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(11, 85, 28, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(11, 140, 28, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(11, 113, 28, 16));
        label_DI4 = new QLabel(groupBox);
        label_DI4->setObjectName(QString::fromUtf8("label_DI4"));
        label_DI4->setGeometry(QRect(40, 113, 16, 17));
        label_DI5 = new QLabel(groupBox);
        label_DI5->setObjectName(QString::fromUtf8("label_DI5"));
        label_DI5->setGeometry(QRect(40, 140, 16, 17));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(90, 10, 121, 171));
        groupBox_2->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(12, 26, 28, 16));
        label_AI1 = new QLabel(groupBox_2);
        label_AI1->setObjectName(QString::fromUtf8("label_AI1"));
        label_AI1->setGeometry(QRect(48, 26, 71, 20));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(12, 50, 28, 16));
        label_AI2 = new QLabel(groupBox_2);
        label_AI2->setObjectName(QString::fromUtf8("label_AI2"));
        label_AI2->setGeometry(QRect(48, 50, 71, 20));
        label_AI3 = new QLabel(groupBox_2);
        label_AI3->setObjectName(QString::fromUtf8("label_AI3"));
        label_AI3->setGeometry(QRect(48, 74, 71, 20));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(12, 74, 28, 16));
        label_AI4 = new QLabel(groupBox_2);
        label_AI4->setObjectName(QString::fromUtf8("label_AI4"));
        label_AI4->setGeometry(QRect(48, 98, 71, 20));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(12, 98, 28, 16));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(12, 122, 28, 16));
        label_AI5 = new QLabel(groupBox_2);
        label_AI5->setObjectName(QString::fromUtf8("label_AI5"));
        label_AI5->setGeometry(QRect(48, 122, 71, 20));
        label_AI6 = new QLabel(groupBox_2);
        label_AI6->setObjectName(QString::fromUtf8("label_AI6"));
        label_AI6->setGeometry(QRect(48, 146, 71, 20));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(12, 146, 28, 16));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(220, 10, 151, 171));
        groupBox_5->setFont(font);
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(1, 40, 51, 20));
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_kdy_open = new QLabel(groupBox_5);
        label_kdy_open->setObjectName(QString::fromUtf8("label_kdy_open"));
        label_kdy_open->setGeometry(QRect(60, 40, 16, 17));
        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(1, 60, 51, 20));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_kdy_off = new QLabel(groupBox_5);
        label_kdy_off->setObjectName(QString::fromUtf8("label_kdy_off"));
        label_kdy_off->setGeometry(QRect(60, 60, 16, 17));
        label_kdy_raise = new QLabel(groupBox_5);
        label_kdy_raise->setObjectName(QString::fromUtf8("label_kdy_raise"));
        label_kdy_raise->setGeometry(QRect(60, 80, 16, 17));
        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(0, 80, 51, 20));
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(1, 120, 51, 20));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_23 = new QLabel(groupBox_5);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(1, 100, 51, 20));
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_kdy_fall = new QLabel(groupBox_5);
        label_kdy_fall->setObjectName(QString::fromUtf8("label_kdy_fall"));
        label_kdy_fall->setGeometry(QRect(60, 100, 16, 17));
        label_kdy_error = new QLabel(groupBox_5);
        label_kdy_error->setObjectName(QString::fromUtf8("label_kdy_error"));
        label_kdy_error->setGeometry(QRect(60, 120, 16, 17));
        label_kdy_data = new QLabel(groupBox_5);
        label_kdy_data->setObjectName(QString::fromUtf8("label_kdy_data"));
        label_kdy_data->setGeometry(QRect(60, 20, 81, 20));
        label_kdy_data->setStyleSheet(QString::fromUtf8(""));
        label_kdy_data->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_24 = new QLabel(groupBox_5);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(0, 140, 51, 20));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_25 = new QLabel(groupBox_5);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(0, 20, 51, 20));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_kdy_zidong = new QLabel(groupBox_5);
        label_kdy_zidong->setObjectName(QString::fromUtf8("label_kdy_zidong"));
        label_kdy_zidong->setGeometry(QRect(60, 140, 16, 17));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 161, 111));
        groupBox_3->setFont(font);
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(11, 31, 32, 16));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(11, 58, 32, 16));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(11, 85, 32, 16));
        checkBox_DO1 = new QCheckBox(groupBox_3);
        checkBox_DO1->setObjectName(QString::fromUtf8("checkBox_DO1"));
        checkBox_DO1->setGeometry(QRect(45, 30, 80, 20));
        checkBox_DO1->setFocusPolicy(Qt::NoFocus);
        checkBox_DO1->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        checkBox_DO2 = new QCheckBox(groupBox_3);
        checkBox_DO2->setObjectName(QString::fromUtf8("checkBox_DO2"));
        checkBox_DO2->setGeometry(QRect(45, 57, 80, 20));
        checkBox_DO2->setFocusPolicy(Qt::NoFocus);
        checkBox_DO2->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        checkBox_DO3 = new QCheckBox(groupBox_3);
        checkBox_DO3->setObjectName(QString::fromUtf8("checkBox_DO3"));
        checkBox_DO3->setGeometry(QRect(45, 84, 80, 20));
        checkBox_DO3->setFocusPolicy(Qt::NoFocus);
        checkBox_DO3->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(200, 10, 161, 141));
        groupBox_4->setFont(font);
        checkBox_DYC_3 = new QCheckBox(groupBox_4);
        checkBox_DYC_3->setObjectName(QString::fromUtf8("checkBox_DYC_3"));
        checkBox_DYC_3->setGeometry(QRect(50, 85, 80, 20));
        checkBox_DYC_3->setFocusPolicy(Qt::NoFocus);
        checkBox_DYC_3->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        checkBox_DYC_2 = new QCheckBox(groupBox_4);
        checkBox_DYC_2->setObjectName(QString::fromUtf8("checkBox_DYC_2"));
        checkBox_DYC_2->setGeometry(QRect(50, 58, 80, 20));
        checkBox_DYC_2->setFocusPolicy(Qt::NoFocus);
        checkBox_DYC_2->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(11, 31, 32, 16));
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(11, 58, 32, 16));
        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(11, 85, 32, 16));
        checkBox_DYC_1 = new QCheckBox(groupBox_4);
        checkBox_DYC_1->setObjectName(QString::fromUtf8("checkBox_DYC_1"));
        checkBox_DYC_1->setGeometry(QRect(50, 31, 80, 20));
        checkBox_DYC_1->setFocusPolicy(Qt::NoFocus);
        checkBox_DYC_1->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 110, 32, 16));
        checkBox_DYC_4 = new QCheckBox(groupBox_4);
        checkBox_DYC_4->setObjectName(QString::fromUtf8("checkBox_DYC_4"));
        checkBox_DYC_4->setGeometry(QRect(50, 110, 80, 20));
        checkBox_DYC_4->setFocusPolicy(Qt::NoFocus);
        checkBox_DYC_4->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(mian_widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mian_widget);
    } // setupUi

    void retranslateUi(QWidget *mian_widget)
    {
        mian_widget->setWindowTitle(QApplication::translate("mian_widget", "Form", nullptr));
        label_picture->setText(QString());
        label_liusu_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- m/s</span></p></body></html>", nullptr));
        label_current_flow_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- m3/s</span></p></body></html>", nullptr));
        label_power->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\347\224\265\345\216\213\357\274\232</span></p></body></html>", nullptr));
        label_power_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- V</span></p></body></html>", nullptr));
        label_shuiwei_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- m</span></p></body></html>", nullptr));
        label_leiji_rain_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- mm</span></p></body></html>", nullptr));
        label_leiji_flow->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\347\264\257\350\256\241\346\265\201\351\207\217\357\274\232</span></p></body></html>", nullptr));
        label_leiji_rain->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\347\264\257\350\256\241\351\233\250\351\207\217\357\274\232</span></p></body></html>", nullptr));
        label_current_rain->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\345\275\223\345\211\215\351\233\250\351\207\217\357\274\232</span></p></body></html>", nullptr));
        label_liusu->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\346\265\201\351\200\237\357\274\232</span></p></body></html>", nullptr));
        label_leiji_flow_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- m3/s</span></p></body></html>", nullptr));
        label_current_flow->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\347\236\254\346\227\266\346\265\201\351\207\217\357\274\232</span></p></body></html>", nullptr));
        label_current_rain_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- mm</span></p></body></html>", nullptr));
        label_shuiwei->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\346\260\264\344\275\215\357\274\232</span></p></body></html>", nullptr));
        label_xiehong_flow->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">\346\263\204\346\264\252\346\265\201\351\207\217\357\274\232</span></p></body></html>", nullptr));
        label_xiehong_flow_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p><span style=\" font-weight:600;\">--- m3/s</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("mian_widget", "\345\237\272\346\234\254\345\217\202\346\225\260", nullptr));
        groupBox->setTitle(QApplication::translate("mian_widget", "\345\274\200\345\205\245\347\212\266\346\200\201", nullptr));
        label->setText(QApplication::translate("mian_widget", "DI1:", nullptr));
        label_DI1->setText(QString());
        label_2->setText(QApplication::translate("mian_widget", "DI2:", nullptr));
        label_DI2->setText(QString());
        label_DI3->setText(QString());
        label_3->setText(QApplication::translate("mian_widget", "DI3:", nullptr));
        label_5->setText(QApplication::translate("mian_widget", "DI5:", nullptr));
        label_4->setText(QApplication::translate("mian_widget", "DI4:", nullptr));
        label_DI4->setText(QString());
        label_DI5->setText(QString());
        groupBox_2->setTitle(QApplication::translate("mian_widget", "\346\250\241\345\205\245\346\225\260\346\215\256", nullptr));
        label_6->setText(QApplication::translate("mian_widget", "AI1:", nullptr));
        label_AI1->setText(QString());
        label_7->setText(QApplication::translate("mian_widget", "AI2:", nullptr));
        label_AI2->setText(QString());
        label_AI3->setText(QString());
        label_8->setText(QApplication::translate("mian_widget", "AI3:", nullptr));
        label_AI4->setText(QString());
        label_9->setText(QApplication::translate("mian_widget", "AI4:", nullptr));
        label_10->setText(QApplication::translate("mian_widget", "AI5:", nullptr));
        label_AI5->setText(QString());
        label_AI6->setText(QString());
        label_11->setText(QApplication::translate("mian_widget", "AI6:", nullptr));
        groupBox_5->setTitle(QApplication::translate("mian_widget", "\345\274\200\345\272\246\344\273\252\347\212\266\346\200\201", nullptr));
        label_19->setText(QApplication::translate("mian_widget", "\345\205\250\345\274\200:", nullptr));
        label_kdy_open->setText(QString());
        label_20->setText(QApplication::translate("mian_widget", "\345\205\250\345\205\263:", nullptr));
        label_kdy_off->setText(QString());
        label_kdy_raise->setText(QString());
        label_21->setText(QApplication::translate("mian_widget", "\344\270\212\345\215\207:", nullptr));
        label_22->setText(QApplication::translate("mian_widget", "\346\225\205\351\232\234:", nullptr));
        label_23->setText(QApplication::translate("mian_widget", "\344\270\213\351\231\215:", nullptr));
        label_kdy_fall->setText(QString());
        label_kdy_error->setText(QString());
        label_kdy_data->setText(QApplication::translate("mian_widget", "<html><head/><body><p>--- cm</p></body></html>", nullptr));
        label_24->setText(QApplication::translate("mian_widget", "\350\207\252\345\212\250:", nullptr));
        label_25->setText(QApplication::translate("mian_widget", "\345\274\200\345\272\246\345\200\274:", nullptr));
        label_kdy_zidong->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mian_widget", "\351\207\207\351\233\206\347\212\266\346\200\201", nullptr));
        groupBox_3->setTitle(QApplication::translate("mian_widget", "\345\274\200\345\207\272\346\216\247\345\210\266", nullptr));
        label_12->setText(QApplication::translate("mian_widget", "DO1:", nullptr));
        label_13->setText(QApplication::translate("mian_widget", "DO2:", nullptr));
        label_14->setText(QApplication::translate("mian_widget", "DO3:", nullptr));
        checkBox_DO1->setText(QString());
        checkBox_DO2->setText(QString());
        checkBox_DO3->setText(QString());
        groupBox_4->setTitle(QApplication::translate("mian_widget", "\345\217\257\346\216\247\347\224\265\346\272\220", nullptr));
        checkBox_DYC_3->setText(QString());
        checkBox_DYC_2->setText(QString());
        label_15->setText(QApplication::translate("mian_widget", "DYC1:", nullptr));
        label_16->setText(QApplication::translate("mian_widget", "DYC2:", nullptr));
        label_17->setText(QApplication::translate("mian_widget", "DYC3:", nullptr));
        checkBox_DYC_1->setText(QString());
        label_18->setText(QApplication::translate("mian_widget", "DYC4:", nullptr));
        checkBox_DYC_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("mian_widget", "\350\276\223\345\207\272\346\216\247\345\210\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mian_widget: public Ui_mian_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIAN_WIDGET_H
