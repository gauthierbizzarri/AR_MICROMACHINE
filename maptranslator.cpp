#include "maptranslator.h"
#include <QJsonArray>
#include <QJsonObject>
#include <circle.h>
#include <player.h>

MapTranslator::MapTranslator(MapInfo* info)
{
    this->info = info;
}

void MapTranslator::update(QJsonDocument message)
{
    QJsonObject base = message.object();
    QJsonArray points = base.value("checkpoints").toArray();
    QJsonArray obstacles = base.value("obstacles").toArray();
    info->clear();
    for(int i = 0; i<points.size(); i++)
    {
        QJsonObject pointObj = points[i].toObject();
        QString id = pointObj.value("id").toString();
        Checkpoint* point = new Checkpoint(pointObj.value("x").toInt(), pointObj.value("y").toInt());
        info->addObject(id, point);
    }
    // obstacles
    for(int i = 0; i<obstacles.size(); i++)
    {
        QJsonObject obtclObj = obstacles[i].toObject();
        QString id = obtclObj.value("id").toString();
        if(obtclObj.value("id").toInt() %2 == 0)
        {
            Circle* circle = new Circle(obtclObj.value("x").toInt(), obtclObj.value("y").toInt());
            info->addObject(id, circle);
        }
        else
        {
            float angle = obtclObj.value("angle").toDouble();
            Rectangle* obstacle = new Rectangle(obtclObj.value("x").toInt(), obtclObj.value("y").toInt(), angle);
            info->addObject(id, obstacle);
        }
    }
}

void MapTranslator::update_players(QJsonDocument message)
{

    qDebug()<<"Update players ";
    QJsonObject base = message.object();
    QJsonArray players = base.value("players").toArray();
    qDebug()<<"PLAYERS RECEIVED"<<players;
    info->clear_players();
    // UPDATE PLAYER
    for(int i = 0; i<players.size(); i++)
    {
        qDebug()<<"Player upated"<<"\n";
        qDebug()<<players[i];
        QJsonObject playerObj = players[i].toObject();
        QString uuid = playerObj.value("uuid").toString();
        Player* player = new Player(playerObj.value("x").toInt(), playerObj.value("y").toInt());
        info->addObject(uuid, player);
    }

}
