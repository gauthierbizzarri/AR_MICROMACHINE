#include "uibutton.h"
#include <QPainter>
#include <QPaintEvent>
#include <game/utils/resourceloader.h>

UiButton::UiButton(QString text, float width, float height) : QPushButton(text)
{    
    QString style = "QPushButton{ border: 5px solid #9B7D5B; border-radius:25px; background-color : rgba(255, 206, 150, 0.6); } QPushButton:hover{background-color : rgba(255, 206, 150, 0.9)} QPushButton:target{background-color : rgba(170, 138, 100, 1)}";
    setStyleSheet(style);
    setFixedWidth(width);
    setFixedHeight(height);
    QImage ticon = ResourceLoader::getInstance()->getImage("ui:spotcar");
    icon = new QImage(ticon.scaled(ticon.width()*3, ticon.height()*3));
}

void UiButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(width()-icon->width(), height()-icon->height()-5, *icon);
    event->ignore();
}
