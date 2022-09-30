#include "item.h"

Item::Item(QJsonObject item)
    :Entity{
        item["x"].toInt(),
        item["y"].toInt(),
        item["angle"].toDouble()
    }
{

}

Item Item::fromJson(QJsonDocument jsonItem) {
    return Item(jsonItem.object());
}
