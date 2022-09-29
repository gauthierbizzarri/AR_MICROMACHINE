#include "mqttdialog.h"

const QString MqttDialog::MAP = "map";
const QString MqttDialog::PLAYER_CONTROL = "player/control";
const QString MqttDialog::PLAYER_REGISTER = "player/register";
const QString MqttDialog::GAME = "game";

MqttDialog::MqttDialog()
{
    mclient = new QMqttClient(this);
    mclient->setHostname("10.3.0.218");
    mclient->setPort(1883);
    mclient->setUsername("phoenix");
    mclient->setPassword("ardent");

    connect(mclient, &QMqttClient::connected, this, &MqttDialog::onConnect);
    connect(mclient, &QMqttClient::messageReceived, this, &MqttDialog::onMessageRecieved);
}

MqttDialog::~MqttDialog()
{
    delete mclient;
}

MqttDialog *MqttDialog::pub(QString name, QByteArray data)
{
    if(connectionAcquired)
    {
        mclient->publish(QMqttTopicName(name), data);
    }
    return this;
}

MqttDialog *MqttDialog::sub(QString name)
{
    if(connectionAcquired)
    {
        mclient->subscribe(QMqttTopicFilter(name));
    }
    return this;
}

void MqttDialog::establishConnection()
{
    mclient->connectToHost();
}

void MqttDialog::onConnect()
{
    connectionAcquired = true;
    emit connected();
}

void MqttDialog::onMessageRecieved(const QByteArray &data, QMqttTopicName name)
{
    emit messageRecieved(data, name);
}
