#include "ai_manager.h"

AI_Manager::AI_Manager(QObject *parent)
    : QObject{parent}
{
    m_uuid = QUuid::createUuid();
    m_uuidStrFormat = QUuid::WithoutBraces;
    qDebug() << m_uuid.toString(m_uuidStrFormat);

    m_talker = new QtMqttTalker(m_uuid, m_uuidStrFormat);
    m_ai = new AI(m_uuid, m_uuidStrFormat);

    connect(m_talker, &QtMqttTalker::updateMap, m_ai, &AI::mapDatas);
    connect(m_talker, &QtMqttTalker::updateGame, m_ai, &AI::playerDatas);
    connect(m_ai, &AI::controllerInputs, m_talker, &QtMqttTalker::TalkerController);
}
