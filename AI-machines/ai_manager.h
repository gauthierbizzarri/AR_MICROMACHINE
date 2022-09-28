#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include <QObject>

#include "qtmqtttalker.h"
#include "ai.h"

class AI_Manager : public QObject
{
    Q_OBJECT
private:
    QtMqttTalker* m_talker;
    AI* m_ai;
public:
    explicit AI_Manager(QObject *parent = nullptr);

signals:

};

#endif // AI_MANAGER_H
