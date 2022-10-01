#include "startscreenlayer.h"
#include <game/utils/resourceloader.h>
#include <game/ui/animatedbackground.h>

StartScreenLayer::StartScreenLayer(QWidget* parent):DisplayView(parent)
{
    int buttonwidth = 200;
    int buttonheight= 100;
    QString style = "QPushButton{ border: 5px solid #9B7D5B; border-radius:25px; background-color : rgba(255, 206, 150, 0.6); } QPushButton:hover{background-color : rgba(255, 206, 150, 0.9)} QPushButton:target{background-color : rgba(170, 138, 100, 1)}";
    ingame = false;
    mroot = new QVBoxLayout(this);
    mstart = new QPushButton("Start game");
    mstart->setFixedWidth(buttonwidth);
    mstart->setFixedHeight(buttonheight);
    mstart->setStyleSheet(style);
    connect(mstart, &QPushButton::clicked, this, &StartScreenLayer::onStartClicked);
    mroot->addWidget(mstart);

    moptions = new QPushButton("Options");
    moptions->setFixedWidth(buttonwidth);
    moptions->setFixedHeight(buttonheight);
    moptions->setStyleSheet(style);
    connect(moptions, &QPushButton::clicked, this, &StartScreenLayer::onOptionClicked);
    mroot->addWidget(moptions);

    mquit = new QPushButton("Quit game");
    mquit->setFixedWidth(buttonwidth);
    mquit->setFixedHeight(buttonheight);
    mquit->setStyleSheet(style);
    connect(mquit, &QPushButton::clicked, this, &StartScreenLayer::onQuitClicked);
    mroot->addWidget(mquit);
    mroot->setSpacing(25);
    mroot->setAlignment(Qt::AlignCenter);

    QWidget* widget = new AnimatedBackground(mroot, ResourceLoader::getInstance()->getAnimation("ui:start:background"));
    QHBoxLayout* root = new QHBoxLayout();
    root->addWidget(widget);
    setContentsMargins(0, 0, 0, 0);
    setLayout(root);
}

StartScreenLayer::~StartScreenLayer()
{
    delete mstart;
    delete moptions;
    delete mquit;
    delete mroot;
}

void StartScreenLayer::outGame()
{
    mstart->setText("Start game");
    ingame = false;
}

void StartScreenLayer::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape && ingame)
    {
        qDebug()<<"coucou";
        emit(onStartClicked(previous));
    }
}

void StartScreenLayer::onStartClicked(bool checked)
{
    Q_UNUSED(checked);
    mstart->setText("Back to game");
    if(ingame)
        emit stateChange(AppState::PLAYED);
    else
        emit stateChange(AppState::STARTED);
    ingame = true;
}

void StartScreenLayer::onOptionClicked(bool checked)
{
    Q_UNUSED(checked);
    emit stateChange(AppState::OPTIONS);
}

void StartScreenLayer::onQuitClicked(bool checked)
{
    Q_UNUSED(checked);
    emit stateChange(AppState::QUITED);
}
