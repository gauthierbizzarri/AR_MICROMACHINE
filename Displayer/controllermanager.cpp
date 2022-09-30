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
    sendControll();
}

void ControllerManager::onComputeStreering(float steering)
{
    base["angle"] = steering;
    sendControll();
}

void ControllerManager::onBombAction()
{
    QJsonObject buttons = base["buttons"].toObject();
    buttons["bomb"]=true;
    base["buttons"]=buttons;
    sendControll();
}

void ControllerManager::onBananaAction()
{
    QJsonObject buttons = base["buttons"].toObject();
    buttons["banana"]=true;
    base["buttons"]=buttons;
    sendControll();
}

void ControllerManager::onRocketAction()
{
    QJsonObject buttons = base["buttons"].toObject();
    buttons["rocket"]=true;
    base["buttons"]=buttons;
    sendControll();
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
}

void ControllerManager::onMqttConnected()
{
    connected = true;
}

void ControllerManager::sendControll()
{
    mclient->pub(MqttDialog::PLAYER_CONTROL, QJsonDocument(base).toJson());
}

void ControllerManager::onPaused(bool pause)
{
    paused = pause;
    if(pause)
    {
        base["power"] = 0;
    }
}
