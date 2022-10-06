#ifndef IHM_MAP_H
#define IHM_MAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>

class IHM_Map : public QWidget
{

    Q_OBJECT

    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QGraphicsItemGroup* m_group_player; // item which are players
    QGraphicsItemGroup* m_group_default; // item which are not players

public:
    explicit IHM_Map(QWidget *parent = nullptr);

    void update();

};

#endif // IHM_MAP_H
