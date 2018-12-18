

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




void WaterPool:: doSomething()
{
    if ( !isAlive())
    {
        return;
    }
    
    //if the tunnelman is within 3 radius of water, add water ammo <=3.00
    //play sound SOUND_GOT_GOODIE if picked up
}

GoldNugget ::GoldNugget(int x, int y, StudentWorld *world):
Actor(TID_GOLD ,x,y,world,right, 1, 2), GoldPick(false)
{
    setVisible(false);
}

void GoldNugget :: doSomething()
{
    if ( !isAlive())
    {
        return;
    }
    //if tunnelman is close by consume
    if (getWorld()-> calcRad(getX(),getY(),getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY() )<=3.00)
    {
        setDead();
        getWorld()-> playSound(SOUND_GOT_GOODIE);
        getWorld()->getTunnelMan()->incGold();
    }
    
    //if tunnelman is close by make visible
    if (getWorld()-> calcRad(getX(),getY(),getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY() )<=4.00)
    {
        setVisible(true);
        return;
    }
    
    
    //need getProtestor func
    if (getWorld()-> calcRad(getX(),getY(),getWorld()->getProtestor()->getX(), getWorld()->getProtestor()->getY() )<=3.00)
    {
        GoldPick = true;
        setDead();
        getWorld()->playSound( SOUND_PROTESTER_FOUND_GOLD);
        getWorld()->increaseScore(25);
        //take nearest path back to top right, bribed, leave the oil field
    }
    
    
    
    
    
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

//
void Protester::FindExitPath(char maze[64][64], int width, int height, int startX, int startY,
                             std::string path, std::string& pathToExit, bool &found, TunnelMan *& player)
{
    if (found) return;
    
    for (int i = 0; i < 4; i++) {
        int next_x = startX + direction[i][0];
        int next_y = startY + direction[i][1];
        
        if (i == 0) {
            if (next_x >= 0 && next_x <= width && next_y >= 0 && next_y <= height && !checkForObstacles(next_x+3, next_y, right, player)) {
                if (maze[next_x][next_y] == '.')
                {
                    maze[next_x][next_y] = 'X';
                    FindExitPath(maze, width, height, next_x, next_y, path + dir_path[i], pathToExit, found, player);
                    
                    if (!found)
                        maze[next_x][next_y] = '.';
                }
                if (next_x == 60 && next_y == 60)
                {
                    path += dir_path[i];
                    found = true;
                    pathToExit = path;
                }
            }
        }
        
        else if (i == 1) {
            if (next_x >= 0 && next_x <= width && next_y >= 0 && next_y <= height && !checkForObstacles(next_x, next_y, left, player)) {
                if (maze[next_x][next_y] == '.')
                {
                    maze[next_x][next_y] = 'X';
                    FindExitPath(maze, width, height, next_x, next_y, path + dir_path[i], pathToExit, found, player);
                    
                    if (!found)
                        maze[next_x][next_y] = '.';
                }
                
                else if (next_x == 60 && next_y == 60)
                {
                    path += dir_path[i];
                    found = true;
                    pathToExit = path;
                    
                }
            }
        }
        
        if (i == 2) {
            if (next_x >= 0 && next_x <= width && next_y >= 0 && next_y <= height && !checkForObstacles(next_x, next_y, up, player)) {
                if (maze[next_x][next_y] == '.')
                {
                    maze[next_x][next_y] = 'X';
                    FindExitPath(maze, width, height, next_x, next_y, path + dir_path[i], pathToExit, found, player);
                    
                    if (!found)
                        maze[next_x][next_y] = '.';
                }
                
                else if (next_x == 60 && next_y == 60)
                {
                    path += dir_path[i];
                    found = true;
                    pathToExit = path;
                    
                }
            }
        }
        
        if (i == 3) {
            if (next_x >= 0 && next_x <= width && next_y >= 0 && next_y <= height && !checkForObstacles(next_x, next_y-3, down, player)) {
                if (maze[next_x][next_y] == '.')
                {
                    maze[next_x][next_y] = 'X';
                    FindExitPath(maze, width, height, next_x, next_y, path + dir_path[i], pathToExit, found, player);
                    
                    if (!found)
                        maze[next_x][next_y] = '.';
                }
                
                else if (next_x == 60 && next_y == 60)
                {
                    path += dir_path[i];
                    found = true;
                    pathToExit = path;
                }
            }
        }
        
    }
}


void Protester::checkPerpenPath(int col, int row, Direction currDir, TunnelMan * player, std::vector<Direction>& dir) const
{
    StudentWorld * Game = player->getWorld();
    
    switch (currDir)
    {
            bool flag;
            
        case right: case left:
        {
            flag = true;
            
            for (int i = 0; i < 4; i++)
                if (!Game->isValidSpotToMove(col+i, row-1))
                    flag = false;
            
            if (flag) dir.push_back(down);
            
            flag = true;
            
            for (int i = 0; i < 4; i++)
                if (!Game->isValidSpotToMove(col+i, row+4))
                    flag = false;
            
            if (flag) dir.push_back(up);
        }
        case down: case up:
        {
            flag = true;
            
            for (int i = 0; i < 4; i++)
                if (!Game->isValidSpotToMove(col-1, row+i))
                    flag = false;
            
            if (flag) dir.push_back(left);
            
            flag = true;
            
            for (int i = 0; i < 4; i++)
                if (!Game->isValidSpotToMove(col+4, row+i))
                    flag = false;
            
            if (flag) dir.push_back(right);
            
        }
        case GraphObject::none:
            break;
    }
    
}


void Protester::doSomething(TunnelMan * player)
{
    
    StudentWorld * Game = player->getWorld();
    
    
    if (update(player)) return;
    else
    {
        decreShoutingTime();
        decreTicksSincePerpenMoves();
    }
    
    if (Game->isPlayerCloseBy(getX(), getY()) && !leaveOilFieldState() && getShoutingInterval() == 0)
    {
   //     Game->playSound(SOUND_PROTESTER_YELL);
        //player->decreHitpts(20);
  //      setShoutingInterval(15);
    }
    
    if (canSeePlayer(getX(), getY(), player))            //    If a player is in horizontal or vertical sight without objects in between
    {
        setNumSquaresToMoveInCurrentDirection(0);
        int currLevel = player->getWorld()->getLevel();
        int N = std::max(0, static_cast<int>(3 - currLevel / 4));
        setTicksToWaitBetweenMoves(N);
        return;
    }
    
    if (getTicksSincePerpenMoves() <= 0)
        GoToPerpenPath(player);
    
    if (getNumSquaresToMoveInCurrentDirection() > 0)
        GoToCurrDirection(player);
    else
        pickNewDirection(player);
    
    
    int currLevel = player->getWorld()->getLevel();
    int N = std::max(0, static_cast<int>(3 - currLevel / 4));
    setTicksToWaitBetweenMoves(N);
}


bool Protester::update(TunnelMan * player)
{
    if (getX() == 60 && getY() == 60 && leaveOilFieldState()) {
        setDead();
        return true;
    }
    
    if (getTicksToWaitBetweenMoves() > 0)
    {
        decreTicksToWaitBetweenMoves();
        return true;
    }
    
    if (leaveOilFieldState())
    {
        GoToExit(player);
        return true;
    }
    
    return false;
}

void Protester::GoToPerpenPath(TunnelMan * player)
{
    std::vector<Direction> perpenDir;
    
    checkPerpenPath(getX(), getY(), getDirection(), player, perpenDir);
    
    if (perpenDir.size() == 1) {
        setDirection(perpenDir[0]);
        setTicksSincePerpenMoves(200);
        
        int N = rand() % 53 + 8;
        setNumSquaresToMoveInCurrentDirection(N);
    }
    
    else if (perpenDir.size() > 1)
    {
        int i = rand() % perpenDir.size();
        
        setDirection(perpenDir[i]);
        setTicksSincePerpenMoves(200);
        
        int N = rand() % 53 + 8;
        setNumSquaresToMoveInCurrentDirection(N);
    }
}

void Protester::GoToCurrDirection(TunnelMan * player)
{
    StudentWorld * Game = player->getWorld();
    Direction currDir = getDirection();
    
    switch (currDir)
    {
        case up:
            if (Game->isValidSpotToMove(getX(), getY()+4))
                moveTo(getX(), getY()+1);
            else setNumSquaresToMoveInCurrentDirection(0);
            break;
        case down:
            if (Game->isValidSpotToMove(getX(), getY()-1))
                moveTo(getX(), getY()-1);
            else setNumSquaresToMoveInCurrentDirection(0);
            break;
        case right:
            if (Game->isValidSpotToMove(getX()+4, getY()))
                moveTo(getX()+1, getY());
            else setNumSquaresToMoveInCurrentDirection(0);
            break;
        case left:
            if (Game->isValidSpotToMove(getX()-1, getY()))
                moveTo(getX()-1, getY());
            else setNumSquaresToMoveInCurrentDirection(0);
            break;
    }
    
    decreNumSquaresToMoveInCurrentDirection();
}

void Protester::pickNewDirection(TunnelMan * player)
{
    StudentWorld * Game = player->getWorld();
    int N;
    Direction newDir;
    bool rightDir;
    
    do
    {
        rightDir = true;
        
        newDir = static_cast<Direction>(rand() % 4 + 1);                    // 1 to 4
        N = rand() % 53 + 8;                                                //    8 <= numSquaresToMoveInCurrentDirection <= 60
        
        setNumSquaresToMoveInCurrentDirection(N);
        
        switch (newDir)
        {
                
            case right:
                if (Game->isValidSpotToMove(getX()+1, getY()))
                    setDirection(right);
                else rightDir = false;
                break;
                
            case left:
                if (Game->isValidSpotToMove(getX()-1, getY()))
                    setDirection(left);
                else rightDir = false;
                break;
                
            case up:
                if (Game->isValidSpotToMove(getX(), getY()+1))
                    setDirection(up);
                else rightDir = false;
                break;
                
            case down:
                if (Game->isValidSpotToMove(getX(), getY()-1))
                    setDirection(down);
                else rightDir = false;
                break;
        }
    } while (!rightDir);
    
}

void Protester::GoToExit(TunnelMan * player)
{
    if (getPathToExit() == "") {
        std::string input;
        std::string exitPath;
        bool found = false;
        
        FindExitPath(maze, 60, 60, getX(), getY(), input, exitPath, found, player);
        setPathToExit(exitPath);
    }
    else
    {
        char currDir = getDirection();
        char Dir = getPathToExit()[0];
        getPathToExit().erase(0, 1);
        
        switch (Dir)
        {
            case 'W':
                if (currDir != left)
                    setDirection(left);
                moveTo(getX()-1, getY());
                break;
            case 'E':
                if (currDir != right)
                    setDirection(right);
                moveTo(getX()+1, getY());
                break;
            case 'N':
                if (currDir != up)
                    setDirection(up);
                moveTo(getX(), getY()+1);
                break;
            case 'S':
                if (currDir != down)
                    setDirection(down);
                moveTo(getX(), getY()-1);
                break;
        }
    }
    
    int currLevel = player->getWorld()->getLevel();
    int N = std::max(0, static_cast<int>(3 - currLevel / 4));
    setTicksToWaitBetweenMoves(N);
}


bool Protester::checkForObstacles(int col, int row, Direction dir, TunnelMan * player) const
{
    return false;
}



Protester::Protester(int imageID, int startX, int startY,StudentWorld *world, Direction dir, double size, unsigned int depth) :
Actor(imageID,startX,startY,world,dir,size,depth)
{
    memset(maze, '.', sizeof(maze));
}


bool Protester::canSeePlayer(int col, int row, TunnelMan * player)
{
    StudentWorld * Game = player->getWorld();
    int playerX = player->getX();
    int playerY = player->getY();
    int i = 0;
    
    if (col == playerX && row != playerY)                                //    if a player is in vertical sight
    {
        int distance = row - playerY;
        if (distance < 0)                                                //    if a player is above protester
        {
            while (distance + i != 0)
            {
                if (checkForObstacles(col, row+i, up, player))
                    return false;
                i++;
            }
            
            setDirection(up);
            moveTo(getX(), getY()+1);
            
            return true;
        }
        else                                                                //    if a player is below protester
        {
            while (distance - i != 0)
            {
                if (checkForObstacles(col, row-i, down, player))
                    return false;
                i++;
            }
            
            setDirection(down);
            moveTo(getX(), getY()-1);
            
            return true;
        }
    }
    
    else if (row == playerY && col != playerX)                            // if a player is in horizontal sight
    {
        int distance = col - playerX;
        
        if (distance < 0)                                                //    if a player is more right
        {
            while (distance + i != 0)
            {
                if (checkForObstacles(col+i, row, right, player))
                    return false;
                i++;
            }
            
            setDirection(right);
            moveTo(getX()+1, getY());
            
            return true;
            
        }
        else                                                                //    if a player is more left
        {
            while (distance - i != 0)
            {
                if (checkForObstacles(col-i, row, left, player))
                    return false;
                i++;
            }
            setDirection(left);
            moveTo(getX()-1, getY());
            return true;
        }
    }
    return false;
}

//
RegularProtestor::RegularProtestor(int x, int y, StudentWorld *world) :
Protester(TID_PROTESTER, 60, 60,world, left, 1.0, 0)
{
    int currLevel =  getWorld()->getLevel();
    int T = std::max(0, static_cast<int>(3 - currLevel / 4));
    int N = rand() % 53 + 8;
    
    setTicksToWaitBetweenMoves(T);
    setVisible(true);
//    setTicksToWaitBetweenTurns(200);
    setNumSquaresToMoveInCurrentDirection(N);
    setTicksSincePerpenMoves(0);
}




void RegularProtestor::doSomething()
{
    if (!isAlive())
    {
        return;
    }
  
}

