#ifndef MAPINFO_H
#define MAPINFO_H

#include <checkpoint.h>
#include <rectangle.h>
#include <QVBoxLayout>
#include <QDebug>

class MapInfo: public QObject{
    Q_OBJECT
private:
    /**
     * @brief objects mapping of object on the map, with their id
     */
    std::map<QString, CircuitElement*> mobjects;
public:
    MapInfo():QObject(){
        mobjects = std::map<QString, CircuitElement*>();
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

    /**
     * @brief removeObject removed an object from the map
     * @param id id of the object to be removed
     */
    void removeObject(QString id){
        CircuitElement* object = mobjects[id];
        mobjects.erase(id);
        emit objectRemoved(object);
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
        for(std::map<QString, CircuitElement*>::iterator it = mobjects.begin(); it != mobjects.end(); ++it)
        {
            this->removeObject(it->first);
        }
    }

signals:
    void objectAdded(CircuitElement* object);
    void objectRemoved(CircuitElement* object);
};

#endif // MAPINFO_H
