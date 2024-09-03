#include "PlayerPlane.h"
#include "Manager.h"
#include "Bullet.h"
#include "Global.h"

void PlayerPlane::fire()
{
    //添加子弹
    auto b = new Bullet(0 ,0,":/Resource/images/bullet1.png");
    b->setPos(position.x() + width()/2,position.y());
    b->velocity.setY(-1);
    b->setType(EntityType::ET_Bullet);
    Mgr->addEntity(b);
}
