#include "connectionlayer.h"
#include <QLabel>
#include <QPushButton>

ConnectionLayer::ConnectionLayer(QWidget* parent) : DisplayView(parent)
{
    root = new QVBoxLayout(this);
    QLabel* label = new QLabel("Game is connecting lol ...");
    root->addWidget(label);
    QPushButton* back = new QPushButton("Back");
    connect(back, &QPushButton::clicked, this, &ConnectionLayer::backBtnClicked);
    root->addWidget(back);

    setLayout(root);
}

void ConnectionLayer::init(MqttDialog *diag)
{
    this->diag = diag;
    if(diag->isConnected())
    {
        nextLayer();
    }
    else
    {
        connect(diag, &MqttDialog::connected, this, &ConnectionLayer::nextLayer);
    }
}

void ConnectionLayer::nextLayer()
{
    emit connectionDone(1);
}

void ConnectionLayer::backBtnClicked(bool checked)
{
    Q_UNUSED(checked);
    this->diag->cutConnection();
    emit goBack(0);
}
