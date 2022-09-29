#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <circuitelement.h>
#include <QDebug>
#include <mapinfo.h>
#include <displayview.h>

class GameScreen : public DisplayView{
    Q_OBJECT
private:
    QHBoxLayout* mroot;
    QGraphicsView* mview;
    QGraphicsScene* mscene;

public:
    GameScreen(QWidget* parent = nullptr) : DisplayView(parent)
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
        mscene->deleteLater();
        mview->deleteLater();
        mroot->deleteLater();
    }
public slots:
    /**
     * @brief onObjectRemoved called whenever an object gets removed from the map
     */
    void onObjectRemoved(CircuitElement* e)
    {
        mscene->removeItem(e);
    }
    /**
     * @brief onObjectAdded called whenever an object gets added to the map
     */
    void onObjectAdded(CircuitElement* e)
    {
        mscene->addItem(e);
    }

    void onSizeChange(QSize size)
    {
        mscene->setSceneRect(0, 0, size.width(), size.height());
    }

signals:
    void pauseMenu(int);
    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key::Key_Escape)
        {
            emit pauseMenu(0);
        }
        event->ignore();
    }
};

#endif // GAMESCREEN_H
