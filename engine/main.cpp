
#include <QApplication>

#include "game_engine.h"
#include "controller.h"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifndef GAMEPAD_ONLY
    GameEngine::instance();
#endif

    Controller::createGamepad();

    return a.exec();
}
