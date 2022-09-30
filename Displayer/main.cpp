#include "mainwindow.h"

#include <QApplication>
#include <controlleradapter.h>
#include <keyboardcontroller.h>
#include <controllermanager.h>
#include <gamepadcontroller.h>
#include <mqttdialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MqttDialog* dialog = new MqttDialog();
    MainWindow w(dialog);
    ControllerAdapter* controller = new KeyboardController();
    ControllerManager* manager = new ControllerManager(dialog);
    manager->setup(&w, controller);
    w.show();
    a.exec();
    delete controller;
    delete dialog;
    delete manager;
    return EXIT_SUCCESS;
}
