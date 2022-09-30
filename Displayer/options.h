#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>


class Options : public QObject
{
    Q_OBJECT
public:
    bool fullScreen = false;
    float masterSound = 1;
    float musicSound = 1;
    float soundEffects = 1;
private:
    static Options* instance;
    Options();
public:
    static Options* getInstance();
    void apply();
signals:
    void update(const Options* options);
};

#endif // OPTIONS_H
