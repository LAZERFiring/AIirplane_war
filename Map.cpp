#include "Map.h"
#include "Game.h"
Map::Map()
{
    yPos1 = -Game::HEIGHT;
    yPos2 = 0;
    pixmap.load(":/Resource/images/background.png");
}

void Map::update()
{
    yPos1 += speed;
    if(yPos1>=0)
    {
        yPos1 = -Game::HEIGHT;
    }

    yPos2 += speed;
    if(yPos2>=Game::HEIGHT)
    {
        yPos2 = 0;
    }
}

void Map::draw(QPainter *painter)
{
    painter->drawPixmap(0,yPos1,pixmap);
    painter->drawPixmap(0,yPos2,pixmap);
}
