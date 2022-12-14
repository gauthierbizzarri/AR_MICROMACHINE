#ifndef MQTTDIALOG_H
#define MQTTDIALOG_H

#include <QMqttClient>
#include <QObject>

class MqttDialog: public QObject
{
    Q_OBJECT

private:
    QMqttClient* mclient;
    bool connectionAcquired;
public:
    static const QString MAP;
    static const QString PLAYER_CONTROL;
    static const QString PLAYER_REGISTER;
    static const QString GAME;
    static const QString GAME_PROPERTIES;

    MqttDialog();
    ~MqttDialog();
    MqttDialog*  pub(QString name, QByteArray data);
    MqttDialog* sub(QString name);
    void establishConnection(QString host, int port, QString username = "", QString password = "");
    void cutConnection();
    bool isConnected();

private slots:
    void onConnect();
    void onDisconnect();
    void onMessageRecieved(const QByteArray &data, QMqttTopicName name);

signals:
    void connected();
    void disconnected();
    void messageRecieved(const QByteArray&, QMqttTopicName);
};

#endif // MQTTDIALOG_H
