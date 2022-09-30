#include "player.h"

Player::Player(QJsonObject player)
    : Entity{
      player["x"].toInt(),
      player["y"].toInt(),
      player["angle"].toDouble()
    }
{
    m_uuid = QUuid(player["uuid"].toString());
    m_lastCheckpoint = player["lastCheckpoint"].toInt();
}

QUuid Player::get_uuid() {
    return m_uuid;
}

int Player::get_lastCheckpoint() {
    return m_lastCheckpoint;
}

Player Player::fromJson(QJsonDocument jsonPlayer) {
    return Player(jsonPlayer.object());
}

void Player::debug() {
    qDebug("Player debugging");
    qDebug() << m_uuid;
    qDebug() << m_lastCheckpoint;
}
