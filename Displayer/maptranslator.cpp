#include "maptranslator.h"
#include <QJsonArray>
#include <QJsonObject>

MapTranslator::MapTranslator(MapInfo* info)
{
    this->info = info;
}

void MapTranslator::update(QJsonDocument message)
{
    QJsonObject base = message.object();
    QJsonArray points = base.value("checkpoints").toArray();
    QJsonArray obstacles = base.value("obstacles").toArray();
    std::vector<int> currentObst;
    std::vector<int> currentPts;
    for(int i = 0; i<points.size(); i++)
    {
        QJsonObject pointObj = points[i].toObject();
        Position* pos = new Position(pointObj.value("x").toInt(), pointObj.value("y").toInt());
        int id = pointObj.value("id").toInt();
        if(!info->containsPoint(id))
        {
            Point* point = new Point(id, pos);
            info->addPoint(point);
        }
        else
            info->movePoint(id, pos);
        currentPts.push_back(id);
    }
    for(int i = 0; i<points.size(); i++)
    {
        QJsonObject obtclObj = obstacles[i].toObject();
        Position* pos = new Position(obtclObj.value("x").toInt(), obtclObj.value("y").toInt());
        float angle = obtclObj.value("angle").toDouble();
        int id = obtclObj.value("id").toInt();

        if(!info->containsObstacle(id))
        {
            Obstacle* obstacle = new Obstacle(id, pos, angle);
            info->addObstacle(obstacle);
        }
        else
            info->moveObstacle(id, pos, angle);
        currentObst.push_back(id);
    }
    std::map<int, Point*> pvalues = info->getPoints();
    for(std::map<int,Point*>::iterator iter = pvalues.begin(); iter != pvalues.end(); ++iter)
    {
        if(std::find(currentPts.begin(), currentObst.end(), iter->second->getId()) == currentPts.end())
        {
            info->removePoint(iter->second);
        }
    }
    std::map<int, Obstacle*> ovalues = info->getObstacles();
    for(std::map<int,Obstacle*>::iterator iter = ovalues.begin(); iter != ovalues.end(); ++iter)
    {
        if(std::find(currentPts.begin(), currentObst.end(), iter->second->getId()) == currentPts.end())
        {
            info->removeObstacle(iter->second);
        }
    }
}
