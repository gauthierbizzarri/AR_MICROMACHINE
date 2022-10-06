#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QJsonObject>
#include <QMap>
#include <QThread>
#include "ihm.h"
#include "client.h"
#include "game_properties.h"
#include "game_map.h"
#include "game_entity.h"
#include "game_checkpoint.h"

// ////////////////////////////////////////////////////////////////////////////
// Class
// ////////////////////////////////////////////////////////////////////////////

class GameEngine : public QObject
{
    Q_OBJECT

    static GameEngine* s_instance;

    bool m_running;

    IHM* m_ihm;
    Client* m_client;
    QList<GameEntity*> m_entitites;
    GameProperties m_properties;
    GameMap* m_map;

    GameCheckpoint* m_checkpoint;

    explicit GameEngine(QObject *parent = nullptr);

public:
    ~GameEngine();

    QJsonObject toJson();
    GameProperties* getProperties();
    static GameEngine* instance();


public slots:
    void map(QJsonObject object);
    void playerRegister(QJsonObject object);
    void playerControl(QJsonObject object);
    void loopProperties();
    void loopUpdate();
    void loopIA();

};

// ////////////////////////////////////////////////////////////////////////////
//
// ////////////////////////////////////////////////////////////////////////////

#endif // GAME_ENGINE_H
