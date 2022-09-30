#include "connectionlayer.h"
#include <QLabel>
#include <QPushButton>
#include <game/utils/properties/gameproperties.h>
#include <QJsonDocument>

ConnectionLayer::ConnectionLayer(MqttDialog *diag, QWidget* parent) : DisplayView(parent)
{
    loaded = false;
    this->diag = diag;
    root = new QVBoxLayout(this);
    label = new QLabel("Game is connecting lol ...");
    root->addWidget(label);
    QPushButton* back = new QPushButton("Back");
    connect(back, &QPushButton::clicked, this, &ConnectionLayer::backBtnClicked);
    root->addWidget(back);

    setLayout(root);
}

void ConnectionLayer::init(QString id, QString pseudo, QString vehicle, QString host, int port, QString username, QString password)
{
    loaded = false;
    this->id = id;
    this->pseudo = pseudo;
    this->vehicle = vehicle;
    connect(diag, &MqttDialog::connected, this, &ConnectionLayer::onConnect);
    connect(diag, &MqttDialog::messageRecieved, this, &ConnectionLayer::onMessage);
    diag->establishConnection(host, port, username, password);
}

void ConnectionLayer::onConnect()
{
    label->setText("Waiting for game properties");
    diag->sub(MqttDialog::MAP);
    diag->sub(MqttDialog::GAME);
    diag->sub(MqttDialog::GAME_PROPERTIES);
    QJsonObject data{
        {"uuid", id},
        {"pseudo", pseudo},
        {"controller", "keyboard"},
        {"vehicle", vehicle},
        {"team", "null"}
    };
    diag->pub(MqttDialog::PLAYER_REGISTER, QJsonDocument(data).toJson());
}

void ConnectionLayer::backBtnClicked(bool checked)
{
    Q_UNUSED(checked);
    this->diag->cutConnection();
    emit stateChange(AppState::STARTED);
}

void ConnectionLayer::onMessage(const QByteArray &data, QMqttTopicName name)
{
    if(name.name() == MqttDialog::GAME_PROPERTIES && !loaded)
    {
        GameProperties::getInstance()->fill(QJsonDocument::fromJson(data).object());
        loaded = true;
        emit stateChange(AppState::CONNECTED);
    }
}
