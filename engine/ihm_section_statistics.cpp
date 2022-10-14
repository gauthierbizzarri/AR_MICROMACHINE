
#include <QHBoxLayout>
#include <QLabel>
#include "ihm_section_statistics.h"

Stats::Stats(QObject* parent, GamePlayer* player)
    : QObject{parent}
{

    this->next = nullptr;
    this->prev = nullptr;

    this->id = 0;
    this->name = player->getPseudo();
    this->check = player->getCheckpoint();
    this->lap = player->getLap();

}

void Stats::update(GamePlayer* player) {

    int oldId = this->id;
    int newId = this->id;
    this->check = player->getCheckpoint();
    this->lap = player->getLap();

    auto stats = this->next;
    while(stats != nullptr) {
        if(this->lap > stats->lap) {
            stats = stats->next;
            qDebug() << ".";
        }
        else {
            newId = stats->id;
            stats = nullptr;
        }
    }

    qDebug() << oldId << "-->" << newId;

    emit this->changed(oldId, this->id, this);
}

IHM_SectionStatistics::IHM_SectionStatistics(QWidget* parent)
    : QWidget(parent)
{

    this->m_stats = nullptr;

    auto layout = new QVBoxLayout();
    auto layoutArray = new QHBoxLayout();
    this->m_layoutName = new QVBoxLayout();
    this->m_layoutLap = new QVBoxLayout();
    this->m_layoutCheck = new QVBoxLayout();

    auto spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    layoutArray->addLayout(this->m_layoutName);
    layoutArray->addLayout(this->m_layoutLap);
    layoutArray->addLayout(this->m_layoutCheck);
    layout->addLayout(layoutArray);
    layout->addWidget(spacer);
    this->setLayout(layout);

}

void IHM_SectionStatistics::addPlayer(GamePlayer* player) {

    auto stats = new Stats(this, player);
    this->m_layoutName->addWidget(new QLabel(stats->name));
    this->m_layoutLap->addWidget(new QLabel(QString::number(stats->lap)));
    this->m_layoutCheck->addWidget(new QLabel(QString::number(stats->check)));

    if(this->m_stats == nullptr)
        this->m_stats = stats;
    else {
        stats->id = this->m_stats->id +1;
        stats->next = this->m_stats;
        this->m_stats->prev = stats;
        this->m_stats = stats;
    }

    connect(player, &GamePlayer::statsChanged, stats, &Stats::update);
    connect(stats, &Stats::changed, this, [this](int o, int n, Stats* stats) {
        qDebug() << o << "->" << n;

        auto nameW = (QLabel*) this->m_layoutName->takeAt(o)->widget();
        auto lapW = (QLabel*) this->m_layoutLap->takeAt(o)->widget();
        auto checkW = (QLabel*) this->m_layoutCheck->takeAt(o)->widget();

        lapW->setText(QString::number(stats->lap));
        checkW->setText(QString::number(stats->check));

        this->m_layoutName->insertWidget(n, nameW);
        this->m_layoutLap->insertWidget(n, lapW);
        this->m_layoutCheck->insertWidget(n, checkW);

    });
}

