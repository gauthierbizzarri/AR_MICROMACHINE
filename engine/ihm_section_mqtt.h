#ifndef IHM_SECTIONMQTT_H
#define IHM_SECTIONMQTT_H

#include <QTabWidget>
#include <QLineEdit>

class IHM_SectionMqtt : public QWidget
{
    Q_OBJECT

    QLineEdit* leHost;
    QLineEdit* lePort;
    QLineEdit* leUser;
    QLineEdit* lePass;

public:
    IHM_SectionMqtt(QWidget *parent);

signals:
    void connectTo(QString host, int port, QString user, QString pass);

};

#endif // IHM_SECTIONMQTT_H
