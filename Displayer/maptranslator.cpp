#include "maptranslator.h"
#include <QJsonArray>
#include <QJsonObject>

MapTranslator::MapTranslator(QJsonDocument jsonmessage)
{
    this->original = jsonmessage;
}

MapInfo* MapTranslator::translate()
{
   QJsonObject base = this->original.object();
   QJsonArray points = base.value("checkpoints").toArray();
   QJsonArray obstacles = base.value("obstacles").toArray();
   MapInfo* info = new MapInfo();
   for(int i = 0; i<points.size(); i++)
   {
       QJsonObject pointObj = points[i].toObject();
       Point* point = new Point(pointObj.value("id").toInt(), new Position(pointObj.value("x").toInt(), pointObj.value("y").toInt()));
       info->addPoint(point);
   }
   for(int i = 0; i<points.size(); i++)
   {
       QJsonObject obtclObj = obstacles[i].toObject();
       Obstacle* obstacle = new Obstacle(obtclObj.value("id").toInt(), new Position(obtclObj.value("x").toInt(), obtclObj.value("y").toInt()), obtclObj.value("angle").toDouble());
       info->addObstacle(obstacle);
   }
   return info;
}
