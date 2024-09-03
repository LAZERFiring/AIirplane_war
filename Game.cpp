#include "Game.h"
#include <QIcon>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "PlayerPlane.h"
#include <QKeyEvent>
#include "Map.h"
#include <QDebug>
#include "EnemyPlane.h"
#include <qrandom.h>
#include "Global.h"
#include "Bullet.h"


PlayerPlane *player;
Game::Game(QWidget *parent)
    : QWidget{parent}
{
    QTimer* timer = new QTimer(this);
    timer->callOnTimeout(this,[=]()
    {
        //更新数据
        updateGame();
        //绘图
        update();
    });
    timer->start(1000/60); //游戏帧率是多少？ 60fps
}

void Game::run()
{
    this->show();
}

void Game::initGame(int w, int h, const QString &title,const QIcon& icon)
{
    setFixedSize(w,h);
    setWindowTitle(title);
    if(!icon.isNull())
    {
        setWindowIcon(icon);
    }
    WIDTH = w;
    HEIGHT = h;
    globalElapsedTimer.start();

    map = new Map;
    player = Mgr->addEntity(new PlayerPlane(0,0,"://Resource/images/hero1.png"));
    player->setType(EntityType::ET_Player);

    auto anima = player->addAnimation("normal",new Animation);
    anima->addFrame(":/Resource/images/hero1.png");
    anima->addFrame(":/Resource/images/hero2.png");
    player->runAnimation("normal");

    auto animaBoom = player->addAnimation("boom",new Animation(200));
    animaBoom->addFrame(":/Resource/images/hero_blowup_n1.png");
    animaBoom->addFrame(":/Resource/images/hero_blowup_n2.png");
    animaBoom->addFrame(":/Resource/images/hero_blowup_n3.png");
    animaBoom->addFrame(":/Resource/images/hero_blowup_n4.png");

}

void Game::cleanGame()
{
    delete Mgr;
    delete map;
}

void Game::updateGame()
{
    Mgr->refersh();
    map->update();
    Mgr->update();
    //限制飞机范围
    if(player->position.x() + player->width()/2 < 0 )
    {
        player->position.setX(0 - player->width()/2);
    }
    if(player->position.x()+ player->width()/2 > Game::WIDTH)
    {
        player->position.setX(Game::WIDTH - player->width()/2);
    }
    if(player->position.y() < 0 )
    {
        player->position.setY(0);
    }
    if(player->position.y() + player->height()  > Game::HEIGHT )
    {
        player->position.setY(Game::HEIGHT - player->height());
    }
    //qInfo()<<player->position<<player->position.toPoint();

    static int i = 0;
    //发射子弹
    if(i % 30 == 0)
        player->fire();


    //敌机出场
    if(i % 60 == 0)
    {
        QStringList es ={":/Resource/images/enemy1.png",
                         ":/Resource/images/enemy2.png",
                         ":/Resource/images/enemy3_hit.png"};
        auto e = Mgr->addEntity(new EnemyPlane(0,0,es[QRandomGenerator::global()->bounded(3)]));
        e->setPos(QRandomGenerator::global()->bounded(Game::WIDTH - e->width()),-e->height());
        e->velocity.setY(1);
        e->setType(EntityType::ET_Enemy);

    }


    //碰撞检测
    for(auto e : Mgr->getEntityByType<EnemyPlane>(EntityType::ET_Enemy))
    {
        bool isboom = false;
        //子弹与敌机的碰撞
        for(auto b :  Mgr->getEntityByType<Bullet>(EntityType::ET_Bullet))
        {
            if(e->collider.intersects(b->collider))
            {
                b->destroy();
                e->destroy();
                isboom = true;
                break;
            }
        }
        //玩家与敌机的碰撞
        if(!isboom && player->collider.intersects(e->collider))
        {
            e->destroy();
            player->runAnimation("boom",true);
            //player->destroy();
            //close();
        }
    }


    i++;
}

void Game::drawGame(QPainter *painter)
{
    map->draw(painter);
    //由Manager来绘制的，有先后顺序
    Mgr->draw(painter);

}

void Game::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    drawGame(&painter);
}

void Game::closeEvent(QCloseEvent *ev)
{
    cleanGame();
}

void Game::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
    case Qt::Key_Up:
        player->velocity.setY(-1);
        break;
    case Qt::Key_Down:
        player->velocity.setY(1);
        break;
    case Qt::Key_Left:
        player->velocity.setX(-1);
        break;
    case Qt::Key_Right:
        player->velocity.setX(1);
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
    case Qt::Key_Up:
        player->velocity.setY(0);
        break;
    case Qt::Key_Down:
        player->velocity.setY(0);
        break;
    case Qt::Key_Left:
        player->velocity.setX(0);
        break;
    case Qt::Key_Right:
        player->velocity.setX(0);
        break;
    }
}
