#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <mapinfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MapInfo* minfo;
    QGraphicsScene* mscene;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
private slots:
    void onObjectRemoved(CircuitElement*);
    void onObjectAdded(CircuitElement*);
};
#endif // MAINWINDOW_H
