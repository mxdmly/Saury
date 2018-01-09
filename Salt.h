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

    bool ifRun_b;

    QSqlDatabase dbBAS_qdb;
    QSqlDatabase dbEtone_qdb;
};
