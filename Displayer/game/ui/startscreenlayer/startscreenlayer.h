#ifndef STARTLAYERSCREEN_H
#define STARTLAYERSCREEN_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>
#include <game/ui/displayview.h>
#include <game/ui/generics/uibutton.h>

class StartScreenLayer : public DisplayView{
    Q_OBJECT
private:
    QVBoxLayout* mroot;
    UiButton* mstart;
    UiButton* moptions;
    UiButton* mquit;
    bool ingame;
public:
    StartScreenLayer(QWidget* parent = nullptr);

    ~StartScreenLayer();

    void outGame();
    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void onStartClicked(bool checked = false);

    void onOptionClicked(bool checked = false);

    void onQuitClicked(bool checked = true);
};

#endif
