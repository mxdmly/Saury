#include "Salt.h"
#include <QDebug>

Salt::Salt()
{
    ifRun_b = true;

}

Salt::~Salt()
{
    ;
}

void Salt::run()
{

    while (ifRun_b) {
        qDebug() << "salt";

        msleep(2000);
    }
}

void Salt::iniDB()
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
