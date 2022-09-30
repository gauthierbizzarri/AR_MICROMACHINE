#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>

#include "ai_manager.h"

AI_Manager* ai_manager;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("Hello World!");

    ai_manager = new AI_Manager();

    return a.exec();
}
