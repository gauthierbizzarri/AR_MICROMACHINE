#include "player.h"

Player::Player(QJsonObject player)
    : Entity{
      player["x"].toInt(),
      player["y"].toInt(),
      player["angle"].toDouble()
    }
{
    m_uuid = QUuid(player["uuid"].toString());
}

QUuid Player::get_uuid() {
    return m_uuid;
}

Player Player::fromJson(QJsonDocument jsonPlayer) {
    return Player(jsonPlayer.object());
}
