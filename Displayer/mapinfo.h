#ifndef MAPINFO_H
#define MAPINFO_H

#include <point.h>
#include <obstacle.h>
#include <stdlib.h>
#include <QVBoxLayout>

class MapInfo: public QVBoxLayout{
    Q_OBJECT
private:
    std::vector<Point*> points;
    std::vector<Obstacle*> obstacles;
public:
    MapInfo(){
        this->points = std::vector<Point*>();
        this->obstacles = std::vector<Obstacle*>();
    }

    void addPoint(Point* point){
        this->addWidget(point);
        this->points.push_back(point);
    }

    void addObstacle(Obstacle* obstacle){
        this->addWidget(obstacle);
        this->obstacles.push_back(obstacle);
    }

    std::vector<Point*> getPoints()
    {
        return this->points;
    }

    std::vector<Obstacle*> getObstacles()
    {
        return this->obstacles;
    }
};

#endif // MAPINFO_H
