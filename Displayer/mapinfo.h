#ifndef MAPINFO_H
#define MAPINFO_H

#include <checkpoint.h>
#include <rectangle.h>
#include <player.h>

#include <circle.h>

#include <banana.h>
#include <rocket.h>
#include <bomb.h>

#include <QVBoxLayout>
#include <QDebug>

class MapInfo: public QObject{
    Q_OBJECT
private:
    /**
     * @brief objects mapping of object on the map, with their id
     */
    std::map<QString, CircuitElement*> mobjects;
    std::map<QString, CircuitElement*> mitems;
public:
    MapInfo():QObject(){
        mobjects = std::map<QString, CircuitElement*>();
        mitems = std::map<QString, CircuitElement*>();
    }

    ~MapInfo(){
        clear();
        clear_players();
        clear_items();
    }

    /**
     * @brief addObject adds an object to the map
     * @param id id of the object
     * @param object object to be added
     */
    void addObject(QString id, CircuitElement* object){
        mobjects.insert_or_assign(id, object);
        emit objectAdded(object);
    }

    void addItem(QString id, CircuitElement* object){
        mitems.insert_or_assign(id, object);
        emit objectAdded(object);
    }

    /**
     * @brief removeObject removed an object from the map
     * @param id id of the object to be removed
     */
    void removeObject(QString id){
        if(mobjects.count(id)==0) return;
        CircuitElement* object = mobjects[id];
        mobjects.erase(id);
        emit objectRemoved(object);
        delete(object);
    }


    /**
     * @brief contains check if the map holds an object with the given id
     * @param id id of the object
     * @return true if objec on the map, false overwise
     */
    bool contains(QString id)
    {
        return mobjects.count(id);
    }

    /**
     * @brief getObjects gets all the objects on the map
     * @return the map object representing the mapping between ids and objects
     */
    std::map<QString, CircuitElement*> getObjects() const
    {
        return mobjects;
    }

    /**
     * @brief getObject gets the object corresponding to the id
     * @param id id of the object
     * @return the object, or nullptr
     */
    CircuitElement* getObject(QString id)
    {
        return mobjects[id];
    }

    /**
     * @brief clear removes all objects from the map
     */
    void clear()
    {
        for(const auto &pair : std::map<QString, CircuitElement*>(mobjects))
        {
            qDebug()<<"CLEAR ELEMENT"<<pair.second->property("TYPE");
            if ( (pair.second->property("TYPE")!="Player") )
            this->removeObject(pair.first);
        }
    }

    void clear_players()
        {

        for(const auto &pair : std::map<QString, CircuitElement*>(mobjects))
        {
            qDebug()<<"CLEAR ELEMENT"<<pair.second->property("TYPE");
            if (  (pair.second->property("TYPE")=="Player") )
            this->removeObject(pair.first);
        }


        }


    void clear_items()
        {

        for(const auto &pair : std::map<QString, CircuitElement*>(mitems))
            delete(mitems[pair.first]);


        }


signals:
    void objectAdded(CircuitElement* object);
    void objectRemoved(CircuitElement* object);
};

#endif // MAPINFO_H
