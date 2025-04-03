
#ifndef DATA_THREAD_H
#define DATA_THREAD_H

#include <QThread>
#include <mainwindow.h>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

//typedef struct
//{
//    int id;
//    QString mark;
//    double data;
//}DATA_BASE3;

class data_Thread : public QThread
{
    Q_OBJECT
public:
    explicit data_Thread(QObject *parent = 0);
    short workCount = 0;//计数

public slots:
//    // 查询全部数据
//    void queryTable(QString tableName);
//    // 查询指定数据
//    DATA_BASE3 query_oneTable(QString tableName,QString data_time);
//    // 插入数据
//    void singleInsertData(QString table_name,DATA_BASE3 &singleData); // 插入单条数据
//    void moreInsertData(QString tableName,QList<DATA_BASE3> &moreData); // 插入多条数据
//    // 修改数据
//    void modifyData(QString tableName,DATA_BASE3 db);
//    // 删除数据
//    void deleteData(QString tableName,int id);
//    //删除数据表
//    void deleteTable(QString tableName);

private:
    virtual void run();//任务处理线程
    bool FindFileForDelete(const QString & path);//循环删除过期图片
//    QSqlDatabase thread_data_base;// 用于建立和数据库的连接

signals:
//    void Rain_Signal(int);
};

#endif // DATA_THREAD_H
