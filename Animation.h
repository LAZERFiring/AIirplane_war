#ifndef ANIMATION_H
#define ANIMATION_H

#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QVector2D>
class Animation
{
public:
    Animation(int speed = 500);
    //添加帧图
    void addFrame(const QString& filename);
    QPixmap getFrame(int index)const;
    qsizetype count()const;
    void setPos(const QVector2D& pos);

    void update();
    void draw(QPainter*painter);
    inline bool finished()const{return index == count() - 1;};

private:
    QList<QPixmap> pixmaps;
    int xPos = -100;
    int yPos = -100;
    int index = 0;
    int speed = 500;
};

#endif // ANIMATION_H
