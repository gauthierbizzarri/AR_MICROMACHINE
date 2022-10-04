
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include <QJsonArray>
#include <QTimer>
#include <QRandomGenerator>

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
    this->m_checkpoint = nullptr;

    // Connect

    connect(this->m_client, &Client::receivedMap, this, &GameEngine::map);
    connect(this->m_client, &Client::receivedPlayerRegister, this, &GameEngine::playerRegister);
    connect(this->m_client, &Client::receivedPlayerControl, this, &GameEngine::playerControl);

    // Post init

    this->m_running = true;
    this->m_ihm->show();

    this->loopProperties();
    this->loopUpdate();
    this->loopIA();
}

GameEngine::~GameEngine() {

    delete this->m_ihm;
    delete this->m_client;

}

// ////////////////////////////////////////////////////////////////////////////
// Methods
// ////////////////////////////////////////////////////////////////////////////

QJsonObject GameEngine::toJson() {

    QJsonObject json;

    json.insert(QString("elapsedTime"), QJsonValue(0));
    json.insert(QString("infoMessage"), QJsonValue("Serveur fonctionnel, et oui"));
    json.insert(QString("status"), QJsonValue("progress"));

    QJsonArray players;
    QJsonArray items;

    for(GameEntity* entity : this->m_entitites) {

        if(qobject_cast<GamePlayer*>(entity) != nullptr) {
            players.append(entity->toJson());
        }
        else {
            // Handle game item
        }

    }

    json.insert(QString("players"), players);
    json.insert(QString("items"), items);

    return json;
}
// ////////////////////////////////////////////////////////////////////////////
// Slots - GameEngine
// ////////////////////////////////////////////////////////////////////////////

void GameEngine::map(QJsonObject json) {
    //qDebug() << "map : " << json;

    GameCheckpoint* firstCP = nullptr;
    GameCheckpoint* currentCP = nullptr;

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
            auto gameCP = new GameCheckpoint(this->m_ihm, checkpoint["x"].toInt(), checkpoint["y"].toInt(), this->m_properties.checkpointRadius);
            gameCP->id = checkpoint["id"].toInt();

            if(firstCP == nullptr) {
                firstCP = gameCP;
                this->m_checkpoint = gameCP;
            }
            else {
                currentCP->next = gameCP;
            }
            currentCP = gameCP;

            this->m_map->insert(QString::number(checkpoint["id"].toInt()), gameCP);
        }
        currentCP->next = firstCP;
    }
    // handle obstacle
    {
        QJsonArray obstacles = json["obstacles"].toArray();
        for(int i = 0; i < obstacles.size(); i++) {
            auto obstacle = obstacles[i].toObject();
            int id = obstacle["id"].toInt();

            if(id %2 == 0)
                this->m_map->insert(QString::number(id), new GameCircle(this->m_ihm, obstacle["x"].toInt(), obstacle["y"].toInt(), this->m_properties.circleRadius));
            else
                this->m_map->insert(QString::number(id), new GameRectangle(this->m_ihm, obstacle["x"].toInt(), obstacle["y"].toInt(), obstacle["angle"].toDouble(), this->m_properties.rectangleWidth, this->m_properties.rectangleHeight));
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
        auto rand = QRandomGenerator::global();
        auto x = (rand->generate()*1.0 /rand->max()) *1000.0;
        auto y = (rand->generate()*1.0 /rand->max()) *1000.0;

        auto player = new GamePlayer(this->m_ihm, (int) x, (int) y, uuid,
                         json["pseudo"].toString().left(16), json["controller"].toString(),
                         json["vehicle"].toString(), json["team"].toInt());
        player->setCheckpoint(this->m_checkpoint);
        this->m_entitites.append(player);
        this->m_ihm->m_mapView->update();
    }

}

void GameEngine::playerControl(QJsonObject json) {
    //qDebug() << "control : " << json;

    QString uuid = json["uuid"].toString();
    ;
    json["power"];
    for(GameEntity* entity : this->m_entitites) {
        GamePlayer* player = qobject_cast<GamePlayer*>(entity);
        if(player != nullptr) {
            if(player->getUuid() == uuid) {
                //qDebug() << uuid << " control " << json;
                player->setSteering(json["angle"].toDouble());
                player->setPower(json["power"].toInt());
                break;
            }
        }
    }

}

void GameEngine::loopProperties() {

    if(this->m_running) {
        QTimer::singleShot(1000, this, &GameEngine::loopProperties);
        this->m_client->publishProperties(this->m_properties.toJson());
    }

}

void GameEngine::loopUpdate() {

    if(this->m_running) {
        QTimer::singleShot(50, this, &GameEngine::loopUpdate);

        for(GameEntity* entity : this->m_entitites) {
            entity->update();
        }

        for(GameEntity* entity : this->m_entitites) {
            entity->checkCollision();
        }

        this->m_client->publishGame(this->toJson());

    }
}

void GameEngine::loopIA() {

    if(this->m_running) {
        QTimer::singleShot(1000, this, &GameEngine::loopIA);

        this->m_client->publishMap();
    }

}

