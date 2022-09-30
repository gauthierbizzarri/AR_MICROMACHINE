
// ////////////////////////////////////////////////////////////////////////////
// Class MapView
// ////////////////////////////////////////////////////////////////////////////

#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QDebug>
#include "ihm.h"
#include "game_map_object.h"

// ////////////////////////////////////////////////////////////////////////////
// Class MapView
// ////////////////////////////////////////////////////////////////////////////

MapView::MapView(QWidget *parent) : QWidget(parent) {

    this->setMinimumSize(600, 600);
    this->setMaximumSize(600, 600);

    this->m_scene = new QGraphicsScene(this);
    this->m_scene->setSceneRect(0, 0, 600, 600);

    this->m_view = new QGraphicsView(this);
    this->m_view->setScene(this->m_scene);

    this->m_group_player = new QGraphicsItemGroup();
    this->m_group_default = new QGraphicsItemGroup();

    this->m_scene->setBackgroundBrush(Qt::darkYellow);
    this->m_scene->addItem(this->m_group_player);
    this->m_scene->addItem(this->m_group_default);
}

MapView::~MapView() {

}

void MapView::update() {

    // remove everything from the group

    for(auto item : this->m_group_default->childItems())
        this->m_group_default->removeFromGroup(item);

    // add everything that need to be added

    for(int i = 0; i < gameObjects.length(); i++) {
        //qDebug() << gameObjects[i];
        this->m_group_default->addToGroup(gameObjects[i]->getItem());
    }
}

// ////////////////////////////////////////////////////////////////////////////
// Class TabView
// ////////////////////////////////////////////////////////////////////////////

TabView::TabView(QWidget *parent) {

}

TabView::~TabView() {

}

// ////////////////////////////////////////////////////////////////////////////
// Class IHM
// ////////////////////////////////////////////////////////////////////////////

IHM::IHM(QWidget *parent)
    : QMainWindow(parent)
{

    QHBoxLayout* layout = new QHBoxLayout();
    this->m_mapView = new MapView(this);
    this->m_tabView = new TabView(this);

    layout->addWidget(this->m_mapView);
    layout->addWidget(this->m_tabView);
    layout->setMargin(10);

    QWidget* root = new QWidget();
    root->setLayout(layout);

    this->setCentralWidget(root);

}

IHM::~IHM()
{
}

