#ifndef AI_H
#define AI_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QtMath>
#include <QtAlgorithms>

#include "map.h"
#include "game.h"
#include "player.h"

class AI : public QObject
{
    Q_OBJECT
private:
    QUuid m_uuid;
    QUuid::StringFormat m_uuidStrFormat;

    Map* m_map;
    Game* m_game;

    Player* m_player;
    Checkpoint* m_nextCheckpoint;
    int m_lastCheckpointId;

    QList<Checkpoint> m_checkpoints;

public:
    explicit AI(QUuid, QUuid::StringFormat, QObject *parent = nullptr);
    void set_checkpoints();
    void process();
    static bool compareCheckpoints(const Checkpoint &, const Checkpoint &);

signals:
    void controllerInputs(QJsonDocument);

public slots:
    void mapDatas(QJsonDocument);
    void playerDatas(QJsonDocument);
};

#endif // AI_H
