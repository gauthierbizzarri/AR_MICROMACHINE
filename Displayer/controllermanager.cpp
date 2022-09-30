#include "controllermanager.h"
#include <QJsonDocument>

ControllerManager::ControllerManager(MqttDialog* client)
{
    connected = false;
    paused = false;

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
    connect(frame, &MainWindow::registered, this, &ControllerManager::onRegistered);
    connect(frame, &MainWindow::paused, this, &ControllerManager::onPaused);
    frame->installEventFilter(adapter);
}

void ControllerManager::onComputeThrotle(float power)
{
    base["power"] = power;
    sendee["power"] = power;
    sendControll(sendee);
}

void ControllerManager::onComputeStreering(float steering)
{
    sendee["angle"] = steering;
    sendControll(sendee);
}

void ControllerManager::onBombAction()
{
    QJsonObject buttons = sendee["buttons"].toObject();
    buttons["bomb"]=true;
    sendee["buttons"]=buttons;
    sendControll(sendee);
}

void ControllerManager::onBananaAction()
{
    QJsonObject buttons = sendee["buttons"].toObject();
    buttons["banana"]=true;
    sendee["buttons"]=buttons;
    sendControll(sendee);
}

void ControllerManager::onRocketAction()
{
    QJsonObject buttons = sendee["buttons"].toObject();
    buttons["rocket"]=true;
    sendee["buttons"]=buttons;
    sendControll(sendee);
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

void ControllerManager::onMqttConnected()
{
    connected = true;
}

void ControllerManager::sendControll(QJsonObject data)
{
    mclient->pub(MqttDialog::PLAYER_CONTROL, QJsonDocument(data).toJson());
    qDebug()<<data;
    sendee = QJsonObject(base);
}

void ControllerManager::onPaused(bool pause)
{
    paused = pause;
    if(pause)
    {
        base["power"] = 0;
    }
}
