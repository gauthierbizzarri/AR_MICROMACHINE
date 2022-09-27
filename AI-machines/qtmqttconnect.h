#ifndef QTMQTTCONNECT_H
#define QTMQTTCONNECT_H

#include <QObject>
#include <QtMqtt>

class QtMqttConnect : public QObject
{
    Q_OBJECT
public:
    QMqttClient m_client;
    explicit QtMqttConnect(QObject *parent = nullptr);

signals:

};

#endif // QTMQTTCONNECT_H
