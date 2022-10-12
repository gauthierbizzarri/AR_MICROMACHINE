#ifndef GAMEBANANA_H
#define GAMEBANANA_H

#include "game_entity.h"

class GameBanana : public GameEntity
{
    Q_OBJECT

    int m_ttl;
    int m_age;
    QString m_uuid;

public:
    GameBanana(QWidget* parent, GameProperties* properties);

    void set(int x, int y);

    void updateProperties(GameProperties* properties);
    QJsonObject toJson();
    void update();
    void getHit();

};

#endif // GAMEBANANA_H
