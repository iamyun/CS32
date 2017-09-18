#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	std::vector<GameObject*>& getObjects(int x, int y);
	void addObject(GameObject* obj);
	std::string formatStatText(int score, int level, int sublevel, int lives, int health, int ammo, int bonus);
	void setDisplayText();
	bool finishLev();
	virtual int getCurrentSubLevel()
    {
		//return the current sublevel
        return m_subLev; 
	}
	void moveToSub(int sub)
	{
		//get what's the sublevel to move to
		m_newSubLev = sub;
	}
	Player* getPlayer()
	{
		return m_player[m_subLev];
	}
	int getTimeLimit()
	{
		return m_timeLimit;
	}
	int getAmmo()
	{
		//check how many ammunitions the player has
		return m_ammunition;
	}
	void addAmmo()
	{
		//increase the ammunition that player has
		m_ammunition += 25;
	}
	void decAmmo()
	{
		m_ammunition--;
	}
	void restoreHealth()
	{
		//retore to full health, 20 hit points
		m_hitP = 20;
	}
	void decHitPoint(int damaged)
	{
		m_hitP -= damaged;
	}
	int getHitPoint()
	{
		return m_hitP;
	}
private:
	std::vector< std::vector <GameObject*> > objects;
	std::vector <GameObject*> getObj;
	std::vector<GameObject*> life;
	std::vector <Player*> m_player;
	GameObject* m_exit;
	int m_timeLimit;
	int loadLevel();
	int loadSubLevel(int subLevel);
	int m_subLev;
	int m_newSubLev;
	int m_ammunition;
	int m_hitP;
};

#endif // STUDENTWORLD_H_
