#ifndef OPTIONSLAYER_H
#define OPTIONSLAYER_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <options.h>
#include <QSlider>
#include <QDebug>
#include <displayview.h>
#include <QKeyEvent>

class OptionsLayer : public DisplayView
{
    Q_OBJECT
private:
    QVBoxLayout* mroot;
    QHBoxLayout* mfullscreen;
    QHBoxLayout* mvolume;
    QHBoxLayout* msoundeffects;
    QHBoxLayout* mmusic;
    QHBoxLayout* mbuttons;
public:
    OptionsLayer(QWidget* parent = nullptr);
private:
    QHBoxLayout* makeSlider(QString text, float value, void (OptionsLayer::*func)(int));

private slots:

    void setFullScreen(bool value);

    void setSound(int value);

    void setSoundEffect(int value);

    void setMusic(int value);

    void onSave(bool checked);

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // OPTIONSLAYER_H
