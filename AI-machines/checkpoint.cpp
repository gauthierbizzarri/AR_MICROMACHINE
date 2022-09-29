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

int Checkpoint::get_id() {
    return m_id;
}

Checkpoint Checkpoint::fromJson(QJsonDocument jsonCheckpoint) {
    return Checkpoint(jsonCheckpoint.object());
}

void Checkpoint::debug() {
    qDebug("Checkpoint Debugging !");
    qDebug() << "id:" << m_id;
    qDebug() << "x:" << get_x();
    qDebug() << "y:" << get_y();
    qDebug() << "angle:" << get_angle();
}
