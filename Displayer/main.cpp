#include "game/ui/mainwindow.h"

#include <QApplication>
#include <game/controller/controlleradapter.h>
#include <game/controller/keyboard/keyboardcontroller.h>
#include <game/controller/controllermanager.h>
#include <game/controller/gamepad/gamepadcontroller.h>
#include <game/utils/mqtt/mqttdialog.h>

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
