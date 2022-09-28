#include "mainwindow.h"

#include <checkpoint.h>
#include <maptranslator.h>
#include <QJsonObject>
#include <QStringView>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    mscene = new QGraphicsScene();
    mscene->setSceneRect(0, 0, 1000, 1000);
    QGraphicsView* view = new QGraphicsView();

    minfo = new MapInfo();
    connect(minfo, &MapInfo::objectAdded, this, &MainWindow::onObjectAdded);
    connect(minfo, &MapInfo::objectRemoved, this, &MainWindow::onObjectRemoved);




    mclient = new QMqttClient(this);
    connect(mclient, &QMqttClient::connected, this, &MainWindow::onMqttConnected);
    connect(mclient, &QMqttClient::messageReceived, this, &MainWindow::onMessageRecieve);
    mclient->setHostname("10.3.0.218");
    mclient->setPort(1883);
    mclient->setUsername("phoenix");
    mclient->setPassword("ardent");

    mclient->connectToHost();

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
    mscene->removeItem(e);
}

void MainWindow::onObjectAdded(CircuitElement *e)
{
    mscene->addItem(e);
}

void MainWindow::onMqttConnected()
{
    mclient->subscribe(QMqttTopicFilter("/map"));
    mclient->subscribe(QMqttTopicFilter("/game"));
}

void MainWindow::onMessageRecieve(const QByteArray &message, const QMqttTopicName &topic)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(message, &error);
    if(error.error == QJsonParseError::NoError)
    {
        qDebug()<<"Message received"<<"\n";
        qDebug()<<"ON TOPIC"<<topic.name();
        qDebug()<<doc;
        if(topic.name() == "/map")
        {
            MapTranslator trans(minfo);
            //trans.info->clear();
            trans.update(doc);
        }
        if(topic.name() == "/game")
        {
            MapTranslator trans(minfo);
            //trans.info->clear();
            trans.update_players(doc);
        }
    }
    else
    {
        qDebug()<<"Error in string";
        qDebug()<<error.errorString();
    }
}

