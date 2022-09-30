#include <QCoreApplication>
#include "manager.h"


manager* manage;


int main(int argc, char *argv[])
{

   QCoreApplication a(argc, argv);

    manage = new manager();


    return a.exec();
}
