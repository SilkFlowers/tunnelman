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

Boulder::Boulder(int x, int y, StudentWorld* world):
Actor(TID_BOULDER,x,y,world,down,1.0,1)
{
    
}

TunnelMan::TunnelMan(StudentWorld* world):
Actor(TID_PLAYER,30,60,world),m_health(10),m_ammo(5),m_sonarCharge(1),m_goldNuggets(0)
{
    
}
//4 square long, size 1
//depth of 1
WaterSquirt :: WaterSquirt(int x, int y , StudentWorld * world , Direction dir):
Actor(TID_WATER_SPURT,x,y,world,dir,1.0,1)
{
    
}


void TunnelMan::doSomething()
{
    if (!isAlive())
    {
        return;
    }
    
    int KeyPressed = -1;
    if ( getWorld() -> getKey(KeyPressed))
    {
        switch (KeyPressed)
        {
            case  KEY_PRESS_UP:
                if ( getY() <60)
                {
                    setDirection(up);
                    moveTo( getX(),getY() +1);
                    
                    getWorld() -> removeDirt(getX(),getY());
                    

                }
                break;
            case KEY_PRESS_DOWN:
                if (getY() >0 )
                {
                    setDirection(down);
                    moveTo(getX(), getY()-1);

                   getWorld() -> removeDirt(getX(),getY());
                    

                }
                break;
            case KEY_PRESS_LEFT:
                if ( getX() >0)
                {
                    setDirection(left);
                    moveTo(getX()-1, getY());
                    getWorld() -> removeDirt(getX(),getY());

                }
                break;
            case KEY_PRESS_RIGHT:
                if ( getX() <60)
                {
                    setDirection(right);
                    moveTo(getX()+1, getY());
                    getWorld() -> removeDirt(getX(),getY());
                    
                }
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                //kill player
                break;
            case KEY_PRESS_SPACE:
            {
                if(getAmmo() <= 0)
                {
                    break;
                }
                shootWater(getWorld(), getDirection(),getX(),getY());
                break;
                //getWorld()->squirt(x, y, getDirection());
                break;
            }
            case 'Z':
            case 'z':
            {
                if(m_sonarCharge <= 0)
                    break;
                //getWorld()->revealSonar(getX(), getY());
                m_sonarCharge--;
            }
                
        }
    }
    
    
}
void TunnelMan:: shootWater(StudentWorld *world, GraphObject::Direction dir, int x, int y)
{
    if (getAmmo() <= 0 )
    {
        return;
    }
    else if (dir == right)
    {
        //WaterSquirt ();
    }
    else if ( dir == left)
    {
    }
    else if (dir == up)
    {
        
    }
    else if (dir == down)
    {
       // WaterSquirt();
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
