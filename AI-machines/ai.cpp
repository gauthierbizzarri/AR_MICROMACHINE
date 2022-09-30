#include "ai.h"

AI::AI(QUuid uuid, QUuid::StringFormat uuidStrFormat, QObject *parent)
    : QObject{parent}
{
    m_uuid = uuid;
    m_uuidStrFormat = uuidStrFormat;

    m_map = nullptr;
    m_game = nullptr;
    m_player = nullptr;
    m_nextCheckpoint = nullptr;
}

void AI::mapDatas(QJsonDocument map) {
    m_map = new Map(Map::fromJson(map));
    set_checkpoints();
}

void AI::playerDatas(QJsonDocument game) {
    m_game = new Game(Game::fromJson(game));
    process();
}

void AI::set_checkpoints() {
    if (!m_map) return;
    m_checkpoints = m_map->get_checkpoints();
}

void AI::process() {
    qDebug("process IA");

    if (!m_map) return;
    if (m_checkpoints.isEmpty()) return;
    if (!m_game) return;

    foreach (Player player, m_game->get_players()) {
        //if (player.get_uuid() == m_uuid) {
        if (player.get_uuid() == "ia_uuid") {
            m_player = &player;
            break;
        }
    }

    if (!m_player) return;

    m_lastCheckpointId = m_player->get_lastCheckpoint();

    qDebug("Last id");
    qDebug() << m_lastCheckpointId;

    /*
    foreach (Checkpoint checkpoint, m_checkpoints) {
        bool isNext = false;

        if (!m_nextCheckpoint) isNext = true;

        if (isNext) {
            m_nextCheckpoint = new Checkpoint(checkpoint);
        }
    }
    */

    qDebug("Next Checkpoint!");
    m_nextCheckpoint->debug();

    QJsonObject jsonOutput;

    jsonOutput.insert("uuid", m_uuid.toString(m_uuidStrFormat));
    jsonOutput.insert("angle", M_PI/2);
    jsonOutput.insert("power", 100);

    qDebug("json uuid");
    qDebug() << jsonOutput["uuid"];

    QJsonObject buttons;

    buttons.insert("banana", false);
    buttons.insert("bomb", false);
    buttons.insert("rocket", false);

    jsonOutput.insert("buttons", buttons);

    QJsonDocument output = QJsonDocument(jsonOutput);

    emit controllerInputs(output);
}
