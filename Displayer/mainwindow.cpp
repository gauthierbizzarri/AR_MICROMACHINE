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

    mscene = new QGraphicsScene();
    mscene->setSceneRect(0, 0, 1000, 1000);
    QGraphicsView* view = new QGraphicsView();

    minfo = new MapInfo();
    connect(minfo, &MapInfo::objectAdded, this, &MainWindow::onObjectAdded);

    MapTranslator trans(minfo);
    trans.update(doc);
    QHBoxLayout* layout = new QHBoxLayout(this);
    view->setScene(mscene);
    layout->addWidget(view);
    setLayout(layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onObjectRemoved(CircuitElement *e)
{
    qDebug()<<"removed "<<e->getId();
    mscene->removeItem(e);
}

void MainWindow::onObjectAdded(CircuitElement *e)
{
    qDebug()<<"added "<<e->getId();
    mscene->addItem(e);
}

