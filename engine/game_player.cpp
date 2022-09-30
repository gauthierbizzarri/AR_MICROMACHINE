
#include <QDebug>
#include <QPainter>

#include "game_player.h"

GamePlayer::GamePlayer(QWidget* parent, QString uuid, QString pseudo, QString controller, QString vehicle, int team)
    : GameEntity(parent, 500, 500), m_uuid(uuid), m_pseudo(pseudo), m_conrtoller(controller), m_vehicle(vehicle), m_team(team)
{
    this->m_color = "red"; // TODO : donner une couleur qui dépend du nom du joueur, ou de l'équipe s'il y en a plusieurs
    this->m_steering = 0;
    this->m_angle = 0;

    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-12.5, -12.5, 25, 25);
    item->moveBy(m_x*0.6, m_y*0.6);
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
    this->m_angle = value;
}

QJsonObject GamePlayer::toJson() {

    QJsonObject json;

    json.insert(QString("uuid"), QJsonValue(this->m_uuid));
    json.insert(QString("pseudo"), QJsonValue(this->m_pseudo));
    json.insert(QString("color"), QJsonValue(this->m_color));
    json.insert(QString("team"), QJsonValue(this->m_team));
    json.insert(QString("x"), QJsonValue(this->X()));
    json.insert(QString("y"), QJsonValue(this->Y()));
    json.insert(QString("angle"), QJsonValue(0));
    json.insert(QString("speed"), QJsonValue(0));
    json.insert(QString("vehicle"), QJsonValue(this->m_vehicle));
    json.insert(QString("lastCheckpoint"), QJsonValue(0));
    json.insert(QString("currentLap"), QJsonValue(0));
    json.insert(QString("status"), QJsonValue(""));
    json.insert(QString("controller"), QJsonValue(this->m_conrtoller));

    QJsonObject items;
    items.insert(QString("banana"), QJsonValue(0));
    items.insert(QString("bomb"), QJsonValue(0));
    items.insert(QString("rocket"), QJsonValue(0));

    json.insert(QString("items"), items);

    return json;
}

void GamePlayer::update() {

    qDebug() << "hell update";
    this->m_x += 10;

}
