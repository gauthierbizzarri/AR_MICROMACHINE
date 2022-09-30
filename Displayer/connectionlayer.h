#ifndef CONNECTIONLAYER_H
#define CONNECTIONLAYER_H

#include <displayview.h>
#include <mqttdialog.h>
#include <QVBoxLayout>
#include <QLabel>
#include <appstate.h>

class ConnectionLayer : public DisplayView
{
    Q_OBJECT
private:
    QVBoxLayout* root;
    MqttDialog* diag;
    QLabel* label;

    QString id;
    QString pseudo;
    QString vehicle;
    bool loaded;
public:
    ConnectionLayer(MqttDialog *diag, QWidget* parent = nullptr);
    void init(QString id, QString pseudo, QString vehicle, QString host, int port, QString username, QString password);

private slots:
    void onConnect();
    void backBtnClicked(bool);
    void onMessage(const QByteArray &data, QMqttTopicName name);

};

#endif // CONNECTIONLAYER_H
