#ifndef ALARMLOG_WIDGET_H
#define ALARMLOG_WIDGET_H

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
#include "keyboard.h"
#include "keyboard_ABC.h"

namespace Ui {
class alarmLog_widget;
}

class alarmLog_widget : public QWidget
{
    Q_OBJECT

public:
    explicit alarmLog_widget(QWidget *parent = nullptr);
    ~alarmLog_widget();
private:
    Ui::alarmLog_widget *ui;
    QCalendarWidget *calendar; //日历

    KeyBoard *keyBoard=nullptr;
    KeyBoard_ABC *keyBoard_ABC=nullptr;

    QSqlDatabase alarm_data_base;// 用于建立和数据库的连接
    QSqlQueryModel *model;
private slots:
    bool eventFilter(QObject *, QEvent *);
    void callKeyBoard(QLineEdit *a);
    void alarmlog_button_init(QPushButton *button_init);
    void changedata(void);
    void excel_load_5min(QString tableName,QTableView *tableview,QString data_time1,QString data_time2);

    void on_tab_button_timestart_clicked();
    void on_tab_button_determine_clicked();

    void on_pushButton_log_clicked();
    void on_pushButton_log_clear_clicked();
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
};

#endif // ALARMLOG_WIDGET_H
