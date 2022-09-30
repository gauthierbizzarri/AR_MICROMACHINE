#ifndef MONQTMQTT_H
#define MONQTMQTT_H

#include <QDebug>
#include <QJsonDocument>
#include <QMqttClient>

class monqtmqtt: public QObject
{
    Q_OBJECT
    QMqttClient* m_client;
public:
    monqtmqtt();
    void Connect();
    void QtMqttPub(QString m, QByteArray message);

public slots:
    void messageReceived(const QByteArray &message, const QMqttTopicName &topic );
    void online();
    void pubmap(QJsonDocument);

signals:
    void conn();
};

#endif // MONQTMQTT_H
