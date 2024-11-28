#ifndef HISTORY_WIDGET_H
#define HISTORY_WIDGET_H

#include "mainwindow.h"
#include <QWidget>
#include <QCalendarWidget>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QtCharts>         // 导入QtCharts所有的头文件，也可以单独导入某一个
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class history_widget;
}

class history_widget : public QWidget
{
    Q_OBJECT

public:
    explicit history_widget(QWidget *parent = nullptr);
    ~history_widget();

private slots:
    void history_button_init(QPushButton *button_init);
    void changedata(void);
    void excel_load_5min(QString tableName,QTableView *tableview,QString data_time1,QString data_time2);
    //void Qchar_Init_15min(QString tableName,QChartView *chartView);

    void on_button_water_timestart_clicked();
    void on_button_flow_speed_timestart_clicked();
    void on_button_flow_now_timestart_clicked();
    void on_button_rain_now_timestart_clicked();

    void on_button_water_determine_clicked();
    void on_button_rain_now_determine_clicked();
    void on_button_flow_speed_determine_clicked();
    void on_button_flow_now_determine_clicked();

private:
    Ui::history_widget *ui;
    QCalendarWidget *calendar; //日历

    QSqlDatabase history_data_base;// 用于建立和数据库的连接
    QSqlQueryModel *model;
    /* 创建excel表数据模型 */
    //QStandardItemModel* model;
};

#endif // HISTORY_WIDGET_H
