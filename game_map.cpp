
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include "game_map.h"

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

GameMap::GameMap(QObject *parent, int width, int height)
    : QObject{parent}, m_width(width), m_height(height)
{

    this->m_objects.keys();

}

// ////////////////////////////////////////////////////////////////////////////
// Methods
// ////////////////////////////////////////////////////////////////////////////

void GameMap::setSize(int width, int height) {
    this->m_width = width;
    this->m_height = height;
}

void GameMap::insert(QString uid, GameMapObject* object) {

    this->m_objects.insert(uid, object);

}

void GameMap::deleteCheckpointsNObstacles() {

    for(const auto key : this->m_objects.keys())
    {
        if(key.size() <= 3 ) {
            qDebug() << "remove" << key;
            delete this->m_objects.take(key);
        }
    }

}

QList<QString> GameMap::getKeys() {

    return this->m_objects.keys();
}
