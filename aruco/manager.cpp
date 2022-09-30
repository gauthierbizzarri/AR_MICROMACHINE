#include "manager.h"

manager::manager(QObject *parent)
    : QObject{parent}
{
    m_qtmqtt = new monqtmqtt();
    m_traitement = new Traitement_Image();

    connect(m_qtmqtt,&monqtmqtt::conn,m_traitement,&Traitement_Image::rect);
    connect(m_traitement,&Traitement_Image::jsonmap,m_qtmqtt,&monqtmqtt::pubmap);
}
