#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int x, int y, StudentWorld* world, Direction dir, double size, unsigned int depth):
GraphObject(imageID,x,y,dir,size,depth),m_alive(true),worldPtr(world)
{
    setVisible(true);
}

Earth::Earth(int x, int y, StudentWorld* world):
Actor(TID_EARTH,x,y,world,right,.25,3)
{
    
}
Boulder::Boulder(int x, int y, StudentWorld* world) :
Actor(TID_BOULDER, x, y, world, down, 1.0, 1),m_fallState(0)
{
    
}

void Boulder::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    
    //0=stable, 1=waiting, 2=falling
    if (dirtBelow() && m_fallState==0)
    {
        return;
    }
    else if (m_fallState == 0)
    {
        m_fallState = 1;
    }
    else if (m_fallState == 1)
    {
        tickTime++;
        if (tickTime >= 30)
        {
            getWorld()->playSound(SOUND_FALLING_ROCK);
            m_fallState = 2;
        }
    }
    else if (m_fallState == 2)
    {
        int protesterX;
        int protesterY;
        int tunnelManX=getWorld()->getTunnelMan()->getX();
        int tunnelManY=getWorld()->getTunnelMan()->getY();
        double xSide;
        double ySide;
        double radius;
        for (size_t i = 0; i < getWorld()->getProtestorVec().size(); i++)
        {
            protesterX = getWorld()->getProtestorVec().at(i)->getX();
            protesterY = getWorld()->getProtestorVec().at(i)->getY();
            xSide = getX() - protesterX;
            ySide = getY() - protesterY;
            radius = sqrt(pow(xSide, 2.0) + pow(ySide, 2.0));
            
            if (radius <= 3)
            {
                getWorld()->getProtestorVec().at(i)->setAnnoyance(100);
            }
        }
        xSide = getX() - tunnelManX;
        ySide = getY() - tunnelManY;
        radius = sqrt(pow(xSide, 2.0) + pow(ySide, 2.0));
        if (radius <= 3)
        {
            getWorld()->getTunnelMan()->setDead();
        }
        
        if (getY() == 0 || getWorld()->getContentsOf(getX(), getY() - 1) == TID_EARTH || getWorld()->isBoulder(getX(),getY()-4))
        {
            setDead();
        }
        else
        {
            moveTo(getX(), getY() - 1);
        }
    }
    
}
bool Boulder::dirtBelow()
{
    for (int x = getX(); x<getX() + 4; x++)
    {
        if (getWorld()->getContentsOf(x, getY() - 1) == TID_EARTH)
        {
            return true;
        }
    }
    
    return false;
}
TunnelMan::TunnelMan(StudentWorld* world):
Actor(TID_PLAYER,30,60,world),m_health(10),m_ammo(5),m_sonarCharge(1),m_goldNuggets(0)
{
    
}
void TunnelMan::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    
    if (!isAlive())
    {
        return;
    }
    
    int KeyPressed = -1;
    if (getWorld()->getKey(KeyPressed))
    {
        switch (KeyPressed)
        {
            case  KEY_PRESS_UP:
                
                if (getY() <60 && getDirection()==up && !getWorld()->isBoulder(getX(),getY()+1))
                {
                    moveTo(getX(), getY() + 1);
                    //getWorld()->setGridContent(getX(), getY(), 10);
                    //getWorld()->setGridContent(getX(), getY()+1, TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(up);
                }
                break;
            case KEY_PRESS_DOWN:
                if (getY() >0 && getDirection() == down && !getWorld()->isBoulder(getX(), getY() - 1))
                {
                    moveTo(getX(), getY() - 1);
                    //getWorld()->setGridContent(getX(), getY(), 10);
                    //getWorld()->setGridContent(getX(), getY()-1, TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(down);
                }
                break;
            case KEY_PRESS_LEFT:
                if (getX() >0 && getDirection() == left && !getWorld()->isBoulder(getX()-1, getY()))
                {
                    moveTo(getX() - 1, getY());
                    //getWorld()->setGridContent(getX(), getY(), 10);
                    //getWorld()->setGridContent(getX()-1, getY(), TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(left);
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getX() <60 && getDirection() == right && !getWorld()->isBoulder(getX()+1, getY()))
                {
                    moveTo(getX() + 1, getY());
                    //getWorld()->setGridContent(getX(), getY(), 10);
                    //getWorld()->setGridContent(getX()+1, getY(), TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(right);
                }
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                //kill player
                break;
            case KEY_PRESS_SPACE:
            {
                getWorld()->shootWater(getX(), getY());
                break;
            }
            case 'Z':
            case 'z':
            {
                if (m_sonarCharge <= 0)
                    break;
                //getWorld()->revealSonar(getX(), getY());
                m_sonarCharge--;
            }
                
        }
    }
    
}
int TunnelMan::getHealth()const
{
    return m_health;
}
int TunnelMan::getAmmo()const
{
    return m_ammo;
}
int TunnelMan::getSonar()const
{
    return m_sonarCharge;
}
int TunnelMan::getGold()const
{
    return m_goldNuggets;
}
void TunnelMan::decrementAmmo()
{
    if (m_ammo > 0)
    {
        m_ammo--;
    }
}
void TunnelMan::incrementAmmo()
{
    m_ammo += 5;
}
void TunnelMan::incrementSonar()
{
    m_sonarCharge++;
}
WaterSquirt::WaterSquirt(int x, int y, StudentWorld * world, Direction dir) :
Actor(TID_WATER_SPURT, x, y, world, dir, 1.0, 1),m_ticksLeft(0)
{
    
}
void WaterSquirt::doSomething()
{
    m_ticksLeft++;
    int x = getX();
    int y = getY();
    if (m_ticksLeft == 8)
    {
        setDead();
    }
    else if (getDirection() == right)
    {
        if (x + 1 <= 60 && getWorld()->getContentsOf(x + 1, y) == 10)
        {
            moveTo(x + 1, y);
        }
        else
        {
            setDead();
        }
    }
    else if (getDirection() == left)
    {
        if (x - 1 >= 0 && getWorld()->getContentsOf(x - 1, y) == 10)
        {
            moveTo(x - 1, y);
        }
        else
        {
            setDead();
        }
    }
    else if (getDirection() == up)
    {
        if (y + 1 <= 60 && getWorld()->getContentsOf(x, y + 1) == 10)
        {
            moveTo(x, y+1);
        }
        else
        {
            setDead();
        }
    }
    else if (getDirection() == down)
    {
        if (y - 1 >= 0 && getWorld()->getContentsOf(x, y - 1) == 10)
        {
            moveTo(x, y-1);
        }
        else
        {
            setDead();
        }
    }
    
}
Goodie::Goodie(int imageID, int x, int y, StudentWorld * world, Direction dir, double size, unsigned int depth) :
Actor(imageID, x, y, world, dir, size, depth)
{
    
}
WaterPool::WaterPool(int x, int y, StudentWorld * world):
Goodie(TID_WATER_POOL, x, y, world, right, 1.0, 2),m_ticksLeft(std::max(100, int(300 - 10 * world->getLevel())))
{
    
}
void WaterPool::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    
    m_ticksLeft--;
    if (m_ticksLeft == 0)
    {
        setDead();
    }
    
    int tunnelManX = getWorld()->getTunnelMan()->getX();
    int tunnelManY = getWorld()->getTunnelMan()->getY();
    double xSide = getX() - tunnelManX;
    double ySide = getY() - tunnelManY;
    double radius = sqrt(pow(xSide, 2.0) + pow(ySide, 2.0));
    if (radius <= 3)
    {
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getTunnelMan()->incrementAmmo();
        getWorld()->increaseScore(500);
    }
}
BarrelOfOil::BarrelOfOil(int x, int y, StudentWorld * world):
Goodie(TID_BARREL, x, y, world, right, 1.0, 2)
{
    setVisible(false);
}
void BarrelOfOil::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    
    int tunnelManX = getWorld()->getTunnelMan()->getX();
    int tunnelManY = getWorld()->getTunnelMan()->getY();
    double xSide = getX() - tunnelManX;
    double ySide = getY() - tunnelManY;
    double radius = sqrt(pow(xSide, 2.0) + pow(ySide, 2.0));
    
    if (!isVisible() && radius <= 4)
    {
        setVisible(true);
        return;
    }
    
    if (radius <= 3)
    {
        setDead();
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()->increaseScore(1000);
        getWorld()->decrementBarrelsNeeded();
    }
}
GoldNugget::GoldNugget(int x, int y, StudentWorld *world) :
Goodie(TID_GOLD, x, y, world, right, 1.0, 2)
{
    
}
void GoldNugget::doSomething()
{
    
}
SonarKit::SonarKit(int x, int y, StudentWorld * world) :
Goodie(TID_SONAR,x,y,world,right,1.0,2),m_ticksLeft(std::max(100, int(300 - 10 * world->getLevel())))
{
    
}
void SonarKit::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    m_ticksLeft--;
    if (m_ticksLeft <= 0)
    {
        setDead();
    }
    
    int tunnelManX = getWorld()->getTunnelMan()->getX();
    int tunnelManY = getWorld()->getTunnelMan()->getY();
    double xSide = getX() - tunnelManX;
    double ySide = getY() - tunnelManY;
    double radius = sqrt(pow(xSide, 2.0) + pow(ySide, 2.0));
    
    if (radius <= 3)
    {
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(75);
    }
}
Protester::Protester(int imageID, int x, int y, StudentWorld* world, int hitPoints) :
Actor(imageID, x, y, world, left, 1.0, 0),m_leaveField(false),
m_ticksToWaitBetweenMoves(std::max(0, int(3 - world->getLevel() / 4))),m_annoyance(0)
{
    
}
int Protester::numSquaresToMoveInCurrentDirection()const
{
    return (int)(rand() % 53 + 8);
}



void Protester::setAnnoyance(int annoy)
{
    m_annoyance = annoy;
}



RegularProtester::RegularProtester(int x, int y, StudentWorld* world):
Protester(TID_PROTESTER, x, y, world, 5)
{
    state = "alive";
    m_restTicks = getWorld()->getRestTicks();
    m_nonRestTicks = 15;
    m_numSquares = getWorld()->RandInt(8, 60);
    m_hitPoints = 5;
}


void RegularProtester::doSomething()
{
    if (getHealth()<= 0)
        {
            setState(false);
            getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
            return;
        }
        if (m_restTicks != 0)
        {
            m_restTicks--;
            return;
        }
        if (m_restTicks == 0)
        {
            if (getWorld()->isTunnelAround(getX(), getY()))
            {
                if (m_nonRestTicks >= 15)
                {
                    getWorld()->playSound(SOUND_PROTESTER_YELL);
                    getWorld() -> getTunnelMan()-> setHealth(getHealth() -2);
                    m_nonRestTicks = 0;
                    m_restTicks = 25;
                    return;
                }
                else
                {
                    m_nonRestTicks++;
                    return;
                }
            }
            if (!getWorld()->isTunnelAround(getX(), getY()))
            {
                if (getWorld()->canSeeTunnel(getX(), getY()) == 1)
                {
                    setDirection(left);
                    moveTo(getX() - 1, getY());
                    m_restTicks = getWorld()->getRestTicks();
                    m_numSquares = 0;
                    m_nonRestTicks++;
                    return;
                }
                if (getWorld()->canSeeTunnel(getX(), getY()) == 2)
                {
                    setDirection(right);
                    moveTo(getX() + 1, getY());
                    m_restTicks = getWorld()->getRestTicks();
                    m_numSquares = 0;
                    m_nonRestTicks++;
                    return;
                }
                if (getWorld()->canSeeTunnel(getX(), getY()) == 3)
                {
                    setDirection(up);
                    moveTo(getX(), getY() + 1);
                    m_restTicks = getWorld()->getRestTicks();
                    m_numSquares = 0;
                    m_nonRestTicks++;
                    return;
                }
                if (getWorld()->canSeeTunnel(getX(), getY()) == 4)
                {
                    setDirection(down);
                    moveTo(getX(), getY() -1);
                    m_restTicks = getWorld()->getRestTicks();
                    m_numSquares = 0;
                    m_nonRestTicks++;
                    return;
                }
                if (m_numSquares <= 0)
                {
                    int x = getWorld()->RandInt(1, 4);
                    m_numSquares = getWorld()->RandInt(8, 60);
                    switch (x)
                    {
                        case 1:
                            setDirection(left);
                            break;
                        case 2:
                            setDirection(right);
                            break;
                        case 3:
                            setDirection(up);
                            break;
                        case 4:
                            setDirection(down);
                            break;
                    }
                    m_restTicks = getWorld()->getRestTicks();
                    return;
                    
                }
                if (getDirection() == left)
                {
                    if (getWorld()-> getContentsOf(getX()-1, getY()) == TID_EARTH || getX() - 1 <= 0)
                    {
                        m_numSquares = 0;
                        return;
                    }
                    moveTo(getX() - 1, getY());
                    m_numSquares--;
                    m_restTicks = getWorld()->getRestTicks();
                    m_nonRestTicks++;
                    return;
                }
                if (getDirection() == right)
                {
                    if (getWorld()->getContentsOf(getX()+4, getY())  || getX() + 4 > 63)
                    {
                        m_numSquares = 0;
                        return;
                    }
                    moveTo(getX() + 1, getY());
                    m_numSquares--;
                    m_restTicks = getWorld()->getRestTicks();
                    m_nonRestTicks++;
                    return;
                }
                if (getDirection() == up)
                {
                    if (getWorld()->getContentsOf(getX(), getY())  || getY() + 4 >= 60)
                    {
                        m_numSquares = 0;
                        return;
                    }
                    moveTo(getX(), getY() + 1);
                    m_numSquares--;
                    m_restTicks = getWorld()->getRestTicks();
                    m_nonRestTicks++;
                    return;
                }
                if (getDirection() == down)
                {
                    if (getWorld()->getContentsOf(getX(), getY()-1) || getY() - 1 <= 0)
                    {
                        m_numSquares = 0;
                        return;
                    }
                    moveTo(getX(), getY() - 1);
                    m_numSquares--;
                    m_restTicks = getWorld()->getRestTicks();
                    m_nonRestTicks++;
                    return;
                }
            }
            m_nonRestTicks++;
            moveTo(getX() - 1, getY());
            m_restTicks = getWorld()->getRestTicks();
        }
}

