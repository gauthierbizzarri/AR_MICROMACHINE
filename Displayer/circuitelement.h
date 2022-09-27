#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#include <position.h>
#include <quuid.h>
#include <QWidget>
#include <QPaintEvent>

class CircuitElement: public QWidget
{
    Q_OBJECT
protected:
    int id;
    Position* pos;
    CircuitElement(QWidget* parent, int id, Position* pos):QWidget(parent){
        this->id = id;
        this->pos = pos;
    }
public:
    Position* getPosition(){
        return this->pos;
    }
    int getId(){
        return this->id;
    }
    virtual void paintEvent(QPaintEvent* event);
};

#endif // CIRCUITELEMENT_H
