#include "game_player.h"

GamePlayer::GamePlayer(QWidget* parent, QString uuid, QString pseudo, QString controller, QString vehicle, int team)
    : GameEntity{parent, 0, 0}, m_uuid(uuid), m_pseudo(pseudo), m_conrtoller(controller), m_vehicle(vehicle), m_team(team)
{
    this->m_color = "red"; // TODO : donner une couleur qui dépend du nom du joueur, ou de l'équipe s'il y en a plusieurs
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
    return this->m_conrtoller
}

QString GamePlayer::getVehicle() {
    return this->m_vehicle;
}

int GamePlayer::getTeam() {
    return this->m_team;
}
