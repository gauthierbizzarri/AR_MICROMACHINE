#include "ai.h"

AI::AI(QUuid uuid, QUuid::StringFormat uuidStrFormat, QObject *parent)
    : QObject{parent}
{
    m_uuid = uuid;
    m_uuidStrFormat = uuidStrFormat;
}

void AI::mapDatas(QJsonDocument map) {
    m_map = map;
}

void AI::playerDatas(QJsonDocument game) {
    m_game = game;
    process();
}

void AI::process() {
    qDebug("process IA");
    qDebug() << m_map;
    qDebug() << m_game;

    if (m_map.isEmpty()) return;
    if (m_game.isEmpty()) return;

    for (const auto player : m_game.object()["players"].toArray()) {
        if (QUuid(player.toObject()["uuid"].toString()) == /*m_uuid*/ "ia_uuid") {
            m_player = player.toObject();
            break;
        }
    }

    qDebug() << m_player;
    if (m_player.isEmpty()) return;



    qDebug("true uuid");
    qDebug() << m_uuid.toString(m_uuidStrFormat);
    qDebug("player !");
    qDebug() << m_player;

    QJsonObject jsonOutput;

    jsonOutput.insert("uuid", m_uuid.toString(m_uuidStrFormat));
    jsonOutput.insert("angle", "90");
    jsonOutput.insert("power", "100");

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
