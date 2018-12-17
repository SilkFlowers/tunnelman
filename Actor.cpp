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
//only pick up by tunnel man
//T = max(100, 300 – 10*current_level_number)

WaterPool::WaterPool(int x, int y, StudentWorld* world):
Actor(TID_WATER_POOL ,x,y,world,right, 1, 2)
{
    
}

GoldNugget ::GoldNugget(int x, int y, StudentWorld *world):
Actor(TID_GOLD ,x,y,world,right, 1, 2)
{
    
}

void WaterPool:: doSomething()
{
    if ( !isAlive())
    {
        return;
    }
    
    //if the tunnelman is within 3 radius of water, add water ammo <=3.00
    //play sound SOUND_GOT_GOODIE if picked up
}


Boulder::Boulder(int x, int y, StudentWorld* world):
Actor(TID_BOULDER,x,y,world,down,1.0,1)
{
    isStable = true;
    isWaiting = false;
    isFalling = false;
}

void Boulder:: doSomething()
{
    if ( !isAlive())
    {
        return;
    }
    
}
void Boulder::dirtBelow()
{
    bool temp = false;
    for ( int x =getX(); x<getX()+4 ; x++)
    {
        if (getWorld()->getContentsOf(x,getY() - 1) == 1)
        {
            temp = true;
            break;
        }
    }
    if ( temp == false)
    {
        setState(false, false, true);
    }
}

bool Boulder:: Tick30()
{
    tickTime++;
    if (tickTime == 30 && FallReady())
    {
        tickTime = 0;
        setState(false, false, true);
        return true;
    }
    return false;
}

bool Boulder:: FallReady()
{
    bool tempIsDirt = true;
    bool tempIsBoulder = true;
    
    for (int x = 0; x < 4; x++)
    {
        if (getWorld()->getContentsOf(getX() + x, getY() - 1) ==0)
        {
            tempIsDirt = false;
        }
        else
        {
            //dirt exist
            tempIsDirt = true;
            break;
        }
        
        if (getWorld()->getContentsOf(getX(), getY()-1) ==0  )
            tempIsBoulder = false;
        else
        {
            //boulder exist
            tempIsBoulder = true;
            break;
        }
    }
    
    if (getY() > -1 && tempIsBoulder == false && tempIsDirt == false)
        return true;
    else
        return false;
}

void Boulder:: FallB()
{
    if ( FallReady())
    {
        moveTo(getX(), getY()-1);
    }
    else
    {
        //kill protestor,  FIX ME FIX ME
        setDead();
    }
    // boulder kills tunnelman if he is under. CHECK IF THE TUNNEL MAN IS THERE KILL HIM AND SWO
    
    
    
    
    //if (getWorld()->touchedByFrack(getX(), getY(), 3))
        //getWorld()->returnFrack()->setHitPts(0);
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
                
                if (getY() <60 && getDirection()==up)
                {
                    moveTo(getX(), getY() + 1);
                    getWorld()->setGridContent(getX(), getY(), 10);
                    getWorld()->setGridContent(getX(), getY()+1, TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(up);
                }
                break;
            case KEY_PRESS_DOWN:
                if (getY() >0 && getDirection() == down)
                {
                    moveTo(getX(), getY() - 1);
                    getWorld()->setGridContent(getX(), getY(), 10);
                    getWorld()->setGridContent(getX(), getY()-1, TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(down);
                }
                break;
            case KEY_PRESS_LEFT:
                if (getX() >0 && getDirection() == left)
                {
                    moveTo(getX() - 1, getY());
                    getWorld()->setGridContent(getX(), getY(), 10);
                    getWorld()->setGridContent(getX()-1, getY(), TID_PLAYER);
                    getWorld()->removeDirt(getX(), getY());
                }
                else
                {
                    setDirection(left);
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getX() <60 && getDirection() == right)
                {
                    moveTo(getX() + 1, getY());
                    getWorld()->setGridContent(getX(), getY(), 10);
                    getWorld()->setGridContent(getX()+1, getY(), TID_PLAYER);
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
WaterSquirt::WaterSquirt(int x, int y, StudentWorld * world, Direction dir) :
Actor(TID_WATER_SPURT, x, y, world, dir, 1.0, 1),ticksLeft(0)
{
    
}
void WaterSquirt::doSomething()
{
    ticksLeft++;
    int x = getX();
    int y = getY();
    if (ticksLeft == 8)
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
RegularProtester::RegularProtester(int x, int y, StudentWorld* world):
Actor(TID_PROTESTER, x, y, world, left, 1.0, 1),m_health(5),m_leaveField(false), ticksToWaitBetweenMoves(std::max(0, int(3-getWorld()->getLevel() / 4)))
{
    
}
void RegularProtester::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    
    if (m_health == 0)
    {
        m_leaveField = true;
        if (getX() == 60 && getY() == 60)
        {
            setDead();
        }
    }
}
int RegularProtester::numSquaresToMoveInCurrentDirection()const
{
    return (int)(rand() % 53 + 8);
}
