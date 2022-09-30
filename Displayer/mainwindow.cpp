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
    START_MENU_VIEW = 0;
    rootLayout->addWidget(setupGameView());
    GAME_VIEW = 1;
    rootLayout->addWidget(setupOptionsView());
    OPTIONS_VIEW = 2;
    rootLayout->addWidget(setupRegister());
    REGISTER_VIEW = 3;
    rootLayout->addWidget(setupConnectionLayer());
    CONNECTING_VIEW = 4;
    root->setLayout(rootLayout);

    currentstate = AppState::STARTMENU;

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
    connect(start, &DisplayView::stateChange, this, &MainWindow::onStateChange);
    return start;
}

GameScreen* MainWindow::setupGameView()
{
    GameScreen* screen = new GameScreen(this);
    connect(screen, &DisplayView::stateChange, this, &MainWindow::onStateChange);
    connect(minfo, &MapInfo::objectAdded, screen, &GameScreen::onObjectAdded);
    connect(minfo, &MapInfo::objectRemoved, screen, &GameScreen::onObjectRemoved);
    connect(minfo, &MapInfo::sizeChanged, screen, &GameScreen::onSizeChange);
    return screen;
}

OptionsLayer* MainWindow::setupOptionsView()
{
    OptionsLayer* options = new OptionsLayer(this);
    connect(options, &DisplayView::stateChange, this, &MainWindow::onStateChange);
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
    connect(layer, &ConnectionLayer::stateChange, this, &MainWindow::onStateChange);
    layer->init(mclient);
    return layer;
}

void MainWindow::showView(int i)
{
    ((DisplayView*)rootLayout->widget(i))->setPrevious(currentstate);
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
    onStateChange(AppState::CONNECTED);
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
    onStateChange(AppState::REGISTERED);
    this->id = id;
    this->pseudo = pseudo;
    this->vehicle = vehicle;
    mclient->establishConnection(host, port, username, password);
    emit registered(id);
}

void MainWindow::onMqttDisconnected()
{
    onStateChange(AppState::DISCONNECTED);
}

void MainWindow::onStateChange(AppState state)
{
    switch(state)
    {
        case AppState::STARTMENU:
            ((StartScreenLayer*)rootLayout->widget(START_MENU_VIEW))->outGame();
            showView(START_MENU_VIEW);
        break;
        case AppState::OPTIONS:
            showView(OPTIONS_VIEW);
        break;
        case AppState::STARTED:
            showView(REGISTER_VIEW);
        break;
        case AppState::REGISTERED:
            showView(CONNECTING_VIEW);
        break;
        case AppState::PLAYED:
            emit paused(false);
            showView(GAME_VIEW);
        break;
        case AppState::PAUSED:
            emit paused(true);
            showView(START_MENU_VIEW);
        break;
        case AppState::DISCONNECTED:
            showView(CONNECTING_VIEW);
        break;
        case AppState::CONNECTED:
            showView(GAME_VIEW);
        break;
        case AppState::QUITED:
            close();
        break;
        default:
        break;
    }
    currentstate = state;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit quitting();
    event->accept();
}

