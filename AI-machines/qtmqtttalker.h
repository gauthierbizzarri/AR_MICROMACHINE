#ifndef QTMQTTTALKER_H
#define QTMQTTTALKER_H

#include <QObject>
#include <QtMqtt>

class QtMqttTalker : public QObject
{
    Q_OBJECT
public:
    QMqttClient* m_client;

    QMqttTopicFilter m_topicFilter;
    QMqttTopicName m_topicName;

    quint8 m_qos;

    explicit QtMqttTalker(QObject *parent = nullptr);
    void QtMqttSub();
    void QtMqttPub(QByteArray message);
    void QtMqttDebug();

signals:
    void jsonAI(QJsonDocument);

private slots:
    void TalkerMessageReceived(const QByteArray &, const QMqttTopicName &);

    void TalkerConnected();
    void TalkerDebugState(QMqttClient::ClientState);
    void TalkerDebugError(QMqttClient::ClientError);
};

#endif // QTMQTTTALKER_H
