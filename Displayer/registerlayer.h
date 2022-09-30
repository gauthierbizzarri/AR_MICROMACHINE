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
    RegisterLayer(QWidget* parent = nullptr): DisplayView(parent)
    {
        mroot = new QVBoxLayout();
        QGroupBox* playerGroup = new QGroupBox("Player:");
        QVBoxLayout* playerLayout = new QVBoxLayout();

        mpseudo = new QHBoxLayout();
        QLabel* pseudoLabel = new QLabel("Pseudo:");
        QLineEdit* pseudoEntry = new QLineEdit("my awsome pseudo");
        connect(pseudoEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPseudo);
        mpseudo->addWidget(pseudoLabel);
        mpseudo->addWidget(pseudoEntry);
        playerLayout->addLayout(mpseudo);

        mvehicle = new QHBoxLayout();
        QComboBox* vehicleBox = new QComboBox();
        QLabel* vehicleLabel = new QLabel("Vehicle:");
        vehicleBox->addItem("car");
        vehicleBox->addItem("motorcicle");
        vehicleBox->addItem("truck");
        connect(vehicleBox, &QComboBox::currentTextChanged, this, &RegisterLayer::vehicleChanged);
        mvehicle->addWidget(vehicleLabel);
        mvehicle->addWidget(vehicleBox);
        playerLayout->addLayout(mvehicle);

        playerGroup->setLayout(playerLayout);
        mroot->addWidget(playerGroup);

        QGroupBox* hostGroup = new QGroupBox("Server:");
        QVBoxLayout* hostLayout = new QVBoxLayout();

        mhost = new QHBoxLayout();
        QLabel* hostLabel = new QLabel("Host:");
        QLineEdit* hostEntry = new QLineEdit("localhost");
        connect(hostEntry, &QLineEdit::textEdited, this, &RegisterLayer::editHost);
        mhost->addWidget(hostLabel);
        mhost->addWidget(hostEntry);
        hostLayout->addLayout(mhost);

        mport = new QHBoxLayout();
        QLabel* portLabel = new QLabel("Port:");
        QLineEdit* portEntry = new QLineEdit("1883");
        connect(portEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPort);
        mport->addWidget(portLabel);
        mport->addWidget(portEntry);
        hostLayout->addLayout(mport);

        musername = new QHBoxLayout();
        QLabel* usernameLabel = new QLabel("Username:");
        QLineEdit* usernameEntry = new QLineEdit("");
        connect(portEntry, &QLineEdit::textEdited, this, &RegisterLayer::editUsername);
        musername->addWidget(usernameLabel);
        musername->addWidget(usernameEntry);
        hostLayout->addLayout(musername);

        mpassword = new QHBoxLayout();
        QLabel* passwordLabel = new QLabel("Password:");
        QLineEdit* passwordEntry = new QLineEdit("");
        connect(portEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPassword);
        mpassword->addWidget(passwordLabel);
        mpassword->addWidget(passwordEntry);
        hostLayout->addLayout(mpassword);

        hostGroup->setLayout(hostLayout);
        mroot->addWidget(hostGroup);

        QPushButton* ok = new QPushButton("Launch");
        connect(ok, &QPushButton::clicked, this, &RegisterLayer::accept);
        mroot->addWidget(ok);
        setLayout(mroot);
    }
private slots:
    void editPseudo(const QString &value)
    {
        pseudo = value;
    }

    void editPort(const QString &value)
    {
        port = value.toInt();
    }

    void editPassword(const QString &value)
    {
        password = value;
    }

    void editUsername(const QString &value)
    {
        username = value;
    }

    void editHost(const QString &value)
    {
        host = value;
    }

    void accept(bool checked)
    {
        Q_UNUSED(checked);
        QUuid id = QUuid::createUuid();
        if(pseudo.isEmpty())
        {
            qDebug("pseudo empty");
        }
        else if(host.isEmpty())
        {
            qDebug("host empty");
        }
        else
        {
            emit registered(id.toString(QUuid::WithoutBraces), pseudo, vehicle, host, port, username, password);
        }
    }

    void vehicleChanged(QString text)
    {
        vehicle = text;
    }
signals:
    void registered(QString uuid, QString psueod, QString vehicle, QString host, int port, QString username, QString password);

};

#endif // REGISTERLAYER_H
