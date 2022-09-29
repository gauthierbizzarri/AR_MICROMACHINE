#ifndef AI_H
#define AI_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class AI : public QObject
{
    Q_OBJECT
private:
    QUuid m_uuid;
    QUuid::StringFormat m_uuidStrFormat;

    QJsonDocument m_map;
    QJsonDocument m_game;

    QJsonObject m_player;
    QJsonObject m_checkpoint;

public:
    explicit AI(QUuid, QUuid::StringFormat, QObject *parent = nullptr);
    void process();

signals:
    void controllerInputs(QJsonDocument);

public slots:
    void mapDatas(QJsonDocument);
    void playerDatas(QJsonDocument);
};

#endif // AI_H
