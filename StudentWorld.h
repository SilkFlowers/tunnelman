#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

const int TID_FREESPACE =10;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

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
    
    //void setObject(int x, int y, int ID);
    
    void setGridContent(int x, int y, int ID);
    
    void initWater ();
    
    void removeDirt(int a, int b);
    
    void shootWater(int x, int y);
    
    bool touchTunnelMan(int x, int y, int radius);
    
    double calcRad(int x1, int y1, int x2, int y2);
    bool WithinRadius();
    ~StudentWorld();
    
    bool    isValidSpotToMove(int col, int row) const;
    bool    isWithinRange_Boulder(int col, int row) const;
    bool    isEarthIndex(int col, int row) const;

    
private:
    std::vector<Actor*> m_actor;
    TunnelMan* m_tunnelman;
    Earth* m_field[64][64];
    int grid[64][64];
    int barrels_collected;
    int ticks_elapsed;
};

#endif // STUDENTWORLD_H_
