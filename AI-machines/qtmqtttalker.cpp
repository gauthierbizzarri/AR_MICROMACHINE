#include "qtmqtttalker.h"

QtMqttTalker::QtMqttTalker(QObject *parent)
    : QObject{parent}
{
    m_uuid = QUuid::createUuid();

    qDebug() << m_uuid;

    m_topicProperties = QMqttTopicFilter("/game/properties");
    m_topicRegister =   QMqttTopicName("/player/register");
    m_topicGame =       QMqttTopicFilter("/game");
    m_topicController = QMqttTopicName("/player/control");

    m_qos = 0;

    m_client = new QMqttClient(this);
    m_client->setHostname("10.3.0.218");
    m_client->setPort(1883);
    m_client->setUsername("phoenix");
    m_client->setPassword("ardent");

    connect(m_client, &QMqttClient::stateChanged, this, &QtMqttTalker::TalkerDebugState);
    connect(m_client, &QMqttClient::errorChanged, this, &QtMqttTalker::TalkerDebugError);
    connect(m_client, &QMqttClient::connected,    this, &QtMqttTalker::TalkerConnected);

    m_client->connectToHost();

    qDebug("Constructed");
}

void QtMqttTalker::QtMqttSub() {
    auto subscription = m_client->subscribe(m_topicGame, m_qos);
    if (!subscription) {
        qDebug() << "Could not subscribe. Is there a valid connection?";
        return;
    }

    connect(m_client, &QMqttClient::messageReceived, this, &QtMqttTalker::TalkerMessageReceived);

    qDebug("MqttSub!");
}

void QtMqttTalker::QtMqttPub(QByteArray message) {
    m_client->publish(m_topicController, message, m_qos);

    qDebug("MqttPub!");
}

void QtMqttTalker::TalkerMessageReceived(const QByteArray &message, const QMqttTopicName &topicName) {
    qDebug() << message;
    qDebug() << topicName;

    QJsonParseError error;
    QJsonDocument jsonMessage = QJsonDocument::fromJson(message, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << error.errorString();
        return;
    }

    qDebug() << jsonMessage;
    qDebug() << jsonMessage.toJson();

    emit jsonAI(jsonMessage);
}

void QtMqttTalker::TalkerConnected() {
    QtMqttSub();
}

void QtMqttTalker::TalkerDebugState(QMqttClient::ClientState state) {
    qDebug() << state;
}

void QtMqttTalker::TalkerDebugError(QMqttClient::ClientError error) {
    qDebug() << error;
}


