#include "map.h"

Map::Map(QJsonObject map)
{
    m_width = map["mapWidth"].toInt();
    m_height = map["mapHeight"].toInt();

    QList<Checkpoint> checkpoints;

    foreach (const auto checkpoint, map["checkpoints"].toArray()) {
        checkpoints.append(Checkpoint(checkpoint.toObject()));
    }

    /*
    while(!checkpoints.isEmpty()) {
        for (int i = 1; i < checkpoints.size(); i++) {

        }
    }
    */

    foreach (const auto obstacle, map["obstacles"].toArray()) {
        m_obstacles.append(Obstacle(obstacle.toObject()));
    }
}

QList<Checkpoint> Map::get_checkpoints() {
    return m_checkpoints;
}

Map Map::fromJson(QJsonDocument jsonMap) {
    return Map(jsonMap.object());
}

void Map::debug() {
    qDebug("Map debugging !");
    qDebug() << m_width;
    qDebug() << m_height;
    foreach(Checkpoint checkpoint, m_checkpoints) {
        checkpoint.debug();
    }
    foreach(Obstacle obstacle, m_obstacles) {
        obstacle.debug();
    }
}
