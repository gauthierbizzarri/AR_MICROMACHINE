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

    // POINTS
    for(int i = 0; i<points.size(); i++)
    {
        QJsonObject pointObj = points[i].toObject();
        QString id = QString::number(pointObj["id"].toDouble());
        Checkpoint* point = new Checkpoint(pointObj.value("x").toInt(), pointObj.value("y").toInt());
        minfo->addObject(id, point);
    }

    // OBSTACLES
    for(int i = 0; i<obstacles.size(); i++)
    {
        QJsonObject obtclObj = obstacles[i].toObject();
        QString id = QString::number(obtclObj["id"].toDouble());
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

void MapTranslator::update_game(QJsonDocument message)
{

    QJsonObject base = message.object();


    // UPDATE PLAYERS

    QJsonArray players = base.value("players").toArray();
    minfo->clear_players();
    for(int i = 0; i<players.size(); i++)
    {
        QJsonObject PlayerObj = players[i].toObject();
        QString uuid = QString::number(PlayerObj["uuid"].toDouble());
        float angle = PlayerObj.value("angle").toDouble();
        Player* player = new Player(PlayerObj.value("x").toInt(), PlayerObj.value("y").toInt(),angle);

        // SET DATA OF PLAYER
        QString colorstr =PlayerObj.value("color").toString();

        // Get color
        QColor color = this->get_color(colorstr);

        int team = PlayerObj.value("team").toDouble();

        int speed = PlayerObj.value("speed").toDouble();

        QString vehicule = PlayerObj.value("vehicle").toString();

        player->set_data(color,team,angle,speed,vehicule);
        minfo->addObject(uuid, player);
    }



    // UPDATE ITEMS

    QJsonArray items = base.value("items").toArray();
    minfo->clear_items();
    // UPDATE PLAYER
    for(int i = 0; i<items.size(); i++)
    {
        qDebug()<<"Items in list";
        QJsonObject ItemObj = items[i].toObject();
        QString type = ItemObj["type"].toString();
        // BANANA
        if (type =="banana")
        {
            Banana* banana = new Banana(ItemObj.value("x").toInt(), ItemObj.value("y").toInt());
            minfo->addItem(QVariant(i).toString(), banana);
        }

        // ROCKET
        if (type =="rocket")
        {
            Rocket* rocket = new Rocket(ItemObj.value("x").toInt(), ItemObj.value("y").toInt());
            minfo->addItem(QVariant(i).toString(), rocket);
        }

        if (type =="bomb")
        {
            Bomb* bomb = new Bomb(ItemObj.value("x").toInt(), ItemObj.value("y").toInt());
            minfo->addItem(QVariant(i).toString(), bomb);
        }

    }


}

QColor MapTranslator::get_color(QString colorstr){

     QColor color = Qt::black;

    if (colorstr.contains("yellow"))
    {
        color = Qt::yellow;
    }

    else if (colorstr.contains("red"))
    {
        color = Qt::red;
    }

    else if (colorstr.contains("green"))
    {
        color = Qt::green;
    }

    else if (colorstr.contains("blue"))
    {
        color = Qt::blue;
    }
    return color;
}


