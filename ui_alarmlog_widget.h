/********************************************************************************
** Form generated from reading UI file 'alarmlog_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMLOG_WIDGET_H
#define UI_ALARMLOG_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_alarmLog_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_upLimit;
    QLineEdit *lineEdit_downLimit;
    QWidget *tab;
    QLabel *label_time;
    QPushButton *tab_button_timestart;
    QPushButton *tab_button_determine;
    QTableView *tableView_data;
    QWidget *tab_2;
    QPushButton *pushButton_log;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton_log_clear;

    void setupUi(QWidget *alarmLog_widget)
    {
        if (alarmLog_widget->objectName().isEmpty())
            alarmLog_widget->setObjectName(QString::fromUtf8("alarmLog_widget"));
        alarmLog_widget->resize(400, 256);
        tabWidget = new QTabWidget(alarmLog_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        comboBox = new QComboBox(tab_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(30, 20, 101, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(10);
        comboBox->setFont(font);
        comboBox->setFocusPolicy(Qt::NoFocus);
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 150, 93, 28));
        pushButton->setFocusPolicy(Qt::NoFocus);
        label = new QLabel(tab_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 51, 16));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 100, 51, 16));
        lineEdit_upLimit = new QLineEdit(tab_3);
        lineEdit_upLimit->setObjectName(QString::fromUtf8("lineEdit_upLimit"));
        lineEdit_upLimit->setGeometry(QRect(90, 70, 71, 21));
        lineEdit_downLimit = new QLineEdit(tab_3);
        lineEdit_downLimit->setObjectName(QString::fromUtf8("lineEdit_downLimit"));
        lineEdit_downLimit->setGeometry(QRect(90, 100, 71, 21));
        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_time = new QLabel(tab);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(130, 7, 111, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(9);
        label_time->setFont(font1);
        tab_button_timestart = new QPushButton(tab);
        tab_button_timestart->setObjectName(QString::fromUtf8("tab_button_timestart"));
        tab_button_timestart->setGeometry(QRect(10, 4, 110, 30));
        tab_button_timestart->setFocusPolicy(Qt::NoFocus);
        tab_button_determine = new QPushButton(tab);
        tab_button_determine->setObjectName(QString::fromUtf8("tab_button_determine"));
        tab_button_determine->setGeometry(QRect(294, 4, 71, 30));
        tab_button_determine->setFocusPolicy(Qt::NoFocus);
        tableView_data = new QTableView(tab);
        tableView_data->setObjectName(QString::fromUtf8("tableView_data"));
        tableView_data->setGeometry(QRect(5, 40, 360, 140));
        tableView_data->setFont(font1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        pushButton_log = new QPushButton(tab_2);
        pushButton_log->setObjectName(QString::fromUtf8("pushButton_log"));
        pushButton_log->setGeometry(QRect(270, 7, 93, 28));
        pushButton_log->setFocusPolicy(Qt::NoFocus);
        plainTextEdit = new QPlainTextEdit(tab_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 40, 371, 141));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(6);
        plainTextEdit->setFont(font2);
        pushButton_log_clear = new QPushButton(tab_2);
        pushButton_log_clear->setObjectName(QString::fromUtf8("pushButton_log_clear"));
        pushButton_log_clear->setGeometry(QRect(10, 7, 93, 28));
        pushButton_log_clear->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(alarmLog_widget);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(alarmLog_widget);
    } // setupUi

    void retranslateUi(QWidget *alarmLog_widget)
    {
        alarmLog_widget->setWindowTitle(QApplication::translate("alarmLog_widget", "Form", nullptr));
        comboBox->setItemText(0, QApplication::translate("alarmLog_widget", "\346\260\264\344\275\215", nullptr));
        comboBox->setItemText(1, QApplication::translate("alarmLog_widget", "\346\265\201\351\207\217", nullptr));
        comboBox->setItemText(2, QApplication::translate("alarmLog_widget", "\351\233\250\351\207\217", nullptr));
        comboBox->setItemText(3, QApplication::translate("alarmLog_widget", "\346\265\201\351\200\237", nullptr));

        pushButton->setText(QApplication::translate("alarmLog_widget", "\344\277\235\345\255\230\345\217\202\346\225\260", nullptr));
        label->setText(QApplication::translate("alarmLog_widget", "\344\270\212\351\231\220\357\274\232", nullptr));
        label_2->setText(QApplication::translate("alarmLog_widget", "\344\270\213\351\231\220\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("alarmLog_widget", "\345\221\212\350\255\246\351\205\215\347\275\256", nullptr));
        label_time->setText(QString());
        tab_button_timestart->setText(QApplication::translate("alarmLog_widget", "\350\256\276\347\275\256\346\237\245\350\257\242\346\227\266\351\227\264", nullptr));
        tab_button_determine->setText(QApplication::translate("alarmLog_widget", "\346\237\245\350\257\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("alarmLog_widget", "\345\274\202\345\270\270\350\256\260\345\275\225", nullptr));
        pushButton_log->setText(QApplication::translate("alarmLog_widget", "\346\230\276\347\244\272\346\227\245\345\277\227", nullptr));
        pushButton_log_clear->setText(QApplication::translate("alarmLog_widget", "\346\270\205\351\231\244\346\227\245\345\277\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("alarmLog_widget", "\350\256\276\345\244\207\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class alarmLog_widget: public Ui_alarmLog_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMLOG_WIDGET_H
