#ifndef MAPINFO_H
#define MAPINFO_H

#include <point.h>
#include <obstacle.h>
#include <stdlib.h>

class MapInfo{
private:
    std::vector<Point*> points;
    std::vector<Obstacle*> obstacles;
public:
    MapInfo(std::vector<Point*> points, std::vector<Obstacle*> obstacles){
        this->points = points;
        this->obstacles = obstacles;
    }
    MapInfo(){
        this->points = std::vector<Point*>();
        this->obstacles = std::vector<Obstacle*>();
    }

    void addPoint(Point* point){
        this->points.push_back(point);
    }

    void addObstacle(Point* point){
        this->points.push_back(point);
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
