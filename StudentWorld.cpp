#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}
int StudentWorld::init()
{
    ticks_elapsed = 0;
    barrels_collected = 0;
    for (int i = 0; i<64; i++)
    {
        for (int j = 0; j<61; j++)
        {
            grid[i][j] = 0;
        }
    }
    barrels_collected = 0;
    m_tunnelman = new TunnelMan(this);
    
    //Initializing Earth
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            //Shaft
            if ((i >= 30 && i <= 33) && (j >= 4 && j <= 59))
            {

            }
            else {
                m_field[i][j] = new Earth(i, j,this);
                grid[i][j] = 1;
            }
        }
        
    }
//    for ( int j = 0 ; j < 64; j++)
//    {
//        for ( int i=30; i <34 ; i++)
//        {
//            m_field[i][j] -> setVisible(false);
//        }
//    }
    
    
    
    return GWSTATUS_CONTINUE_GAME;
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

void StudentWorld::textDisplay()
{
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
    int health = m_tunnelman->getHealth() * 10;
    int gold = m_tunnelman->getGold();
    int squirts = m_tunnelman->getAmmo();
    int sonar = m_tunnelman->getSonar();
    
    //change oil number
    int oil = 0;
    ostringstream oss;
    oss.setf(ios::fixed);
    // “Scr: 0321000 Lvl: 52 Lives: 3 Hlth: 80% Water: 20 Gld: 3 Sonar: 1 Oil Left: 2”
    oss << "Scr: " << setw(8) << setfill('0') << score << "  Lives " << lives << "  Lvl: "
    << setw(2) << setfill(' ') << level << "  Hlth: " << setw(3) << setfill(' ') << health
    << "%  Water:" << setw(2) << setfill(' ') << squirts << "  Gld: " << setw(2) << setfill(' ')
    << gold << "  Sonar: " << setw(2) << setfill(' ') << sonar << "  Oil Left" << setw(2) << setfill(' ') << oil;
    string text;
    text = oss.str();
    GameWorld::setGameStatText(text);
}
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    ticks_elapsed++;
    StudentWorld::textDisplay();
    m_tunnelman->doSomething();
    
    vector<Actor*>::iterator i;
    //Each actor moves.
    for (i = m_actor.begin(); i != m_actor.end(); i++)
    {
        if ((*i)->isAlive())
        {
            (*i)->doSomething();
            //If FrackMan dies
            if (!m_tunnelman->isAlive())
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
        }
    }
    //Remove dead objects
    for (i = m_actor.begin(); i != m_actor.end();)
    {
        if (!(*i)->isAlive())
        {
            delete *i;
            i = m_actor.erase(i);
        }
        else i++;
    }
    if (!m_tunnelman->isAlive())
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld:: getContent()
{
    //if ( )
    
    
    
    return false;
    
}
void StudentWorld:: removeDirt(int x , int y, Actor::Direction dir)
{
    //ERROR WHEN TRYING TO DIG EARTH THROUGH SHAFT FIX 
    switch( dir)
    {
        case Actor::right:
           m_field[x+3][y]->setVisible(false);
            m_field[x+3][y+1]->setVisible(false);
            m_field[x+3][y+2]->setVisible(false);
            m_field[x+3][y+3]->setVisible(false);
            break;
        case Actor::left:
            m_field[x][y]->setVisible(false);
            m_field[x][y+1]->setVisible(false);
            m_field[x][y+2]->setVisible(false);
            m_field[x][y+3]->setVisible(false);
            break;
    
        case Actor::up:
            m_field[x][y+3]->setVisible(false);
            m_field[x+1][y+3]->setVisible(false);
            m_field[x+2][y+3]->setVisible(false);
            m_field[x+3][y+3]->setVisible(false);
            break;
        case Actor::down:
            m_field[x][y]->setVisible(false);
            m_field[x+1][y]->setVisible(false);
            m_field[x+2][y]->setVisible(false);
            m_field[x+3][y]->setVisible(false);
    break;
    }

}
