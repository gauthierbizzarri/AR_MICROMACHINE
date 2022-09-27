#ifndef MAPTRANSLATOR_H
#define MAPTRANSLATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mapinfo.h>
#include <QJsonDocument>

class MapTranslator : QWidget
{
    Q_OBJECT
private:
    QJsonDocument original;
public:
    MapTranslator(QJsonDocument jsonmessage);
    MapInfo translate();
    virtual void paintEvent(QPaintEvent* event);
};

#endif // MAPTRANSLATOR_H
