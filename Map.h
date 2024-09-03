#ifndef MAP_H
#define MAP_H
#include "Entity.h"
class Map : public Entity
{
public:
    Map();
    void update()override;
    void draw(QPainter*painter)override;
private:
    QPixmap pixmap;
    int yPos1;
    int yPos2;
    int speed = 2;
};

#endif // MAP_H
