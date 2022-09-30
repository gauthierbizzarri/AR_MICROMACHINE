#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUuid>

class Player : public Entity
{
private:
    QUuid m_uuid;
    int m_lastCheckpoint;

public:
    Player(QJsonObject);

    QUuid get_uuid();
    int get_lastCheckpoint();

    static Player fromJson(QJsonDocument);

    void debug();
};

#endif // PLAYER_H
