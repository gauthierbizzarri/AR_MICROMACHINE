#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include <QJsonDocument>
#include <QJsonObject>

class Item : public Entity
{
public:
    Item(QJsonObject);

    static Item fromJson(QJsonDocument);
};

#endif // ITEM_H
