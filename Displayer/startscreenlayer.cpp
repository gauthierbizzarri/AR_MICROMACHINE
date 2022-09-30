#include "startscreenlayer.h"

StartScreenLayer::StartScreenLayer(QWidget* parent):DisplayView(parent)
{
    ingame = false;
    mroot = new QVBoxLayout(this);
    mstart = new QPushButton("Start game");
    mstart->setFixedWidth(100);
    mstart->setFixedHeight(50);
    connect(mstart, &QPushButton::clicked, this, &StartScreenLayer::onStartClicked);
    mroot->addWidget(mstart);

    moptions = new QPushButton("Options");
    moptions->setFixedWidth(100);
    moptions->setFixedHeight(50);
    connect(moptions, &QPushButton::clicked, this, &StartScreenLayer::onOptionClicked);
    mroot->addWidget(moptions);

    mquit = new QPushButton("Quit game");
    mquit->setFixedWidth(100);
    mquit->setFixedHeight(50);
    connect(mquit, &QPushButton::clicked, this, &StartScreenLayer::onQuitClicked);
    mroot->addWidget(mquit);
    mroot->setSpacing(10);
    mroot->setAlignment(Qt::AlignCenter);
    setLayout(mroot);
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