#include "data_thread.h"
#include "mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QCoreApplication>
#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QMutex>

extern QMutex g_mutex;
extern COMM_CONFIG comm_config[11];
extern bool sys_busy;

data_Thread::data_Thread(QObject *parent) :
    QThread(parent)
{
//    QMutexLocker locker(&g_mutex);
//    thread_data_base=QSqlDatabase::addDatabase("QSQLITE","connect6");
//    thread_data_base.setDatabaseName(MainWindow::dbFile);
//    thread_data_base.open();

//    DATA_BASE3 DATA_BASE_Test1 = {1, "Uart_Addr1", 01};
//    DATA_BASE3 DATA_BASE_Test2 = {1, "20240103154530", 3305};
//    DATA_BASE3 DATA_BASE_Test3 = {1, "20240103154530", 82305};
//    singleInsertData("Config",DATA_BASE_Test1);
//    singleInsertData("Flow",DATA_BASE_Test2);
//    singleInsertData("Water",DATA_BASE_Test3);
}

bool Watch_dog_flag = true;
void data_Thread::run()
{
    while(1)
    {
        QApplication::processEvents();//防止死循环
        workCount++;
#ifdef BRUN
        QFile file("/etc/pointercal");
        QFile file1("/home/ts_init.sh");
        if(file.exists() && (file1.exists()))//文件存在
        {
            system("rm /home/ts_init.sh");
            system("sync");
            system("reboot -f");
        }
#endif
        if(workCount > 9)
        {
            workCount = 0;
#ifdef ARM
            //看门狗
            if(sys_busy == true)
            {
                if(Watch_dog_flag)
                    system("echo 1 > /sys/class/gpio/gpio208/value");
                else
                    system("echo 0 > /sys/class/gpio/gpio208/value");
                Watch_dog_flag = !Watch_dog_flag;
            }

            if((QTime::currentTime().hour() == 0) && (QTime::currentTime().minute() == 0) && (QTime::currentTime().second() == 0))//每天0点清理图片
                FindFileForDelete("/home/images/images1");
#else
            QString path = QDir::currentPath();
            FindFileForDelete(path + "/home/images/images1");
#endif
        }
//        modifyData("student",2, "zhaoliu", 26);
//        queryTable("student");
        QThread::sleep(1);
    }
}

bool data_Thread::FindFileForDelete(const QString &path)
{
    QDir dir(path);
    if (!dir.exists())//不存在
        return false;
    dir.setFilter(QDir::Files);//获取所有文件
    QFileInfoList list = dir.entryInfoList();//获取文件列表
    auto file_count = list.count();
    if (file_count <= 0)
    {
        return true;
    }

    int i=0;
    do{
        QFileInfo fileInfo = list.at(i);
        //如果是文件，判断文件日期 目前默认是30天。
        QDateTime delDateTime = QDateTime::currentDateTime().addDays(-30);
        qint64 nSecs = delDateTime.secsTo(fileInfo.created());//Linux 30天前的时间和该文件创建时间的差值秒
        //qint64 nSecs = delDateTime.secsTo(fileInfo.birthTime());//Windows 30天前的时间和该文件创建时间的差值秒
        if (nSecs < 0)
        {
           qDebug()<<"picture DEL DateTime="<<delDateTime;
           qDebug()<<"rm picture start";
           //qDebug() << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10).arg(fileInfo.fileName(),10).arg(fileInfo.path()))<<endl;
           //删除30天前的文件
           fileInfo.dir().remove(fileInfo.fileName());
        }
        i++;
    }while(i<list.size());
    return true;
}

// 查询全部数据
//void data_Thread::queryTable(QString tableName)
//{
//    QSqlQuery sqlQuery(thread_data_base);
//    sqlQuery.exec("SELECT * FROM " +tableName);
//    if(!sqlQuery.exec())
//    {
//        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
//    }
//    else
//    {
//        while(sqlQuery.next())
//        {
//            int id = sqlQuery.value(0).toInt();
//            QString mark = sqlQuery.value(1).toString();
//            int data = sqlQuery.value(2).toInt();
//            qDebug()<<QString("Bid:%1    mark:%2    data:%3").arg(id).arg(mark).arg(data);
//        }
//    }
//}

// 查询指定行数据
//DATA_BASE3 data_Thread::query_oneTable(QString tableName,QString data_time)
//{
//    DATA_BASE3 db_search;
//    QSqlQuery sqlQuery(thread_data_base);
//    sqlQuery.exec(QString("SELECT * FROM " +tableName+ " WHERE mark > %1").arg(data_time));
//    if(!sqlQuery.exec())
//    {
//        qDebug() << "Error: Fail to query table. " << sqlQuery.lastError();
//    }
//    else
//    {
//        while(sqlQuery.next())
//        {
//            db_search.id = sqlQuery.value(0).toInt();
//            db_search.mark = sqlQuery.value(1).toString();
//            db_search.data = sqlQuery.value(2).toInt();
//            qDebug()<<db_search.id<<db_search.mark<<db_search.data;
//        }
//    }
//    return db_search;
//}

// 插入单条数据
//void data_Thread::singleInsertData(QString table_name, DATA_BASE3 &singledb)
//{
//    QSqlQuery sqlQuery(thread_data_base);
//    sqlQuery.prepare("INSERT INTO " + table_name + " VALUES(:id,:mark,:data)");
//    //sqlQuery.bindValue(":id", singledb.id);
//    sqlQuery.bindValue(":mark", singledb.mark);
//    sqlQuery.bindValue(":data", singledb.data);
//    if(!sqlQuery.exec())
//    {
//        qDebug() << "Error: Fail to insert data. " << sqlQuery.lastError();
//    }
//    else
//    {
//        // do something
//    }
//}

// 插入多条数据
//void data_Thread::moreInsertData(QString tableName,QList<DATA_BASE3>& moredb)
//{
//    // 进行多个数据的插入时，可以利用绑定进行批处理
//    QSqlQuery sqlQuery(thread_data_base);
//    sqlQuery.prepare("INSERT INTO " + tableName + " VALUES(?,?,?)");
//    QVariantList idList,markList,dataList;
//    for(int i=0; i< moredb.size(); i++)
//    {
//        idList <<  moredb.at(i).id;
//        markList << moredb.at(i).mark;
//        dataList << moredb.at(i).data;
//    }
//    sqlQuery.addBindValue(idList);
//    sqlQuery.addBindValue(markList);
//    sqlQuery.addBindValue(dataList);

//    if (!sqlQuery.execBatch()) // 进行批处理，如果出错就输出错误
//    {
//        qDebug() << sqlQuery.lastError();
//    }
//}

// 修改数据
//void data_Thread::modifyData(QString tableName,DATA_BASE3 db)
//{
//    QSqlQuery sqlQuery(thread_data_base);
//    sqlQuery.prepare("UPDATE " + tableName + " SET mark=?,data=? WHERE id=?");
//    sqlQuery.addBindValue(db.mark);
//    sqlQuery.addBindValue(db.data);
//    sqlQuery.addBindValue(db.id);
//    if(!sqlQuery.exec())
//    {
//        qDebug() << sqlQuery.lastError();
//    }
//    else
//    {
//        qDebug() << "updated data success!";
//    }
//}

// 删除数据
//void data_Thread::deleteData(QString tableName,int id)
//{
//    QSqlQuery sqlQuery(thread_data_base);

//    sqlQuery.exec(QString("DELETE FROM " +tableName+ " WHERE id = %1").arg(id));
//    if(!sqlQuery.exec())
//    {
//        qDebug()<<sqlQuery.lastError();
//    }
//    else
//    {
//        qDebug()<<"deleted data success!";
//    }
//}

//删除数据表
//void data_Thread::deleteTable(QString tableName)
//{
//    QSqlQuery sqlQuery(thread_data_base);

//    sqlQuery.exec(QString("DROP TABLE %1").arg(tableName));
//    if(sqlQuery.exec())
//    {
//        qDebug() << sqlQuery.lastError();
//    }
//    else
//    {
//        qDebug() << "deleted table success";
//    }
//}
