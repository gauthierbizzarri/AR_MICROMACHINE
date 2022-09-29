#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <startscreenlayer.h>
#include <QStackedLayout>
#include <registerlayer.h>
#include <mqttdialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MqttDialog* dialog, QWidget *parent = nullptr);
    ~MainWindow();


private:
    /**
     * @brief minfo map informations
     */
    MapInfo* minfo;
    /**
     * @brief mclient mqtt client
     */
    MqttDialog* mclient;

    QWidget* root;
    QStackedLayout* rootLayout;

    QWidget* mmain;
    StartScreenLayer* mstartLayer;
    GameScreen* mgameLayer;
    OptionsLayer* moptions;
    RegisterLayer* mregister;

    QWidget* currentLayer;

    void setupMqtt();
    StartScreenLayer* setupStartScreenView();
    GameScreen* setupGameView();
    OptionsLayer* setupOptionsView();
    RegisterLayer* setupRegister();

    void showView(int);

public slots:
    /**
     * @brief onMqttConnected called on mqtt brocker connection
     */
    void onMqttConnected();
    /**
     * @brief onMessageRecieve called on message arrival
     */
    void onMessageRecieve(const QByteArray&, const QMqttTopicName&);
    void applyOptions(const Options* options);
    void onRegistered(QString id, QString pseudo, QString vehicle);
    void pauseGame(int display);
    void playGame(int display);

signals:
    void quitting();
    void registered(QString uuid);
    void paused(bool);
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
