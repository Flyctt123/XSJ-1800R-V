/********************************************************************************
** Form generated from reading UI file 'camera_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_WIDGET_H
#define UI_CAMERA_WIDGET_H

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

class Ui_camera_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBox_init;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_save;
    QCheckBox *checkBox_open;
    QWidget *tab_3;
    QCheckBox *checkBox_water;
    QCheckBox *checkBox_flow_current;
    QPushButton *pushButton_osd_save;
    QWidget *tab_2;
    QComboBox *comboBox_takephoto;
    QPushButton *pushButton_takephoto;
    QLabel *label_image;

    void setupUi(QWidget *camera_widget)
    {
        if (camera_widget->objectName().isEmpty())
            camera_widget->setObjectName(QString::fromUtf8("camera_widget"));
        camera_widget->resize(400, 261);
        tabWidget = new QTabWidget(camera_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        comboBox_init = new QComboBox(tab);
        comboBox_init->addItem(QString());
        comboBox_init->addItem(QString());
        comboBox_init->addItem(QString());
        comboBox_init->setObjectName(QString::fromUtf8("comboBox_init"));
        comboBox_init->setGeometry(QRect(9, 20, 101, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        comboBox_init->setFont(font);
        comboBox_init->setFocusPolicy(Qt::NoFocus);
        comboBox_init->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 20, 111, 22));
        label->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 46, 81, 22));
        label_2->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(140, 72, 81, 22));
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_ip = new QLineEdit(tab);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(220, 20, 151, 22));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(10);
        lineEdit_ip->setFont(font1);
        lineEdit_name = new QLineEdit(tab);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(220, 46, 151, 22));
        lineEdit_name->setFont(font1);
        lineEdit_password = new QLineEdit(tab);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(220, 72, 151, 22));
        lineEdit_password->setFont(font1);
        pushButton_save = new QPushButton(tab);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(280, 110, 71, 27));
        pushButton_save->setFocusPolicy(Qt::NoFocus);
        checkBox_open = new QCheckBox(tab);
        checkBox_open->setObjectName(QString::fromUtf8("checkBox_open"));
        checkBox_open->setGeometry(QRect(14, 70, 80, 20));
        checkBox_open->setFocusPolicy(Qt::NoFocus);
        checkBox_open->setStyleSheet(QString::fromUtf8("QCheckBox::indicator:unchecked {\n"
"image: url(:/back/image/switch_off.png);\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"image: url(:/back/image/switch_on.png);\n"
"}\n"
"QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        checkBox_water = new QCheckBox(tab_3);
        checkBox_water->setObjectName(QString::fromUtf8("checkBox_water"));
        checkBox_water->setGeometry(QRect(130, 30, 121, 19));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(10);
        checkBox_water->setFont(font2);
        checkBox_water->setFocusPolicy(Qt::NoFocus);
        checkBox_flow_current = new QCheckBox(tab_3);
        checkBox_flow_current->setObjectName(QString::fromUtf8("checkBox_flow_current"));
        checkBox_flow_current->setGeometry(QRect(130, 60, 131, 19));
        checkBox_flow_current->setFont(font2);
        checkBox_flow_current->setFocusPolicy(Qt::NoFocus);
        pushButton_osd_save = new QPushButton(tab_3);
        pushButton_osd_save->setObjectName(QString::fromUtf8("pushButton_osd_save"));
        pushButton_osd_save->setGeometry(QRect(270, 130, 71, 28));
        pushButton_osd_save->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        comboBox_takephoto = new QComboBox(tab_2);
        comboBox_takephoto->addItem(QString());
        comboBox_takephoto->addItem(QString());
        comboBox_takephoto->addItem(QString());
        comboBox_takephoto->setObjectName(QString::fromUtf8("comboBox_takephoto"));
        comboBox_takephoto->setGeometry(QRect(10, 10, 101, 31));
        comboBox_takephoto->setFocusPolicy(Qt::NoFocus);
        comboBox_takephoto->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\256\213\344\275\223\";"));
        pushButton_takephoto = new QPushButton(tab_2);
        pushButton_takephoto->setObjectName(QString::fromUtf8("pushButton_takephoto"));
        pushButton_takephoto->setGeometry(QRect(10, 50, 101, 31));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_takephoto->sizePolicy().hasHeightForWidth());
        pushButton_takephoto->setSizePolicy(sizePolicy);
        pushButton_takephoto->setFont(font2);
        pushButton_takephoto->setFocusPolicy(Qt::NoFocus);
        label_image = new QLabel(tab_2);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setGeometry(QRect(120, 5, 251, 171));
        label_image->setStyleSheet(QString::fromUtf8("background-color: rgb(222, 222, 222);"));
        label_image->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(camera_widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(camera_widget);
    } // setupUi

    void retranslateUi(QWidget *camera_widget)
    {
        camera_widget->setWindowTitle(QApplication::translate("camera_widget", "Form", nullptr));
        comboBox_init->setItemText(0, QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\2641", nullptr));
        comboBox_init->setItemText(1, QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\2642", nullptr));
        comboBox_init->setItemText(2, QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\2643", nullptr));

        label->setText(QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\264IP\357\274\232", nullptr));
        label_2->setText(QApplication::translate("camera_widget", " \350\264\246\345\217\267\357\274\232", nullptr));
        label_3->setText(QApplication::translate("camera_widget", " \345\257\206\347\240\201\357\274\232", nullptr));
        pushButton_save->setText(QApplication::translate("camera_widget", "\344\277\235\345\255\230", nullptr));
        checkBox_open->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\264\351\205\215\347\275\256", nullptr));
        checkBox_water->setText(QApplication::translate("camera_widget", "\346\260\264\344\275\215", nullptr));
        checkBox_flow_current->setText(QApplication::translate("camera_widget", "\347\236\254\346\227\266\346\265\201\351\207\217", nullptr));
        pushButton_osd_save->setText(QApplication::translate("camera_widget", "\344\277\235\345\255\230", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("camera_widget", "\345\255\227\347\254\246\345\217\240\345\212\240", nullptr));
        comboBox_takephoto->setItemText(0, QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\2641", nullptr));
        comboBox_takephoto->setItemText(1, QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\2642", nullptr));
        comboBox_takephoto->setItemText(2, QApplication::translate("camera_widget", "\346\221\204\345\203\217\345\244\2643", nullptr));

        pushButton_takephoto->setText(QApplication::translate("camera_widget", "\346\211\213\345\212\250\346\212\223\346\213\215", nullptr));
        label_image->setText(QApplication::translate("camera_widget", " \346\212\223\346\213\215\347\232\204\345\233\276\347\211\207", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("camera_widget", "\346\212\223\346\213\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class camera_widget: public Ui_camera_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_WIDGET_H
