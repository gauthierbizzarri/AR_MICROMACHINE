#include "animatedbackground.h"
#include <QLabel>

AnimatedBackground::AnimatedBackground(QLayout* layout, QMovie* movie, QWidget* parent) : QFrame(parent)
{
    mmovie = movie;
    connect(mmovie, &QMovie::frameChanged, [=]{ update(); });
    connect(mmovie, &QMovie::finished, [=]{ mmovie->start(); });
    movie->jumpToFrame(0);
    setLayout(layout);
    mmovie->start();
    setContentsMargins(0, 0, 0, 0);
}

void AnimatedBackground::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, mmovie->currentImage().scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    event->ignore();
}
