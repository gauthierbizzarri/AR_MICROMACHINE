#include "entity.h"

Entity::Entity(int x, int y, double angle)
{
    m_x = x;
    m_y = y;
    m_angle = angle;
}

void Entity::set_x(int x) {
    m_x = x;
}
int Entity::get_x() {
    return m_x;
}

void Entity::set_y(int y) {
    m_y = y;
}
int Entity::get_y() {
    return m_y;
}

void Entity::set_angle(double angle) {
    m_angle = angle;
}
double Entity::get_angle() {
    return m_angle;
}
