#include "Salt.h"
#include <QDebug>
#include <Lemon.h>
#include <QDateTime>
#include <QRegularExpression>

using namespace std;

Lemon lemon;
QString sendDate_str;
int ii;
int isUpdate;

Salt::Salt()
{
    ifRun_b = true;
    lemon = Lemon();
}

Salt::~Salt()
{
    ;
}

void Salt::run()
{
    iniDB();
    qEtone_sqs = QSqlQuery(dbEtone_qdb);
    qIntoEtone_sqs = QSqlQuery(dbEtone_qdb);

    lemon.ini();
    lemon.Sign();

    while (ifRun_b) {
        qDebug() << "salt";

        //sendDataTABLEUPLOAD();
        //sendDataTABLEZ();
        sendDataTABLES();

        //写入log文件
        QFile f("C:\\Saury\\out.log");
        f.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream textStream(&f);
        textStream << sendDate_str << endl;
        qDebug() << sendDate_str << endl;

        msleep(20000);
    }
}

void Salt::iniDB()
{
    dbEtone_qdb = QSqlDatabase::addDatabase("QODBC", "dbEtone");
    dbEtone_qdb.setDatabaseName("dbEtone");//数据连接名，在控制面板设置
    dbEtone_qdb.setUserName("sa");
    dbEtone_qdb.setPassword("sa123!@#");

    if(!dbEtone_qdb.open())
    {
        qDebug() << dbEtone_qdb.lastError();
    }
}

QString Salt::getDateTime()//这个时间作为上传时间，用于写入结果
{
    QDateTime dateTime;
    QString dateTime_str = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return dateTime_str;
}

QString Salt::getTime()//这个时间用于组合QString语句上传
{
    time_t myTime = time(NULL);
    tm *myTm = localtime(&myTime);
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    int yyyy = myTm->tm_year + 1900;
    int mm = myTm->tm_mon + 1;
    int dd = myTm->tm_mday;
    int hh = myTm->tm_hour;
    int min = myTm->tm_min;
    int sec = myTm->tm_sec;
    QString yyyy_str = QString::number(yyyy, 10);
    QString mm_str = QString::number(mm, 10);
    QString dd_str = QString::number(dd, 10);
    QString hh_str = QString::number(hh, 10);
    QString min_str = "";
    if (min < 10)
    {
        min_str = "0" + QString::number(min, 10);
    }
    else
    {
        min_str = QString::number(min, 10);
    }
    QString sec_str = QString::number(sec, 10);
    if (sec < 10)
    {
        sec_str = "0" + QString::number(sec, 10);
    }
    else
    {
        sec_str = QString::number(sec, 10);
    }
    QString inPut_str = yyyy_str + mm_str + dd_str + hh_str + min_str + sec_str;
    return inPut_str;
}

void Salt::sendDataTABLEUPLOAD()//首页上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM dbo.TT WHERE dbo.TT.ISUPLOAD <> 0 AND dbo.TT.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs.exec(sendDate_str);
    qDebug() << qEtone_sqs.numRowsAffected();

    //上传到社保局
    while (qEtone_sqs.next()) {
        ii = 1;
        sendDate_str = "3710^100007^2333";
        QRegularExpression re("\\^[0-9]+-[0-9]+-[0-9]+");
        QRegularExpressionMatch match = re.match(lemon.bcNum_str);
        sendDate_str.append(match.captured(0));
        sendDate_str.append("^");
        sendDate_str.append(getTime());
        sendDate_str.append("-100007-1111^441200^");
        for (int i = 4; i < 178; ++i) {
            sendDate_str.append(qEtone_sqs.value(i).toString()).append("|");
        }
        sendDate_str.append("^1^");
        isUpdate = lemon.sendData(sendDate_str);

        qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.TT SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon.outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID = \'").append(qEtone_sqs.value(0).toString()).append("\'");
        qIntoEtone_sqs.exec(sendDate_str);

        qDebug() << ii;
        ii++;

        msleep(100);
    }
}

void Salt::sendDataTABLEZ()//诊断上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM dbo.ZZ WHERE dbo.ZZ.ISUPLOAD <> 0 AND dbo.ZZ.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs.exec(sendDate_str);
    qDebug() << qEtone_sqs.numRowsAffected();

    //上传到社保局
    while (qEtone_sqs.next()) {
        ii = 1;
        sendDate_str = "3720^100007^2333";
        QRegularExpression re("\\^[0-9]+-[0-9]+-[0-9]+");
        QRegularExpressionMatch match = re.match(lemon.bcNum_str);
        sendDate_str.append(match.captured(0));
        sendDate_str.append("^");
        sendDate_str.append(getTime());
        sendDate_str.append("-100007-1111^441200^");
        for (int i = 5; i < 17; ++i) {
            sendDate_str.append(qEtone_sqs.value(i).toString()).append("|");
        }
        sendDate_str.append("^1^");
        isUpdate = lemon.sendData(sendDate_str);

        qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.ZZ SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon.outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID = \'").append(qEtone_sqs.value(0).toString()).append("\'");
        qIntoEtone_sqs.exec(sendDate_str);

        qDebug() << ii;
        ii++;

        msleep(100);
    }
}

void Salt::sendDataTABLES()//手术上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM dbo.SS WHERE dbo.SS.ISUPLOAD <> 0 AND dbo.SS.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs.exec(sendDate_str);
    qDebug() << qEtone_sqs.numRowsAffected();

    //上传到社保局
    while (qEtone_sqs.next()) {
        ii = 1;
        sendDate_str = "3730^100007^2333";
        QRegularExpression re("\\^[0-9]+-[0-9]+-[0-9]+");
        QRegularExpressionMatch match = re.match(lemon.bcNum_str);
        sendDate_str.append(match.captured(0));
        sendDate_str.append("^");
        sendDate_str.append(getTime());
        sendDate_str.append("-100007-1111^441200^");
        for (int i = 5; i < 33; ++i) {
            sendDate_str.append(qEtone_sqs.value(i).toString()).append("|");
        }
        sendDate_str.append("^1^");
        isUpdate = lemon.sendData(sendDate_str);

        qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.SS SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon.outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID = \'").append(qEtone_sqs.value(0).toString()).append("\'");
        qIntoEtone_sqs.exec(sendDate_str);

        qDebug() << ii;
        ii++;

        msleep(100);
    }
}
