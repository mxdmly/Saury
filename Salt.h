#include <QThread>
#include <QDebug>
#include <iostream>
#include <windows.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QByteArray>
#include <QSqlError>

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

    bool ifRun_b;

    QSqlDatabase dbEtone_qdb;
    QSqlQuery qEtone_sqs;
    QSqlQuery qIntoEtone_sqs;
};
