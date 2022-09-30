#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

#include "monqtmqtt.h"
#include "traitement_image.h"

class manager : public QObject
{
    Q_OBJECT

private:
    monqtmqtt * m_qtmqtt;
    Traitement_Image* m_traitement ;

public:
    explicit manager(QObject *parent = nullptr);

signals:

};

#endif // MANAGER_H
