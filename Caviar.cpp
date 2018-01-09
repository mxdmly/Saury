#include "Caviar.h"
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTextStream>
#include <QFile>

QDateTime upTime = QDateTime(QDate(2018, 1, 9), QTime(16, 36, 0, 0));
QDateTime thisTime;
QString cxBAS_str;
QString xrBAS_str;

Caviar::Caviar()
{
    ifRun_b = true;
}

Caviar::~Caviar()
{
    dbBAS_qdb.close();
    dbEtone_qdb.close();
}

void Caviar::run()
{
    while (ifRun_b) {
        qDebug() << "caviar";

        iniDB();
        cxBAS_str = openSqlFile("C:\\Saury\\qTPATIENTVISIT.sql");
        xrBAS_str = openSqlFile("C:\\Saury\\qIntoTABLEUPLOAD.sql");
        cxBAS_str.append("2769191").append("\'");

        cxBAS_qsq = QSqlQuery(dbBAS_qdb);
        xrBAS_qsq = QSqlQuery(dbEtone_qdb);

        cxBAS_qsq.exec(cxBAS_str);

        while (cxBAS_qsq.next()) {
            for (int i = 0; i < 150; ++i) {
                xrBAS_str.append(cxBAS_qsq.value(i).toString());
            }
            xrBAS_qsq.exec(xrBAS_str);
        }

        thisTime = QDateTime::currentDateTime();//get this time

        if(upTime.operator <=(thisTime))//if thisTime >= upTime
        {
            qDebug() << "+1 Day";
            upTime = upTime.addDays(1);
            sleep(86400);
        }

        qDebug() << upTime.toString("yyyy-MM-dd hh:mm:ss");

        msleep(2000);
    }
}

void Caviar::iniDB()
{
    dbBAS_qdb = QSqlDatabase::addDatabase("QODBC", "dbBAS");
    dbBAS_qdb.setDatabaseName("dbBAS");//数据连接名，在控制面板设置
    dbBAS_qdb.setUserName("william");
    dbBAS_qdb.setPassword("");

    dbEtone_qdb = QSqlDatabase::addDatabase("QODBC", "dbEtone");
    dbEtone_qdb.setDatabaseName("dbEtone");//数据连接名，在控制面板设置
    dbEtone_qdb.setUserName("sa");
    dbEtone_qdb.setPassword("sa123!@#");

    if(!dbBAS_qdb.open())
    {
        qDebug() << dbBAS_qdb.lastError();
    }
    if(!dbEtone_qdb.open())
    {
        qDebug() << dbEtone_qdb.lastError();
    }
}

QString Caviar::openSqlFile(QString str)//打开sql文件读取文本内容
{
    QString query_str;
    QFile file(str);//打开这个文件
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open sql file Error";
    }
    else
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            query_str.append(line);
        }
        if(query_str == NULL)qDebug() << "sql query is NULL";
    }
    return query_str;
}
