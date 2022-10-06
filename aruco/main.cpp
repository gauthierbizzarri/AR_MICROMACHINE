#include <QCoreApplication>
#include "manager.h"


manager* manage;
Traitement_Image* ttr;


int main(int argc, char *argv[])
{

   QCoreApplication a(argc, argv);

   // manage = new manager();

    ttr = new Traitement_Image;
    ttr->rect();
    return a.exec();
}
