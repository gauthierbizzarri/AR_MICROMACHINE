#ifndef REGISTERLAYER_H
#define REGISTERLAYER_H

#include <displayview.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QUuid>
#include <QDebug>

class RegisterLayer : public DisplayView
{
    Q_OBJECT
private:
    QHBoxLayout* mpseudo;
    QHBoxLayout* mvehicle;
    QVBoxLayout* mroot;
    QString pseudo;
    QString vehicle;
public:
    RegisterLayer(QWidget* parent = nullptr): DisplayView(parent)
    {
        mroot = new QVBoxLayout();

        mpseudo = new QHBoxLayout();
        QLabel* pseudoLabel = new QLabel("Pseudo:");
        QLineEdit* pseudoEntry = new QLineEdit("my awsome pseudo");
        connect(pseudoEntry, &QLineEdit::textEdited, this, &RegisterLayer::editPseudo);
        mpseudo->addWidget(pseudoLabel);
        mpseudo->addWidget(pseudoEntry);

        QPushButton* ok = new QPushButton("Launch");
        connect(ok, &QPushButton::clicked, this, &RegisterLayer::accept);

        mroot->addLayout(mpseudo);
        mroot->addWidget(ok);
        setLayout(mroot);
    }
private slots:
    void editPseudo(const QString &value)
    {
        pseudo = value;
    }

    void accept(bool checked)
    {
        Q_UNUSED(checked);
        QUuid id = QUuid::createUuid();
        emit registered(id.toString(QUuid::WithoutBraces), pseudo, "car");
    }
signals:
    void registered(QString uuid, QString psueod, QString vehicle);

};

#endif // REGISTERLAYER_H
