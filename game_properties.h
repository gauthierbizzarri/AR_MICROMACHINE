#ifndef GAME_PROPERTIES_H
#define GAME_PROPERTIES_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QJsonObject>

// ////////////////////////////////////////////////////////////////////////////
// Class
// ////////////////////////////////////////////////////////////////////////////

class GameProperties
{

public:

    int lapsNb;         // nombre de tour
    int teamNb;         // nombre de team

    float circleRadius;     // m - rayon des obstacles circulaire
    float rectangleWidth;   // m - largeur des obstacles rectangulaire
    float rectangleHeight;  // m - hauteur des obstacles rectangulaire
    float checkpointRadius; // m - rayon des checkpoints

    int bananaNb;       //     - nombre de banane au début de la partie
    int bananaCd;       // s   - temps avant qu'un joueur puisse réutiliser une banane
    int bananaTtl;      // s   - durée de vie d'une banane
    int bombNb;         //     - nombre de bombe au début de la partie
    int bombCd;         // s   - temps avant qu'un joueur puisse réutiliser une bombe
    int bombTtl;        // s   - durée avant qu'une bombe explose après qu'elle soit posé
    int rocketNb;       //     - nombre de missile au début de la partie
    int rocketCd;       // s   - temps avant qu'un joueur puisse réutiliser un missile
    int rocketSpeed;    // m/s - vitesse des missiles

    int bikeSpeed;           // m/s  - vitesse des motos
    float bikeAcceleration;  // m/s² - accélération des motos
    int bikeWeight;          // kg   - poids des motos
    float bikeSteering;      // rad  - angle de braquage des motos
    int carSpeed;            // m/s  - vitesse des voitures
    float carAcceleration;   // m/s² - accélération des voitures
    int carWeight;           // kg   - poids des voitures
    float carSteering;       // rad  - angle de braquage des voitures
    int truckSpeed;          // m/s  - vitesse des camions
    float truckAcceleration; // m/s² - accélération des camions
    int truckWeight;         // kg   - poids des camions
    float truckSteering;     // rad  - angle de braquage des camions

public:
    GameProperties();

    QJsonObject toJson();

};

// ////////////////////////////////////////////////////////////////////////////
//
// ////////////////////////////////////////////////////////////////////////////

#endif // GAME_PROPERTIES_H
