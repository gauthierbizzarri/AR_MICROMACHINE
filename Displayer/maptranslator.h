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
    MapInfo* info;
public:
    MapTranslator(MapInfo* info);
    void update(QJsonDocument message);
};

#endif // MAPTRANSLATOR_H
