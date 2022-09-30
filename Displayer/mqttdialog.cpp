#include "mqttdialog.h"

const QString MqttDialog::MAP = "map";
const QString MqttDialog::PLAYER_CONTROL = "player/control";
const QString MqttDialog::PLAYER_REGISTER = "player/register";
const QString MqttDialog::GAME = "game";

MqttDialog::MqttDialog()
{
    mclient = new QMqttClient(this);

    connect(mclient, &QMqttClient::connected, this, &MqttDialog::onConnect);
    connect(mclient, &QMqttClient::disconnected, this, &MqttDialog::onDisconnect);
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

void MqttDialog::establishConnection(QString host, int port, QString username, QString password)
{
    if(connectionAcquired)
        mclient->disconnectFromHost();

    mclient->setHostname(host);
    mclient->setPort(port);
    mclient->setUsername(username);
    mclient->setPassword(password);
    mclient->connectToHost();
}

void MqttDialog::cutConnection()
{
    mclient->disconnectFromHost();
}

bool MqttDialog::isConnected()
{
    return connectionAcquired;
}

void MqttDialog::onConnect()
{
    qDebug()<<"connected";
    connectionAcquired = true;
    emit connected();
}

void MqttDialog::onDisconnect()
{
    connectionAcquired = false;
    emit disconnected();
}

void MqttDialog::onMessageRecieved(const QByteArray &data, QMqttTopicName name)
{
    qDebug()<<data;
    emit messageRecieved(data, name);
}
