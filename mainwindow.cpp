#include "mainwindow.h"

#include <checkpoint.h>
#include <maptranslator.h>
#include <QJsonObject>
#include <QStringView>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(1920, 1080);
    //applyOptions(Options::getInstance());
    //connect(Options::getInstance(), &Options::update, this, &MainWindow::applyOptions);
    minfo = new MapInfo();

    mclient = new QMqttClient(this);
    connect(mclient, &QMqttClient::connected, this, &MainWindow::onMqttConnected);
    connect(mclient, &QMqttClient::connected, this, &MainWindow::setupStartScreenView);
    connect(mclient, &QMqttClient::messageReceived, this, &MainWindow::onMessageRecieve);
    setupMqtt();
}

MainWindow::~MainWindow()
{
    currentLayer->deleteLater();
    minfo->deleteLater();
    mclient->deleteLater();
}

void MainWindow::setupMqtt()
{
    mclient->setHostname("10.3.0.218");
    mclient->setPort(1883);
    mclient->setUsername("phoenix");
    mclient->setPassword("ardent");

    mclient->connectToHost();
}

void MainWindow::setupStartScreenView()
{
    mstartLayer = new StartScreenLayer(this);
    currentLayer = mstartLayer;
    connect(mstartLayer, &StartScreenLayer::gameStart, this, &MainWindow::setupGameView);
    connect(mstartLayer, &StartScreenLayer::exit, this, &MainWindow::close);
    connect(mstartLayer, &StartScreenLayer::options, this, &MainWindow::setupOptionsView);
    setCentralWidget(mstartLayer);
}

void MainWindow::setupGameView()
{
    mgameLayer = new GameScreen(this);
    currentLayer = mgameLayer;
    connect(minfo, &MapInfo::objectAdded, mgameLayer, &GameScreen::onObjectAdded);
    connect(minfo, &MapInfo::objectRemoved, mgameLayer, &GameScreen::onObjectRemoved);
    setCentralWidget(mgameLayer);
}

void MainWindow::setupOptionsView()
{
    moptions = new OptionsLayer(this);
    currentLayer = moptions;
    connect(moptions, &OptionsLayer::optionsDone, this, &MainWindow::setupStartScreenView);
    setCentralWidget(moptions);
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
        qDebug()<<doc<<"\n";
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


void MainWindow::applyOptions(const Options *options)
{
    if(options->fullScreen)
    {
        showFullScreen();
    }
    else
    {
        showNormal();
    }
}



