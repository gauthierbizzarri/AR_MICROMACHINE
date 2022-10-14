
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include "game_properties.h"

// ////////////////////////////////////////////////////////////////////////////
// VehicleProperties
// ////////////////////////////////////////////////////////////////////////////

VehicleProperties::VehicleProperties()
{

}

VehicleProperties::VehicleProperties(int v, float a, int we, float sa, int w, int h)
    : maxSpeed(v), acceleration(a), weight(we), steeringAngle(sa), width(w), height(h)
{

}

QJsonObject VehicleProperties::toJson()
{
    QJsonObject json;

    json.insert(QString("maxSpeed"), QJsonValue(this->maxSpeed));
    json.insert(QString("acceleration"), QJsonValue(this->acceleration));
    json.insert(QString("weight"), QJsonValue(this->weight));
    json.insert(QString("steeringAngle"), QJsonValue(this->steeringAngle));
    json.insert(QString("width"), QJsonValue(this->width));
    json.insert(QString("height"), QJsonValue(this->height));

    return json;
}

// ////////////////////////////////////////////////////////////////////////////
// GameProperties
// ////////////////////////////////////////////////////////////////////////////

GameProperties::GameProperties()
{
    this->lapsNb = 3;
    this->teamNb = 0;

    this->circleRadius = 20; // m
    this->rectangleWidth = 10; // m
    this->rectangleHeight = 40; // m
    this->checkpointRadius = 10; // m

    this->bananaNb = 10;
    this->bananaCd = 1; // s
    this->bananaTtl = 60; // s
    this->bananaRadius = 5; // m
    this->bombNb = 10;
    this->bombCd = 1; // s
    this->bombTtl = 2; // s
    this->bombSize = 5; // m
    this->bombExplostionSize = 50; // m
    this->rocketNb = 3;
    this->rocketCd = 1; // s
    this->rocketSpeed = 160; // m/s
    this->rocketRadius = 5; // m

    this->bike = VehicleProperties(55, 6.9, 180, 1.6, 10, 20);
    this->car = VehicleProperties(69, 5.0, 1460, 1.2, 20, 40);
    this->truck = VehicleProperties(44, 3.3, 35000, 1, 30, 90);

}

QJsonObject GameProperties::toJson() {
    QJsonObject json;

    json.insert(QString("lapsNb"), QJsonValue(this->lapsNb));
    json.insert(QString("teamNb"), QJsonValue(this->teamNb));

    json.insert(QString("circleRadius"), QJsonValue(this->circleRadius));
    json.insert(QString("rectangleWidth"), QJsonValue(this->rectangleWidth));
    json.insert(QString("rectangleHeight"), QJsonValue(this->rectangleHeight));
    json.insert(QString("checkpointRadius"), QJsonValue(this->checkpointRadius));

    json.insert(QString("bananaNb"), QJsonValue(this->bananaNb));
    json.insert(QString("bananaCd"), QJsonValue(this->bananaCd));
    json.insert(QString("bananaTtl"), QJsonValue(this->bananaTtl));
    json.insert(QString("bananaRadius"), QJsonValue(this->bananaRadius));
    json.insert(QString("bombNb"), QJsonValue(this->bombNb));
    json.insert(QString("bombTtl"), QJsonValue(this->bombTtl));
    json.insert(QString("bombCd"), QJsonValue(this->bombCd));
    json.insert(QString("bombRadius"), QJsonValue(this->bombSize));
    json.insert(QString("bombExplosionRadius"), QJsonValue(this->bombExplostionSize));
    json.insert(QString("rocketSpeed"), QJsonValue(this->rocketSpeed));
    json.insert(QString("rocketCd"), QJsonValue(this->rocketCd));
    json.insert(QString("rocketNb"), QJsonValue(this->rocketNb));
    json.insert(QString("rocketRadius"), QJsonValue(this->rocketRadius));

    QJsonObject vehicles;

    vehicles.insert(QString("bike"), this->bike.toJson());
    vehicles.insert(QString("car"), this->car.toJson());
    vehicles.insert(QString("truck"), this->truck.toJson());

    json.insert(QString("vehicleOptions"), vehicles);

    return json;
}
