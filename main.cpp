#include <QApplication>
#include "Game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;
    game.initGame(480,852,"MyGame");
    game.run();

    return a.exec();
}
