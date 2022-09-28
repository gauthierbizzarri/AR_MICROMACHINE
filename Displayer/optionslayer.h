#ifndef OPTIONSLAYER_H
#define OPTIONSLAYER_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <options.h>

class OptionsLayer : public QWidget
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
    OptionsLayer(QWidget* parent = nullptr) : QWidget(parent)
    {
        mroot = new QVBoxLayout();

        mfullscreen = new QHBoxLayout();
        QLabel* fullscreenLabel = new QLabel("Fullscreen:");
        QCheckBox* isFullscreenCheckBox = new QCheckBox();
        connect(isFullscreenCheckBox, &QCheckBox::clicked, this, &OptionsLayer::setFullScreen);
        isFullscreenCheckBox->setChecked(Options::getInstance()->fullScreen);
        mfullscreen->addWidget(fullscreenLabel);
        mfullscreen->addWidget(isFullscreenCheckBox);
        mroot->addLayout(mfullscreen);

        mbuttons = new QHBoxLayout();
        QPushButton* save = new QPushButton("Save");
        connect(save, &QPushButton::clicked, this, &OptionsLayer::onSave);
        mbuttons->addWidget(save);
        QPushButton* close = new QPushButton("Close");
        connect(close, &QPushButton::clicked, this, &OptionsLayer::onClose);
        mbuttons->addWidget(close);
        mroot->addLayout(mbuttons);

        setLayout(mroot);
    }
private slots:

    void setFullScreen(bool value)
    {
        Options::getInstance()->fullScreen = value;
    }

    void onSave(bool checked)
    {
        Q_UNUSED(checked);
        Options::getInstance()->apply();
        emit optionsDone();
    }

    void onClose(bool checked)
    {
        Q_UNUSED(checked);
        emit optionsDone();
    }
signals:
    void optionsDone();
};

#endif // OPTIONSLAYER_H
