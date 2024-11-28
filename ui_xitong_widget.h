/********************************************************************************
** Form generated from reading UI file 'xitong_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XITONG_WIDGET_H
#define UI_XITONG_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xitong_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_version;
    QPushButton *pushButton_save_info;
    QLabel *label_3;
    QLineEdit *lineEdit_station_info;
    QWidget *tab_2;
    QPushButton *usb_Button_check;
    QLabel *label_usb;
    QGroupBox *groupBox_2;
    QPushButton *usb_Button_picture;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QPushButton *usb_Button_data;
    QPushButton *usb_Button_history;
    QGroupBox *groupBox_3;
    QPushButton *usb_Button_update;
    QPushButton *usb_Button_Config_update;
    QWidget *tab_3;
    QPushButton *pushButton_restart;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_sysclear;
    QPushButton *pushButton_reSendclear;
    QWidget *tab_4;
    QPushButton *pushButton_save_time;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_year;
    QLabel *label;
    QLineEdit *lineEdit_mon;
    QLabel *label_2;
    QLineEdit *lineEdit_day;
    QLabel *label_4;
    QLineEdit *lineEdit_hour;
    QLabel *label_5;
    QLineEdit *lineEdit_min;
    QLabel *label_6;
    QLineEdit *lineEdit_sec;
    QLabel *label_7;

    void setupUi(QWidget *xitong_widget)
    {
        if (xitong_widget->objectName().isEmpty())
            xitong_widget->setObjectName(QString::fromUtf8("xitong_widget"));
        xitong_widget->resize(551, 302);
        tabWidget = new QTabWidget(xitong_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_version = new QLabel(tab);
        label_version->setObjectName(QString::fromUtf8("label_version"));
        label_version->setGeometry(QRect(10, 20, 361, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(9);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_version->setFont(font);
        label_version->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        pushButton_save_info = new QPushButton(tab);
        pushButton_save_info->setObjectName(QString::fromUtf8("pushButton_save_info"));
        pushButton_save_info->setGeometry(QRect(280, 140, 71, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        pushButton_save_info->setFont(font1);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 73, 72, 15));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        lineEdit_station_info = new QLineEdit(tab);
        lineEdit_station_info->setObjectName(QString::fromUtf8("lineEdit_station_info"));
        lineEdit_station_info->setGeometry(QRect(90, 70, 101, 21));
        lineEdit_station_info->setFont(font);
        lineEdit_station_info->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\256\213\344\275\223\";"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        usb_Button_check = new QPushButton(tab_2);
        usb_Button_check->setObjectName(QString::fromUtf8("usb_Button_check"));
        usb_Button_check->setGeometry(QRect(20, 10, 101, 27));
        usb_Button_check->setFont(font1);
        usb_Button_check->setFocusPolicy(Qt::NoFocus);
        label_usb = new QLabel(tab_2);
        label_usb->setObjectName(QString::fromUtf8("label_usb"));
        label_usb->setGeometry(QRect(130, 13, 141, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label_usb->setFont(font2);
        label_usb->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";\n"
"color: rgb(247, 0, 0);"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(120, 60, 121, 121));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(8);
        groupBox_2->setFont(font3);
        usb_Button_picture = new QPushButton(groupBox_2);
        usb_Button_picture->setObjectName(QString::fromUtf8("usb_Button_picture"));
        usb_Button_picture->setGeometry(QRect(10, 70, 101, 27));
        usb_Button_picture->setFont(font3);
        usb_Button_picture->setFocusPolicy(Qt::NoFocus);
        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 30, 101, 27));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font4.setPointSize(9);
        comboBox->setFont(font4);
        comboBox->setFocusPolicy(Qt::NoFocus);
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 60, 101, 121));
        groupBox->setFont(font3);
        usb_Button_data = new QPushButton(groupBox);
        usb_Button_data->setObjectName(QString::fromUtf8("usb_Button_data"));
        usb_Button_data->setGeometry(QRect(10, 30, 81, 27));
        usb_Button_data->setFocusPolicy(Qt::NoFocus);
        usb_Button_history = new QPushButton(groupBox);
        usb_Button_history->setObjectName(QString::fromUtf8("usb_Button_history"));
        usb_Button_history->setGeometry(QRect(10, 70, 81, 27));
        usb_Button_history->setFocusPolicy(Qt::NoFocus);
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(250, 60, 101, 121));
        groupBox_3->setFont(font3);
        usb_Button_update = new QPushButton(groupBox_3);
        usb_Button_update->setObjectName(QString::fromUtf8("usb_Button_update"));
        usb_Button_update->setGeometry(QRect(10, 70, 81, 27));
        usb_Button_update->setFont(font3);
        usb_Button_update->setFocusPolicy(Qt::NoFocus);
        usb_Button_Config_update = new QPushButton(groupBox_3);
        usb_Button_Config_update->setObjectName(QString::fromUtf8("usb_Button_Config_update"));
        usb_Button_Config_update->setGeometry(QRect(10, 30, 81, 27));
        usb_Button_Config_update->setFont(font3);
        usb_Button_Config_update->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        pushButton_restart = new QPushButton(tab_3);
        pushButton_restart->setObjectName(QString::fromUtf8("pushButton_restart"));
        pushButton_restart->setGeometry(QRect(210, 40, 101, 31));
        pushButton_restart->setFocusPolicy(Qt::NoFocus);
        pushButton_reset = new QPushButton(tab_3);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));
        pushButton_reset->setGeometry(QRect(210, 90, 101, 31));
        pushButton_reset->setFocusPolicy(Qt::NoFocus);
        pushButton_sysclear = new QPushButton(tab_3);
        pushButton_sysclear->setObjectName(QString::fromUtf8("pushButton_sysclear"));
        pushButton_sysclear->setGeometry(QRect(60, 40, 101, 31));
        pushButton_sysclear->setFocusPolicy(Qt::NoFocus);
        pushButton_reSendclear = new QPushButton(tab_3);
        pushButton_reSendclear->setObjectName(QString::fromUtf8("pushButton_reSendclear"));
        pushButton_reSendclear->setGeometry(QRect(60, 90, 101, 31));
        pushButton_reSendclear->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        pushButton_save_time = new QPushButton(tab_4);
        pushButton_save_time->setObjectName(QString::fromUtf8("pushButton_save_time"));
        pushButton_save_time->setGeometry(QRect(260, 140, 93, 28));
        pushButton_save_time->setFocusPolicy(Qt::NoFocus);
        layoutWidget = new QWidget(tab_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 311, 51));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_year = new QLineEdit(layoutWidget);
        lineEdit_year->setObjectName(QString::fromUtf8("lineEdit_year"));

        gridLayout->addWidget(lineEdit_year, 0, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font5;
        font5.setPointSize(10);
        label->setFont(font5);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit_mon = new QLineEdit(layoutWidget);
        lineEdit_mon->setObjectName(QString::fromUtf8("lineEdit_mon"));

        gridLayout->addWidget(lineEdit_mon, 0, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font5);

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        lineEdit_day = new QLineEdit(layoutWidget);
        lineEdit_day->setObjectName(QString::fromUtf8("lineEdit_day"));

        gridLayout->addWidget(lineEdit_day, 0, 4, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font5);

        gridLayout->addWidget(label_4, 0, 5, 1, 1);

        lineEdit_hour = new QLineEdit(layoutWidget);
        lineEdit_hour->setObjectName(QString::fromUtf8("lineEdit_hour"));

        gridLayout->addWidget(lineEdit_hour, 1, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font5);

        gridLayout->addWidget(label_5, 1, 1, 1, 1);

        lineEdit_min = new QLineEdit(layoutWidget);
        lineEdit_min->setObjectName(QString::fromUtf8("lineEdit_min"));

        gridLayout->addWidget(lineEdit_min, 1, 2, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font5);

        gridLayout->addWidget(label_6, 1, 3, 1, 1);

        lineEdit_sec = new QLineEdit(layoutWidget);
        lineEdit_sec->setObjectName(QString::fromUtf8("lineEdit_sec"));

        gridLayout->addWidget(lineEdit_sec, 1, 4, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font5);

        gridLayout->addWidget(label_7, 1, 5, 1, 1);

        tabWidget->addTab(tab_4, QString());

        retranslateUi(xitong_widget);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(xitong_widget);
    } // setupUi

    void retranslateUi(QWidget *xitong_widget)
    {
        xitong_widget->setWindowTitle(QApplication::translate("xitong_widget", "Form", nullptr));
        label_version->setText(QApplication::translate("xitong_widget", "\350\275\257\344\273\266\347\211\210\346\234\254\357\274\23220240131B", nullptr));
        pushButton_save_info->setText(QApplication::translate("xitong_widget", "\344\277\235\345\255\230", nullptr));
        label_3->setText(QApplication::translate("xitong_widget", "\347\253\231\347\202\271\345\220\215\347\247\260\357\274\232", nullptr));
        lineEdit_station_info->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("xitong_widget", "\350\256\276\345\244\207\344\277\241\346\201\257", nullptr));
        usb_Button_check->setText(QApplication::translate("xitong_widget", "\346\243\200\346\265\213USB\350\256\276\345\244\207", nullptr));
        label_usb->setText(QString());
        groupBox_2->setTitle(QApplication::translate("xitong_widget", "\345\233\276\347\211\207\345\257\274\345\207\272", nullptr));
        usb_Button_picture->setText(QApplication::translate("xitong_widget", "\345\233\276\347\211\207\345\257\274\345\207\272", nullptr));
        comboBox->setItemText(0, QApplication::translate("xitong_widget", "\346\221\204\345\203\217\345\244\2641", nullptr));
        comboBox->setItemText(1, QApplication::translate("xitong_widget", "\346\221\204\345\203\217\345\244\2642", nullptr));
        comboBox->setItemText(2, QApplication::translate("xitong_widget", "\346\221\204\345\203\217\345\244\2643", nullptr));

        groupBox->setTitle(QApplication::translate("xitong_widget", "\346\225\260\346\215\256\345\257\274\345\207\272", nullptr));
        usb_Button_data->setText(QApplication::translate("xitong_widget", "\346\225\260\346\215\256\345\257\274\345\207\272", nullptr));
        usb_Button_history->setText(QApplication::translate("xitong_widget", "\346\227\245\345\277\227\345\257\274\345\207\272", nullptr));
        groupBox_3->setTitle(QApplication::translate("xitong_widget", "\350\256\276\345\244\207\346\233\264\346\226\260", nullptr));
        usb_Button_update->setText(QApplication::translate("xitong_widget", "\347\211\210\346\234\254\345\215\207\347\272\247", nullptr));
        usb_Button_Config_update->setText(QApplication::translate("xitong_widget", "\351\205\215\347\275\256\346\233\264\346\226\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("xitong_widget", "USB\350\256\276\345\244\207", nullptr));
        pushButton_restart->setText(QApplication::translate("xitong_widget", "\351\207\215\345\220\257\350\256\276\345\244\207", nullptr));
        pushButton_reset->setText(QApplication::translate("xitong_widget", "\346\201\242\345\244\215\345\207\272\345\216\202\350\256\276\347\275\256", nullptr));
        pushButton_sysclear->setText(QApplication::translate("xitong_widget", "\346\270\205\347\251\272\345\216\206\345\217\262\346\225\260\346\215\256", nullptr));
        pushButton_reSendclear->setText(QApplication::translate("xitong_widget", "\346\270\205\347\251\272\350\241\245\344\274\240\346\225\260\346\215\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("xitong_widget", "\350\256\276\345\244\207\347\256\241\347\220\206", nullptr));
        pushButton_save_time->setText(QApplication::translate("xitong_widget", "\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        label->setText(QApplication::translate("xitong_widget", "\345\271\264", nullptr));
        label_2->setText(QApplication::translate("xitong_widget", "\346\234\210", nullptr));
        label_4->setText(QApplication::translate("xitong_widget", "\346\227\245", nullptr));
        label_5->setText(QApplication::translate("xitong_widget", "\346\227\266", nullptr));
        label_6->setText(QApplication::translate("xitong_widget", "\345\210\206", nullptr));
        label_7->setText(QApplication::translate("xitong_widget", "\347\247\222", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("xitong_widget", "\347\263\273\347\273\237\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class xitong_widget: public Ui_xitong_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XITONG_WIDGET_H
