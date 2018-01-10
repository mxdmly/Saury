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
QString crBAStheS_str;
QString crBAS_str;

QString descTOP_str;

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
    iniDB();
    cxBAS_qsq = QSqlQuery(dbBAS_qdb);
    crEtone_qsq = QSqlQuery(dbEtone_qdb);

    while (ifRun_b) {
        qDebug() << "caviar";
/*
        crEtone_qsq.exec("SELECT TOP 1 TT.FID_TPATIENTVISIT FROM db_upload.dbo.TT ORDER BY TT.ID DESC");
        if(crEtone_qsq.next())descTOP_str = crEtone_qsq.value(0).toString();

        cxBAS_str = openSqlFile("C:\\Saury\\qTPATIENTVISIT.sql");
        crBAStheS_str = openSqlFile("C:\\Saury\\qIntoTABLEUPLOAD_S.sql");
        //cxBAS_str.append("= ").append("2784075").append(" ORDER BY dbo.TPATIENTVISIT.FID ASC");
        cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY dbo.TPATIENTVISIT.FID ASC");

        cxBAS_qsq.exec(cxBAS_str);//to TABLEUPLOAD
        qDebug() << cxBAS_qsq.numRowsAffected();
        int ii = 1;
        while (cxBAS_qsq.next()) {
            crBAS_str = "DECLARE @bah VARCHAR(20) DECLARE @cyt VARCHAR(20) SET @bah = ";
            crBAS_str.append("\'");
            crBAS_str.append(cxBAS_qsq.value(2).toString()).append("\'");
            crBAS_str.append(" SET @cyt = ").append("\'");
            crBAS_str.append(cxBAS_qsq.value(33).toString()).append("\'").append(" ");
            crBAS_str.append(crBAStheS_str);
            crBAS_str.append("\'").append(cxBAS_qsq.value(0).toString()).append("\'");
            crBAS_str.append(",@id, @zy, LEFT(@qh, 6),").append("\'").append("01").append("\'");
            crBAS_str.append(",\'").append(cxBAS_qsq.value(1).toString()).append("\'");
            crBAS_str.append(",\'").append(cxBAS_qsq.value(2).toString()).append("\'");
            crBAS_str.append(",\'").append(cxBAS_qsq.value(3).toString()).append("\'");
            crBAS_str.append(",\'").append(cxBAS_qsq.value(4).toString()).append("\'");
            crBAS_str.append(",\'").append(cxBAS_qsq.value(5).toString()).append("\'");
            crBAS_str.append(",REPLACE(\'").append(cxBAS_qsq.value(6).toString()).append("\', \'Y\', \'\')");
            for (int i = 7; i < 146; ++i) {
                crBAS_str.append(",").append("\'").append(cxBAS_qsq.value(i).toString()).append("\'");
            }
            crBAS_str.append(")");
            crEtone_qsq.exec(crBAS_str);
            qDebug() << ii;ii++;
        }
/*
        QFile f("C:\\Saury\\out.log");
        f.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream textStream(&f);
        textStream << crBAS_str << endl;*/

        crEtone_qsq.exec("SELECT TOP 1 ZZ.ZID FROM db_upload.dbo.ZZ ORDER BY ZZ.ID DESC");
        if(crEtone_qsq.next())descTOP_str = crEtone_qsq.value(0).toString();
        cxBAS_str = openSqlFile("C:\\Saury\\qZ.sql");
        cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TDIAGNOSE.FID ASC");
        cxBAS_qsq.exec(cxBAS_str);//to Z
        int ii = 1;
        while (cxBAS_qsq.next()) {
            crBAS_str = "";
            crEtone_qsq.exec(crBAS_str);

            qDebug() << ii;ii++;
        }


        thisTime = QDateTime::currentDateTime();//get this time

        if(upTime.operator <=(thisTime))//if thisTime >= upTime
        {
            qDebug() << "+1 Day";
            upTime = upTime.addDays(1);


            cxBAS_qsq.clear();
            crEtone_qsq.clear();
            dbBAS_qdb.close();
            dbEtone_qdb.close();
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
        qDebug() << "BAS Error" << dbBAS_qdb.lastError();
    }
    if(!dbEtone_qdb.open())
    {
        qDebug() << "ET Error" << dbEtone_qdb.lastError();
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
