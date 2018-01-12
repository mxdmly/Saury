#include "Lemon.h"
#include <iostream>

using namespace std;

Lemon::Lemon()
{
    ;
}


Lemon::~Lemon()
{
    if (hDLL != NULL)
    {
        try
        {
            FreeLibrary(hDLL);//卸载SiInterface.dll文件；
        }
        catch (const std::exception&)
        {
            ;
        }
    }
}

void Lemon::ini()
{
    myNum_str = "2333";
    BUSINESS_HANDLE = NULL;
    hDLL = LoadLibrary(L"C:\\MyDLL\\SiInterface.dll");
    //初始化社保动态库
    if (hDLL != NULL)
    {
        try
        {
            typedef int(*pTest)(char * a);
            pTest INIT = NULL;
            INIT = (pTest)GetProcAddress(hDLL, "INIT");
            char chFH[100] = "";
            if (INIT(chFH) == 0)
            {
                qDebug() << "ini success";
            }
            else
            {
                QString strError = QString::fromLocal8Bit(chFH, 100);//转为QString输出
                qDebug() << QString(strError);
            }
            //通过了，2333
            BUSINESS_HANDLE = (re_i_p)GetProcAddress(hDLL, "BUSINESS_HANDLE");
        }
        catch (const std::exception&)
        {
            qDebug() << "iniError";
        }
    }
}

int Lemon::Sign()
{
    int ifSign_i;
    try
    {
        QString topInData_str = "9100^100007^";
        topInData_str.append(myNum_str);//4096
        topInData_str.append("^^");
        topInData_str.append(getTime());
        topInData_str.append("-100007-1111^441200^^1^");
        //char ch_InData[] = "9100^100007^8888^^20171213005255-100007-8645^441200^^1^";//保留旧数据
        QByteArray b = topInData_str.toLatin1();
        char * ch_InData = b.data();
        char ch_OutData[512] = "";
        ifSign_i = BUSINESS_HANDLE(ch_InData, ch_OutData);//使用函数
        if (ifSign_i == 0)//返回 0 代表成功
        {
            bcNum_str = ch_OutData;
            QString send_str = ch_InData;
            send_str.append("\nout\n");
            send_str.append(bcNum_str);
            qDebug() << send_str;
        }
        else
        {
            QString strError = QString::fromLocal8Bit(ch_OutData, 512);//转为QString输出
            qDebug() << QString("\n" + strError + "           error");
        }
    }
    catch (const std::exception&)
    {
        qDebug() << "Sign is Error";
    }
    return ifSign_i;
}

int Lemon::sendData(QString in_str)
{
    int ifSendDate_i;
    char * inData_ch = new char;
    qDebug () << "myGod" << inData_ch << endl;
    memset(outData_ch, 0, sizeof(1024));
    if (hDLL != NULL && BUSINESS_HANDLE != NULL)
    {
        try
        {
            string uploadTemp_str = string((const char *)in_str.toLocal8Bit());//Chinese
            inData_ch = const_cast<char*>(uploadTemp_str.c_str());
            ifSendDate_i = BUSINESS_HANDLE(inData_ch, outData_ch);//使用函数
            if (ifSendDate_i == 0)
            {
                QString send_str = inData_ch;
                send_str.append("\nout\n");
                QString hhh = QString::fromLocal8Bit(outData_ch);
                send_str.append(hhh);
                qDebug() << send_str;
            }
            else
            {
                QString strError = QString::fromLocal8Bit(outData_ch, 1024);//转为QString输出
                qDebug() << QString("\n" + strError + " error\n");
            }
        }
        catch (const std::exception&)
        {
            qDebug() << "sendData";
        }
    }
    else
    {
        qDebug() << "No............";
    }
    return ifSendDate_i;
}

QString Lemon::getTime()
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
