#ifndef IHM_SECTIONS_H
#define IHM_SECTIONS_H

#include <QTabWidget>

#include "ihm_section_properties.h"
#include "ihm_section_mqtt.h"
#include "ihm_section_statistics.h"

class IHM_Sections : public QTabWidget
{
    Q_OBJECT

public:

    IHM_SectionProperties* m_properties;
    IHM_SectionMqtt* m_mqtt;
    IHM_SectionStatistics* m_stats;

    explicit IHM_Sections(QWidget *parent = nullptr);

signals:

};

#endif // IHM_SECTIONS_H
