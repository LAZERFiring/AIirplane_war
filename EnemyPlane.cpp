#include "EnemyPlane.h"
#include "Game.h"

void EnemyPlane::update()
{
    if(position.y() > Game::HEIGHT)
    {
        destroy();
    }
    Sprite::update();
}
