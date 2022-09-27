#include "mainwindow.h"

#include <point.h>
#include <maptranslator.h>
#include <QJsonObject>
#include <QStringView>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray points;
    QJsonObject point;
    point.insert("id", 0);
    point.insert("x", 100);
    point.insert("y", 200);
    points.append(point);
    obj.insert("checkpoints", points);
    QJsonArray obsts;
    QJsonObject obst;
    obst.insert("id", 0);
    obst.insert("x", 200);
    obst.insert("y", 200);
    obst.insert("angle", 0.4);
    obsts.append(obst);
    obj.insert("obstacles", obsts);
    doc.setObject(obj);

    MapTranslator trans(doc);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1000, 1000);
    QGraphicsView* view = new QGraphicsView();
    MapInfo* info = trans.translate();
    for(uint i = 0; i<info->getPoints().size(); i++)
    {
        scene->addItem(info->getPoints()[i]);
    }
    for(uint i = 0; i<info->getObstacles().size(); i++)
    {
        scene->addItem(info->getObstacles()[i]);
    }
    QHBoxLayout* layout = new QHBoxLayout(this);
    view->setScene(scene);
    layout->addWidget(view);
    setLayout(layout);
}

MainWindow::~MainWindow()
{
}

