#ifndef MAPTRANSLATOR_H
#define MAPTRANSLATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <mapinfo.h>
#include <QJsonDocument>

class MapTranslator
{
private:
    QJsonDocument original;
public:
    MapTranslator(QJsonDocument jsonmessage);
    MapInfo* translate();
};

#endif // MAPTRANSLATOR_H
