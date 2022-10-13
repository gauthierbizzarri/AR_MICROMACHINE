#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <QMap>
#include <QImage>
#include <QMovie>

class ResourceLoader
{
private:
    QMap<QString, QImage> resources;
    QMap<QString, QMovie*> animations;
    static ResourceLoader* instance;

    ResourceLoader();
public:
    static ResourceLoader* getInstance();
    QImage getImage(QString id);
    QMovie* getAnimation(QString id);
};

#endif // RESOURCELOADER_H
