#ifndef DISPLAYLAYER_H
#define DISPLAYLAYER_H

#include <QWidget>
#include <mainwindow.h>

class DisplayLayer : public QWidget
{
protected:
    MainWindow* parent;
    DisplayLayer(MainWindow* parent) : QWidget(parent){
        this->parent=parent;
    }
public:
    virtual void init() = 0;
};

#endif // DISPLAYLAYER_H
