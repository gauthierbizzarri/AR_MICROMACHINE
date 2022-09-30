#include "resourceloader.h"

ResourceLoader* ResourceLoader::instance = nullptr;

ResourceLoader::ResourceLoader()
{
    resources.insert("missing_texture", QImage(":ressources/missing_texture.png"));
    resources.insert("vehicle:default", QImage(":/ressources/car.png"));
    resources.insert("vehicle:car:red", QImage(":/ressources/red_car.png"));
    resources.insert("vehicle:car:blue", QImage(":/ressources/blue_car.png"));
    resources.insert("vehicle:car:green", QImage(":/ressources/green_car.png"));
    resources.insert("vehicle:truck:red", QImage(":/ressources/red_truck.png"));
    resources.insert("vehicle:truck:blue", QImage(":/ressources/blue_truck.png"));
    resources.insert("vehicle:truck:green", QImage(":/ressources/green_catruck.png"));
    resources.insert("vehicle:bike:red", QImage(":/ressources/red_bike.png"));
    resources.insert("vehicle:bike:blue", QImage(":/ressources/blue_bike.png"));
    resources.insert("vehicle:bike:green", QImage(":/ressources/green_bike.png"));
}

ResourceLoader *ResourceLoader::getInstance()
{
    if(instance == nullptr)
    {
        instance = new ResourceLoader();
    }
    return instance;
}

QImage ResourceLoader::get(QString id)
{
    if(!resources.contains(id)) return resources["missing_texture"];
    return resources[id];
}
