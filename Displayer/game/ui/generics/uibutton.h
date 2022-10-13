#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <QPushButton>
#include <QThread>


class UiButton : public QPushButton
{
private:
    QImage* icon;
public:
    UiButton(QString text, float width, float height);



    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // UIBUTTON_H
