#ifndef MAPINFO_H
#define MAPINFO_H

#include <point.h>
#include <obstacle.h>
#include <stdlib.h>
#include <QVBoxLayout>

class MapInfo: public QObject{
    Q_OBJECT
private:
    std::map<int, Point*> points;
    std::map<int, Obstacle*> obstacles;
public:
    MapInfo():QObject(){
        this->points = std::map<int, Point*>();
        this->obstacles = std::map<int, Obstacle*>();
    }

    void addPoint(Point* point){
        this->points.insert_or_assign(point->getId(), point);
        emit objectAdded(point);
    }

    void addObstacle(Obstacle* obstacle){
        this->obstacles.insert_or_assign(obstacle->getId(), obstacle);
        emit objectAdded(obstacle);
    }

    void removePoint(Point* point){
        this->points.erase(point->getId());
        emit objectRemoved(point);
    }

    void removeObstacle(Obstacle* obstacle){
        this->obstacles.erase(obstacle->getId());
        emit objectRemoved(obstacle);
    }

    bool containsPoint(int id)
    {
        return this->points.count(id);
    }

    bool containsObstacle(int id)
    {
        return this->obstacles.count(id);
    }

    void movePoint(int id, Position* newPos)
    {
        this->points[id]->setPosition(newPos);
    }

    void moveObstacle(int id, Position* newPos, float angle)
    {
        this->obstacles[id]->setPosition(newPos);
        this->obstacles[id]->setAngle(angle);
    }

    std::map<int, Point*> getPoints()
    {
        return this->points;
    }

    std::map<int, Obstacle*> getObstacles()
    {
        return this->obstacles;
    }

signals:
    void objectAdded(CircuitElement* object);
    void objectRemoved(CircuitElement* object);
};

#endif // MAPINFO_H
