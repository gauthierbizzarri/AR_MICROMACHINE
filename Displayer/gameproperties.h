#ifndef GAMEPROPERTIES_H
#define GAMEPROPERTIES_H

#include <QString>
#include <vehicleproperties.h>
#include <map>

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
    float circleRadius = 30;
    /**
     * @brief rectangleWidth width of rectangle obstacles in meters
     */
    float rectangleWidth = 30;
    /**
     * @brief rectangleHeight height of rectangle obstacles in meters
     */
    float rectangleHeight = 30;
    /**
     * @brief checkpointRadius radius of checkpoints in meters
     */
    float checkpointRadius = 10;

    /**
     * @brief bananaNb number of banana powerups for each player at start, -1 for infinity
     */
    int bananaNb = -1;
    /**
     * @brief bananaCd cooldown of the banana powerup, -1 for instant recharge, in ms
     */
    int bananaCd = -1;
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
    /**
     * @brief rocketSpeed rocket powerup speed in m/s
     */
    int rocketSpeed = 150;

    std::map<QString, VechicleProperties> vehicleProperties = {
        {"car", VechicleProperties()},
        {"motorbike", VechicleProperties()},
        {"truck", VechicleProperties()}
    };

    static GameProperties* getInstance()
    {
        if(GameProperties::instance == nullptr)
        {
            GameProperties::instance = new GameProperties();
        }
        return GameProperties::instance;
    }

private:
    static GameProperties* instance;
    GameProperties(){};
};

#endif // GAMEPROPERTIES_H
