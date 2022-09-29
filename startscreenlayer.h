#ifndef STARTSCREENLAYER_H
#define STARTSCREENLAYER_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

class StartScreenLayer : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* mroot;
    QPushButton* mstart;
    QPushButton* moptions;
    QPushButton* mquit;
public:
    StartScreenLayer(QWidget* parent = nullptr):QWidget(parent)
    {
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
private slots:
    void onStartClicked(bool checked = false)
    {
        Q_UNUSED(checked);
        emit gameStart();
    }
    void onOptionClicked(bool checked = false)
    {
        Q_UNUSED(checked);
        emit options();
    }
    void onQuitClicked(bool checked = true)
    {
        Q_UNUSED(checked);
        emit exit();
    }
signals:
    void gameStart();
    void options();
    void exit();
};

#endif
