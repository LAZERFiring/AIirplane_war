#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H

#include "Sprite.h  "
class PlayerPlane : public Sprite
{
public:
    using Sprite::Sprite;
    void fire();
};

#endif // PLAYERPLANE_H
