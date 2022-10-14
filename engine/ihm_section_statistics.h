#ifndef IHM_SECTIONSTATISTICS_H
#define IHM_SECTIONSTATISTICS_H

#include <QWidget>
#include <QVBoxLayout>
#include "game_player.h"

class Stats : public QObject
{
    Q_OBJECT

public:

    Stats* next;
    Stats* prev;

    int id;
    QString name;
    int lap;
    int check;

    Stats(QObject* parent, GamePlayer* player);

public slots:
    void update(GamePlayer* player);

signals:
    void changed(int oldId, int newId, Stats* stats);

};

class IHM_SectionStatistics : public QWidget
{

    QVBoxLayout* m_layoutName;
    QVBoxLayout* m_layoutLap;
    QVBoxLayout* m_layoutCheck;

    Stats* m_stats;

public:
    IHM_SectionStatistics(QWidget* parent);

    void addPlayer(GamePlayer* player);
    void insert(Stats* stats);

};

#endif // IHM_SECTIONSTATISTICS_H
