#include "monqtmqtt.h"




monqtmqtt::monqtmqtt()
{
        this->m_client = new QMqttClient();
    /*
    this->m_client->setHostname(QString("10.3.0.218"));
        this->m_client->setPort(1883);
        this->m_client->setUsername("phoenix");
        this->m_client->setPassword("ardent");
        this->m_client = new QMqttClient();
*/
    this->m_client->setHostname(QString("10.3.2.55"));
    this->m_client->setPort(1883);
    this->m_client->setUsername("hostuser");
    this->m_client->setPassword("Hostuser123");

    connect(this->m_client,&QMqttClient::messageReceived,this,&monqtmqtt::messageReceived);
    connect(this->m_client,&QMqttClient::connected,this,&monqtmqtt::online);

    this->m_client->connectToHost();
}



void monqtmqtt::QtMqttPub(QString m, QByteArray message) {
    m_client->publish(m, message);

    qDebug("MqttPubsend to map");
}

void monqtmqtt::messageReceived(const QByteArray &message, const QMqttTopicName &topic ){
    qDebug()<<message;
}

void monqtmqtt::online(){
    qDebug("connected");
    emit conn();
}

void monqtmqtt::pubmap(QJsonDocument jmap){
    QtMqttPub("map",jmap.toJson());
}
