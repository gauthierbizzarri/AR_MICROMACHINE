#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "game_entity.h"
#include "game_checkpoint.h"
#include "game_sketch.h"
#include "game_item_banana.h"
#include "game_item_bomb.h"
#include "game_item_rocket.h"

class GamePlayer : public GameEntity
{
    Q_OBJECT

    QString m_uuid;
    QString m_pseudo;
    QString m_conrtoller;
    QString m_vehicle;
    int m_team;

    int m_checkpoint;
    int m_lap;

    QString m_color;
    double m_steering;
    double m_angle;
    int m_power;
    QPointF m_speed;
    int m_stunnedAge;
    int m_bananaCd;
    int m_bombCd;
    int m_rocketCd;
    int m_bananaCdMax;
    int m_bombCdMax;
    int m_rocketCdMax;

    int m_maxSpeed;
    double m_acceleration;
    int m_weight;
    double m_maxSteering;
    int m_width;
    int m_height;

    int m_ttl;

    GameSketch c1;
    GameSketch c2;
    GameSketch c3;
    GameSketch c4;

public:
    GamePlayer(QWidget* parent, int x, int y, QString uuid, QString pseudo, QString controller, QString vehicle, int team, GameProperties* properties);
    ~GamePlayer();

    QString getUuid();
    QString getPseudo();
    QString getColor();
    QString getController();
    QString getVehicle();
    int getTeam();
    int getCheckpoint();
    int getLap();
    bool isStun();

    void setSteering(double value);
    void setPower(int value);
    bool canPlaceBanana();
    void placeBanana(GameBanana* prop);
    bool canPlaceBomb();
    void placeBomb(GameBomb* prop);
    bool canFireRocket();
    void fireRocket(GameRocket* prop);

    void reset(int x, int y);
    void checkCollision();
    void collideWith(GameMapObject* object);

    void updateProperties(GameProperties* properties);

    QJsonObject toJson();
    void update();
    void getHit();

signals:
    void statsChanged(GamePlayer* player);

};

#endif // GAMEPLAYER_H
