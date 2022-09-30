#ifndef CONNECTIONLAYER_H
#define CONNECTIONLAYER_H

#include <displayview.h>
#include <mqttdialog.h>
#include <QVBoxLayout>

class ConnectionLayer : public DisplayView
{
    Q_OBJECT
private:
    QVBoxLayout* root;
    MqttDialog* diag;
public:
    ConnectionLayer(QWidget* parent = nullptr);
    void init(MqttDialog*);

private slots:
    void nextLayer();
    void backBtnClicked(bool);

signals:
    void connectionDone(int);
    void goBack(int);
};

#endif // CONNECTIONLAYER_H
