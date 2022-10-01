#ifndef ANIMATEDBACKGROUND_H
#define ANIMATEDBACKGROUND_H

#include <QFrame>
#include <QMovie>
#include <QPaintEvent>
#include <QPainter>
#include <QLayout>

class AnimatedBackground : public QFrame
{
private:
    QMovie* mmovie;
    int currentFrame;
public:
    AnimatedBackground(QLayout* layout, QMovie* movie, QWidget* parent = nullptr);



    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // ANIMATEDBACKGROUND_H
