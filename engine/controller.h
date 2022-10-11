#ifndef CONTROLLER_H
#define CONTROLLER_H

// Nécessite d'ajouter la ligne QT += gamepad dans le .pro

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QObject>

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QDial>
#include <QPushButton>

#include <QGamepadManager>
#include <QGamepad>
#include <QMqttClient>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

#include "main.h"

// ////////////////////////////////////////////////////////////////////////////
// Defines
// ////////////////////////////////////////////////////////////////////////////

#define CONTROLLER_UUID "hehehe"
#define CONTROLLER_REGISTER "{\"uuid\":\"<uuid>\",\"pseudo\":\"<name>\",\"controller\":\"controller\",\"vehicle\":\"<vehicle>\",\"team\":0}"

// ////////////////////////////////////////////////////////////////////////////
// Class
// ////////////////////////////////////////////////////////////////////////////

class Controller : public QObject
{
    Q_OBJECT

    QMqttClient* m_mqtt;
    QGamepad* m_gamepad;
    QString m_name;
    QString m_uuid;
    double m_direction;
    int m_acceleration;
    int m_deceleration;
    bool m_banana;
    bool m_bomb;
    bool m_rocket;

    int m_choice;
    bool m_playing;

    QMainWindow* m_wRoot;
    QLabel* m_wMqtt;
    QLabel* m_wVehicle;

public:
    // ////////////////////////////////////////////////////////////////////////
    // Constructor / Desctructor

    Controller(QGamepad* gamepad, QString name) {

        // Pre init

        this->m_name = name;
        this->m_uuid = QUuid::createUuid().toString();
        this->m_direction = 0;
        this->m_deceleration = 0;
        this->m_acceleration = 0;
        this->m_banana = false;
        this->m_bomb = false;
        this->m_rocket = false;

        this->m_choice = 0;
        this->m_playing = false;

        // Init widget

        this->m_wRoot = new QMainWindow();

        this->showHome();
        this->m_wRoot->setWindowTitle("Gamepad " + this->m_name);
        this->m_wRoot->setMinimumSize(300, 100);
        this->m_wRoot->show();

        connect(this->m_wRoot, &QWidget::destroyed, this, [this]() {
            delete this;
        });

        // Init gamepad

        this->m_gamepad = gamepad;
        connect(this->m_gamepad, &QGamepad::buttonAChanged, this, &Controller::buttonA);
        connect(this->m_gamepad, &QGamepad::buttonBChanged, this, &Controller::buttonB);
        connect(this->m_gamepad, &QGamepad::buttonXChanged, this, &Controller::buttonX);
        connect(this->m_gamepad, &QGamepad::buttonYChanged, this, &Controller::buttonY);
        connect(this->m_gamepad, &QGamepad::buttonL2Changed, this, &Controller::triggerLeft);
        connect(this->m_gamepad, &QGamepad::buttonR2Changed, this, &Controller::triggerRight);
        connect(this->m_gamepad, &QGamepad::axisLeftXChanged, this, &Controller::axisX);
        connect(this->m_gamepad, &QGamepad::buttonLeftChanged, this, &Controller::buttonL);
        connect(this->m_gamepad, &QGamepad::buttonRightChanged, this, &Controller::buttonR);

        // Init mqtt

        this->m_mqtt=new QMqttClient(this);
        this->m_mqtt->setHostname(MQTT_HOST);
        this->m_mqtt->setPort(MQTT_PORT);
        this->m_mqtt->setUsername(MQTT_USER);
        this->m_mqtt->setPassword(MQTT_PASS);
        this->m_mqtt->connectToHost();
        connect(this->m_mqtt, &QMqttClient::connected, this, [this]() {

            //this->m_mqtt->publish(QString(MQTT_TOPIC_PLAYER_REGISTER), QString(CONTROLLER_REGISTER).toUtf8());
            qDebug() << "connected";

        });
        qDebug() << "connect to" << MQTT_HOST << ":" << MQTT_PORT << MQTT_USER << MQTT_PASS << " - " << this->m_uuid;

    }

    virtual ~Controller() {
        delete this->m_gamepad;
    }

    // ////////////////////////////////////////////////////////////////////////
    // Methods

    void publish() {

        QJsonObject json;
        json.insert(QString("uuid"), QJsonValue(this->m_uuid));
        json.insert(QString("angle"), QJsonValue(this->m_direction));
        json.insert(QString("power"), QJsonValue(this->m_acceleration -this->m_deceleration));

        QJsonObject buttons;
        buttons.insert(QString("banana"), QJsonValue(this->m_banana));
        buttons.insert(QString("bomb"), QJsonValue(this->m_bomb));
        buttons.insert(QString("rocket"), QJsonValue(this->m_rocket));

        json.insert(QString("buttons"), buttons);

        if(this->m_banana)
            this->m_banana = false;
        if(this->m_bomb)
            this->m_bomb = false;
        if(this->m_rocket)
            this->m_rocket = false;

        this->m_mqtt->publish(QString(MQTT_TOPIC_PLAYER_CONTROL), QJsonDocument(json).toJson(QJsonDocument::Compact));

    }

    void showHome() {

        QWidget* root = new QWidget(this->m_wRoot);

        auto layoutV = new QVBoxLayout();
        auto layoutH = new QHBoxLayout();
        auto layoutHVehicle = new QHBoxLayout();

        this->m_wMqtt = new QLabel(QString("%1:%2 - %3 %4").arg(MQTT_HOST).arg(MQTT_PORT).arg(MQTT_USER).arg(MQTT_PASS), root);
        this->m_wVehicle = new QLabel("---", root);
        auto wVehicleL = new QLabel("<", root);
        auto wVehicleR = new QLabel(">", root);
        auto wVehicleSpacer = new QWidget(root);
        wVehicleSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        auto wVehicleX = new QLabel("Press X to play", root);

        auto spacerV = new QWidget(root);
        spacerV->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutHVehicle->addWidget(wVehicleL);
        layoutHVehicle->addWidget(this->m_wVehicle);
        layoutHVehicle->addWidget(wVehicleR);
        layoutHVehicle->addWidget(wVehicleSpacer);
        layoutHVehicle->addWidget(wVehicleX);

        layoutV->addWidget(this->m_wMqtt);
        layoutV->addLayout(layoutHVehicle);
        //layoutV->addWidget(spacerV);
        layoutH->addLayout(layoutV);
        root->setLayout(layoutH);

        auto widget = this->m_wRoot->takeCentralWidget();
        if(widget)
            delete widget;
        this->m_wRoot->setCentralWidget(root);

    }

    void showGamepad() {

        QWidget* root = new QWidget(this->m_wRoot);

        auto layoutV = new QVBoxLayout();
        auto layoutH = new QHBoxLayout();
        auto layoutVBtn = new QVBoxLayout();

        auto wBrake = new QProgressBar(root);
        wBrake->setOrientation(Qt::Vertical);
        auto wAcc = new QProgressBar(root);
        wAcc->setOrientation(Qt::Vertical);
        auto wDir = new QDial(root);
        wDir->setValue(50);
        auto wBanana = new QPushButton("BANANA !", root);
        auto wBomb = new QPushButton("GRENADA !", root);
        auto wRocket = new QPushButton("FIRE !", root);

        layoutVBtn->addWidget(wBanana);
        layoutVBtn->addWidget(wBomb);
        layoutVBtn->addWidget(wRocket);
        layoutH->addWidget(wBrake);
        layoutH->addWidget(wDir);
        layoutH->addWidget(wAcc);
        layoutH->addLayout(layoutVBtn);
        layoutV->addLayout(layoutH);
        root->setLayout(layoutV);

        connect(this, &Controller::brake, wBrake, &QProgressBar::setValue);
        connect(this, &Controller::acceleration, wAcc, &QProgressBar::setValue);
        connect(this, &Controller::direction, wDir, &QDial::setValue);
        connect(this, &Controller::banana, wBanana, &QPushButton::setDisabled);
        connect(this, &Controller::bomb, wBomb, &QPushButton::setDisabled);
        connect(this, &Controller::rocket, wRocket, &QPushButton::setDisabled);

        auto widget = this->m_wRoot->takeCentralWidget();
        if(widget)
            delete widget;
        this->m_wRoot->setCentralWidget(root);

    }

    static void createGamepad() {


        auto gamepads = QGamepadManager::instance()->connectedGamepads();

        for(int i = 0; i < gamepads.size(); i++) {

            new Controller(new QGamepad(gamepads[i]), QString("gr4-") + QString::number(i));
        }

    }

    // ////////////////////////////////////////////////////////////////////////
    // Slots

public slots:

    void buttonA(bool value) {

        if(value)
            this->m_mqtt->publish(QString(MQTT_TOPIC_PLAYER_REGISTER),
                                  QString(CONTROLLER_REGISTER)
                                  .replace(QString("<uuid>"), QString(this->m_uuid))
                                  .replace(QString("<name>"), QString(this->m_name))
                                  .replace(QString("<vehicle>"), QString(this->m_choice == 0 ? "bike" : (this->m_choice == 1 ? "car" : "truck")) )
                                  .toUtf8());
        this->m_playing = true;
        this->showGamepad();

    }

    void buttonB(bool value) {

        this->m_banana = value;
        emit this->banana(value);

        if(value) {
            this->publish();
        }

    }

    void buttonX(bool value) {

        this->m_bomb = value;
        emit this->bomb(value);

        if(value) {
            this->publish();
        }
    }

    void buttonY(bool value) {

        this->m_rocket = value;
        emit this->rocket(value);

        if(value) {
            this->publish();
        }

    }

    void triggerLeft(double value) {

        if(value < 1.0) {
            this->m_deceleration = (int) (value *100);
            emit this->brake(this->m_deceleration);
            this->publish();
        }
    }

    void triggerRight(double value) {

        if(value < 1.0) {
            this->m_acceleration = (int) (value *100);
            emit this->acceleration(this->m_acceleration);
            this->publish();
        }
    }

    void axisX(double value) {

        this->m_direction = -(((int) (value *100))*0.01) *1.57;
        emit this->direction((value +1)*25 +25);
        this->publish();

    }

    void buttonL(bool value) {

        if(value && !this->m_playing) {
            this->m_choice = (this->m_choice -1) %3;
            this->m_wVehicle->setText(QString(this->m_choice == 0 ? "bike" : (this->m_choice == 1 ? "car" : "truck")));
        }
    }

    void buttonR(bool value) {

        if(value && !this->m_playing) {
            this->m_choice = (this->m_choice +1) %3;
            this->m_wVehicle->setText(QString(this->m_choice == 0 ? "bike" : (this->m_choice == 1 ? "car" : "truck")));
        }
    }

signals:
    void brake(int);
    void acceleration(int);
    void direction(int);
    void banana(bool);
    void bomb(bool);
    void rocket(bool);

};

#endif // CONTROLLER_H
