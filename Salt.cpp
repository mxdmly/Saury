#include "Salt.h"
#include <lemon.h>

using namespace std;

extern QMutex qlock;
QDateTime supTime;
QDateTime sthisTime;
Lemon *lemon;
QString sendDate_str;
int s_ii;
int isUpdate;
QString setJylsh_str;//就诊流水号
QString whereID_str;
int sall_i = 0;
int sget_i = 0;
QString sLog_str;

Salt::Salt()
{
    ifRun_b = true;
    supTime = QDateTime(QDate::currentDate().addDays(1), QTime(1, 30, 0, 0));
    dbEtoneS_qdb = QSqlDatabase();
    qEtone_sqs = NULL;
    qIntoEtone_sqs = NULL;
    lemon = NULL;
}

Salt::~Salt()
{
    try
    {
        if(qEtone_sqs != NULL)
        {
            qEtone_sqs->clear();
            delete qEtone_sqs;
            qEtone_sqs = NULL;
        }
        if(qIntoEtone_sqs != NULL)
        {
            qIntoEtone_sqs->clear();
            delete qIntoEtone_sqs;
            qIntoEtone_sqs = NULL;
        }
        if(dbEtoneS_qdb.isOpen())dbEtoneS_qdb.close();
        delete lemon;
        lemon = NULL;
    }
    catch (QString str)
    {
        qDebug() << str;
    }
}

void Salt::run()
{
    QMutexLocker qmlock(&qlock);
    //qDebug() << lemon;
    lemon = new Lemon();
    //qDebug() << lemon;

    while (ifRun_b) {
        qmlock.relock();

        sthisTime = QDateTime::currentDateTime();//get this time
        if(supTime.operator <=(sthisTime))//if sthisTime >= supTime
        {
            supTime = supTime.addDays(1);
//------------------------------------------------------------------------------------------
            iniDB();
            qEtone_sqs = new QSqlQuery(dbEtoneS_qdb);
            qIntoEtone_sqs = new QSqlQuery(dbEtoneS_qdb);
            if(lemon->Sign() == 0)
            {
                sLog_str = "";
                qDebug() << "---------------------------------------------";
                sLog_str.append("---------------------------------------------").append("\n");
                qDebug() << "UpLoad";
                sLog_str.append("UpLoad").append("\n");
                sget_i = 0;
                sendDataTABLEUPLOAD();
                qDebug() << "--------HH" << "\t" << sall_i << "\t" << sget_i;
                sLog_str.append("--------HH").append("\t").append(QString::number(sall_i, 10)).append("\t").append(QString::number(sget_i, 10)).append("\n");
                sget_i = 0;
                sendDataTABLEZ();
                qDebug() << "--------ZD" << "\t" << sall_i << "\t" << sget_i;
                sLog_str.append("--------ZD").append("\t").append(QString::number(sall_i, 10)).append("\t").append(QString::number(sget_i, 10)).append("\n");
                sget_i = 0;
                sendDataTABLES();
                qDebug() << "--------SS" << "\t" << sall_i << "\t" << sget_i;
                sLog_str.append("--------SS").append("\t").append(QString::number(sall_i, 10)).append("\t").append(QString::number(sget_i, 10)).append("\n");
                sget_i = 0;
                sendDataTABLEB();
                qDebug() << "------BABY" << "\t" << sall_i << "\t" << sget_i;
                sLog_str.append("------BABY").append("\t").append(QString::number(sall_i, 10)).append("\t").append(QString::number(sget_i, 10)).append("\n");
    //------------------------------------------------------------------------------------------
                qDebug() << "==============================================";
                sLog_str.append("+1 Day").append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).append("\n");
                sLog_str.append("==============================================").append("\n\n");
                writeLog(sLog_str);

                lemon->SignOut();
            }
            else
            {
                writeLog(lemon->outData_ch);//写入失败结果
            }
            qEtone_sqs->clear();
            delete qEtone_sqs;
            qEtone_sqs = NULL;
            qIntoEtone_sqs->clear();
            delete qIntoEtone_sqs;
            qIntoEtone_sqs = NULL;
            dbEtoneS_qdb.close();
            qmlock.unlock();
            sleep(86000);
        }
        qmlock.unlock();
        msleep(2000);
    }
}

void Salt::sendDataTABLEUPLOAD()//首页上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM db_upload.dbo.TABLEUPLOAD WHERE TABLEUPLOAD.ISUPLOAD <> 0 AND TABLEUPLOAD.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs->exec(sendDate_str);
    sall_i = qEtone_sqs->numRowsAffected();

    //上传到社保局
    s_ii = 1000;
    while (qEtone_sqs->next()) {
        sendDate_str = "3710^100007^";
        sendDate_str.append(lemon->myNum_str).append(lemon->bcNum_str).append("^");
        setJylsh_str = QString("").append(getTime()).append("-100007-").append(QString::number(s_ii, 10));//保留上传的流水号，不知道有啥用
        sendDate_str.append(setJylsh_str).append("^441200^");
        for (int i = 4; i < 178; ++i) {
            sendDate_str.append(qEtone_sqs->value(i).toString()).append("|");
        }
        sendDate_str.append("^1^");
        isUpdate = lemon->sendData(sendDate_str);

        //qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.TABLEUPLOAD SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",JYLSH = \'").append(setJylsh_str).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon->outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID = \'").append(qEtone_sqs->value(0).toString()).append("\'");
        qIntoEtone_sqs->exec(sendDate_str);
        s_ii++;
        if(isUpdate == 0)sget_i++;
    }
}

void Salt::sendDataTABLEZ()//诊断上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM db_upload.dbo.TABLEZ WHERE TABLEZ.ZZDLX = '1' AND TABLEZ.ISUPLOAD <> 0 AND TABLEZ.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs->exec(sendDate_str);
    sall_i = qEtone_sqs->numRowsAffected();

    //上传到社保局
    s_ii = 1000;
    while (qEtone_sqs->next()) {
        sendDate_str = "3720^100007^";
        sendDate_str.append(lemon->myNum_str).append(lemon->bcNum_str).append("^");
        setJylsh_str = QString("").append(getTime()).append("-100007-").append(QString::number(s_ii, 10));//保留上传的流水号，不知道有啥用
        sendDate_str.append(setJylsh_str).append("^441200^");
        for (int i = 5; i < 17; ++i) {
            sendDate_str.append(qEtone_sqs->value(i).toString()).append("|");
        }
        whereID_str = qEtone_sqs->value(0).toString().append("\'");
        //添加其他诊断，如果有的话
        qIntoEtone_sqs->exec(
                    QString("SELECT * FROM db_upload.dbo.TABLEZ WHERE TABLEZ.ZZDLX <> \'1")
                    .append("\' AND TABLEZ.FPRN = \'")
                    .append(qEtone_sqs->value(3).toString()).append("\'").append(" AND TABLEZ.FTIMES = \'")
                    .append(qEtone_sqs->value(4).toString()).append("\'")
                    );
        if(qIntoEtone_sqs->numRowsAffected() >= 1)
        {
            sendDate_str = sendDate_str.left(sendDate_str.length() -1);//如果有其他诊断，删除最后的字符|换成$
            int px_i = 2;
            while (qIntoEtone_sqs->next()) {
                sendDate_str.append("$").append(QString::number(px_i, 10));
                for (int i = 11; i < 17; ++i) {
                    sendDate_str.append("|").append(qIntoEtone_sqs->value(i).toString());
                }
                //whereID_str.append(",\'").append(qIntoEtone_sqs->value(0).toString()).append("\'");
                px_i++;
            }
            sendDate_str.append("|");
        }
        sendDate_str.append("^1^");
        isUpdate = lemon->sendData(sendDate_str);

        //qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.TABLEZ SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",JYLSH = \'").append(setJylsh_str).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon->outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID IN (\'").append(whereID_str).append(")");
        qIntoEtone_sqs->exec(sendDate_str);

        s_ii++;
        if(isUpdate == 0)sget_i++;
    }
}

void Salt::sendDataTABLES()//手术上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM db_upload.dbo.TABLES WHERE TABLES.SPX = '1' AND TABLES.ISUPLOAD <> 0 AND TABLES.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs->exec(sendDate_str);
    sall_i = qEtone_sqs->numRowsAffected();

    //上传到社保局
    s_ii = 1000;
    while (qEtone_sqs->next()) {
        sendDate_str = "3730^100007^";
        sendDate_str.append(lemon->myNum_str).append(lemon->bcNum_str).append("^");
        setJylsh_str = QString("").append(getTime()).append("-100007-").append(QString::number(s_ii, 10));//保留上传的流水号，不知道有啥用
        sendDate_str.append(setJylsh_str).append("^441200^");
        for (int i = 5; i < 33; ++i) {
            sendDate_str.append(qEtone_sqs->value(i).toString()).append("|");
        }

        whereID_str = qEtone_sqs->value(0).toString().append("\'");
        //添加其他诊断，如果有的话
        qIntoEtone_sqs->exec(
                    QString("SELECT * FROM db_upload.dbo.TABLES WHERE TABLES.SPX <> \'1")
                    .append("\' AND TABLES.FPRN = \'")
                    .append(qEtone_sqs->value(3).toString()).append("\'").append(" AND TABLES.FTIMES = \'")
                    .append(qEtone_sqs->value(4).toString()).append("\'")
                    );
        if(qIntoEtone_sqs->numRowsAffected() >= 1)
        {
            sendDate_str = sendDate_str.left(sendDate_str.length() -1);//如果有其他诊断，删除最后的字符|换成$
            while (qIntoEtone_sqs->next()) {
                sendDate_str.append("$").append(qIntoEtone_sqs->value(9).toString());
                for (int i = 10; i < 33; ++i) {
                    sendDate_str.append("|").append(qIntoEtone_sqs->value(i).toString());
                }
                //whereID_str.append(",\'").append(qIntoEtone_sqs->value(0).toString()).append("\'");
            }
        }
        sendDate_str.append("|");
        sendDate_str.append("^1^");
        isUpdate = lemon->sendData(sendDate_str);

        //qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.TABLES SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",JYLSH = \'").append(setJylsh_str).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon->outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID IN (\'").append(whereID_str).append(")");
        qIntoEtone_sqs->exec(sendDate_str);

        s_ii++;
        if(isUpdate == 0)sget_i++;
    }
}

void Salt::sendDataTABLEB()//BB信息上传
{
    //查询亿通数据
    sendDate_str = "SELECT * FROM db_upload.dbo.TABLEBABY WHERE TABLEBABY.ISUPLOAD <> 0 AND TABLEBABY.InSurVisitId <> \'";
    sendDate_str.append("\'");
    qEtone_sqs->exec(sendDate_str);
    sall_i = qEtone_sqs->numRowsAffected();

    //上传到社保局
    s_ii = 1000;
    while (qEtone_sqs->next()) {
        sendDate_str = "3740^100007^";
        sendDate_str.append(lemon->myNum_str).append(lemon->bcNum_str).append("^");
        setJylsh_str = QString("").append(getTime()).append("-100007-").append(QString::number(s_ii, 10));//保留上传的流水号，不知道有啥用
        sendDate_str.append(setJylsh_str).append("^441200^");
        for (int i = 5; i < 20; ++i) {
            sendDate_str.append(qEtone_sqs->value(i).toString()).append("|");
        }
        sendDate_str.append("^1^");
        isUpdate = lemon->sendData(sendDate_str);

        //qDebug() << sendDate_str << endl;

        //写入结果
        sendDate_str = "UPDATE db_upload.dbo.TABLEBABY SET ISUPLOAD = \'";
        sendDate_str.append(QString::number(isUpdate, 10)).append("\'");
        sendDate_str.append(",JYLSH = \'").append(setJylsh_str).append("\'");
        sendDate_str.append(",RESULT = \'").append(QString::fromLocal8Bit(lemon->outData_ch)).append("\'");
        sendDate_str.append(",UPTIME = \'").append(getDateTime()).append("\'");
        sendDate_str.append(" WHERE ID = \'").append(qEtone_sqs->value(0).toString()).append("\'");
        qIntoEtone_sqs->exec(sendDate_str);

        s_ii++;
        if(isUpdate == 0)sget_i++;
    }
}

void Salt::iniDB()//初始化db，每次使用前调用，用完后关闭
{
    if(!dbEtoneS_qdb.isValid())
    {
        dbEtoneS_qdb = QSqlDatabase::addDatabase("QODBC", "dbSalt");
        dbEtoneS_qdb.setDatabaseName("dbSalt");//数据连接名，在控制面板设置
        dbEtoneS_qdb.setUserName("YBB");
        dbEtoneS_qdb.setPassword("0");
    }

    if(!dbEtoneS_qdb.open())
    {
        writeLog(dbEtoneS_qdb.lastError().text());
        qDebug() << "ET Error" << dbEtoneS_qdb.lastError().text();
    }
}

QString Salt::getDateTime()//这个时间作为上传时间，用于写入结果
{
    QDateTime dateTime;
    QString dateTime_str = dateTime.currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
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

void Salt::writeLog(QString str)
{
    QFile f("C:\\Saury\\out.log");
    f.open(QIODevice::Text | QIODevice::Append);
    QTextStream textStream(&f);
    textStream << str << endl << endl;
    f.close();
}
