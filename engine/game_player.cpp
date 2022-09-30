
#include <QDebug>
#include <QPen>
#include <qmath.h>

#include "game_player.h"

GamePlayer::GamePlayer(QWidget* parent, QString uuid, QString pseudo, QString controller, QString vehicle, int team)
    : GameEntity(parent, 500, 500), m_uuid(uuid), m_pseudo(pseudo), m_conrtoller(controller), m_vehicle(vehicle), m_team(team)
{
    this->m_color = "red"; // TODO : donner une couleur qui dépend du nom du joueur, ou de l'équipe s'il y en a plusieurs
    this->m_steering = 0;
    this->m_angle = 0;
    this->m_power = 0;

    QGraphicsRectItem* item = new QGraphicsRectItem(-12.5, -6, 25, 12);
    QPen pen;
    pen.setWidth(1);
    item->setPen(pen);
    item->setBrush(QBrush(Qt::blue));
    item->moveBy(this->m_x*0.6, this->m_y*0.6);
    item->setRotation(0);

    this->m_item = item;

    qDebug() << "player log : " << pseudo;
}

GamePlayer::~GamePlayer() {

}

QString GamePlayer::getUuid() {
    return this->m_uuid;
}

QString GamePlayer::getPseudo() {
    return this->m_pseudo;
}

QString GamePlayer::getColor() {
    return this->m_color;
}

QString GamePlayer::getController() {
    return this->m_conrtoller;
}

QString GamePlayer::getVehicle() {
    return this->m_vehicle;
}

int GamePlayer::getTeam() {
    return this->m_team;
}

void GamePlayer::setSteering(double value) {
    this->m_steering = value;
}

void GamePlayer::setPower(int value) {
    this->m_power = value;
}

QJsonObject GamePlayer::toJson() {

    QJsonObject json;

    json.insert(QString("uuid"), QJsonValue(this->m_uuid));
    json.insert(QString("pseudo"), QJsonValue(this->m_pseudo));
    json.insert(QString("color"), QJsonValue(this->m_color));
    json.insert(QString("team"), QJsonValue(this->m_team));
    json.insert(QString("x"), QJsonValue(this->X()));
    json.insert(QString("y"), QJsonValue(this->Y()));
    json.insert(QString("angle"), QJsonValue(this->m_angle));
    json.insert(QString("speed"), QJsonValue(this->m_power));
    json.insert(QString("vehicle"), QJsonValue(this->m_vehicle));
    json.insert(QString("lastCheckpoint"), QJsonValue(0));
    json.insert(QString("currentLap"), QJsonValue(0));
    json.insert(QString("status"), QJsonValue("driving"));
    json.insert(QString("controller"), QJsonValue(this->m_conrtoller));

    QJsonObject items;
    items.insert(QString("banana"), QJsonValue(1));
    items.insert(QString("bomb"), QJsonValue(1));
    items.insert(QString("rocket"), QJsonValue(1));

    json.insert(QString("items"), items);

    return json;
}

void GamePlayer::update() {

    this->m_angle += this->m_steering;

    int futurX = this->m_x +cos(this->m_angle) *this->m_power;
    int futurY = this->m_y -sin(this->m_angle) *this->m_power;

    if(futurX < 50)
        this->m_x = 50;
    else {
        if(futurX > 950)
            this->m_x = 950;
        else
            this->m_x = this->m_x +cos(this->m_angle) *this->m_power /2;
    }

    if(futurY < 50)
        this->m_y = 50;
    else {
        if(futurY > 950)
            this->m_y = 950;
        else
            this->m_y = this->m_y -sin(this->m_angle) *this->m_power /2;
    }


    this->m_item->setX(this->m_x*0.6);
    this->m_item->setY(this->m_y*0.6);
    this->m_item->setRotation(-this->m_angle *57.2974);

}
