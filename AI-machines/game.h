#ifndef GAME_H
#define GAME_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "player.h"
#include "item.h"

class Game
{
private:
    QList<Player> m_players;
    QList<Item> m_items;

public:
    Game(QJsonObject);

    QList<Player> get_players();
    QList<Item> get_items();

    static Game fromJson(QJsonDocument);
};

#endif // GAME_H
