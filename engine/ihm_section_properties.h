#ifndef IHM_SECTIONPROPERTIES_H
#define IHM_SECTIONPROPERTIES_H

#include <QWidget>
#include <QLineEdit>

class IHM_SectionProperties : public QWidget
{
    Q_OBJECT

    QLineEdit* leLapNumber;
    QLineEdit* leCheckRadius;
    QLineEdit* leCircleRadius;
    QLineEdit* leRectWidth;
    QLineEdit* leRectHeight;
    QLineEdit* leBananaNb;
    QLineEdit* leBananaRadius;
    QLineEdit* leBananaCd;
    QLineEdit* leBananaTtl;
    QLineEdit* leBombNb;
    QLineEdit* leBombRadius;
    QLineEdit* leBombExRadius;
    QLineEdit* leBombCd;
    QLineEdit* leBombTtl;
    QLineEdit* leRocketNb;
    QLineEdit* leRocketRadius;
    QLineEdit* leRocketCd;
    QLineEdit* leRocketSpeed;
    QLineEdit* leBikeSpeed;
    QLineEdit* leBikeAcc;
    QLineEdit* leBikeWeight;
    QLineEdit* leBikeSteering;
    QLineEdit* leBikeWidth;
    QLineEdit* leBikeHeight;
    QLineEdit* leCarSpeed;
    QLineEdit* leCarAcc;
    QLineEdit* leCarWeight;
    QLineEdit* leCarSteering;
    QLineEdit* leCarWidth;
    QLineEdit* leCarHeight;
    QLineEdit* leTruckSpeed;
    QLineEdit* leTruckAcc;
    QLineEdit* leTruckWeight;
    QLineEdit* leTruckSteering;
    QLineEdit* leTruckWidth;
    QLineEdit* leTruckHeight;

public:
    explicit IHM_SectionProperties(QWidget *parent);

signals:

};

#endif // IHM_SECTIONPROPERTIES_H
