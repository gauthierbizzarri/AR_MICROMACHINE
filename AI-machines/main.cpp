#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>

#include "qtmqtttalker.h"

QtMqttTalker* talker;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("Hello World!");

    talker = new QtMqttTalker();

    return a.exec();
}
