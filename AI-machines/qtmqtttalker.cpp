#include "qtmqtttalker.h"

QtMqttTalker::QtMqttTalker(QUuid uuid, QUuid::StringFormat uuidStrFormat, QObject *parent)
    : QObject{parent}
{
    m_uuid = uuid;
    m_uuidStrFormat = uuidStrFormat;

    m_topicProperties = QMqttTopicFilter("game/properties");
    m_topicRegister =   QMqttTopicName("player/register");
    m_topicMap =        QMqttTopicFilter("map");
    m_topicGame =       QMqttTopicFilter("game");
    m_topicController = QMqttTopicName("player/control");

    m_qos = 0;

    m_client = new QMqttClient(this);
    //m_client->setHostname("10.3.0.218");
    m_client->setHostname("localhost");
    m_client->setPort(1883);
    m_client->setUsername("phoenix");
    m_client->setPassword("ardent");

    connect(m_client, &QMqttClient::stateChanged, this, &QtMqttTalker::TalkerDebugState);
    connect(m_client, &QMqttClient::errorChanged, this, &QtMqttTalker::TalkerDebugError);
    connect(m_client, &QMqttClient::connected,    this, &QtMqttTalker::TalkerConnected);

    m_client->connectToHost();
}

void QtMqttTalker::QtMqttSub() {
    auto propertiesSubscription = m_client->subscribe(m_topicProperties, m_qos);
    auto mapSubscription = m_client->subscribe(m_topicMap, m_qos);
    auto gameSubscription = m_client->subscribe(m_topicGame, m_qos);

    if (!propertiesSubscription) {
        qDebug() << "Could not subscribe to propeties. Is there a valid connection?";
        return;
    }
    if (!mapSubscription) {
        qDebug() << "Could not subscribe to map. Is there a valid connection?";
        return;
    }
    if (!gameSubscription) {
        qDebug() << "Could not subscribe to game. Is there a valid connection?";
        return;
    }

    connect(m_client, &QMqttClient::messageReceived, this, &QtMqttTalker::TalkerMessageReceived);
}

void QtMqttTalker::QtMqttPub(QMqttTopicName topic, QByteArray message) {
    m_client->publish(topic, message, m_qos);
}

void QtMqttTalker::QtMqttProperties(QJsonDocument properties) {
    qDebug() << "properties";
    qDebug() << properties;
    TalkerRegister();
}
void QtMqttTalker::QtMqttMap(QJsonDocument map) {
    qDebug() << "map";
    qDebug() << map;
    emit updateMap(map);
}
void QtMqttTalker::QtMqttGame(QJsonDocument game) {
    qDebug() << "game";
    qDebug() << game;
    emit updateGame(game);
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
    if (topicName.name() == m_topicMap.filter()) {
        QtMqttMap(jsonMessage);
    }
    if (topicName.name() == m_topicGame.filter()) {
        QtMqttGame(jsonMessage);
    }
}

void QtMqttTalker::TalkerRegister() {
    QJsonObject jsonLogin;

    jsonLogin.insert("uuid", m_uuid.toString(m_uuidStrFormat));
    jsonLogin.insert("pseudo", "ia_" + m_uuid.toString(m_uuidStrFormat));
    jsonLogin.insert("controller", "ia");
    jsonLogin.insert("vehicle", "car");
    jsonLogin.insert("team", 0);

    QJsonDocument login = QJsonDocument(jsonLogin);

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


