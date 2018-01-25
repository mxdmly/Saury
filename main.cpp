#include <QtCore>
#include <QCoreApplication>
#include <Caviar.h>
#include <Salt.h>
#include <iostream>
#include <Lemon.h>
#include <QDebug>

using namespace std;

void isRun(QThread *qth)
{
    if(qth->isRunning())
    {
        Sleep(2000);
        isRun(qth);
    }
}
/*
void ss(char * a)
{
    a = {0};
    char sss[] = "ss00s";
    a = sss;
    qDebug() << &a << a;
}
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Caviar *caviar = new Caviar();
    Salt *salt = new Salt();

    caviar->start();
    Sleep(2000);
    salt->start();

    int i;
    cin >> i;
    caviar->ifRun_b = i;
    salt->ifRun_b = i;

    isRun(caviar);
    delete caviar;
    isRun(salt);
    delete salt;
    cout << "IS END" << endl;
/*
    char * chFH = new char[1000000];
    ss(chFH);*/

    return a.exec();
}
