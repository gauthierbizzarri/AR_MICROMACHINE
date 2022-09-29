#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <circuitelement.h>

class GameScreen : public QWidget{
private:
    QHBoxLayout* mroot;
    QGraphicsView* mview;
    QGraphicsScene* mscene;

public:
    GameScreen(QWidget* parent = nullptr) : QWidget(parent)
    {
        mroot = new QHBoxLayout(this);
        mscene = new QGraphicsScene();
        mscene->setSceneRect(0, 0, 1000, 1000);
        mview = new QGraphicsView();
        mview->setScene(mscene);
        mroot->addWidget(mview);
        setLayout(mroot);
    }

    ~GameScreen()
    {
        delete mscene;
        delete mview;
        delete mroot;
    }
public slots:
    /**
     * @brief onObjectRemoved called whenever an object gets removed from the map
     */
    void onObjectRemoved(CircuitElement* e)
    {

        mview->update();
        mscene->removeItem(e);
    }
    /**
     * @brief onObjectAdded called whenever an object gets added to the map
     */
    void onObjectAdded(CircuitElement* e)
    {

        mview->update();
        mscene->addItem(e);
    }
};

#endif // GAMESCREEN_H
