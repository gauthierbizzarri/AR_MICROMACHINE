#ifndef CLIENT_H
#define CLIENT_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QJsonObject>
#include <QtMqtt/QMqttClient>

// ////////////////////////////////////////////////////////////////////////////
// Class Client
// ////////////////////////////////////////////////////////////////////////////

class Client : public QObject
{

    Q_OBJECT

    QMqttClient* m_mqtt;

public:
    Client(QObject* parent);
    virtual ~Client();

public slots:
    void debugStatus(QMqttClient::ClientState state);
    void debugError(QMqttClient::ClientError error);
    void connected();
    void messageReceived(const QByteArray& message, const QMqttTopicName& topic);
    void publishProperties(QJsonObject properties);
    void publishGame(QJsonObject engine);

signals:
    void receivedMap(QJsonObject object);
    void receivedPlayerRegister(QJsonObject object);
    void receivedPlayerControl(QJsonObject object);

};

// ////////////////////////////////////////////////////////////////////////////
// Class Client
// ////////////////////////////////////////////////////////////////////////////

#endif // CLIENT_H
