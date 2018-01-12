#include <QDebug>
#include <QCoreApplication>
#include <Caviar.h>
#include <Salt.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Caviar *caviar = new Caviar();
    Salt *salt = new Salt();

    //caviar->start();
    salt->start();

    int i;
    cin >> i;
    caviar->ifRun_b = i;
    salt->ifRun_b = i;

    return a.exec();
}
