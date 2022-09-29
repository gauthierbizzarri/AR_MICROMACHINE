#include "options.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

Options* Options::instance = nullptr;

Options::Options(): QObject()
{
    /*
    QString val;
    QFile file;
    file.setFileName("./options.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonParseError error;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8(), &error);
    if(error.error == QJsonParseError::NoError)
    {
        QJsonObject obj = d.object();
        fullScreen = obj.value("fullscreen").toBool(true);
        masterSound = obj.value("sound").toDouble(1);
        soundEffects = obj.value("soundeffects").toDouble(1);
        musicSound = obj.value("music").toDouble(1);
    }
    */

    fullScreen = 1;
    masterSound =1;
    soundEffects =1;
    musicSound =1;

    //else
    //{
    //    qWarning()<< "Option parse error: " << error.errorString();
    //}
}

Options *Options::getInstance()
{
    if(Options::instance == nullptr)
        Options::instance = new Options();
    return Options::instance;
}

void Options::apply()
{
    QJsonDocument doc;
    QJsonObject root;
    root.insert("fullscreen", fullScreen);
    root.insert("sound", masterSound);
    root.insert("soundeffects", soundEffects);
    root.insert("music", musicSound);
    doc.setObject(root);

    QFile file;
    file.setFileName("./options.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(doc.toJson());
        file.close();
        emit update(this);
    }
    else
    {
        qDebug()<<"not opened";
    }
}

