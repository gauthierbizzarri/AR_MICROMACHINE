
#include <QApplication>
#include "game_engine.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //GameEngine engine;

    Controller::createGamepad();


    return a.exec();
}
