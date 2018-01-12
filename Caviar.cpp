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
QString crEtonetheS_str;
QString crEtone_str;

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

        crEtone_qsq.exec("SELECT TOP 1 TT.FID_TPATIENTVISIT FROM db_upload.dbo.TT ORDER BY TT.ID DESC");
        if(crEtone_qsq.next())descTOP_str = crEtone_qsq.value(0).toString();

        cxBAS_str = openSqlFile("C:\\Saury\\qTPATIENTVISIT.sql");
        crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoTABLEUPLOAD_S.sql");
        cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY dbo.TPATIENTVISIT.FID ASC");

        cxBAS_qsq.exec(cxBAS_str);//to TABLEUPLOAD
        int ii = 1;
        qDebug() << cxBAS_qsq.numRowsAffected();
        while (cxBAS_qsq.next()) {
            crEtone_str = "DECLARE @name VARCHAR(20) DECLARE @cyt VARCHAR(20) SET @name = ";
            crEtone_str.append("\'");
            crEtone_str.append(cxBAS_qsq.value(7).toString()).append("\'");
            crEtone_str.append(" SET @cyt = ").append("\'");
            crEtone_str.append(cxBAS_qsq.value(33).toString()).append("\'").append(" ");
            crEtone_str.append(crEtonetheS_str);
            crEtone_str.append("\'").append(cxBAS_qsq.value(0).toString()).append("\'");
            crEtone_str.append(",@id, @zy, LEFT(@qh, 6),").append("\'").append("01").append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(1).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(2).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(3).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(4).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(5).toString()).append("\'");
            crEtone_str.append(",REPLACE(\'").append(cxBAS_qsq.value(6).toString()).append("\', \'Y\', \'\')");
            for (int i = 7; i < 146; ++i) {
                crEtone_str.append(",\'").append(cxBAS_qsq.value(i).toString()).append("\'");
            }
            crEtone_str.append(",@cbd,@cbx,@cby)");
            crEtone_qsq.exec(crEtone_str);
            qDebug() << ii;ii++;
        }

        crEtone_qsq.exec("SELECT TOP 1 ZZ.ZID FROM db_upload.dbo.ZZ ORDER BY ZZ.ID DESC");
        if(crEtone_qsq.next())descTOP_str = crEtone_qsq.value(0).toString();
        cxBAS_str = openSqlFile("C:\\Saury\\qZ.sql");
        crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoZ.sql");
        cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TDIAGNOSE.FID ASC");
        cxBAS_qsq.exec(cxBAS_str);//to Z
        ii = 1;
        qDebug() << cxBAS_qsq.numRowsAffected();
        while (cxBAS_qsq.next()) {
            crEtone_str = "DECLARE @bah VARCHAR(20) DECLARE @cs VARCHAR(20) SET @bah = \'";
            crEtone_str.append(cxBAS_qsq.value(1).toString()).append("\'");
            crEtone_str.append(" SET @cs = \'").append(cxBAS_qsq.value(2).toString()).append("\'").append(" ");
            crEtone_str.append(crEtonetheS_str);
            crEtone_str.append("\'").append(cxBAS_qsq.value(0).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(1).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(2).toString()).append("\'");
            crEtone_str.append(",@zy,@qh,@tp,@sfz");
            for (int i = 3; i < 9; ++i) {
                crEtone_str.append(",\'").append(cxBAS_qsq.value(i).toString()).append("\'");
            }
            crEtone_str.append(")");
            crEtone_qsq.exec(crEtone_str);

            qDebug() << ii;ii++;
        }

        crEtone_qsq.exec("SELECT TOP 1 SS.SID FROM db_upload.dbo.SS ORDER BY SS.ID DESC");
        if(crEtone_qsq.next())descTOP_str = crEtone_qsq.value(0).toString();
        cxBAS_str = openSqlFile("C:\\Saury\\qS.sql");
        crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoS.sql");
        cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TOPERATION.FID ASC");
        cxBAS_qsq.exec(cxBAS_str);//to S
        ii = 1;
        qDebug() << cxBAS_qsq.numRowsAffected();
        while (cxBAS_qsq.next()) {
            crEtone_str = "DECLARE @bah VARCHAR(20) DECLARE @cs VARCHAR(20) SET @bah = \'";
            crEtone_str.append(cxBAS_qsq.value(1).toString()).append("\'");
            crEtone_str.append(" SET @cs = \'").append(cxBAS_qsq.value(2).toString()).append("\'").append(" ");
            crEtone_str.append(crEtonetheS_str);
            crEtone_str.append("\'").append(cxBAS_qsq.value(0).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(1).toString()).append("\'");
            crEtone_str.append(",\'").append(cxBAS_qsq.value(2).toString()).append("\'");
            crEtone_str.append(",@zy,@qh,@tp,@sfz");
            for (int i = 3; i < 26; ++i) {
                crEtone_str.append(",\'").append(cxBAS_qsq.value(i).toString()).append("\'");
            }
            crEtone_str.append(")");
            crEtone_qsq.exec(crEtone_str);

            qDebug() << ii;ii++;
        }


        QFile f("C:\\Saury\\out.log");
        f.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream textStream(&f);
        textStream << crEtonetheS_str << endl << endl;


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
