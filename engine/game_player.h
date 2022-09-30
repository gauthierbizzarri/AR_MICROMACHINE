#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "game_entity.h"

class GamePlayer : public GameEntity
{
    Q_OBJECT

    QString m_uuid;
    QString m_pseudo;
    QString m_conrtoller;
    QString m_vehicle;
    int m_team;

    QString m_color;
    double m_steering;
    double m_angle;
    int m_power;

public:
    GamePlayer(QWidget* parent, QString uuid, QString pseudo, QString controller, QString vehicle, int team);
    ~GamePlayer();

    QString getUuid();
    QString getPseudo();
    QString getColor();
    QString getController();
    QString getVehicle();
    int getTeam();

    void setSteering(double value);
    void setPower(int value);

    QJsonObject toJson();
    void update();

signals:
    void endOfLife();

};

#endif // GAMEPLAYER_H
