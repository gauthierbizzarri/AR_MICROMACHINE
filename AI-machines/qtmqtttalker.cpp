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
    auto propertiesSubscription = m_client->subscribe(m_topicProperties, m_qos);
    auto gameSubscription = m_client->subscribe(m_topicGame, m_qos);

    if (!propertiesSubscription) {
        qDebug() << "Could not subscribe. Is there a valid connection?";
        return;
    }
    if (!gameSubscription) {
        qDebug() << "Could not subscribe. Is there a valid connection?";
        return;
    }

    connect(m_client, &QMqttClient::messageReceived, this, &QtMqttTalker::TalkerMessageReceived);

    qDebug("MqttSub!");
}

void QtMqttTalker::QtMqttPub(QMqttTopicName topic, QByteArray message) {
    m_client->publish(topic, message, m_qos);

    qDebug("MqttPub!");
}

void QtMqttTalker::QtMqttProperties(QJsonDocument properties) {
    qDebug() << "properties";
    qDebug() << properties;
    TalkerRegister();
}
void QtMqttTalker::QtMqttGame(QJsonDocument game) {
    qDebug() << "game";
    qDebug() << game;
    emit jsonAI(game);
}

void QtMqttTalker::TalkerMessageReceived(const QByteArray &message, const QMqttTopicName &topicName) {
    QJsonParseError error;
    QJsonDocument jsonMessage = QJsonDocument::fromJson(message, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << error.errorString();
        return;
    }

    if (topicName.name() == m_topicProperties.filter()) {
        QtMqttProperties(jsonMessage);
    }
    if (topicName.name() == m_topicGame.filter()) {
        QtMqttGame(jsonMessage);
    }
}

void QtMqttTalker::TalkerRegister() {
    QVariantMap loginMap;

    loginMap["uuid"] = m_uuid;
    loginMap["pseudo"] = "ia" + m_uuid.toString();
    loginMap["controller"] = "ia";
    loginMap["vehicle"] = "car";
    loginMap["team"] = "0";

    QJsonDocument login = QJsonDocument(QJsonObject::fromVariantMap(loginMap));

    qDebug() << login;

    QtMqttPub(m_topicRegister, login.toJson());
}

void QtMqttTalker::TalkerController(QJsonDocument controller) {
    qDebug() << controller;

    QtMqttPub(m_topicController, controller.toJson());
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


