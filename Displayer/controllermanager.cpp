#include "controllermanager.h"
#include <QJsonDocument>

ControllerManager::ControllerManager(MqttDialog* client)
{
    running = true;
    connected = false;
    paused = false;
    connect(this, &ControllerManager::finished, this, &QObject::deleteLater);

    mclient = client;
    connect(mclient, &MqttDialog::connected, this, &ControllerManager::onMqttConnected);

}

void ControllerManager::setup(MainWindow *frame, ControllerAdapter *adapter)
{
    connect(adapter, &ControllerAdapter::computeThrotle, this, &ControllerManager::onComputeThrotle);
    connect(adapter, &ControllerAdapter::computeStreering, this, &ControllerManager::onComputeStreering);
    connect(adapter, &ControllerAdapter::bananaAction, this, &ControllerManager::onBananaAction);
    connect(adapter, &ControllerAdapter::bombAction, this, &ControllerManager::onBombAction);
    connect(adapter, &ControllerAdapter::rocketAction, this, &ControllerManager::onRocketAction);
    connect(frame, &MainWindow::quitting, this, &ControllerManager::onFrameClosed);
    connect(frame, &MainWindow::registered, this, &ControllerManager::onRegistered);
    connect(frame, &MainWindow::paused, this, &ControllerManager::onPaused);
    connect(this, &ControllerManager::controllComputed, this, &ControllerManager::sendControll);
    frame->installEventFilter(adapter);
}

void ControllerManager::run()
{
    while(running)
    {
        delay(1000);
        if(!base.empty() && connected && !paused)
        {
            emit controllComputed(QJsonDocument(sendee).toJson());
            sendee = QJsonObject(base);
        }
    }
}

void ControllerManager::stop()
{
    running = false;
}

void ControllerManager::onComputeThrotle(float power)
{
    base["power"] = power;
}

void ControllerManager::onComputeStreering(float steering)
{
    sendee["angle"] = steering;
}

void ControllerManager::onBombAction()
{
    QJsonObject buttons = sendee["buttons"].toObject();
    buttons["bomb"]=true;
    sendee["buttons"]=buttons;
}

void ControllerManager::onBananaAction()
{
    QJsonObject buttons = sendee["buttons"].toObject();
    buttons["banana"]=true;
    sendee["buttons"]=buttons;
}

void ControllerManager::onRocketAction()
{
    QJsonObject buttons = sendee["buttons"].toObject();
    buttons["rocket"]=true;
    sendee["buttons"]=buttons;
}

void ControllerManager::onRegistered(QString playerUuid)
{
    uuid = playerUuid;
    base = {
        {"uuid", uuid},
        {"angle", 0},
        {"power", 0},
        {"buttons",
         QJsonObject{
            {"banana", false},
            {"bomb", false},
            {"rocket", false}
         }
        }
    };
    sendee = QJsonObject(base);
}

void ControllerManager::onFrameClosed()
{
    running=false;
}

void ControllerManager::onMqttConnected()
{
    connected = true;
}

void ControllerManager::sendControll(QByteArray data)
{
    mclient->pub(MqttDialog::PLAYER_CONTROL, data);
}

void ControllerManager::onPaused(bool pause)
{
    paused = pause;
    if(pause)
    {
        base["power"] = 0;
    }
}
