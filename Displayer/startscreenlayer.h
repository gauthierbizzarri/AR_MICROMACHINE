#ifndef STARTLAYERSCREEN_H
#define STARTLAYERSCREEN_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>
#include <displayview.h>

class StartScreenLayer : public DisplayView{
    Q_OBJECT
private:
    QVBoxLayout* mroot;
    QPushButton* mstart;
    QPushButton* moptions;
    QPushButton* mquit;
    bool ingame;
public:
    StartScreenLayer(QWidget* parent):DisplayView(parent)
    {
        ingame = false;
        mroot = new QVBoxLayout(this);
        mstart = new QPushButton("Start game");
        connect(mstart, &QPushButton::clicked, this, &StartScreenLayer::onStartClicked);
        mroot->addWidget(mstart);

        moptions = new QPushButton("Options");
        connect(moptions, &QPushButton::clicked, this, &StartScreenLayer::onOptionClicked);
        mroot->addWidget(moptions);

        mquit = new QPushButton("Quit game");
        connect(mquit, &QPushButton::clicked, this, &StartScreenLayer::onQuitClicked);
        mroot->addWidget(mquit);
        setLayout(mroot);
    }

    ~StartScreenLayer()
    {
        delete mstart;
        delete moptions;
        delete mquit;
        delete mroot;
    }

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key_Escape && ingame)
        {
            emit(onStartClicked(previous));
        }
    }

private slots:
    void onStartClicked(bool checked = false)
    {
        Q_UNUSED(checked);
        mstart->setText("Back to game");
        if(ingame)
            emit gameStart(1);
        else
            emit gameStart(3);
        ingame = true;
    }
    void onOptionClicked(bool checked = false)
    {
        Q_UNUSED(checked);
        emit options(2);
    }
    void onQuitClicked(bool checked = true)
    {
        Q_UNUSED(checked);
        emit exit();
    }
signals:
    void gameStart(int);
    void options(int);
    void exit();
};

#endif
