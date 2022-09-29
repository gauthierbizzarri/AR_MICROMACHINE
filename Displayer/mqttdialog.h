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

    MqttDialog();
    ~MqttDialog();
    MqttDialog*  pub(QString name, QByteArray data);
    MqttDialog* sub(QString name);
    void establishConnection();

private slots:
    void onConnect();
    void onMessageRecieved(QByteArray data, QMqttTopicName name);

signals:
    void connected();
    void messageRecieved(QByteArray, QMqttTopicName);
};

#endif // MQTTDIALOG_H
