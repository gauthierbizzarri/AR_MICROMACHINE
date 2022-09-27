#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include <position.h>
#include <quuid.h>
#include <QWidget>
#include <QPaintEvent>
#include <QGraphicsItem>

class CircuitElement : public QGraphicsObject
{
protected:
    int id;
    Position* pos;
    CircuitElement(int id, Position* pos, QGraphicsItem* parent = nullptr):QGraphicsObject(parent){
        this->id = id;
        this->pos = pos;
        this->setPos(pos->getX(), pos->getY());
    }
public:
    Position* getPosition(){
        return this->pos;
    }
    void setPosition(Position* pos)
    {
        this->pos = pos;
        this->setPos(pos->getX(), pos->getY());
    }
    int getId(){
        return this->id;
    }
    ~CircuitElement()
    {
        delete this->pos;
    }
};

#endif // CIRCUITELEMENT_H
