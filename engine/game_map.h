#ifndef GAMEMAP_H
#define GAMEMAP_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QMap>
#include "game_map_object.h"

// ////////////////////////////////////////////////////////////////////////////
// Class
// ////////////////////////////////////////////////////////////////////////////

class GameMap : public QObject
{
    Q_OBJECT

    int m_width;
    int m_height;
    QMap<QString, GameMapObject*> m_objects;

public:
    explicit GameMap(QObject *parent, int width, int height);

    void setSize(int width, int height);
    void insert(QString uid, GameMapObject* object);
    void deleteCheckpointsNObstacles();
    QList<QString> getKeys();

signals:

};

// ////////////////////////////////////////////////////////////////////////////
//
// ////////////////////////////////////////////////////////////////////////////

#endif // GAMEMAP_H
