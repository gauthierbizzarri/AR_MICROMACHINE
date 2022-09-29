
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include <QJsonArray>
#include <QTimer>

#include "game_engine.h"
#include "game_checkpoint.h"
#include "game_circle.h"
#include "game_rectangle.h"
#include "game_player.h"

// ////////////////////////////////////////////////////////////////////////////
// Constructor - GameEngine
// ////////////////////////////////////////////////////////////////////////////

GameEngine::GameEngine(QObject *parent)
    : QObject{parent}
{

    // Init

    this->m_ihm = new IHM();
    this->m_client = new Client(this);

    this->m_map = nullptr;

    // Connect

    connect(this->m_client, &Client::receivedMap, this, &GameEngine::map);
    connect(this->m_client, &Client::receivedPlayerRegister, this, &GameEngine::playerRegister);
    connect(this->m_client, &Client::receivedPlayerControl, this, &GameEngine::playerControl);

    // Post init

    this->m_running = true;
    this->m_ihm->show();
    this->sendProperties();
}

GameEngine::~GameEngine() {

    delete this->m_ihm;
    delete this->m_client;

}

// ////////////////////////////////////////////////////////////////////////////
// Methods
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// Slots - GameEngine
// ////////////////////////////////////////////////////////////////////////////

void GameEngine::map(QJsonObject json) {
    qDebug() << "map : " << json;

    // handle map size

    if(this->m_map == nullptr)
        this->m_map = new GameMap(this, json["mapWidth"].toInt(), json["mapHeight"].toInt());
    else
        this->m_map->setSize(json["mapWidth"].toInt(), json["mapHeight"].toInt());

    this->m_map->deleteCheckpointsNObstacles();

    // handle checkpoints
    {
        QJsonArray checkpoints = json["checkpoints"].toArray();
        for(int i = 0; i < checkpoints.size(); i++) {
            auto checkpoint = checkpoints[i].toObject();
            this->m_map->insert(QString::number(checkpoint["id"].toInt()), new GameCheckpoint(this->m_ihm, checkpoint["x"].toInt(), checkpoint["y"].toInt()));
        }
    }
    // handle obstacle
    {
        QJsonArray obstacles = json["obstacles"].toArray();
        for(int i = 0; i < obstacles.size(); i++) {
            auto obstacle = obstacles[i].toObject();
            int id = obstacle["id"].toInt();

            if(id %2)
                this->m_map->insert(QString::number(id), new GameCircle(this->m_ihm, obstacle["x"].toInt(), obstacle["y"].toInt()));
            else
                this->m_map->insert(QString::number(id), new GameRectangle(this->m_ihm, obstacle["x"].toInt(), obstacle["y"].toInt(), obstacle["angle"].toDouble()));
        }
    }

    this->m_ihm->m_mapView->update();
}

void GameEngine::playerRegister(QJsonObject json) {

    QString uuid = json["uuid"].toString();
    bool alreadyLog = false;

    for(GameEntity* entity : this->m_entitites) {
        GamePlayer* player = qobject_cast<GamePlayer*>(entity);
        if(player != nullptr) {
            if(player->getUuid() == uuid) {
                alreadyLog = true;
                break;
            }
        }
    }

    if(!alreadyLog) {
        this->m_entitites.append(new GamePlayer(this->m_ihm, uuid,
                json["pseudo"].toString(), json["controller"].toString(),
                json["vehicle"].toString(), json["team"].toInt()));
    }

}

void GameEngine::playerControl(QJsonObject json) {
    qDebug() << "control : " << json;
}

void GameEngine::sendProperties() {

    if(this->m_running) {
        QTimer::singleShot(1000, this, &GameEngine::sendProperties);
        this->m_client->publishProperties(this->m_properties);
    }

}

void GameEngine::update() {



}
