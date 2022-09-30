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
    RegisterLayer(QWidget* parent = nullptr): DisplayView(parent)
    {
        pseudo = "belzorium";
        host = "10.3.0.218";
        port = 1883;
        username = "phoenix";
        password = "ardent";

        mroot = new QVBoxLayout();
        QGroupBox* playerGroup = new QGroupBox("Player:");
        QVBoxLayout* playerLayout = new QVBoxLayout();

        mpseudo = new QHBoxLayout();
        QLabel* pseudoLabel = new QLabel("Pseudo:");
        QLineEdit* pseudoEntry = new QLineEdit();
        pseudoEntry->setPlaceholderText("My awsome pseudo");
        connect(pseudoEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPseudo);
        mpseudo->addWidget(pseudoLabel);
        mpseudo->addWidget(pseudoEntry);
        playerLayout->addLayout(mpseudo);

        mvehicle = new QHBoxLayout();
        QComboBox* vehicleBox = new QComboBox();
        QLabel* vehicleLabel = new QLabel("Vehicle:");
        vehicleBox->addItem(Player::CAR);
        vehicleBox->addItem(Player::BIKE);
        vehicleBox->addItem(Player::TRUCK);
        vehicle = vehicleBox->itemText(0);
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
        QLineEdit* hostEntry = new QLineEdit();
        hostEntry->setPlaceholderText("server host name");
        connect(hostEntry, &QLineEdit::textEdited, this, &RegisterLayer::editHost);
        mhost->addWidget(hostLabel);
        mhost->addWidget(hostEntry);
        hostLayout->addLayout(mhost);

        mport = new QHBoxLayout();
        QLabel* portLabel = new QLabel("Port:");
        QLineEdit* portEntry = new QLineEdit();
        portEntry->setPlaceholderText("server port (defaults to 1883)");
        connect(portEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPort);
        mport->addWidget(portLabel);
        mport->addWidget(portEntry);
        hostLayout->addLayout(mport);

        musername = new QHBoxLayout();
        QLabel* usernameLabel = new QLabel("Username:");
        QLineEdit* usernameEntry = new QLineEdit();
        usernameEntry->setPlaceholderText("server username");
        connect(usernameEntry, &QLineEdit::textEdited, this, &RegisterLayer::editUsername);
        musername->addWidget(usernameLabel);
        musername->addWidget(usernameEntry);
        hostLayout->addLayout(musername);

        mpassword = new QHBoxLayout();
        QLabel* passwordLabel = new QLabel("Password:");
        QLineEdit* passwordEntry = new QLineEdit();
        passwordEntry->setPlaceholderText("server password");
        connect(passwordEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPassword);
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
        if(value.isEmpty()) pseudo = QUuid::createUuid().toString(QUuid::WithoutBraces);
        else pseudo = value;
    }

    void editPort(const QString &value)
    {
        if(value.isEmpty()) port = 1883;
        else port = value.toInt();
    }

    void editPassword(const QString &value)
    {
        if(value.isEmpty()) password = "ardent";
        else password = value;
    }

    void editUsername(const QString &value)
    {
        if(value.isEmpty()) username = "phoenix";
        else username = value;
    }

    void editHost(const QString &value)
    {
        if(value.isEmpty()) host = "10.3.0.218";
        else host = value;
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
