#include "sqlite.h"
#include <QMutex>
QMutex g_mutex;

sqlite::sqlite(QObject *parent) :
    QThread(parent)
{
    QMutexLocker locker(&g_mutex);
    // 构造函数中初始化数据库对象，并建立数据库
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        // 建立和SQlite数据库的连接
        database = QSqlDatabase::addDatabase("QSQLITE","connect1");
        // 设置数据库文件的名字
        database.setDatabaseName(MainWindow::dbFile);
    }
    openDb();
    // 创建数据表
    createTable();
//    DATA_BASE DATA_BASE_Test2 = {1, "20240102153830", 3315};
//    DATA_BASE DATA_BASE_Test3 = {1, "20240102153830", 82315};
//    DATA_BASE DATA_BASE_Test4 = {1, "20240102153830", 2323};
//    singleInsertData("Flow",DATA_BASE_Test2);
//    singleInsertData("Water",DATA_BASE_Test3);
//    singleInsertData("Rain",DATA_BASE_Test4);
}

void sqlite::run()
{
    while(1)
    {
//        QApplication::processEvents();//防止死循环
//        //modifyData(database,"student",2, "zhaoliu", 25);
//        //queryTable(database,"student");
//        QThread::sleep(1);
    }
}

// 打开数据库
bool sqlite::openDb(void)
{
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        // do something
    }
    return true;
}

// 创建数据表
void sqlite::createTable(void)
{
    // 用于执行sql语句的对象
    QSqlQuery sqlQuery1(database);
    QSqlQuery sqlQuery2(database);
    QSqlQuery sqlQuery3(database);
    QSqlQuery sqlQuery4(database);
    QSqlQuery sqlQuery5(database);
    QSqlQuery sqlQuery6(database);
    QSqlQuery sqlQuery7(database);
    QSqlQuery sqlQuery8(database);
    QSqlQuery sqlQuery9(database);
    QSqlQuery sqlQuery10(database);
    QSqlQuery sqlQuery11(database);
    QSqlQuery sqlQuery12(database);
    QSqlQuery sqlQuery13(database);
    QSqlQuery sqlQuery14(database);
    // 构建创建数据库的sql语句字符串
    QString createSql1 = QString("CREATE TABLE Flow (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data DOUBLE NOT NULL)");
    QString createSql2 = QString("CREATE TABLE Water (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data DOUBLE NOT NULL)");
    QString createSql3 = QString("CREATE TABLE Rain (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data DOUBLE NOT NULL)");
    QString createSql4 = QString("CREATE TABLE Alarm (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql5 = QString("CREATE TABLE Speed (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data DOUBLE NOT NULL)");
    QString createSql6 = QString("CREATE TABLE Rain_Total (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data DOUBLE NOT NULL)");
    QString createSql7 = QString("CREATE TABLE ReSendSW1 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql8 = QString("CREATE TABLE ReSendSW2 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql9 = QString("CREATE TABLE ReSendSW3 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql10 = QString("CREATE TABLE ReSendSW4 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql11 = QString("CREATE TABLE ReSendSZY1 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          count INTEGER NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql12 = QString("CREATE TABLE ReSendSZY2 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          count INTEGER NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql13 = QString("CREATE TABLE ReSendSZY3 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          count INTEGER NOT NULL,\
                          data TEXT NOT NULL)");
    QString createSql14 = QString("CREATE TABLE ReSendSZY4 (\
                          id INTEGER PRIMARY KEY AUTOINCREMENT,\
                          mark TEXT NOT NULL,\
                          count INTEGER NOT NULL,\
                          data TEXT NOT NULL)");
    sqlQuery1.prepare(createSql1);
    sqlQuery2.prepare(createSql2);
    sqlQuery3.prepare(createSql3);
    sqlQuery4.prepare(createSql4);
    sqlQuery5.prepare(createSql5);
    sqlQuery6.prepare(createSql6);
    sqlQuery7.prepare(createSql7);
    sqlQuery8.prepare(createSql8);
    sqlQuery9.prepare(createSql9);
    sqlQuery10.prepare(createSql10);
    sqlQuery11.prepare(createSql11);
    sqlQuery12.prepare(createSql12);
    sqlQuery13.prepare(createSql13);
    sqlQuery14.prepare(createSql14);
    //执行sql语句
    if(!sqlQuery1.exec())
    {
        qDebug() << "Fail to create Flow table";
    }
    if(!sqlQuery2.exec())
    {
        qDebug() << "Fail to create Water table";
    }
    if(!sqlQuery3.exec())
    {
        qDebug() << "Fail to create Rain table";
    }
    if(!sqlQuery4.exec())
    {
        qDebug() << "Fail to create Alarm table";
    }
    if(!sqlQuery5.exec())
    {
        qDebug() << "Fail to create Speed table";
    }
    if(!sqlQuery6.exec())
    {
        qDebug() << "Fail to create Rain_total table";
    }
    if(!sqlQuery7.exec())
    {
        qDebug() << "Fail to create ReSendSW1 table";
    }
    if(!sqlQuery8.exec())
    {
        qDebug() << "Fail to create ReSendSW2 table";
    }
    if(!sqlQuery9.exec())
    {
        qDebug() << "Fail to create ReSendSW3 table";
    }
    if(!sqlQuery10.exec())
    {
        qDebug() << "Fail to create ReSendSW4 table";
    }
    if(!sqlQuery11.exec())
    {
        qDebug() << "Fail to create ReSendSZY1 table";
    }
    if(!sqlQuery12.exec())
    {
        qDebug() << "Fail to create ReSendSZY2 table";
    }
    if(!sqlQuery13.exec())
    {
        qDebug() << "Fail to create ReSendSZY3 table";
    }
    if(!sqlQuery14.exec())
    {
        qDebug() << "Fail to create ReSendSZY4 table";
    }
}

// 判断数据库中某个数据表是否存在
bool sqlite::isTableExist(QString tableName)
{
    database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}

// 查询全部数据
void sqlite::queryTable(QString tableName)
{
    QSqlQuery sqlQuery(database);
    sqlQuery.exec("SELECT * FROM " +tableName);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            int id = sqlQuery.value(0).toInt();
            QString mark = sqlQuery.value(1).toString();
            int data = sqlQuery.value(2).toInt();
            qDebug()<<QString("Aid:%1    mark:%2    data:%3").arg(id).arg(mark).arg(data);
        }
    }
}

// 查询指定行数据
DATA_BASE sqlite::query_oneTable(QString tableName,int id)
{
    QSqlQuery sqlQuery(database);
    sqlQuery.exec(QString("SELECT * FROM " +tableName+ " WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            db.id = sqlQuery.value(0).toInt();
            db.mark = sqlQuery.value(1).toString();
            db.data = sqlQuery.value(2).toInt();
        }
    }
    return db;
}

// 插入单条数据
void sqlite::singleInsertData(QString tableName, DATA_BASE &singledb)
{
    QSqlQuery sqlQuery(database);
    sqlQuery.prepare("INSERT INTO " + tableName + " VALUES(:id,:mark,:data)");
    //sqlQuery.bindValue(":id", singledb.id);
    sqlQuery.bindValue(":mark", singledb.mark);
    sqlQuery.bindValue(":data", singledb.data);
    if(!sqlQuery.exec())
    {
        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
    }
    else
    {
        // do something
    }
}

// 插入多条数据
void sqlite::moreInsertData(QString tableName,QList<DATA_BASE>& moredb)
{
    // 进行多个数据的插入时，可以利用绑定进行批处理
    QSqlQuery sqlQuery(database);
    sqlQuery.prepare("INSERT INTO " + tableName + " VALUES(?,?,?)");
    QVariantList idList,markList,dataList;
    for(int i=0; i< moredb.size(); i++)
    {
        idList <<  moredb.at(i).id;
        markList << moredb.at(i).mark;
        dataList << moredb.at(i).data;
    }
    sqlQuery.addBindValue(idList);
    sqlQuery.addBindValue(markList);
    sqlQuery.addBindValue(dataList);

    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
    {
        qDebug() << sqlQuery.lastError();
    }
}

// 修改数据
void sqlite::modifyData(QString tableName,DATA_BASE db)
{
    QSqlQuery sqlQuery(database);
    sqlQuery.prepare("UPDATE " + tableName + " SET mark=?,data=? WHERE id=?");
    sqlQuery.addBindValue(db.mark);
    sqlQuery.addBindValue(db.data);
    sqlQuery.addBindValue(db.id);
    if(!sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "updated data success!";
    }
}

// 删除数据
void sqlite::deleteData(QString tableName,int id)
{
    QSqlQuery sqlQuery(database);

    sqlQuery.exec(QString("DELETE FROM " +tableName+ " WHERE id = %1").arg(id));
    if(!sqlQuery.exec())
    {
        qDebug()<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"deleted data success!";
    }
}

//删除数据表
void sqlite::deleteTable(QString tableName)
{
    QSqlQuery sqlQuery(database);

    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
    if(sqlQuery.exec())
    {
        qDebug() << sqlQuery.lastError();
    }
    else
    {
        qDebug() << "deleted table success";
    }
}

void sqlite::closeDb(QSqlDatabase database)
{
    database.close();
}
