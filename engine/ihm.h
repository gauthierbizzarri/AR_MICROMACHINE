#ifndef IHM_H
#define IHM_H

// ////////////////////////////////////////////////////////////////////////////
// Includes
// ////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>

#include "ihm_map.h"
#include "ihm_sections.h"

// ////////////////////////////////////////////////////////////////////////////
// Class IHM
// ////////////////////////////////////////////////////////////////////////////

class IHM : public QMainWindow
{
    Q_OBJECT

public:

    IHM_Map* m_map;
    IHM_Sections* m_sections;

public:
    IHM(QWidget *parent = nullptr);
    ~IHM();

};

// ////////////////////////////////////////////////////////////////////////////
//
// ////////////////////////////////////////////////////////////////////////////

#endif // IHM_H
