#include "game.h"

Game::Game(QJsonObject game)
{
    foreach (const auto player, game["players"].toArray()) {
        m_players.append(Player(player.toObject()));
    }

    foreach (const auto item, game["obstacles"].toArray()) {
        m_items.append(Item(item.toObject()));
    }
}

QList<Player> Game::get_players() {
    return m_players;
}

QList<Item> Game::get_items() {
    return m_items;
}

Game Game::fromJson(QJsonDocument jsonGame) {
    return Game(jsonGame.object());
}
