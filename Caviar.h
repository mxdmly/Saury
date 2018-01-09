#include <QThread>
#include <QDebug>
#include <iostream>
#include <windows.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QByteArray>
#include <QSqlError>

class Caviar : public QThread
{
public:
    Caviar();
    ~Caviar();
    void run();
    void iniDB();
    QString openSqlFile(QString str);

    bool ifRun_b;

    QSqlDatabase dbBAS_qdb;
    QSqlDatabase dbEtone_qdb;

    QSqlQuery cxBAS_qsq;
    QSqlQuery xrBAS_qsq;
};

