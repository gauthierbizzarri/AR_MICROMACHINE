
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QScrollArea>

#include "ihm_section_properties.h"
#include "game_engine.h"

inline void addSpaceToLayouts(QVBoxLayout* left, QVBoxLayout* right, int size, QWidget* parent) {
    left->addSpacing(size);
    right->addSpacing(size);
}

inline QLineEdit* addPropertyToLayouts(QVBoxLayout* left, QVBoxLayout* right, QString name, QWidget* parent) {
    auto lineEdit = new QLineEdit(parent);
    left->addWidget(new QLabel(name, parent));
    right->addWidget(lineEdit);
    return lineEdit;
}

IHM_SectionProperties::IHM_SectionProperties(QWidget *parent)
    : QWidget{parent}
{

    auto layoutRoot = new QVBoxLayout();
    auto layoutProperties = new QHBoxLayout();
    auto layoutPLeft = new QVBoxLayout();
    auto layoutPRight = new QVBoxLayout();
    auto layoutButtons = new QHBoxLayout();

    auto buttonLoad = new QPushButton(QString("Load"), this);
    buttonLoad->setToolTip("Affiche les propriétés actuel de la partie");
    auto buttonSave = new QPushButton(QString("Save"), this);
    buttonSave->setToolTip("Met à jour la partie avec les propriétés rentrées");

    auto scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    auto scrollInner = new QWidget(scrollArea);

    this->leLapNumber = addPropertyToLayouts(layoutPLeft, layoutPRight, "Lap Number", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 24, this);
    this->leCheckRadius = addPropertyToLayouts(layoutPLeft, layoutPRight, "Checkpoint Radius", this);
    this->leCircleRadius = addPropertyToLayouts(layoutPLeft, layoutPRight, "Circle Radius", this);
    this->leRectWidth = addPropertyToLayouts(layoutPLeft, layoutPRight, "Rectangle Width", this);
    this->leRectHeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Rectangle Height", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 24, this);
    this->leBananaNb = addPropertyToLayouts(layoutPLeft, layoutPRight, "Banana Number", this);
    this->leBananaRadius = addPropertyToLayouts(layoutPLeft, layoutPRight, "Banana Radius", this);
    this->leBananaCd = addPropertyToLayouts(layoutPLeft, layoutPRight, "Banana Cooldown", this);
    this->leBananaTtl = addPropertyToLayouts(layoutPLeft, layoutPRight, "Banana Time-to-live", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 8, this);
    this->leBombNb = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bomb Number", this);
    this->leBombRadius = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bomb Radius", this);
    this->leBombExRadius = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bomb Explosion Radius", this);
    this->leBombCd = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bomb Cooldown", this);
    this->leBombTtl = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bomb Time-to-live", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 8, this);
    this->leRocketNb = addPropertyToLayouts(layoutPLeft, layoutPRight, "Rocket Number", this);
    this->leRocketRadius = addPropertyToLayouts(layoutPLeft, layoutPRight, "Rocket Radius", this);
    this->leRocketCd = addPropertyToLayouts(layoutPLeft, layoutPRight, "Rocket Cooldown", this);
    this->leRocketSpeed = addPropertyToLayouts(layoutPLeft, layoutPRight, "Rocket Speed", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 24, this);
    this->leBikeSpeed = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bike Max Speed", this);
    this->leBikeAcc = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bike Acceleration", this);
    this->leBikeWeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bike Weight", this);
    this->leBikeSteering = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bike Steering Angle", this);
    this->leBikeWidth = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bike Width", this);
    this->leBikeHeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Bike height", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 8, this);
    this->leCarSpeed = addPropertyToLayouts(layoutPLeft, layoutPRight, "Car Max Speed", this);
    this->leCarAcc = addPropertyToLayouts(layoutPLeft, layoutPRight, "Car Acceleration", this);
    this->leCarWeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Car Weight", this);
    this->leCarSteering = addPropertyToLayouts(layoutPLeft, layoutPRight, "Car Steering Angle", this);
    this->leCarWidth = addPropertyToLayouts(layoutPLeft, layoutPRight, "Car Width", this);
    this->leCarHeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Car height", this);
    addSpaceToLayouts(layoutPLeft, layoutPRight, 8, this);
    this->leTruckSpeed = addPropertyToLayouts(layoutPLeft, layoutPRight, "Truck Max Speed", this);
    this->leTruckAcc = addPropertyToLayouts(layoutPLeft, layoutPRight, "Truck Acceleration", this);
    this->leTruckWeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Truck Weight", this);
    this->leTruckSteering = addPropertyToLayouts(layoutPLeft, layoutPRight, "Truck Steering Angle", this);
    this->leTruckWidth = addPropertyToLayouts(layoutPLeft, layoutPRight, "Truck Width", this);
    this->leTruckHeight = addPropertyToLayouts(layoutPLeft, layoutPRight, "Truck height", this);
    layoutProperties->addLayout(layoutPLeft);
    layoutProperties->addSpacing(24);
    layoutProperties->addLayout(layoutPRight);
    scrollInner->setLayout(layoutProperties);
    scrollArea->setWidget(scrollInner);

    layoutButtons->addWidget(buttonLoad);
    layoutButtons->addWidget(buttonSave);

    layoutRoot->addWidget(scrollArea);
    layoutRoot->addLayout(layoutButtons);

    this->setLayout(layoutRoot);

    connect(buttonLoad, &QPushButton::clicked, this, [this]() {
       GameProperties* prop = GameEngine::instance()->getProperties();

       this->leLapNumber->setText(QString::number(prop->lapsNb));

       this->leCheckRadius->setText(QString::number(prop->checkpointRadius));
       this->leCircleRadius->setText(QString::number(prop->circleRadius));
       this->leRectWidth->setText(QString::number(prop->rectangleWidth));
       this->leRectHeight->setText(QString::number(prop->rectangleHeight));

       this->leBananaNb->setText(QString::number(prop->bananaNb));
       this->leBananaRadius->setText(QString::number(prop->bananaRadius));
       this->leBananaCd->setText(QString::number(prop->bananaCd));
       this->leBananaTtl->setText(QString::number(prop->bananaTtl));

       this->leBombNb->setText(QString::number(prop->bombNb));
       this->leBombRadius->setText(QString::number(prop->bombSize));
       this->leBombExRadius->setText(QString::number(prop->bombExplostionSize));
       this->leBombCd->setText(QString::number(prop->bombCd));
       this->leBombTtl->setText(QString::number(prop->bombTtl));

       this->leRocketNb->setText(QString::number(prop->rocketNb));
       this->leRocketRadius->setText(QString::number(prop->rocketRadius));
       this->leRocketCd->setText(QString::number(prop->rocketCd));
       this->leRocketSpeed->setText(QString::number(prop->rocketSpeed));

       this->leBikeSpeed->setText(QString::number(prop->bike.maxSpeed));
       this->leBikeAcc->setText(QString::number(prop->bike.acceleration));
       this->leBikeWeight->setText(QString::number(prop->bike.weight));
       this->leBikeSteering->setText(QString::number(prop->bike.steeringAngle));
       this->leBikeWidth->setText(QString::number(prop->bike.width));
       this->leBikeHeight->setText(QString::number(prop->bike.height));

       this->leCarSpeed->setText(QString::number(prop->car.maxSpeed));
       this->leCarAcc->setText(QString::number(prop->car.acceleration));
       this->leCarWeight->setText(QString::number(prop->car.weight));
       this->leCarSteering->setText(QString::number(prop->car.steeringAngle));
       this->leCarWidth->setText(QString::number(prop->car.width));
       this->leCarHeight->setText(QString::number(prop->car.height));

       this->leTruckSpeed->setText(QString::number(prop->truck.maxSpeed));
       this->leTruckAcc->setText(QString::number(prop->truck.acceleration));
       this->leTruckWeight->setText(QString::number(prop->truck.weight));
       this->leTruckSteering->setText(QString::number(prop->truck.steeringAngle));
       this->leTruckWidth->setText(QString::number(prop->truck.width));
       this->leTruckHeight->setText(QString::number(prop->truck.height));
    });

    connect(buttonSave, &QPushButton::clicked, this, [this]() {
        GameProperties* prop = GameEngine::instance()->getProperties();

        prop->lapsNb = this->leLapNumber->text().toInt();

        prop->checkpointRadius = this->leCheckRadius->text().toInt();
        prop->circleRadius = this->leCircleRadius->text().toInt();
        prop->rectangleWidth = this->leRectWidth->text().toInt();
        prop->rectangleHeight = this->leRectHeight->text().toInt();

        prop->bananaNb = this->leBananaNb->text().toInt();
        prop->bananaRadius = this->leBananaRadius->text().toInt();
        prop->bananaCd = this->leBananaCd->text().toInt();
        prop->bananaTtl = this->leBananaTtl->text().toInt();

        prop->bombNb = this->leBombNb->text().toInt();
        prop->bombSize = this->leBombRadius->text().toInt();
        prop->bombExplostionSize = this->leBombExRadius->text().toInt();
        prop->bombCd = this->leBombCd->text().toInt();
        prop->bombTtl = this->leBombTtl->text().toInt();

        prop->rocketNb = this->leRocketNb->text().toInt();
        prop->rocketRadius = this->leRocketRadius->text().toInt();
        prop->rocketCd = this->leRocketCd->text().toInt();
        prop->rocketSpeed = this->leRocketSpeed->text().toInt();

        prop->bike.maxSpeed = this->leBikeSpeed->text().toInt();
        prop->bike.acceleration = this->leBikeAcc->text().toDouble();
        prop->bike.weight = this->leBikeWeight->text().toInt();
        prop->bike.steeringAngle = this->leBikeSteering->text().toDouble();
        prop->bike.width = this->leBikeWidth->text().toInt();
        prop->bike.height = this->leBikeHeight->text().toInt();

        prop->car.maxSpeed = this->leCarSpeed->text().toInt();
        prop->car.acceleration = this->leCarAcc->text().toDouble();
        prop->car.weight = this->leCarWeight->text().toInt();
        prop->car.steeringAngle = this->leCarSteering->text().toDouble();
        prop->car.width = this->leCarWidth->text().toInt();
        prop->car.height = this->leCarHeight->text().toInt();

        prop->truck.maxSpeed = this->leTruckSpeed->text().toInt();
        prop->truck.acceleration = this->leTruckAcc->text().toDouble();
        prop->truck.weight = this->leTruckWeight->text().toInt();
        prop->truck.steeringAngle = this->leTruckSteering->text().toDouble();
        prop->truck.width = this->leTruckWidth->text().toInt();
        prop->truck.height = this->leTruckHeight->text().toInt();

        for(GameMapObject* object : gameObjects) {
            object->updateProperties(prop);
        }
    });
}
