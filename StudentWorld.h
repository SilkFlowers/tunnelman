#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <queue>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
const int TID_FREESPACE = 10;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
    }
    
    virtual int init();
    
    virtual int move();
    
    virtual void cleanUp();
    
    void textDisplay();
    
    int getContentsOf(int x, int y);
    
    void setGridContent(int x, int y, int ID);
    
    void removeDirt(int a, int b);
    
    void shootWater(int x, int y);
    
    TunnelMan* getTunnelMan()const;
    
    std::vector<Protester*> getProtestorVec();
    
    int RandInt(int lower, int upper);
 
    void decrementBarrelsNeeded();
    
    int getRandomNum(int max)const;
    int ticksBetweenProtestors();

    
    int getRestTicks();
    
    void makeCoordinate(int &x, int&y);
    
    bool isBoulder(int x, int y)const;
    
    //std::queue<int> computeShortestPath(int startX, int startY, int endX, int endY);
    
    ~StudentWorld();
    
    bool isTunnelAround(int x1, int y1);
    
    int canSeeTunnel(int x, int y);
    
    
    
private:
    std::vector<Actor*> m_actor;
    std::vector<Protester*> m_protestorVec;
    TunnelMan* m_tunnelman;
    Earth* m_field[64][64];
    int grid[64][64];
    int m_barrelsNeeded;
    int ticks_elapsed;
};

#endif // STUDENTWORLD_H_
