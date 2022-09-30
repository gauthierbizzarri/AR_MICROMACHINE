#ifndef GAMEPROPERTIES_H
#define GAMEPROPERTIES_H

#include <QString>
#include <game/utils/properties/vehicleproperties.h>
#include <map>
#include <game/mapobjects/player/player.h>
#include <QJsonObject>

class GameProperties
{

public:

    /**
     * @brief lapsNb number of laps
     */
    int lapsNb = 3;
    /**
     * @brief teamNb number of teams
     */
    int teamNb = 0;

    /**
     * @brief circleRadius the radius of circle obstacles in meters
     */
    int circleRadius = 30;
    /**
     * @brief rectangleWidth width of rectangle obstacles in meters
     */
    int rectangleWidth = 30;
    /**
     * @brief rectangleHeight height of rectangle obstacles in meters
     */
    int rectangleHeight = 30;
    /**
     * @brief checkpointRadius radius of checkpoints in meters
     */
    int checkpointRadius = 10;

    /**
     * @brief bananaNb number of banana powerups for each player at start, -1 for infinity
     */
    int bananaNb = -1;
    /**
     * @brief bananaCd cooldown of the banana powerup, -1 for instant recharge, in ms
     */
    int bananaCd = -1;
    int bananaRadius = 10;
    /**
     * @brief bananaTtl lifetime of a thrown banana
     */
    int bananaTtl = -1;
    /**
     * @brief bombNb number of bombs for each player at start, -1 for infinity
     */
    int bombNb = -1;
    /**
     * @brief bombCd cooldown of the bomb powerup, -1 for instant recharge, in ms
     */
    int bombCd = -1;
    int bombRadius = 10;
    int bombExplosionRadius = 20;
    /**
     * @brief bombTtl time before a bomb explode, -1 for instant explosion (kamikaze mode)
     */
    int bombTtl = -1;
    /**
     * @brief rocketNb number of rocket powerups for each player at start, -1 for infinity
     */
    int rocketNb = -1;
    /**
     * @brief rocketCd cooldown of the rocket powerup, -1 for instant recharge, in ms
     */
    int rocketCd = -1;
    int rocketRadius = 10;
    /**
     * @brief rocketSpeed rocket powerup speed in m/s
     */
    int rocketSpeed = 150;

    std::map<QString, VechicleProperties> vehicleProperties = {
        {Player::CAR, VechicleProperties()},
        {Player::BIKE, VechicleProperties()},
        {Player::TRUCK, VechicleProperties()}
    };

    static GameProperties* getInstance();

    void fill(QJsonObject data);

private:
    static GameProperties* instance;
    GameProperties(){};
};

#endif // GAMEPROPERTIES_H
