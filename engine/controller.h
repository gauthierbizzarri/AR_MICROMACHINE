#ifndef CONTROLLER_H
#define CONTROLLER_H

// Nécessite d'ajouter la ligne QT += gamepad dans le .pro

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QObject>

#include <QGamepadManager>
#include <QGamepad>
#include <QMqttClient>
#include <QJsonDocument>
#include <QJsonObject>

#include "main.h"

// ////////////////////////////////////////////////////////////////////////////
// Defines
// ////////////////////////////////////////////////////////////////////////////

#define CONTROLLER_UUID "hehehe"
#define CONTROLLER_REGISTER "{\"uuid\":\"<uuid>\",\"pseudo\":\"<name>\",\"controller\":\"gamepad\",\"vehicle\":\"car\",\"team\":0}"


// ////////////////////////////////////////////////////////////////////////////
// Class
// ////////////////////////////////////////////////////////////////////////////

class Controller : public QObject
{
    Q_OBJECT

    QMqttClient* m_mqtt;
    QGamepad* m_gamepad;
    QString m_name;
    double m_direction;
    int m_acceleration;
    int m_deceleration;
    bool m_banana;
    bool m_bomb;
    bool m_rocket;

public:
    // ////////////////////////////////////////////////////////////////////////
    // Constructor / Desctructor

    Controller(QGamepad* gamepad, QString name) {

        // Pre init

        this->m_name = name;
        this->m_direction = 0;
        this->m_deceleration = 0;
        this->m_acceleration = 0;
        this->m_banana = false;
        this->m_bomb = false;
        this->m_rocket = false;

        // Init gamepad

        this->m_gamepad = gamepad;
        connect(this->m_gamepad, &QGamepad::buttonAChanged, this, &Controller::buttonA);
        connect(this->m_gamepad, &QGamepad::buttonBChanged, this, &Controller::buttonB);
        connect(this->m_gamepad, &QGamepad::buttonXChanged, this, &Controller::buttonX);
        connect(this->m_gamepad, &QGamepad::buttonYChanged, this, &Controller::buttonY);
        connect(this->m_gamepad, &QGamepad::buttonL2Changed, this, &Controller::triggerLeft);
        connect(this->m_gamepad, &QGamepad::buttonR2Changed, this, &Controller::triggerRight);
        connect(this->m_gamepad, &QGamepad::axisLeftXChanged, this, &Controller::axisX);

        // Init mqtt

        this->m_mqtt=new QMqttClient();
        this->m_mqtt->setHostname(MQTT_HOST);
        this->m_mqtt->setPort(MQTT_PORT);
        this->m_mqtt->setUsername(MQTT_USER);
        this->m_mqtt->setPassword(MQTT_PASS);
        this->m_mqtt->connectToHost();
        connect(this->m_mqtt, &QMqttClient::connected, this, [this]() {

            //this->m_mqtt->publish(QString(MQTT_TOPIC_PLAYER_REGISTER), QString(CONTROLLER_REGISTER).toUtf8());
            qDebug() << "connected";

        });
        qDebug() << "connect to" << MQTT_HOST << ":" << MQTT_PORT << MQTT_USER << MQTT_PASS;

    }

    virtual ~Controller() {
        delete this->m_gamepad;
    }

    // ////////////////////////////////////////////////////////////////////////
    // Methods

    void publish() {

        QJsonObject json;
        json.insert(QString("uuid"), QJsonValue(this->m_name));
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

        this->m_mqtt->publish(QString(MQTT_TOPIC_PLAYER_CONTROL), QJsonDocument(json).toJson());

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
                                  .replace(QString("<uuid>"), QString(this->m_name))
                                  .replace(QString("<name>"), QString(this->m_name))
                                    .toUtf8());

    }

    void buttonB(bool value) {

        this->m_banana = value;

        if(value)
            this->publish();

    }

    void buttonX(bool value) {

        this->m_bomb = value;

        if(value)
            this->publish();

    }

    void buttonY(bool value) {

        this->m_rocket = value;

        if(value)
            this->publish();

    }

    void triggerLeft(double value) {

        if(value < 1.0) {
            this->m_deceleration = (int) (value *100);
            this->publish();
        }
    }

    void triggerRight(double value) {

        if(value < 1.0) {
            this->m_acceleration = (int) (value *100);
            this->publish();
        }
    }

    void axisX(double value) {

        this->m_direction = -(((int) (value *100))*0.01) *1.57;
        this->publish();

    }

};

#endif // CONTROLLER_H
