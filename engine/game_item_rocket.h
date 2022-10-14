#ifndef GAMEROCKET_H
#define GAMEROCKET_H

#include "game_entity.h"

class GameRocket : public GameEntity
{
    Q_OBJECT

    int m_speed;
    double m_angle;
    QString m_uuid;

public:
    GameRocket(QWidget* parent, GameProperties* properties);

    void set(int x, int y, double angle);
    void checkCollision();

    void updateProperties(GameProperties* properties);
    QJsonObject toJson();
    void update();
    void getHit();


};

#endif // GAMEROCKET_H
