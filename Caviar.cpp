#include "Caviar.h"
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTextStream>
#include <QFile>

QMutex qlock;
QDateTime upTime;
QDateTime thisTime;
QString cxBAS_str;
QString crEtonetheS_str;
QString crEtone_str;
QString descTOP_str;
int all_i = 0;
int get_i = 0;
QString log_str;

Caviar::Caviar()
{
    ifRun_b = true;
    upTime = QDateTime(QDate::currentDate().addDays(1), QTime(1, 0, 0, 0));
    cxBAS_qsq = NULL;
    crEtone_qsq = NULL;
    dbBAS_qdb = QSqlDatabase();
    dbEtone_qdb = QSqlDatabase();
}

Caviar::~Caviar()
{
    try
    {
        if(cxBAS_qsq != NULL)
        {
            cxBAS_qsq->clear();
            delete cxBAS_qsq;
            cxBAS_qsq = NULL;
        }
        if(crEtone_qsq != NULL)
        {
            crEtone_qsq->clear();
            delete crEtone_qsq;
            crEtone_qsq = NULL;
        }
        if(dbBAS_qdb.isOpen())dbBAS_qdb.close();
        if(dbEtone_qdb.isOpen())dbEtone_qdb.close();
    }catch(const std::exception&){
        ;
    }
}

void Caviar::run()
{
    QMutexLocker qmlock(&qlock);
    while (ifRun_b) {
        qmlock.relock();

        thisTime = QDateTime::currentDateTime();//get this time
        if(upTime.operator <=(thisTime))//if thisTime >= upTime
        {
            upTime = upTime.addDays(1);
//------------------------------------------------------------------------------------------
            iniDB();
            cxBAS_qsq = new QSqlQuery(dbBAS_qdb);
            crEtone_qsq = new QSqlQuery(dbEtone_qdb);
            qDebug() << QDateTime::currentDateTime();
            qDebug() << "==============================================";
            log_str = "";
            log_str.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd")).append("\n");
            log_str.append("==============================================").append("\n");
            qDebug() << "GetData";
            log_str.append("GetData").append("\n");
            get_i = 0;
            getDataTABLEUPLOAD();
            qDebug() << "--------HH" << "\t" << all_i << "\t" << get_i;
            log_str.append("--------HH").append("\t").append(QString::number(all_i, 10)).append("\t").append(QString::number(get_i, 10)).append("\n");
            sleep(1);
            get_i = 0;
            getDataTABLEZ();
            qDebug() << "--------ZD" << "\t" << all_i << "\t" << get_i;
            log_str.append("--------ZD").append("\t").append(QString::number(all_i, 10)).append("\t").append(QString::number(get_i, 10)).append("\n");
            get_i = 0;
            getDataTABLES();
            qDebug() << "--------SS" << "\t" << all_i << "\t" << get_i;
            log_str.append("--------SS").append("\t").append(QString::number(all_i, 10)).append("\t").append(QString::number(get_i, 10)).append("\n");
            get_i = 0;
            getDataTABLEB();
            qDebug() << "------BABY" << "\t" << all_i << "\t" << get_i;
            log_str.append("------BABY").append("\t").append(QString::number(all_i, 10)).append("\t").append(QString::number(get_i, 10)).append("\n");
//------------------------------------------------------------------------------------------
            log_str.append("+1 Day").append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            writeLog(log_str);
            cxBAS_qsq->clear();
            delete cxBAS_qsq;
            cxBAS_qsq = NULL;
            crEtone_qsq->clear();
            delete crEtone_qsq;
            crEtone_qsq = NULL;
            dbBAS_qdb.close();
            dbEtone_qdb.close();
            qmlock.unlock();
            sleep(86000);
        }
        qmlock.unlock();
        msleep(2000);
    }
}

void Caviar::getDataTABLEUPLOAD()
{
    crEtone_qsq->exec("SELECT TOP 1 TABLEUPLOAD.FID_TPATIENTVISIT FROM db_upload.dbo.TABLEUPLOAD ORDER BY TABLEUPLOAD.ID DESC");
    if(crEtone_qsq->next())descTOP_str = crEtone_qsq->value(0).toString();
    cxBAS_str = openSqlFile("C:\\Saury\\qTPATIENTVISIT.sql");
    crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoTABLEUPLOAD_S.sql");
    cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TPATIENTVISIT.FID ASC");

    if(!cxBAS_qsq->exec(cxBAS_str))log_str.append(cxBAS_qsq->lastError().text());//to TABLEUPLOAD
    all_i = cxBAS_qsq->numRowsAffected();
    while (cxBAS_qsq->next()) {
        crEtone_str = "DECLARE @name VARCHAR(20) DECLARE @cyt VARCHAR(20) SET @name = ";
        crEtone_str.append("\'");
        crEtone_str.append(cxBAS_qsq->value(7).toString()).append("\'");
        crEtone_str.append(" SET @cyt = ").append("\'");
        crEtone_str.append(cxBAS_qsq->value(33).toString()).append("\'").append(" ");
        crEtone_str.append(crEtonetheS_str);
        crEtone_str.append("\'").append(cxBAS_qsq->value(0).toString()).append("\'");
        crEtone_str.append(",@id, @zy, LEFT(@qh, 6),").append("\'").append("01").append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(2).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(3).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(4).toString()).append("\'");
        crEtone_str.append(",").append("@zy");//抛弃5空的原号，复制就诊流水号
        crEtone_str.append(",REPLACE(\'").append(cxBAS_qsq->value(6).toString()).append("\', \'Y\', \'\')");
        for (int i = 7; i < 146; ++i) {
            crEtone_str.append(",\'").append(cxBAS_qsq->value(i).toString()).append("\'");
        }
        crEtone_str.append(",@cbd,@cbx,@cby)");
        if(crEtone_qsq->exec(crEtone_str))get_i += crEtone_qsq->numRowsAffected();
    }
    if(all_i != get_i)log_str.append("Error" + all_i + get_i);
}

void Caviar::getDataTABLEZ()
{
    crEtone_qsq->exec("SELECT TOP 1 TABLEZ.ZID FROM db_upload.dbo.TABLEZ ORDER BY TABLEZ.ID DESC");
    if(crEtone_qsq->next())descTOP_str = crEtone_qsq->value(0).toString();
    cxBAS_str = openSqlFile("C:\\Saury\\qZ.sql");
    crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoZ.sql");
    cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TDIAGNOSE.FID ASC");
    if(!cxBAS_qsq->exec(cxBAS_str))log_str.append(cxBAS_qsq->lastError().text());//to Z
    all_i = cxBAS_qsq->numRowsAffected();
    while (cxBAS_qsq->next()) {
        crEtone_str = "DECLARE @bah VARCHAR(20) DECLARE @cs VARCHAR(20) SET @bah = \'";
        crEtone_str.append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(" SET @cs = \'").append(cxBAS_qsq->value(2).toString()).append("\'").append(" ");
        crEtone_str.append(crEtonetheS_str);
        crEtone_str.append("\'").append(cxBAS_qsq->value(0).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(2).toString()).append("\'");
        crEtone_str.append(",@zy,@qh,@tp,@sfz");
        for (int i = 3; i < 9; ++i) {
            crEtone_str.append(",\'").append(cxBAS_qsq->value(i).toString()).append("\'");
        }
        crEtone_str.append(")");
        if(crEtone_qsq->exec(crEtone_str))get_i += crEtone_qsq->numRowsAffected();
    }
    if(all_i != get_i)log_str.append("Error" + all_i + get_i);
}

void Caviar::getDataTABLES()
{
    crEtone_qsq->exec("SELECT TOP 1 TABLES.SID FROM db_upload.dbo.TABLES ORDER BY TABLES.ID DESC");
    if(crEtone_qsq->next())descTOP_str = crEtone_qsq->value(0).toString();
    cxBAS_str = openSqlFile("C:\\Saury\\qS.sql");
    crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoS.sql");
    cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TOPERATION.FID ASC");
    if(!cxBAS_qsq->exec(cxBAS_str))log_str.append(cxBAS_qsq->lastError().text());//to S
    all_i =  cxBAS_qsq->numRowsAffected();
    while (cxBAS_qsq->next()) {
        crEtone_str = "DECLARE @bah VARCHAR(20) DECLARE @cs VARCHAR(20) SET @bah = \'";
        crEtone_str.append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(" SET @cs = \'").append(cxBAS_qsq->value(2).toString()).append("\'").append(" ");
        crEtone_str.append(crEtonetheS_str);
        crEtone_str.append("\'").append(cxBAS_qsq->value(0).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(2).toString()).append("\'");
        crEtone_str.append(",@zy,@qh,@tp,@sfz");
        for (int i = 3; i < 26; ++i) {
            crEtone_str.append(",\'").append(cxBAS_qsq->value(i).toString()).append("\'");
        }
        crEtone_str.append(")");
        if(crEtone_qsq->exec(crEtone_str))get_i += crEtone_qsq->numRowsAffected();
    }
    if(all_i != get_i)log_str.append("Error" + all_i + get_i);
}

void Caviar::getDataTABLEB()
{
    crEtone_qsq->exec("SELECT TOP 1 TABLEBABY.BID FROM db_upload.dbo.TABLEBABY ORDER BY TABLEBABY.ID DESC");
    if(crEtone_qsq->next())descTOP_str = crEtone_qsq->value(0).toString();
    cxBAS_str = openSqlFile("C:\\Saury\\qB.sql");
    crEtonetheS_str = openSqlFile("C:\\Saury\\qIntoB.sql");
    cxBAS_str.append("> ").append(descTOP_str).append(" ORDER BY TBABYCARD.FID ASC");
    if(!cxBAS_qsq->exec(cxBAS_str))log_str.append(cxBAS_qsq->lastError().text());//to B
    all_i =  cxBAS_qsq->numRowsAffected();
    while (cxBAS_qsq->next()) {
        crEtone_str = "DECLARE @bah VARCHAR(20) DECLARE @cs VARCHAR(20) SET @bah = \'";
        crEtone_str.append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(" SET @cs = \'").append(cxBAS_qsq->value(2).toString()).append("\'").append(" ");
        crEtone_str.append(crEtonetheS_str);
        crEtone_str.append("\'").append(cxBAS_qsq->value(0).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(1).toString()).append("\'");
        crEtone_str.append(",\'").append(cxBAS_qsq->value(2).toString()).append("\'");
        crEtone_str.append(",@zy,@qh,@tp,@sfz");
        for (int i = 3; i < 14; ++i) {
            crEtone_str.append(",\'").append(cxBAS_qsq->value(i).toString()).append("\'");
        }
        crEtone_str.append(")");
        if(crEtone_qsq->exec(crEtone_str))get_i += crEtone_qsq->numRowsAffected();
    }
    if(all_i != get_i)log_str.append("Error" + all_i + get_i);
}

void Caviar::iniDB()
{
    if(!dbBAS_qdb.isValid())
    {
        dbBAS_qdb = QSqlDatabase::addDatabase("QODBC", "dbBAS");
        dbBAS_qdb.setDatabaseName("dbBAS");//数据连接名，在控制面板设置
        dbBAS_qdb.setUserName("YBB");
        dbBAS_qdb.setPassword("0");
    }
    if(!dbEtone_qdb.isValid())
    {
        dbEtone_qdb = QSqlDatabase::addDatabase("QODBC", "dbCaviar");
        dbEtone_qdb.setDatabaseName("dbCaviar");//数据连接名，在控制面板设置
        dbEtone_qdb.setUserName("YBB");
        dbEtone_qdb.setPassword("0");
    }

    if(!dbBAS_qdb.open())
    {
        writeLog(dbBAS_qdb.lastError().text());
        qDebug() << "BAS Error" << dbBAS_qdb.lastError().text();
    }
    if(!dbEtone_qdb.open())
    {
        writeLog(dbEtone_qdb.lastError().text());
        qDebug() << "ET Error" << dbEtone_qdb.lastError().text();
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

void Caviar::writeLog(QString str)
{
    QFile f("C:\\Saury\\out.log");
    f.open(QIODevice::Text | QIODevice::Append);
    QTextStream textStream(&f);
    textStream << str << endl;
    f.close();
}
