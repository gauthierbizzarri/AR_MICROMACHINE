#ifndef GAME_PROPERTIES_H
#define GAME_PROPERTIES_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QJsonObject>

// ////////////////////////////////////////////////////////////////////////////
// Class
// ////////////////////////////////////////////////////////////////////////////

class VehicleProperties
{

public:

    int maxSpeed;           // m/s  - vitesse max
    float acceleration;     // m/s² - accélération
    int weight;             // kg   - poids
    float steeringAngle;    // rad  - angle de braquage
    int width;              // m    - largeur
    int height;             // m    - longueur

public:
    VehicleProperties();
    VehicleProperties(int v, float a, int we, float sa, int w, int h);

    QJsonObject toJson();
};

class GameProperties
{

public:

    int lapsNb;         // nombre de tour
    int teamNb;         // nombre de team

    int circleRadius;     // m - rayon des obstacles circulaire
    int rectangleWidth;   // m - largeur des obstacles rectangulaire
    int rectangleHeight;  // m - hauteur des obstacles rectangulaire
    int checkpointRadius; // m - rayon des checkpoints

    int bananaNb;           //     - nombre de banane au début de la partie
    int bananaCd;           // s   - temps avant qu'un joueur puisse réutiliser une banane
    int bananaTtl;          // s   - durée de vie d'une banane
    int bananaRadius;       // m   - rayon de la banane
    int bombNb;             //     - nombre de bombe au début de la partie
    int bombCd;             // s   - temps avant qu'un joueur puisse réutiliser une bombe
    int bombTtl;            // s   - durée avant qu'une bombe explose après qu'elle soit posé
    int bombSize;           // m   - rayon de la bombe
    int bombExplostionSize; // m   - rayon de l'explosion
    int rocketNb;           //     - nombre de missile au début de la partie
    int rocketCd;           // s   - temps avant qu'un joueur puisse réutiliser un missile
    int rocketSpeed;        // m/s - vitesse des missiles
    int rocketRadius;       // m   - rayon du missile


    VehicleProperties bike;
    VehicleProperties car;
    VehicleProperties truck;

public:
    GameProperties();

    QJsonObject toJson();

};

// ////////////////////////////////////////////////////////////////////////////
//
// ////////////////////////////////////////////////////////////////////////////

#endif // GAME_PROPERTIES_H
