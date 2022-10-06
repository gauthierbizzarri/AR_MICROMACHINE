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
#include <QVector>
#include <opencv2/stitching.hpp>
#include <QPolygon>
#include <QtMath>





#include <QObject>

class Traitement_Image : public QObject
{
    Q_OBJECT
    QJsonArray checkpoints;
    QJsonArray obstacles;
    QJsonObject map;
public:
    explicit Traitement_Image(QObject *parent = nullptr);


public slots:
    void rect();
    void constjson(int id , int x,int y, float angle ,int width,int height);

signals:
    void jsonmap(QJsonDocument);

};

#endif // TRAITEMENT_IMAGE_H
