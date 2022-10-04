#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "game_entity.h"
#include "game_checkpoint.h"
#include "game_sketch.h"

class GamePlayer : public GameEntity
{
    Q_OBJECT

    QString m_uuid;
    QString m_pseudo;
    QString m_conrtoller;
    QString m_vehicle;
    int m_team;

    GameCheckpoint* m_checkpoint;

    QString m_color;
    double m_steering;
    double m_angle;
    int m_power;
    int m_width;
    int m_height;
    QPointF m_collisionF;

    GameSketch c1;
    GameSketch c2;
    GameSketch c3;
    GameSketch c4;

public:
    GamePlayer(QWidget* parent, int x, int y, QString uuid, QString pseudo, QString controller, QString vehicle, int team);
    ~GamePlayer();

    QString getUuid();
    QString getPseudo();
    QString getColor();
    QString getController();
    QString getVehicle();
    int getTeam();

    void setSteering(double value);
    void setPower(int value);
    void setCheckpoint(GameCheckpoint* checkpoint);

    QJsonObject toJson();
    void update();
    void checkCollision();
    void collideWith(GameMapObject* object);


signals:
    void endOfLife();

};

#endif // GAMEPLAYER_H
