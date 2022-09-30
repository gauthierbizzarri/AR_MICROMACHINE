#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

class Entity
{
private:
    int m_x;
    int m_y;
    double m_angle;

public:
    explicit Entity(int x, int y, double angle);

    void set_x(int);
    int get_x();

    void set_y(int);
    int get_y();

    void set_angle(double);
    double get_angle();
};

#endif // ENTITY_H
