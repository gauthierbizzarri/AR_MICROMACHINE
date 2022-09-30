#ifndef FAKEBROKER_H
#define FAKEBROKER_H

#include <QObject>

class FakeBroker : public QObject
{
    Q_OBJECT
public:
    explicit FakeBroker(QObject *parent = nullptr);

signals:

};

#endif // FAKEBROKER_H
