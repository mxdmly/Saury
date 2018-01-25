#include <QtCore>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <windows.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QByteArray>
#include <QSqlError>
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>

class Salt : public QThread
{
public:
    Salt();
    ~Salt();
    void run();
    void iniDB();
    QString getDateTime();
    QString getTime();
    void sendDataTABLEUPLOAD();//发送首页数据
    void sendDataTABLEZ();//发送诊断信息
    void sendDataTABLES();//发送手术
    void sendDataTABLEB();//发送BB信息
    void writeLog(QString str);

    bool ifRun_b;

    QSqlDatabase dbEtoneS_qdb;
    QSqlQuery *qEtone_sqs;
    QSqlQuery *qIntoEtone_sqs;
};
