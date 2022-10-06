
// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QDebug>
#include "ihm.h"
#include "game_map_object.h"
#include "main.h"

// ////////////////////////////////////////////////////////////////////////////
// Constructor
// ////////////////////////////////////////////////////////////////////////////

IHM::IHM(QWidget *parent)
    : QMainWindow(parent)
{

    QHBoxLayout* layout = new QHBoxLayout();
    this->m_map = new IHM_Map(this);
    this->m_sections = new IHM_Sections(this);
    this->m_sections->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    layout->addWidget(this->m_map);
    layout->addWidget(this->m_sections);
    layout->setMargin(10);

    QWidget* root = new QWidget();
    root->setLayout(layout);

    this->setCentralWidget(root);
    //this->setMinimumSize(1100, 850);

}

IHM::~IHM()
{
}

