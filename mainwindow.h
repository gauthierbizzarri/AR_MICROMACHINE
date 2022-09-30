#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <startscreenlayer.h>
#include <gamescreen.h>
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <mapinfo.h>
#include <QMqttClient>
#include <options.h>
#include <optionslayer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
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
    /**
     * @brief mclient mqtt client
     */
    QMqttClient* mclient;

    QWidget* mmain;
    StartScreenLayer* mstartLayer;
    GameScreen* mgameLayer;
    OptionsLayer* moptions;

    QWidget* currentLayer;

    void setupMqtt();
private slots:
    void setupStartScreenView();
    void setupGameView();
    void setupOptionsView();
    /**
     * @brief onMqttConnected called on mqtt brocker connection
     */
    void onMqttConnected();
    /**
     * @brief onMessageRecieve called on message arrival
     */
    void onMessageRecieve(const QByteArray&, const QMqttTopicName&);
    void applyOptions(const Options* options);
};
#endif // MAINWINDOW_H

