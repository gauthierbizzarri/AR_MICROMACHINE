#include "ai_manager.h"

AI_Manager::AI_Manager(QObject *parent)
    : QObject{parent}
{
    m_talker = new QtMqttTalker();
    m_ai = new AI();

    connect(m_talker, &QtMqttTalker::jsonAI, m_ai, &AI::playerDatas);
    connect(m_ai, &AI::controllerInputs, m_talker, &QtMqttTalker::TalkerController);
}
