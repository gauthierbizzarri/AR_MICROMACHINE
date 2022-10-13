#include "gameproperties.h"
#include <QJsonArray>

GameProperties* GameProperties::instance = nullptr;



GameProperties* GameProperties::getInstance()
{
    if(GameProperties::instance == nullptr)
    {
        GameProperties::instance = new GameProperties();
    }
    return GameProperties::instance;
}

void GameProperties::fill(QJsonObject data)
{
    lapsNb = data["lapsNb"].toInt();
    teamNb = data["teamNb"].toInt();
    circleRadius = data["circleRadius"].toInt();
    rectangleWidth = data["rectangleWidth"].toInt();
    rectangleHeight = data["rectangleHeight"].toInt();
    checkpointRadius = data["checkpointRadius"].toInt();
    bananaNb = data["bananaNb"].toInt();
    bananaCd = data["bananaCd"].toInt();
    bananaRadius = data["bananaRadius"].toInt();
    bananaTtl = data["bananaTtl"].toInt();
    bombNb = data["bombNb"].toInt();
    bombCd = data["bombCd"].toInt();
    bombRadius = data["bombRadius"].toInt();
    bombExplosionRadius = data["bombExplositionRadius"].toInt();
    bombTtl = data["bombTtl"].toInt();
    rocketNb = data["rocketNb"].toInt();
    rocketCd = data["rocketCd"].toInt();
    rocketRadius = data["rocketRadius"].toInt();
    rocketSpeed = data["rocketSpeed"].toInt();
    foreach(const QString& key, data["vehicleOptions"].toObject().keys()) {
        QJsonValue value = data["vehicleOptions"].toObject().value(key);
        VechicleProperties props;
        props.fill(value.toObject());
        vehicleProperties.insert_or_assign(key, props);
    }
}
