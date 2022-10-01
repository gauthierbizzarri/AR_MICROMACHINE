#include "resourceloader.h"
#include <QDebug>

ResourceLoader* ResourceLoader::instance = nullptr;

ResourceLoader::ResourceLoader()
{
    resources.insert("missing_texture", QImage(":/ressources/missing_texture.jpg"));
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
    resources.insert("power:banana", QImage(":/ressources/banana_power.png"));
    resources.insert("power:bomb", QImage(":/ressources/bomb_power.png"));
    resources.insert("power:rocket", QImage(":/ressources/rocket_power.png"));

    animations.insert("missing_texture", new QMovie(":/ressources/missing_texture.jpg"));
    animations.insert("ui:start:background", new QMovie(":/ressources/start_background.gif"));
}

ResourceLoader *ResourceLoader::getInstance()
{
    if(instance == nullptr)
    {
        instance = new ResourceLoader();
    }
    return instance;
}

QImage ResourceLoader::getImage(QString id)
{
    if(!resources.contains(id))
    {
        qDebug()<<"failed to load texture"<<id;
        return resources["missing_texture"];
    }
    return resources[id];
}

QMovie* ResourceLoader::getAnimation(QString id)
{
    if(!animations.contains(id))
    {
        qDebug()<<"failed to load animation"<<id;
        return animations["missing_texture"];
    }
    return animations[id];
}
