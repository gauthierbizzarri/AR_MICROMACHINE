#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <game/ui/startscreenlayer/startscreenlayer.h>
#include <game/ui/gamescreen/gamescreen.h>
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <game/utils/map/mapinfo.h>
#include <QMqttClient>
#include <game/utils/options.h>
#include <game/ui/optionslayer/optionslayer.h>
#include <QStackedLayout>
#include <game/ui/registerlayer/registerlayer.h>
#include <game/utils/mqtt/mqttdialog.h>
#include <game/ui/connectionlayer/connectionlayer.h>

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
    int START_MENU_VIEW;
    int GAME_VIEW;
    int OPTIONS_VIEW;
    int REGISTER_VIEW;
    int CONNECTING_VIEW;

    AppState currentstate;
    QString id;
    QString pseudo;
    QString vehicle;
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
    ConnectionLayer* setupConnectionLayer();

    void showView(int);



public slots:
    /**
     * @brief onMessageRecieve called on message arrival
     */
    void onMessageRecieve(const QByteArray&, const QMqttTopicName&);
    void applyOptions(const Options* options);
    void onRegistered(QString id, QString pseudo, QString vehicle, QString host, int port, QString username, QString password);
    void onMqttDisconnected();
    void onStateChange(AppState state);

signals:
    void quitting();
    void registered(QString uuid);
    void paused(bool);
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
