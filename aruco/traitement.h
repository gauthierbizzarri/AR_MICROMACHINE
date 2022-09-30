#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include "QObject"


class traitement : public QObject
{

public:
    traitement();
    void rect();

signals:
    void jmap(QJsonDocument);


};

#endif // TRAITEMENT_H
