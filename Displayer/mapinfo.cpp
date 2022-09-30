#include "mapinfo.h"


MapInfo::MapInfo():QObject(){
    mobjects = std::map<QString, CircuitElement*>();
    mitems = std::map<QString, CircuitElement*>();
}

MapInfo::~MapInfo(){
    clear();
    clear_players();
    clear_items();
}

void MapInfo::setSize(int width, int height)
{
    size = QSize(width, height);
    emit sizeChanged(size);
}

void MapInfo::addObject(QString id, CircuitElement* object){
    if(mobjects.count(id)>0) return;
    mobjects.insert_or_assign(id, object);
    emit objectAdded(object);
}

void MapInfo::addItem(QString id, CircuitElement* object){
    mitems.insert_or_assign(id, object);
    emit objectAdded(object);
}

void MapInfo::removeObject(QString id){
    if(mobjects.count(id)==0) return;
    CircuitElement* object = mobjects[id];
    mobjects.erase(id);
    emit objectRemoved(object);
    delete(object);
}

bool MapInfo::contains(QString id)
{
    return mobjects.count(id);
}

std::map<QString, CircuitElement*> MapInfo::getObjects() const
{
    return mobjects;
}

CircuitElement* MapInfo::getObject(QString id)
{
    return mobjects[id];
}

void MapInfo::clear()
{
    for(const auto &pair : std::map<QString, CircuitElement*>(mobjects))
    {
        if ( (pair.second->property("TYPE")!="Player") )
        this->removeObject(pair.first);
    }
}

void MapInfo::clear_players()
{
    for(const auto &pair : std::map<QString, CircuitElement*>(mobjects))
    {
        if (  (pair.second->property("TYPE")=="Player") )
            this->removeObject(pair.first);
    }

}

void MapInfo::clear_items()
{
    for(const auto &pair : std::map<QString, CircuitElement*>(mitems))
        removeObject(pair.first);
}
