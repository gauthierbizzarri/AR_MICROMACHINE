
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include "ihm_map.h"
#include "game_map_object.h"

// ////////////////////////////////////////////////////////////////////////////
// Defines
// ////////////////////////////////////////////////////////////////////////////

#define MAP_SIZE 1000
#define VIEW_SIZE 800

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

IHM_Map::IHM_Map(QWidget *parent)
    : QWidget{parent}
{

    this->setMinimumSize(VIEW_SIZE +4, VIEW_SIZE +4);
    this->setMaximumSize(VIEW_SIZE +4, VIEW_SIZE +4);

    // Init scene

    this->m_scene = new QGraphicsScene(this);
    this->m_scene->setSceneRect(0, 0, MAP_SIZE, MAP_SIZE);

    for(int i = 1; i < 10; i++) {
        this->m_scene->addLine(0, i*MAP_SIZE/10, MAP_SIZE, i*MAP_SIZE/10);
        this->m_scene->addLine(i*MAP_SIZE/10, 0, i*MAP_SIZE/10, MAP_SIZE);
    }

    this->m_group_player = new QGraphicsItemGroup();
    this->m_group_default = new QGraphicsItemGroup();

    this->m_scene->setBackgroundBrush(Qt::darkGreen);
    this->m_scene->addItem(this->m_group_player);
    this->m_scene->addItem(this->m_group_default);

    // Init view

    this->m_view = new QGraphicsView(this);
    this->m_view->setScene(this->m_scene);
    this->m_view->setMinimumSize(VIEW_SIZE +4, VIEW_SIZE +4);
    this->m_view->setMaximumSize(VIEW_SIZE +4, VIEW_SIZE +4);
    this->m_view->scale(1.0 *VIEW_SIZE/MAP_SIZE, 1.0 *VIEW_SIZE/MAP_SIZE);

}

void IHM_Map::update() {

    // remove everything from the group

    for(auto item : this->m_group_default->childItems())
        this->m_group_default->removeFromGroup(item);

    // add everything that need to be added

    for(int i = 0; i < gameObjects.length(); i++) {
        //qDebug() << gameObjects[i];
        this->m_group_default->addToGroup(gameObjects[i]->getItem());
    }
}
