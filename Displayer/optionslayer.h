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
    OptionsLayer(QWidget* parent = nullptr) : DisplayView(parent)
    {
        mroot = new QVBoxLayout();

        mfullscreen = new QHBoxLayout();
        QLabel* fullscreenLabel = new QLabel(QString("Fullscreen:"));
        QPushButton* isFullscreenButton = new QPushButton(Options::getInstance()->fullScreen ? "ON" : "OFF");
        connect(isFullscreenButton, &QCheckBox::clicked, this, &OptionsLayer::setFullScreen);
        isFullscreenButton->setChecked(Options::getInstance()->fullScreen);
        mfullscreen->addWidget(fullscreenLabel);
        mfullscreen->addWidget(isFullscreenButton);
        mroot->addLayout(mfullscreen);

        mvolume = makeSlider("General volume:", Options::getInstance()->masterSound, &OptionsLayer::setSound);
        mroot->addLayout(mvolume);

        msoundeffects = makeSlider("Sound effects:", Options::getInstance()->soundEffects, &OptionsLayer::setSoundEffect);
        mroot->addLayout(msoundeffects);

        mmusic = makeSlider("Music:", Options::getInstance()->musicSound, &OptionsLayer::setMusic);
        mroot->addLayout(mmusic);

        mbuttons = new QHBoxLayout();
        QPushButton* save = new QPushButton("Save");
        connect(save, &QPushButton::clicked, this, &OptionsLayer::onSave);
        mbuttons->addWidget(save);
        mroot->addLayout(mbuttons);

        setLayout(mroot);
    }
private:
    QHBoxLayout* makeSlider(QString text, float value, void (OptionsLayer::*func)(int))
    {
        QHBoxLayout* layer = new QHBoxLayout();
        QLabel* soundlabel = new QLabel(text);
        QSlider* soundSlider = new QSlider();
        connect(soundSlider, &QSlider::sliderMoved, this, func);
        soundSlider->setTickInterval(1);
        soundSlider->setTickPosition(QSlider::TicksAbove);
        soundSlider->setOrientation(Qt::Orientation::Horizontal);
        soundSlider->setValue(value*100.0);
        layer->addWidget(soundlabel);
        layer->addWidget(soundSlider);
        return layer;
    }

private slots:

    void setFullScreen(bool value)
    {
        Q_UNUSED(value);
        Options::getInstance()->fullScreen = !Options::getInstance()->fullScreen;
        ((QPushButton*)sender())->setText(Options::getInstance()->fullScreen ? "ON" : "OFF");
        Options::getInstance()->apply();
    }

    void setSound(int value)
    {
        Options::getInstance()->masterSound = value/100.0;
    }

    void setSoundEffect(int value)
    {
        Options::getInstance()->soundEffects = value/100.0;
    }

    void setMusic(int value)
    {
        Options::getInstance()->musicSound = value/100.0;
    }

    void onSave(bool checked)
    {
        Q_UNUSED(checked);
        Options::getInstance()->apply();
        emit optionsDone(previous);
    }
signals:
    void optionsDone(int);

    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key_Escape)
        {
            emit(optionsDone(previous));
        }
    }
};

#endif // OPTIONSLAYER_H
