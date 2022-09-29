#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "entity.h"
#include <QJsonDocument>
#include <QJsonObject>

class Checkpoint : public Entity
{
private:
    int m_id;

public:
    explicit Checkpoint(QJsonObject);

    int get_id();

    static Checkpoint fromJson(QJsonDocument);

    void debug();
};

#endif // CHECKPOINT_H
