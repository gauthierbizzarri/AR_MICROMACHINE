#ifndef TRAITEMENT_IMAGE_H
#define TRAITEMENT_IMAGE_H
#include "opencv2/aruco/charuco.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QtDebug>
#include <vector>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>




#include <QObject>

class Traitement_Image : public QObject
{
    Q_OBJECT
public:
    explicit Traitement_Image(QObject *parent = nullptr);

public slots:
    void rect();

signals:
    void jsonmap(QJsonDocument);

};

#endif // TRAITEMENT_IMAGE_H
