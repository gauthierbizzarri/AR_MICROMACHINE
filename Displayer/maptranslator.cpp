#include "maptranslator.h"
#include <QJsonArray>
#include <QJsonObject>
#include <circle.h>

MapTranslator::MapTranslator(MapInfo* info)
{
    minfo = info;
}

void MapTranslator::update(QJsonDocument message)
{
    QJsonObject base = message.object();
    QJsonArray points = base.value("checkpoints").toArray();
    QJsonArray obstacles = base.value("obstacles").toArray();
    minfo->clear();
    for(int i = 0; i<points.size(); i++)
    {
        QJsonObject pointObj = points[i].toObject();
        QString id = pointObj.value("id").toString();
        Checkpoint* point = new Checkpoint(pointObj.value("x").toInt(), pointObj.value("y").toInt());
        minfo->addObject(id, point);
    }
    for(int i = 0; i<obstacles.size(); i++)
    {
        QJsonObject obtclObj = obstacles[i].toObject();
        QString id = obtclObj.value("id").toString();
        if(obtclObj.value("id").toInt() %2 == 0)
        {
            Circle* circle = new Circle(obtclObj.value("x").toInt(), obtclObj.value("y").toInt());
            minfo->addObject(id, circle);
        }
        else
        {
            float angle = obtclObj.value("angle").toDouble();
            Rectangle* obstacle = new Rectangle(obtclObj.value("x").toInt(), obtclObj.value("y").toInt(), angle);
            minfo->addObject(id, obstacle);
        }
    }
}
