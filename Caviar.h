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
#include <QMutex>
#include <QMutexLocker>

class Caviar : public QThread
{
public:
    Caviar();
    ~Caviar();
    void run();
    void iniDB();
    void getDataTABLEUPLOAD();
    void getDataTABLES();
    void getDataTABLEZ();
    void getDataTABLEB();
    QString openSqlFile(QString str);
    void writeLog(QString str);

    bool ifRun_b;

    QSqlDatabase dbBAS_qdb;
    QSqlDatabase dbEtone_qdb;

    QSqlQuery *cxBAS_qsq;
    QSqlQuery *crEtone_qsq;
};

