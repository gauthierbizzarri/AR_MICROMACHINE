#ifndef REGISTERLAYER_H
#define REGISTERLAYER_H

#include <displayview.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QUuid>
#include <QDebug>
#include <QComboBox>
#include <QGroupBox>
#include <player.h>

class RegisterLayer : public DisplayView
{
    Q_OBJECT
private:
    QHBoxLayout* mpseudo;
    QHBoxLayout* mvehicle;
    QVBoxLayout* mroot;
    QHBoxLayout* mhost;
    QHBoxLayout* mport;
    QHBoxLayout* musername;
    QHBoxLayout* mpassword;
    QString pseudo;
    QString vehicle;
    QString host;
    QString username;
    QString password;
    int port;
public:
    RegisterLayer(QWidget* parent = nullptr);
private slots:
    void editPseudo(const QString &value);

    void editPort(const QString &value);

    void editPassword(const QString &value);

    void editUsername(const QString &value);

    void editHost(const QString &value);

    void accept(bool checked);

    void vehicleChanged(QString text);
signals:
    void registered(QString uuid, QString psueod, QString vehicle, QString host, int port, QString username, QString password);

};

#endif // REGISTERLAYER_H
