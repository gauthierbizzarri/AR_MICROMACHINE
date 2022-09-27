#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <mapinfo.h>
#include <QMqttClient>

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
    /**
     * @brief minfo map informations
     */
    MapInfo* minfo;
    QGraphicsScene* mscene;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
    /**
     * @brief mclient mqtt client
     */
    QMqttClient* mclient;
private slots:
    /**
     * @brief onObjectRemoved called whenever an object gets removed from the map
     */
    void onObjectRemoved(CircuitElement*);
    /**
     * @brief onObjectAdded called whenever an object gets added to the map
     */
    void onObjectAdded(CircuitElement*);
    /**
     * @brief onMqttConnected called on mqtt brocker connection
     */
    void onMqttConnected();
    /**
     * @brief onMessageRecieve called on message arrival
     */
    void onMessageRecieve(const QByteArray&, const QMqttTopicName&);
};
#endif // MAINWINDOW_H
