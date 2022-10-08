#ifndef IHM_MAP_H
#define IHM_MAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include "game_entity.h"

class IHM_Map : public QWidget
{

    Q_OBJECT

    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QGraphicsItemGroup* m_group_entity; // item which are players
    QGraphicsItemGroup* m_group_map; // item which are not players

public:
    explicit IHM_Map(QWidget *parent = nullptr);

    void update();
    void addEntity(GameEntity* entity);
    void removeEntity(GameEntity* entity);

};

#endif // IHM_MAP_H
