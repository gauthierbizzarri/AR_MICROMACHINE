#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

#include <QWidget>
#include <appstate.h>

class DisplayView : public QWidget
{
    Q_OBJECT
protected:
    AppState previous;
public:
    DisplayView(QWidget* parent = nullptr) : QWidget(parent)
    {
        previous = AppState::UNKNOWN;
    }

    void setPrevious(AppState prev)
    {
        previous = prev;
    }
signals:
    void stateChange(AppState state);
};

#endif // DISPLAYVIEW_H
