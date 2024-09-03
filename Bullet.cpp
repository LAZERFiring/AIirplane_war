#include "Bullet.h"


void Bullet::update()
{
    if(position.y() + width() < 0)
    {
        destroy();
    }
    Sprite::update();
}
