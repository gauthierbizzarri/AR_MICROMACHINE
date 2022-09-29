#ifndef MAP_H
#define MAP_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "checkpoint.h"
#include "obstacle.h"

class Map
{
private:
    int m_width;
    int m_height;
    QList<Checkpoint> m_checkpoints;
    QList<Obstacle> m_obstacles;

public:
    explicit Map(QJsonObject);

    QList<Checkpoint> get_checkpoints();
    QList<Obstacle> get_obstacles();

    static Map fromJson(QJsonDocument);

    void debug();
};

#endif // MAP_H
