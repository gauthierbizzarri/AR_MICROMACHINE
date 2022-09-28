#ifndef AI_H
#define AI_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

class AI : public QObject
{
    Q_OBJECT
public:
    explicit AI(QObject *parent = nullptr);
    void process(QJsonDocument);

signals:
    void controllerInputs(QJsonDocument);

public slots:
    void playerDatas(QJsonDocument);
};

#endif // AI_H
