#include "optionslayer.h"
#include <game/ui/generics/uibutton.h>

OptionsLayer::OptionsLayer(QWidget* parent) : DisplayView(parent)
{
    mroot = new QVBoxLayout();

    mfullscreen = new QHBoxLayout();
    QLabel* fullscreenLabel = new QLabel(QString("Fullscreen:"));
    QPushButton* isFullscreenButton = new UiButton(Options::getInstance()->fullScreen ? "ON" : "OFF", 300, 60);
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
    QPushButton* save = new UiButton("Save", 300, 100);
    connect(save, &QPushButton::clicked, this, &OptionsLayer::onSave);
    mbuttons->addWidget(save);
    mroot->addLayout(mbuttons);

    setLayout(mroot);
}

QHBoxLayout* OptionsLayer::makeSlider(QString text, float value, void (OptionsLayer::*func)(int))
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

void OptionsLayer::setFullScreen(bool value)
{
    Q_UNUSED(value);
    Options::getInstance()->fullScreen = !Options::getInstance()->fullScreen;
    ((QPushButton*)sender())->setText(Options::getInstance()->fullScreen ? "ON" : "OFF");
    Options::getInstance()->apply();
}

void OptionsLayer::setSound(int value)
{
    Options::getInstance()->masterSound = value/100.0;
}

void OptionsLayer::setSoundEffect(int value)
{
    Options::getInstance()->soundEffects = value/100.0;
}

void OptionsLayer::setMusic(int value)
{
    Options::getInstance()->musicSound = value/100.0;
}

void OptionsLayer::onSave(bool checked)
{
    Q_UNUSED(checked);
    Options::getInstance()->apply();
    emit stateChange(previous);
}

void OptionsLayer::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        emit stateChange(previous);
    }
}
