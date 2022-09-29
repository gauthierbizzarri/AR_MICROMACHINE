#include "checkpoint.h"

Checkpoint::Checkpoint(QJsonObject checkpoint)
    : Entity{
      checkpoint["x"].toInt(),
      checkpoint["y"].toInt(),
      0
    }
{
    m_id = checkpoint["id"].toInt();
}

Checkpoint Checkpoint::fromJson(QJsonDocument jsonCheckpoint) {
    return Checkpoint(jsonCheckpoint.object());
}

void Checkpoint::debug() {
    qDebug("Checkpoint Debugging !");
    qDebug() << m_id;
    qDebug() << get_x();
    qDebug() << get_y();
    qDebug() << get_angle();
}
