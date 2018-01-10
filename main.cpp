#include <QDebug>
#include <QCoreApplication>
#include <Caviar.h>
#include <Salt.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Caviar *ca = new Caviar();
    Salt *sa = new Salt();

    ca->start();
    //sa->start();

    int i;
    cin >> i;
    ca->ifRun_b = i;
    sa->ifRun_b = i;

    return a.exec();
}
