#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
private:
    bool m_alive;
    StudentWorld* worldPtr;
public:
    Actor(int imageID, int x, int y, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0);
    virtual ~Actor() {}
    void virtual doSomething() = 0;
    bool isAlive()const { return m_alive; }
    void setDead() { m_alive = false; }
    StudentWorld* getWorld() { return worldPtr; }
};







class Earth: public Actor
{
public:
    Earth(int x, int y, StudentWorld* world);
    virtual ~Earth() {}
    void virtual doSomething() {}
};




//GoldPick , GoldDrop

class GoldNugget: public Actor
{
private:
    bool GoldPick;
public:
    GoldNugget(int x , int y, StudentWorld * world);
    void virtual doSomething();
};




class WaterPool : public Actor
{
public:
    virtual ~WaterPool(){};
    WaterPool();
    void doSomething( );
};

class Boulder : public Actor
{
private:
    bool isStable;
    bool isFalling;
    bool isWaiting;
    int tickTime;
public:
    void setState(bool stable, bool waiting, bool falling)
    {
        isStable = stable;
        isWaiting = waiting;
        isFalling = falling;
    }
    void virtual dirtBelow();
    void virtual FallB();
    bool virtual FallReady();
    bool virtual Tick30();
    virtual bool canActorPassThroughMe() {return false;}
    Boulder(int x, int y, StudentWorld* world);
    virtual ~Boulder() {}
    void virtual doSomething();
};




class TunnelMan : public Actor
{
private:
    int m_health;
    int m_ammo;
    int m_sonarCharge;
    int m_goldNuggets;
public:
    TunnelMan(StudentWorld* world);
    virtual ~TunnelMan() {}
    void virtual doSomething();
    int getHealth()const;
    int getAmmo()const;
    int getSonar()const;
    int getGold()const;
    void decrementAmmo();
    void incGold(){m_goldNuggets += 10;}
};
class WaterSquirt : public Actor {
private:
    int ticksLeft;
public:
    WaterSquirt(int x, int y, StudentWorld * world, Direction dir);
    virtual ~WaterSquirt() {}
    void virtual doSomething();
};




class Protester : public Actor {
private:
    int m_health;
    bool m_leaveField;
    int ticksToWaitBetweenMoves;
    
    
    //
    
    void    GoToExit(TunnelMan * player);
    void    GoToPerpenPath(TunnelMan * player);
    void    GoToCurrDirection(TunnelMan * player);
    void    pickNewDirection(TunnelMan * player);
    bool    update(TunnelMan * player);
    
    
    int direction[4][2] = { {1,0},{ -1,0 }, {0,1}, {0,-1} };
    std::string dir_path[4] = { "E", "W", "N", "S" };
    std::string pathToExit;
    char maze[64][64];

    
    bool    checkForObstacles(int col, int row, Direction dir, TunnelMan * player) const;
    bool    canSeePlayer(int col, int row, TunnelMan * player);
    
    void    checkPerpenPath(int m_col, int m_row, Direction currDir,
                            TunnelMan * player, std::vector<Direction>& dir) const;
    
    void    FindExitPath(char maze[64][64], int width, int height, int startX, int startY,
                         std::string path, std::string& pathToExit, bool &found, TunnelMan *& player);
    
    int        shouting_interval = 0;
    bool    leaveOilField = false;
    int        TicksToWaitBetweenTurns = 0;
    int        TicksToWaitBetweenMoves = 0;
    int        TicksSincePerpenMoves;
    int        numSquaresToMoveInCurrentDirection = 0;
    
    //
    
public:
    Protester(int imageID, int startX, int startY,StudentWorld *world, Direction dir, double size , unsigned int depth );
    virtual ~Protester() {}
    void  doSomething(TunnelMan * player);
    
    
    
    
    
    //
    void    setPathToExit(std::string path)                    { pathToExit = path; };
    void    setTicksToWaitBetweenMoves(int T)                { TicksToWaitBetweenMoves = T; };
    void    setTicksToWaitBetweenTurns(int T)                { TicksToWaitBetweenTurns = T; };
    void    setNumSquaresToMoveInCurrentDirection(int T)    { numSquaresToMoveInCurrentDirection = T; };
    void    setShoutingInterval(int T)                        { shouting_interval = T; };
    void    setToLeaveOilFieldState()                        { leaveOilField = true; };
    void    setTicksSincePerpenMoves(int T)                    { TicksSincePerpenMoves = T; };
    
    
    // GETTERS //
    
    std::string& getPathToExit()                            { return pathToExit; };
    int         getTicksToWaitBetweenMoves() const                { return TicksToWaitBetweenMoves; };
    int         getTicksToWaitBetweenTurns() const                { return TicksToWaitBetweenTurns; };
    int         getShoutingInterval() const                    { return shouting_interval; };
    int         getNumSquaresToMoveInCurrentDirection() const    { return numSquaresToMoveInCurrentDirection; };
    int         getTicksSincePerpenMoves() const                { return TicksSincePerpenMoves; };
    bool     leaveOilFieldState() const                        { return leaveOilField; };
    
    
    // INCREASE && DECREASE //
    void     decreTicksToWaitBetweenMoves()                    { TicksToWaitBetweenMoves--; };
    void        decreNumSquaresToMoveInCurrentDirection()        { if (numSquaresToMoveInCurrentDirection > 0) numSquaresToMoveInCurrentDirection--; }
    void     decreTicksSincePerpenMoves()                    { if (TicksSincePerpenMoves > 0) TicksSincePerpenMoves--; };
    void     decreShoutingTime()                            { if (shouting_interval > 0) shouting_interval--; };
    
    
    //int numSquaresToMoveInCurrentDirection()const;
};


class Regular_Protestor : Protester
{
public:
    void doSomething();
    Regular_Protestor(int x, int y, StudentWorld *world);
    void numSquaresToMoveInCurrentDirection() const;

};

class Hardcore_Protester: Regular_Protestor
{
    
};


#endif // ACTOR_H_
