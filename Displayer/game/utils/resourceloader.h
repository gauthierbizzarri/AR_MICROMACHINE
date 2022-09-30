#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <QMap>
#include <QImage>

class ResourceLoader
{
private:
    QMap<QString, QImage> resources;
    static ResourceLoader* instance;

    ResourceLoader();
public:
    static ResourceLoader* getInstance();
    QImage get(QString id);
};

#endif // RESOURCELOADER_H
