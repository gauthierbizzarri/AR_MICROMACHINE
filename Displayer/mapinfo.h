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

    QSize size;
public:
    MapInfo();

    ~MapInfo();

    void setSize(int width, int height);

    /**
     * @brief addObject adds an object to the map
     * @param id id of the object
     * @param object object to be added
     */
    void addObject(QString id, CircuitElement* object);
    
    void addItem(QString id, CircuitElement* object);

    /**
     * @brief removeObject removed an object from the map
     * @param id id of the object to be removed
     */
    void removeObject(QString id);

    /**
     * @brief contains check if the map holds an object with the given id
     * @param id id of the object
     * @return true if objec on the map, false overwise
     */
    bool contains(QString id);

    /**
     * @brief getObjects gets all the objects on the map
     * @return the map object representing the mapping between ids and objects
     */
    std::map<QString, CircuitElement*> getObjects() const;

    /**
     * @brief getObject gets the object corresponding to the id
     * @param id id of the object
     * @return the object, or nullptr
     */
    CircuitElement* getObject(QString id);

    /**
     * @brief clear removes all objects from the map
     */
    void clear();

    void clear_players();

    void clear_items();


signals:
    void objectAdded(CircuitElement* object);
    void objectRemoved(CircuitElement* object);
    void sizeChanged(QSize);
};

#endif // MAPINFO_H
