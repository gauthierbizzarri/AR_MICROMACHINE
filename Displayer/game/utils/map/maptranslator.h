#ifndef MAPTRANSLATOR_H
#define MAPTRANSLATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <game/utils/map/mapinfo.h>
#include <QJsonDocument>

class MapTranslator
{
private:
    /**
     * @brief info the map to be updated
     */
    MapInfo* minfo;
public:
    /**
     * @brief MapTranslator updates a map with a json
     * @param info the map to update
     */
    MapTranslator(MapInfo* info);
    /**
     * @brief update updates the map with the data givent bu the json message
     * @param message the json message
     */
    void update(QJsonDocument message);
    void update_game(QJsonDocument message);
    static QColor get_color(QString colorstr);
};

#endif // MAPTRANSLATOR_H

