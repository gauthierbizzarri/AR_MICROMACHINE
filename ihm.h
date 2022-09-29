#ifndef IHM_H
#define IHM_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>

// ////////////////////////////////////////////////////////////////////////////
// Class MapView
// ////////////////////////////////////////////////////////////////////////////

class MapView : public QWidget
{
    Q_OBJECT

    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QGraphicsItemGroup* m_group_player; // item which are players
    QGraphicsItemGroup* m_group_default; // item which are not players

public:
    MapView(QWidget *parent);
    ~MapView();

public slots:
    void update();

};

// ////////////////////////////////////////////////////////////////////////////
// Class TabView
// ////////////////////////////////////////////////////////////////////////////

class TabView : public QWidget
{
    Q_OBJECT

public:
    TabView(QWidget *parent);
    ~TabView();
};

// ////////////////////////////////////////////////////////////////////////////
// Class RankingView
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// Class PropertyView
// ////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
// Class IHM
// ////////////////////////////////////////////////////////////////////////////

class IHM : public QMainWindow
{
    Q_OBJECT

public:

    QPushButton* m_button;

    MapView* m_mapView;
    TabView* m_tabView;

public:
    IHM(QWidget *parent = nullptr);
    ~IHM();

};

// ////////////////////////////////////////////////////////////////////////////
//
// ////////////////////////////////////////////////////////////////////////////

#endif // IHM_H
