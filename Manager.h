#ifndef MANAGER_H
#define MANAGER_H

#include "Entity.h"
#include <QSet>
#include <QDebug>
#define Mgr Manager::getInstance()
class Manager
{
public:
    //获取管理的单例
    static Manager* getInstance()
    {
        static Manager* ins = nullptr;
        if(!ins)
        {
            ins = new Manager;
        }
        return ins;
    }
    template<typename T>
    T* addEntity(T* e)
    {
        entities.insert(e);
        return e;
    }
    template<typename T>
    QSet<T*> getEntityByType(int type)
    {
        QSet<T*> set;
        for(auto e : entities)
        {
            if(e->type() == type)
            {
                set.insert(static_cast<T*>(e));
            }
        }
        return set;
    }

    qsizetype count()const {return entities.count();}
    void update()
    {
        for(auto& e : entities)
        {
            e->update();
        }
    }
    void draw(QPainter*painter)
    {
        for(auto& e: entities)
        {
            e->draw(painter);
        }
    }
    void refersh()
    {
        entities.removeIf([](Entity* e)
        {
            if(!e->isActive())
            {
                qInfo()<<"destroyed"<<e->type();
                delete e;
                return true;
            }
            return false;
        });
    }
private:
    QSet<Entity*> entities; //所有的实体
    Manager(){};
};

#endif // MANAGER_H
