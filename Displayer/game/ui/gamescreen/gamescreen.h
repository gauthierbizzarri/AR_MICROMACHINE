#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <game/mapobjects/circuitelement.h>
#include <game/ui/displayview.h>

class GameScreen : public DisplayView{
private:
    QHBoxLayout* mroot;
    QGraphicsView* mview;
    QGraphicsScene* mscene;

public:
    GameScreen(QWidget* parent = nullptr);

    ~GameScreen();
public slots:
    /**
     * @brief onObjectRemoved called whenever an object gets removed from the map
     */
    void onObjectRemoved(CircuitElement* e);
    /**
     * @brief onObjectAdded called whenever an object gets added to the map
     */
    void onObjectAdded(CircuitElement* e);

    void onSizeChanged(QSize size);



    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // GAMESCREEN_H
