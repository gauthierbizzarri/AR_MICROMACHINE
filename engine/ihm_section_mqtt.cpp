
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "ihm_section_mqtt.h"
#include "main.h"

IHM_SectionMqtt::IHM_SectionMqtt(QWidget *parent)
    : QWidget{parent}
{

    auto layout = new QVBoxLayout();

    auto labelHost = new QLabel("Host", this);
    auto labelPort = new QLabel("Port", this);
    auto labelUser = new QLabel("Username", this);
    auto labelPass = new QLabel("Password", this);
    this->leHost = new QLineEdit(QString(MQTT_HOST), this);
    this->lePort = new QLineEdit(QString::number(MQTT_PORT), this);
    this->leUser = new QLineEdit(QString(MQTT_USER), this);
    this->lePass = new QLineEdit(QString(MQTT_PASS), this);
    auto spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    auto pbRefresh = new QPushButton("Connect", this);

    layout->addWidget(labelHost);
    layout->addWidget(leHost);
    layout->addWidget(labelPort);
    layout->addWidget(lePort);
    layout->addWidget(labelUser);
    layout->addWidget(leUser);
    layout->addWidget(labelPass);
    layout->addWidget(lePass);
    layout->addSpacing(24);
    layout->addWidget(pbRefresh);
    layout->addWidget(spacer);
    this->setLayout(layout);

    connect(pbRefresh, &QPushButton::clicked, this, [this]() {
        emit this->connectTo(this->leHost->text(), this->lePort->text().toInt(), this->leUser->text(), this->lePass->text());
    });

}
