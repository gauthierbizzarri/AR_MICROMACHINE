
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include <QJsonDocument>
#include "client.h"
#include "main.h"

#define EXAMPLE_MAP "{\"mapWidth\":1000,\"mapHeight\":1000,\"checkpoints\":[{\"id\": 121,\"x\": 50,\"y\": 100},{\"id\": 154,\"x\": 500,\"y\": 300},{\"id\": 156,\"x\": 800,\"y\": 800},{\"id\": 183,\"x\": 700,\"y\": 200},{\"id\": 192,\"x\": 350,\"y\": 700}],\"obstacles\":[{\"id\": 231,\"angle\": 0.2,\"x\": 700,\"y\": 600},{\"id\": 233,\"angle\": -0.2,\"x\": 400,\"y\": 550},{\"id\": 234,\"angle\": 0,\"x\": 900,\"y\": 400},{\"id\": 240,\"angle\": 0,\"x\": 200,\"y\": 250},{\"id\": 242,\"angle\": 0.2,\"x\": 0,\"y\": 700},{\"id\": 241,\"angle\": 0,\"x\": 300,\"y\": 1000},{\"id\": 243,\"angle\": 0,\"x\": 500,\"y\": 1000},{\"id\": 245,\"angle\": 1.5707,\"x\": 1000,\"y\": 800},{\"id\": 247,\"angle\": 0,\"x\": 500,\"y\": 0},{\"id\": 249,\"angle\": 0,\"x\": 800,\"y\": 0},{\"id\": 250,\"angle\": 0.2,\"x\": 600,\"y\": 1000}]}"
#define EXAMPLE_REGISTER "{\"uuid\":\"qkfbf541qe684eq1eq86f4g8t3gt4\",\"pseudo\":\"quiscale\",\"controller\":\"keyboard\",\"vehicle\":\"car\",\"team\":0}"
#define EXAMPLE_CONTROL  "{\"uuid\":\"qkfbf541qe684eq1eq86f4g8t3gt4\",\"angle\":0.6,\"power\":100,\"buttons\":{\"banana\":false,\"bomb\":false,\"rocket\":false}}"

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

Client::Client(QObject* parent)
    : QObject{parent}
{

    this->m_mqtt = new QMqttClient();
    this->m_mqtt->setHostname(QString(MQTT_HOST));
    this->m_mqtt->setPort(MQTT_PORT);
    this->m_mqtt->setUsername(MQTT_USER);
    this->m_mqtt->setPassword(MQTT_PASS);

    connect(this->m_mqtt, &QMqttClient::stateChanged, this, &Client::debugStatus);
    connect(this->m_mqtt, &QMqttClient::errorChanged, this, &Client::debugError);
    connect(this->m_mqtt, &QMqttClient::connected, this, &Client::connected);
    connect(this->m_mqtt, &QMqttClient::messageReceived, this, &Client::messageReceived);

    this->m_mqtt->connectToHost();

}

Client::~Client() {

    this->m_mqtt->disconnect();

}

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

void Client::debugStatus(QMqttClient::ClientState state) {
    qDebug() << state;
}

void Client::debugError(QMqttClient::ClientError error) {
    qDebug() << error;
}

void Client::connected() {
    if(!this->m_mqtt->subscribe(QString(MQTT_TOPIC_MAP)))
        qDebug() << "Subscription to /map failed";

    if(!this->m_mqtt->subscribe(QString(MQTT_TOPIC_PLAYER_REGISTER)))
        qDebug() << "Subscription to /player/register failed";

    if(!this->m_mqtt->subscribe(QString(MQTT_TOPIC_PLAYER_CONTROL)))
        qDebug() << "Subscription to /player/control failed";

    qDebug() << "MQTT Client is ready";

    //this->m_mqtt->publish(QString("player/register"), QString(EXAMPLE_REGISTER).toUtf8());

}

void Client::messageReceived(const QByteArray& message, const QMqttTopicName& topic) {

    QJsonDocument jsonDoc = QJsonDocument::fromJson(message);

    if(topic.name() == MQTT_TOPIC_MAP)
        emit this->receivedMap(jsonDoc.object());

    if(topic.name() == MQTT_TOPIC_PLAYER_REGISTER)
        emit this->receivedPlayerRegister(jsonDoc.object());

    if(topic.name() == MQTT_TOPIC_PLAYER_CONTROL)
        emit this->receivedPlayerControl(jsonDoc.object());

}

void Client::publishProperties(QJsonObject propertyJson) {

    this->m_mqtt->publish(QString(MQTT_TOPIC_GAME_PROPERTIES), QJsonDocument(propertyJson).toJson(QJsonDocument::Compact));

}

void Client::publishMap() {

    this->m_mqtt->publish(QString(MQTT_TOPIC_MAP), QString(EXAMPLE_MAP).toUtf8());

}

void Client::publishGame(QJsonObject engineJson) {

    this->m_mqtt->publish(QString(MQTT_TOPIC_GAME), QJsonDocument(engineJson).toJson(QJsonDocument::Compact));

}


