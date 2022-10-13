#include "startscreenlayer.h"
#include <game/utils/resourceloader.h>
#include <game/ui/animatedbackground.h>

StartScreenLayer::StartScreenLayer(QWidget* parent):DisplayView(parent)
{
    int buttonwidth = 400;
    int buttonheight= 100;
    ingame = false;
    mroot = new QVBoxLayout(this);
    mstart = new UiButton("Start game", buttonwidth, buttonheight);
    connect(mstart, &QPushButton::clicked, this, &StartScreenLayer::onStartClicked);
    mroot->addWidget(mstart);

    moptions = new UiButton("Options", buttonwidth, buttonheight);
    connect(moptions, &QPushButton::clicked, this, &StartScreenLayer::onOptionClicked);
    mroot->addWidget(moptions);

    mquit = new UiButton("Quit game", buttonwidth, buttonheight);
    connect(mquit, &QPushButton::clicked, this, &StartScreenLayer::onQuitClicked);
    mroot->addWidget(mquit);

    mroot->setSpacing(25);
    mroot->setAlignment(Qt::AlignCenter);

    QWidget* widget = new AnimatedBackground(mroot, ResourceLoader::getInstance()->getAnimation("ui:start:background"));
    QHBoxLayout* root = new QHBoxLayout();
    root->addWidget(widget);
    root->setMargin(0);
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
