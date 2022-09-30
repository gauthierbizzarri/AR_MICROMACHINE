#include "mainwindow.h"

#include <checkpoint.h>
#include <maptranslator.h>
#include <QJsonObject>
#include <QStringView>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

MainWindow::MainWindow(MqttDialog* dialog, QWidget *parent)
    : QMainWindow(parent)
{

    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(1000, 1000);
    applyOptions(Options::getInstance());
    connect(Options::getInstance(), &Options::update, this, &MainWindow::applyOptions);
    minfo = new MapInfo();
    mclient = dialog;
    root = new QWidget();
    rootLayout = new QStackedLayout();
    rootLayout->addWidget(setupStartScreenView());
    rootLayout->addWidget(setupGameView());
    rootLayout->addWidget(setupOptionsView());
    rootLayout->addWidget(setupRegister());
    ConnectionLayer* conLayer = setupConnectionLayer();
    conLayer->setPrevious(3);
    rootLayout->addWidget(conLayer);
    root->setLayout(rootLayout);

    setCentralWidget(root);

    setupMqtt();

    showView(0);
}

MainWindow::~MainWindow()
{
    root->deleteLater();
    minfo->deleteLater();
}

void MainWindow::setupMqtt()
{
    connect(mclient, &MqttDialog::connected, this, &MainWindow::onMqttConnected);
    connect(mclient, &MqttDialog::disconnected, this, &MainWindow::onMqttDisconnected);
    connect(mclient, &MqttDialog::messageRecieved, this, &MainWindow::onMessageRecieve);
}

StartScreenLayer* MainWindow::setupStartScreenView()
{
    StartScreenLayer* start = new StartScreenLayer(this);
    connect(start, &StartScreenLayer::exit, this, &MainWindow::close);
    connect(start, &StartScreenLayer::gameStart, this, &MainWindow::playGame);
    connect(start, &StartScreenLayer::options, this, &MainWindow::showView);
    return start;
}

GameScreen* MainWindow::setupGameView()
{
    GameScreen* screen = new GameScreen(this);
    connect(screen, &GameScreen::pauseMenu, this, &MainWindow::pauseGame);
    connect(minfo, &MapInfo::objectAdded, screen, &GameScreen::onObjectAdded);
    connect(minfo, &MapInfo::objectRemoved, screen, &GameScreen::onObjectRemoved);
    connect(minfo, &MapInfo::sizeChanged, screen, &GameScreen::onSizeChange);
    return screen;
}

OptionsLayer* MainWindow::setupOptionsView()
{
    OptionsLayer* options = new OptionsLayer(this);
    connect(options, &OptionsLayer::optionsDone, this, &MainWindow::showView);
    return options;
}

RegisterLayer *MainWindow::setupRegister()
{
    RegisterLayer* layer = new RegisterLayer(this);
    connect(layer, &RegisterLayer::registered, this, &MainWindow::onRegistered);
    return layer;
}

ConnectionLayer *MainWindow::setupConnectionLayer()
{
    ConnectionLayer* layer = new ConnectionLayer(this);
    connect(layer, &ConnectionLayer::connectionDone, this, &MainWindow::showView);
    connect(layer, &ConnectionLayer::goBack, this, &MainWindow::backToStart);
    layer->init(mclient);
    return layer;
}

void MainWindow::showView(int i)
{
    ((DisplayView*)rootLayout->widget(i))->setPrevious(rootLayout->currentIndex());
    rootLayout->setCurrentIndex(i);
}

void MainWindow::onMqttConnected()
{
    mclient->sub(MqttDialog::MAP);
    mclient->sub(MqttDialog::GAME);
    QJsonObject data{
        {"uuid", id},
        {"pseudo", pseudo},
        {"controller", "keyboard"},
        {"vehicle", vehicle},
        {"team", "null"}
    };
    mclient->pub(MqttDialog::PLAYER_REGISTER, QJsonDocument(data).toJson());
    showView(1);
}

void MainWindow::onMessageRecieve(const QByteArray &message, const QMqttTopicName &topic)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(message, &error);
    if(error.error == QJsonParseError::NoError)
    {
        if(topic.name() == MqttDialog::MAP)
        {

            MapTranslator trans(minfo);
            trans.update(doc);
        }

        if(topic.name() == MqttDialog::GAME)
        {
            MapTranslator trans(minfo);
            trans.update_game(doc);
        }
    }
    else
    {
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

void MainWindow::onRegistered(QString id, QString pseudo, QString vehicle, QString host, int port, QString username, QString password)
{
    showView(4);
    this->id = id;
    this->pseudo = pseudo;
    this->vehicle = vehicle;
    mclient->establishConnection(host, port, username, password);
    emit registered(id);
}

void MainWindow::pauseGame(int display)
{
    emit paused(true);
    showView(display);
}

void MainWindow::playGame(int display)
{
    emit paused(false);
    showView(display);
}

void MainWindow::onMqttDisconnected()
{
    showView(4);
}

void MainWindow::backToStart(int)
{
    ((StartScreenLayer*)rootLayout->widget(0))->outGame();
    showView(0);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit quitting();
    event->accept();
}

