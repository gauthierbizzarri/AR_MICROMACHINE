
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include "game_properties.h"

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

GameProperties::GameProperties()
{
    this->lapsNb = 3;
    this->teamNb = 0;

    this->circleRadius = 5; // m
    this->rectangleWidth = 10; // m
    this->rectangleHeight = 2; // m
    this->checkpointRadius = 5; // m

    this->bananaNb = 10;
    this->bananaCd = 1; // s
    this->bananaTtl = 60; // s
    this->bombNb = 10;
    this->bombCd = 1; // s
    this->bombTtl = 1; // s
    this->rocketNb = 3;
    this->rocketCd = 1; // s
    this->rocketSpeed = 160; // m/s

    this->bikeSpeed = 55; // m/s
    this->bikeAcceleration = 6.9; // m/s²
    this->bikeWeight = 180; // kg
    this->bikeSteering = 1.6; // rad
    this->carSpeed = 69; // m/s
    this->carAcceleration = 5.0; // m/s²
    this->carWeight = 1460; // kg
    this->carSteering = 1.2; // rad
    this->truckSpeed = 44; // m/s
    this->truckAcceleration = 3.3; // m/s²
    this->truckWeight = 35000; // kg
    this->truckSteering = 1; // rad
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
    json.insert(QString("bombNb"), QJsonValue(this->bombNb));
    json.insert(QString("rocketNb"), QJsonValue(this->rocketNb));
    json.insert(QString("bananaCd"), QJsonValue(this->bananaCd));
    json.insert(QString("bombCd"), QJsonValue(this->bombCd));
    json.insert(QString("rocketCd"), QJsonValue(this->rocketCd));
    json.insert(QString("rocketSpeed"), QJsonValue(this->rocketSpeed));
    json.insert(QString("bananaTtl"), QJsonValue(this->bananaTtl));
    json.insert(QString("bombTtl"), QJsonValue(this->bombTtl));

    QJsonObject vehicles;

    QJsonObject bike;
    bike.insert(QString("maxSpeed"), QJsonValue(this->bikeSpeed));
    bike.insert(QString("acceleration"), QJsonValue(this->bikeAcceleration));
    bike.insert(QString("weight"), QJsonValue(this->bikeWeight));
    bike.insert(QString("steeringAngle"), QJsonValue(this->bikeSteering));
    QJsonObject car;
    car.insert(QString("maxSpeed"), QJsonValue(this->carSpeed));
    car.insert(QString("acceleration"), QJsonValue(this->carAcceleration));
    car.insert(QString("weight"), QJsonValue(this->carWeight));
    car.insert(QString("steeringAngle"), QJsonValue(this->carSteering));
    QJsonObject truck;
    truck.insert(QString("maxSpeed"), QJsonValue(this->truckSpeed));
    truck.insert(QString("acceleration"), QJsonValue(this->truckAcceleration));
    truck.insert(QString("weight"), QJsonValue(this->truckWeight));
    truck.insert(QString("steeringAngle"), QJsonValue(this->truckSteering));

    vehicles.insert(QString("bike"), bike);
    vehicles.insert(QString("car"), car);
    vehicles.insert(QString("truck"), truck);

    json.insert(QString("vehicleOptions"), vehicles);

    return json;
}
