
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QTabWidget>
#include <QDebug>

#include "ihm_sections.h"
#include "ihm_section_properties.h"

// ////////////////////////////////////////////////////////////////////////////
// Prototypes
// ////////////////////////////////////////////////////////////////////////////

QWidget* tabProperties(QWidget* parent);

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

IHM_Sections::IHM_Sections(QWidget *parent)
    : QTabWidget{parent}
{

    this->addTab(new IHM_SectionProperties(this), QString("Properties"));

}

// ////////////////////////////////////////////////////////////////////////////
// Functions
// ////////////////////////////////////////////////////////////////////////////
