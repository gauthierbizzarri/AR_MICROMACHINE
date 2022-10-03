#include "uibutton.h"

UiButton::UiButton(QString text, float width, float height) : QPushButton(text)
{    
    QString style = "QPushButton{ border: 5px solid #9B7D5B; border-radius:25px; background-color : rgba(255, 206, 150, 0.6); } QPushButton:hover{background-color : rgba(255, 206, 150, 0.9)} QPushButton:target{background-color : rgba(170, 138, 100, 1)}";
    setStyleSheet(style);
    setFixedWidth(width);
    setFixedHeight(height);
}
