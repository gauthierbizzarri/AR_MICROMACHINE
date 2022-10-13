#include "gamescreen.h"

GameScreen::GameScreen(QWidget* parent) : DisplayView(parent)
{
    mroot = new QHBoxLayout(this);
    mscene = new QGraphicsScene();
    mscene->setSceneRect(0, 0, 1000, 1000);
    mview = new QGraphicsView();
    mview->setScene(mscene);
    mroot->addWidget(mview);
    setLayout(mroot);
}

GameScreen::~GameScreen()
{
    delete mscene;
    delete mview;
    delete mroot;
}

void GameScreen::onObjectRemoved(CircuitElement* e)
{
    mscene->removeItem(e);
}

void GameScreen::onObjectAdded(CircuitElement* e)
{
    mscene->addItem(e);
}

void GameScreen::onSizeChanged(QSize size)
{
    mscene->setSceneRect(0, 0, size.width(), size.height());
}

void GameScreen::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        emit stateChange(AppState::PAUSED);
    }
    event->ignore();
}
