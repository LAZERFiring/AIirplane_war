#include "Sprite.h"
#include "Game.h"
Sprite::Sprite()
{

}

Sprite::Sprite(int x, int y, const QString &filename)
    :position(x,y)
{
    pixmap.load(filename);
}

Sprite::~Sprite()
{
    for(auto anima : animas)
    {
        delete anima;
    }
}

void Sprite::update()
{
    //position += QVector2D(1,1);
   position += speed * velocity;    //3 * 0
   collider = QRect(position.toPoint(),pixmap.size());
   if(currentAnima)
   {
       currentAnima->update();
       currentAnima->setPos(position);
       if(autoDel && currentAnima->finished())
       {
           destroy();
       }
   }
}

void Sprite::draw(QPainter *painter)
{
    if(!currentAnima)
        painter->drawPixmap(position.toPoint(),pixmap);
    else
        currentAnima->draw(painter);
}

void Sprite::setPos(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

void Sprite::moveBy(int dx, int dy)
{
    position+=QVector2D(dx,dy);
}

Animation *Sprite::addAnimation(const QString &tag, Animation *anima)
{
    if(!anima)
    {
        qWarning()<<"anima is nullptr";
        return nullptr;
    }
    if(animas.contains(tag))
    {
        qWarning()<<"The animation with the tag " + tag + " already exists";
        return anima;
    }
    animas.insert(tag,anima);
    return anima;
}

void Sprite::runAnimation(const QString &tag,bool autoDel)
{
    this->autoDel = autoDel;
    if(!animas.contains(tag))
    {
        qWarning()<<"The animation with the tag " + tag + " not exists";
        return;
    }
    currentAnima = animas.value(tag);
}

