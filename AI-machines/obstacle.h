#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonObject>

#include "entity.h"

class Obstacle : public Entity
{
private:
    int m_id;

public:
    explicit Obstacle(QJsonObject);

    static Obstacle fromJson(QJsonDocument);

    void debug();
};

#endif // OBSTACLE_H
