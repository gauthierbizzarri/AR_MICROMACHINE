#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

#include <QWidget>

class DisplayView : public QWidget
{
protected:
    int previous;
public:
    DisplayView(QWidget* parent = nullptr) : QWidget(parent)
    {
        previous = 0;
    }

    void setPrevious(int prev)
    {
        previous = prev;
    }
};

#endif // DISPLAYVIEW_H
