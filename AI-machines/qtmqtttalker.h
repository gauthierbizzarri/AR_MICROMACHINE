#ifndef QTMQTTTALKER_H
#define QTMQTTTALKER_H

#include <QObject>
#include <QtMqtt>

class QtMqttTalker : public QObject
{
    Q_OBJECT
public:
    QUuid m_uuid;

    QMqttClient* m_client;

    QMqttTopicFilter m_topicProperties;
    QMqttTopicName m_topicRegister;

    QMqttTopicFilter m_topicGame;
    QMqttTopicName m_topicController;

    quint8 m_qos;

    explicit QtMqttTalker(QObject *parent = nullptr);
    void QtMqttSub();
    void QtMqttPub(QMqttTopicName, QByteArray);

    void QtMqttProperties(QJsonDocument);
    void QtMqttGame(QJsonDocument);

    void QtMqttDebug();

signals:
    void jsonAI(QJsonDocument);

private slots:
    void TalkerMessageReceived(const QByteArray &, const QMqttTopicName &);

    void TalkerConnected();
    void TalkerDebugState(QMqttClient::ClientState);
    void TalkerDebugError(QMqttClient::ClientError);

    void TalkerRegister();

public slots:
    void TalkerController(QJsonDocument);
};

#endif // QTMQTTTALKER_H
