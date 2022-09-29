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
public:
    MapInfo* info;
    MapTranslator(MapInfo* info);
    void update(QJsonDocument message);
    void update_players(QJsonDocument message);
};

#endif // MAPTRANSLATOR_H
