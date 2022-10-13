#ifndef PLAYER_H
#define PLAYER_H

#include <game/utils/position.h>
#include <game/mapobjects/circuitelement.h>
#include <QPainter>

class Player : public CircuitElement
{
public:
    /**
     * @brief Circle graphical representation of a circle obstacle
     * @param x x central position of the circle
     * @param y y central position of the circle
     * @param parent graphical item's parent
     */
    static const QString BIKE;
    static const QString CAR;
    static const QString TRUCK;

    Player(int x, int y, float angle, QGraphicsItem* parent = nullptr);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void set_data(QColor color0, int team, int speed, QString vehicule);
    QImage get_vehicle();
    QString get_color(QColor color);
private :
    QColor color;
    int team;
    int speed;
    QString vehicule;
};

#endif // PLAYER_H
