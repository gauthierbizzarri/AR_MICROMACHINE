#ifndef VEHICLEPROPERTIES_H
#define VEHICLEPROPERTIES_H

#include <QJsonObject>

class VechicleProperties{
public:
    /**
     * @brief maxSpeed maximum speed of the vehicle in m/s
     */
    int maxSpeed = 2;
    /**
     * @brief acceleration acceleration of the vehicle in m/s2
     */
    float acceleration = 0.4;
    /**
     * @brief weight weight of the vehicle in kg
     */
    int weight = 600;
    /**
     * @brief steeringAngle steering angle of the vehicle in radians
     */
    float steeringAngle = 1;

    int width = 20;
    int height = 30;

    void fill(QJsonObject data)
    {
        maxSpeed = data["maxSpeed"].toInt();
        acceleration = data["acceleration"].toDouble();
        weight = data["weight"].toInt();
        steeringAngle = data["steeringAngle"].toDouble();
        width = data["width"].toInt();
        height = data["height"].toInt();
    }
};

#endif // VEHICLEPROPERTIES_H
