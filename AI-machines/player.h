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

public:
    Player(QJsonObject);

    QUuid get_uuid();

    static Player fromJson(QJsonDocument);
};

#endif // PLAYER_H
