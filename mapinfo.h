#ifndef MAPINFO_H
#define MAPINFO_H

#include <checkpoint.h>
#include <rectangle.h>
#include <stdlib.h>
#include <QVBoxLayout>
#include <QDebug>

class MapInfo: public QObject{
    Q_OBJECT
private:
    std::map<QString, CircuitElement*> objects;
public:
    MapInfo():QObject(){
        this->objects = std::map<QString, CircuitElement*>();
    }

    void addObject(QString id, CircuitElement* object){
        this->objects.insert_or_assign(id, object);
        emit objectAdded(object);
    }

    void removeObject(QString id){
        CircuitElement* object = this->objects[id];
        this->objects.erase(id);
        emit objectRemoved(object);
    }

    bool contains(QString id)
    {
        return this->objects.count(id);
    }

    std::map<QString, CircuitElement*> getObjects()
    {
        return this->objects;
    }

    CircuitElement* getObject(QString id)
    {
        return this->objects[id];
    }

    void clear()
    {
        for(std::map<QString, CircuitElement*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it)
        {
            if (it->second->property("TYPE")=="Circle" || it->second->property("TYPE")=="Checkpoint" )
            this->removeObject(it->first);
        }
    }
    void clear_players()
    {
        for(std::map<QString, CircuitElement*>::iterator it = this->objects.begin(); it != this->objects.end(); ++it)
        {
            if (it->second->property("TYPE")=="Player")
            this->removeObject(it->first);
        }

    }

signals:
    void objectAdded(CircuitElement* object);
    void objectRemoved(CircuitElement* object);
};

#endif // MAPINFO_H
