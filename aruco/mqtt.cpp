#include "mqtt.h"

mqtt::mqtt()
{
    m_client = new QMqttCient(this);
      m_client->setHostname(ui->lineEditHost->text());
      m_client->setPort(ui->spinBoxPort->value());
}
