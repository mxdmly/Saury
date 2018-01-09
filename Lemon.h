#include <QDebug>
#include <iostream>
#include <windows.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QByteArray>
#include <QSqlError>
#include <QString>

class Lemon
{
public:
    Lemon();
    ~Lemon();
    void ini();
    int Sign();

    QString getTime();

    HINSTANCE hDLL;
    typedef int(*re_i_p)(char* inData, char* outData);
    re_i_p BUSINESS_HANDLE;
    QString myNOBER_str;
    QString ywNOBER_str;
};
