#include "ai.h"

AI::AI(QUuid uuid, QUuid::StringFormat uuidStrFormat, QObject *parent)
    : QObject{parent}
{
    m_uuid = uuid;
    m_uuidStrFormat = uuidStrFormat;
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
    QList<Checkpoint> checkpoints = m_map->get_checkpoints();

    qDebug("Checkpoints !");
    if (checkpoints.isEmpty()) return;

    foreach(Checkpoint checkpoint, checkpoints) {
        checkpoint.debug();
    }
}

void AI::process() {
    qDebug("process IA");

    if (!m_map) return;
    if (!m_game) return;

    foreach (Player player, m_game->get_players()) {
        if (player.get_uuid() == m_uuid /*"ia_uuid"*/) {
            m_player = &player;
            break;
        }
    }

    if (!m_player) return;

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
