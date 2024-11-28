/********************************************************************************
** Form generated from reading UI file 'history_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_WIDGET_H
#define UI_HISTORY_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_history_widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_water;
    QPushButton *button_water_timestart;
    QLabel *label_date_water;
    QPushButton *button_water_determine;
    QTableView *tableView_water;
    QWidget *tab_flow_speed;
    QPushButton *button_flow_speed_determine;
    QLabel *label_date_flow_speed;
    QPushButton *button_flow_speed_timestart;
    QTableView *tableView_flow_speed;
    QWidget *tab_flow_now;
    QPushButton *button_flow_now_timestart;
    QLabel *label_date_flow_now;
    QPushButton *button_flow_now_determine;
    QTableView *tableView_flow_now;
    QWidget *tab_rain_now;
    QTableView *tableView_rain_now;
    QPushButton *button_rain_now_timestart;
    QLabel *label_date_rain_now;
    QPushButton *button_rain_now_determine;

    void setupUi(QWidget *history_widget)
    {
        if (history_widget->objectName().isEmpty())
            history_widget->setObjectName(QString::fromUtf8("history_widget"));
        history_widget->resize(520, 322);
        tabWidget = new QTabWidget(history_widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1, 3, 380, 215));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget:focus {\n"
"    outline: none;\n"
"}"));
        tab_water = new QWidget();
        tab_water->setObjectName(QString::fromUtf8("tab_water"));
        button_water_timestart = new QPushButton(tab_water);
        button_water_timestart->setObjectName(QString::fromUtf8("button_water_timestart"));
        button_water_timestart->setGeometry(QRect(10, 4, 110, 30));
        button_water_timestart->setFocusPolicy(Qt::NoFocus);
        label_date_water = new QLabel(tab_water);
        label_date_water->setObjectName(QString::fromUtf8("label_date_water"));
        label_date_water->setGeometry(QRect(130, 7, 110, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        label_date_water->setFont(font);
        label_date_water->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        button_water_determine = new QPushButton(tab_water);
        button_water_determine->setObjectName(QString::fromUtf8("button_water_determine"));
        button_water_determine->setGeometry(QRect(290, 4, 70, 30));
        button_water_determine->setFocusPolicy(Qt::NoFocus);
        tableView_water = new QTableView(tab_water);
        tableView_water->setObjectName(QString::fromUtf8("tableView_water"));
        tableView_water->setGeometry(QRect(5, 40, 360, 140));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(9);
        tableView_water->setFont(font1);
        tabWidget->addTab(tab_water, QString());
        tab_flow_speed = new QWidget();
        tab_flow_speed->setObjectName(QString::fromUtf8("tab_flow_speed"));
        button_flow_speed_determine = new QPushButton(tab_flow_speed);
        button_flow_speed_determine->setObjectName(QString::fromUtf8("button_flow_speed_determine"));
        button_flow_speed_determine->setGeometry(QRect(290, 4, 70, 30));
        button_flow_speed_determine->setFocusPolicy(Qt::NoFocus);
        label_date_flow_speed = new QLabel(tab_flow_speed);
        label_date_flow_speed->setObjectName(QString::fromUtf8("label_date_flow_speed"));
        label_date_flow_speed->setGeometry(QRect(130, 7, 110, 25));
        label_date_flow_speed->setFont(font);
        button_flow_speed_timestart = new QPushButton(tab_flow_speed);
        button_flow_speed_timestart->setObjectName(QString::fromUtf8("button_flow_speed_timestart"));
        button_flow_speed_timestart->setGeometry(QRect(10, 4, 110, 30));
        button_flow_speed_timestart->setFocusPolicy(Qt::NoFocus);
        tableView_flow_speed = new QTableView(tab_flow_speed);
        tableView_flow_speed->setObjectName(QString::fromUtf8("tableView_flow_speed"));
        tableView_flow_speed->setGeometry(QRect(5, 40, 360, 140));
        tableView_flow_speed->setFont(font1);
        tabWidget->addTab(tab_flow_speed, QString());
        tab_flow_now = new QWidget();
        tab_flow_now->setObjectName(QString::fromUtf8("tab_flow_now"));
        button_flow_now_timestart = new QPushButton(tab_flow_now);
        button_flow_now_timestart->setObjectName(QString::fromUtf8("button_flow_now_timestart"));
        button_flow_now_timestart->setGeometry(QRect(10, 4, 110, 30));
        button_flow_now_timestart->setFocusPolicy(Qt::NoFocus);
        label_date_flow_now = new QLabel(tab_flow_now);
        label_date_flow_now->setObjectName(QString::fromUtf8("label_date_flow_now"));
        label_date_flow_now->setGeometry(QRect(130, 7, 110, 25));
        label_date_flow_now->setFont(font);
        button_flow_now_determine = new QPushButton(tab_flow_now);
        button_flow_now_determine->setObjectName(QString::fromUtf8("button_flow_now_determine"));
        button_flow_now_determine->setGeometry(QRect(290, 4, 70, 30));
        button_flow_now_determine->setFocusPolicy(Qt::NoFocus);
        tableView_flow_now = new QTableView(tab_flow_now);
        tableView_flow_now->setObjectName(QString::fromUtf8("tableView_flow_now"));
        tableView_flow_now->setGeometry(QRect(5, 40, 360, 140));
        tableView_flow_now->setFont(font1);
        tabWidget->addTab(tab_flow_now, QString());
        tab_rain_now = new QWidget();
        tab_rain_now->setObjectName(QString::fromUtf8("tab_rain_now"));
        tableView_rain_now = new QTableView(tab_rain_now);
        tableView_rain_now->setObjectName(QString::fromUtf8("tableView_rain_now"));
        tableView_rain_now->setGeometry(QRect(5, 40, 360, 140));
        tableView_rain_now->setFont(font1);
        button_rain_now_timestart = new QPushButton(tab_rain_now);
        button_rain_now_timestart->setObjectName(QString::fromUtf8("button_rain_now_timestart"));
        button_rain_now_timestart->setGeometry(QRect(10, 4, 110, 30));
        button_rain_now_timestart->setFocusPolicy(Qt::NoFocus);
        label_date_rain_now = new QLabel(tab_rain_now);
        label_date_rain_now->setObjectName(QString::fromUtf8("label_date_rain_now"));
        label_date_rain_now->setGeometry(QRect(130, 7, 110, 25));
        label_date_rain_now->setFont(font);
        button_rain_now_determine = new QPushButton(tab_rain_now);
        button_rain_now_determine->setObjectName(QString::fromUtf8("button_rain_now_determine"));
        button_rain_now_determine->setGeometry(QRect(290, 4, 70, 30));
        button_rain_now_determine->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tab_rain_now, QString());

        retranslateUi(history_widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(history_widget);
    } // setupUi

    void retranslateUi(QWidget *history_widget)
    {
        history_widget->setWindowTitle(QApplication::translate("history_widget", "Form", nullptr));
        button_water_timestart->setText(QApplication::translate("history_widget", "\350\256\276\347\275\256\346\237\245\350\257\242\346\227\266\351\227\264", nullptr));
        label_date_water->setText(QString());
        button_water_determine->setText(QApplication::translate("history_widget", "\346\237\245\350\257\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_water), QApplication::translate("history_widget", "\346\260\264\344\275\215", nullptr));
        button_flow_speed_determine->setText(QApplication::translate("history_widget", "\346\237\245\350\257\242", nullptr));
        label_date_flow_speed->setText(QString());
        button_flow_speed_timestart->setText(QApplication::translate("history_widget", "\350\256\276\347\275\256\346\237\245\350\257\242\346\227\266\351\227\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_flow_speed), QApplication::translate("history_widget", "\346\265\201\351\200\237", nullptr));
        button_flow_now_timestart->setText(QApplication::translate("history_widget", "\350\256\276\347\275\256\346\237\245\350\257\242\346\227\266\351\227\264", nullptr));
        label_date_flow_now->setText(QString());
        button_flow_now_determine->setText(QApplication::translate("history_widget", "\346\237\245\350\257\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_flow_now), QApplication::translate("history_widget", "\347\236\254\346\227\266\346\265\201\351\207\217", nullptr));
        button_rain_now_timestart->setText(QApplication::translate("history_widget", "\350\256\276\347\275\256\346\237\245\350\257\242\346\227\266\351\227\264", nullptr));
        label_date_rain_now->setText(QString());
        button_rain_now_determine->setText(QApplication::translate("history_widget", "\346\237\245\350\257\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_rain_now), QApplication::translate("history_widget", "\345\275\223\345\211\215\351\233\250\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class history_widget: public Ui_history_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_WIDGET_H
