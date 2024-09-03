#ifndef SPRITE_H
#define SPRITE_H
#include "Entity.h"
#include <QVector2D>
#include "Animation.h"
#include <QMap>
class Sprite : public Entity
{
public:
    Sprite();
    Sprite(int x,int y,const QString& filename);
    ~Sprite();
    void update()override;
    void draw(QPainter*painter)override;

    void setPos(int x,int y);
    void moveBy(int dx,int dy);
    inline int width()const{return pixmap.width();};
    inline int height()const{return pixmap.height();};

    Animation* addAnimation(const QString& tag,Animation * anima);
    void runAnimation(const QString& tag,bool autoDel = false);
public:
    QVector2D position; //坐标
    QPixmap pixmap;     //精灵图

    QVector2D velocity;
    int speed = 3;              //速度

    QRect collider;  //碰撞器

private:
    QMap<QString,Animation*> animas;
    Animation * currentAnima = nullptr;
    bool autoDel = false;
};

#endif // SPRITE_H
