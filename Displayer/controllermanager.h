#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <QMainWindow>
#include <QThread>
#include <QJsonObject>
#include <controlleradapter.h>
#include <mainwindow.h>
#include <QCoreApplication>

class ControllerManager : public QThread
{
    Q_OBJECT
private:
    QJsonObject base;
    QJsonObject sendee;
    QString uuid;
    bool running;
    bool connected;
    bool paused;
    MqttDialog* mclient;

    void delay(int ms)
    {
        QTime dieTime= QTime::currentTime().addMSecs(ms);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
public:
    ControllerManager(MqttDialog* client);

    void setup(MainWindow* frame, ControllerAdapter* adapter);
    void run() override;
    void stop();

signals:
    void controllComputed(QByteArray);

private slots:
    void onComputeThrotle(float);
    void onComputeStreering(float);
    void onBombAction();
    void onBananaAction();
    void onRocketAction();
    void onRegistered(QString);
    void onFrameClosed();
    void onMqttConnected();
    void sendControll(QByteArray data);
    void onPaused(bool);
};

#endif // CONTROLLERMANAGER_H
