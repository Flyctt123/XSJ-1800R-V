#ifndef SQLITE_H
#define SQLITE_H

#include <QThread>
#include <mainwindow.h>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

typedef struct
{
    int id;
    QString mark;
    float data;
}DATA_BASE;

class sqlite : public QThread
{
    Q_OBJECT
public:
    explicit sqlite(QObject *parent = 0);
    short workCount = 0;//计数
    DATA_BASE db;
    QSqlDatabase database;// 用于建立和数据库的连接

public slots:
    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString tableName);
    // 查询全部数据
    void queryTable(QString tableName);
    // 查询指定行数据
    DATA_BASE query_oneTable(QString tableName,int id);
    // 插入数据
    void singleInsertData(QString tableName,DATA_BASE &singleData); // 插入单条数据
    void moreInsertData(QString tableName,QList<DATA_BASE> &moreData); // 插入多条数据
    // 修改数据
    void modifyData(QString tableName,DATA_BASE db);
    // 删除数据
    void deleteData(QString tableName,int id);
    //删除数据表
    void deleteTable(QString tableName);
    // 关闭数据库
    void closeDb(QSqlDatabase database);

private:
    virtual void run();//任务处理线程
};

#endif // SQLITE_H
