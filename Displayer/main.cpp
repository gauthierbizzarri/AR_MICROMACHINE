#include "mainwindow.h"

#include <QApplication>
#include <controlleradapter.h>
#include <keyboardcontroller.h>
#include <controllermanager.h>
#include <mqttdialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttDialog* dialog = new MqttDialog();
    MainWindow w(dialog);
    ControllerAdapter* controller = new KeyboardController();
    ControllerManager* manager = new ControllerManager(dialog);
    manager->setup(&w, controller);
    manager->start();
    w.show();
    dialog->establishConnection();
    a.exec();
    manager->stop();
    delete controller;
    delete dialog;
    return EXIT_SUCCESS;
}
