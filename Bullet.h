﻿#ifndef BULLET_H
#define BULLET_H

#include"Sprite.h"
class Bullet : public Sprite
{
public:
    using Sprite::Sprite;
    void update()override;
};

#endif // BULLET_H
