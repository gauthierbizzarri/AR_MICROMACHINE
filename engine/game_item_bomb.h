#ifndef GAMEBOMB_H
#define GAMEBOMB_H

#include "game_entity.h"

class GameBomb : public GameEntity
{
    Q_OBJECT

    int m_ttl;
    int m_age;
    QString m_uuid;
    int m_explosionTtl;
    int m_explosionRadius;
    bool m_exploding;

public:
    GameBomb(QWidget* parent, GameProperties* properties);

    void set(int x, int y);
    void checkCollision();

    void updateProperties(GameProperties* properties);
    QJsonObject toJson();
    void update();
    void getHit();

};

#endif // GAMEBOMB_H
