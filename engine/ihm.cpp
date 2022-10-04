
// ////////////////////////////////////////////////////////////////////////////
// Class MapView
// ////////////////////////////////////////////////////////////////////////////

#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QDebug>
#include "ihm.h"
#include "game_map_object.h"
#include "main.h"

// ////////////////////////////////////////////////////////////////////////////
// Class MapView
// ////////////////////////////////////////////////////////////////////////////

MapView::MapView(QWidget *parent) : QWidget(parent) {

    this->setMinimumSize(IHM_WIDTH*1.1, IHM_HEIGHT*1.1);
    this->setMaximumSize(IHM_WIDTH*1.1, IHM_HEIGHT*1.1);

    this->m_scene = new QGraphicsScene(this);
    this->m_scene->setSceneRect(0, 0, IHM_WIDTH, IHM_HEIGHT);

    this->m_view = new QGraphicsView(this);
    this->m_view->setScene(this->m_scene);
    this->m_view->setMinimumSize(IHM_WIDTH +4, IHM_HEIGHT +4);
    this->m_view->setMaximumSize(IHM_WIDTH +4, IHM_HEIGHT +4);

    for(int i = 1; i < 10; i++) {
        this->m_scene->addLine(0, i*IHM_HEIGHT/10, IHM_WIDTH, i*IHM_HEIGHT/10);
        this->m_scene->addLine(i*IHM_WIDTH/10, 0, i*IHM_WIDTH/10, IHM_HEIGHT);
    }

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
    this->setMinimumSize(IHM_WIDTH*1.1, IHM_HEIGHT*1.1);

}

IHM::~IHM()
{
}

