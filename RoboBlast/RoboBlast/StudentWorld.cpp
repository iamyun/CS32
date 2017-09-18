#include "StudentWorld.h"
#include "Level.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
	m_timeLimit = 3000;
	m_subLev = 0;
	m_newSubLev = 0;
	m_exit = nullptr;
	m_ammunition = 0;
	m_hitP = 20;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

void StudentWorld::addObject(GameObject* obj)
{
	objects[m_subLev].push_back(obj);
}

int StudentWorld::loadLevel()
{
	int curL = getLevel();

	//contruct main level's name in string and load it
	ostringstream oss;
	oss.setf(ios::fixed);
	if (curL < 10)
		oss << "level0" << curL << ".dat";
	else
		oss << "level" << curL << ".dat";
	string curLevel = oss.str();
	Level lev(assetDirectory());
	Level::LoadResult result = lev.loadLevel(curLevel);

	vector <GameObject*> m_obj;

	//return error is not loaded successfully
	if (result == Level::load_fail_file_not_found || result == Level::load_fail_bad_format)
		return GWSTATUS_LEVEL_ERROR;

	//if loaded successfully, insert all objects in the map to a 1D sublevel vector
	for (int r = 0; r < VIEW_HEIGHT; r++)
	{
		for (int c = 0; c < VIEW_WIDTH; c++)
		{
			GameObject *obj = nullptr;
			Level::MazeEntry value = lev.getContentsOf(c, r, 0);
			switch (value)
			{
			case Level::empty:
				break;
			case Level::player:
			{
				Player* obj = new Player(this, c, r, 0);
				m_player.push_back(obj);
				break;
			}
			case Level::wall:
			{
				obj = new Wall(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::fake_wall:
			{
				obj = new fakeWall(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::gold:
			{
				obj = new Gold(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::hostage:
			{
				obj = new Hostage(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::extra_life:
			{
				obj = new ExtraLife(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::restore_health:
			{
				obj = new RestoreHealth(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::ammo:
			{
				obj = new Ammo(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::robot_boss:
			{
				obj = new RobotBoss(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::vert_gangster:
			{
				obj = new Gangster(this, c, r, 0, 1);
				m_obj.push_back(obj);
				break;
			}
			case Level::horiz_gangster:
			{
				obj = new Gangster(this, c, r, 0, 2);
				m_obj.push_back(obj);
				break;
			}
			case Level::farplane_gun:
			{
				obj = new Farplane(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::gate0:
			{
				obj = new Gate(this, c, r, 0, 0);
				m_obj.push_back(obj);
				break;
			}
			case Level::gate1:
			{
				obj = new Gate(this, c, r, 0, 1);
				m_obj.push_back(obj);
				break;
			}
			case Level::gate2:
			{
				obj = new Gate(this, c, r, 0, 2);
				m_obj.push_back(obj);
				break;
			}
			case Level::gate3:
			{
				obj = new Gate(this, c, r, 0, 3);
				m_obj.push_back(obj);
				break;
			}
			case Level::gate4:
			{
				obj = new Gate(this, c, r, 0, 4);
				m_obj.push_back(obj);
				break;
			}
			case Level::gate5:
			{
				obj = new Gate(this, c, r, 0, 5);
				m_obj.push_back(obj);
				break;
			}
			case Level::exit:
			{
				m_exit = new Exit(this, c, r, 0);
				m_obj.push_back(m_exit);
				break;
			}
			case Level::bully_nest:
			{
				obj = new BullyNest(this, c, r, 0);
				m_obj.push_back(obj);
				break;
			}
			}
		}
	}
	//push the 1D sublevel vector to the vector of vector,
	//which keeps track of all objects in that level
	objects.push_back(m_obj);
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::loadSubLevel(int subLevel)
{
	int curL = getLevel();
	int subL = subLevel;

	//contruct the sublevel's map's string name
	ostringstream oss;
	oss.setf(ios::fixed);
	if (curL < 10)
		oss << "level0" << curL << '_' << subL << ".dat";
	else
		oss << "level" << curL << '_' << subL << ".dat";
	string curLevel = oss.str();
	Level lev(assetDirectory());
	Level::LoadResult result = lev.loadLevel(curLevel, subL);

	vector <GameObject*> s_obj;

	//if there's load error, return
	if (result == Level::load_sublevel_fail_file_not_found || result == Level::load_sublevel_fail_bad_format)
		return GWSTATUS_LEVEL_ERROR;

	//if loaded successfully, insert all the objects in the map to a 1D vector
	for (int r = 0; r < VIEW_HEIGHT; r++)
	{
		for (int c = 0; c < VIEW_WIDTH; c++)
		{
			GameObject *obj = nullptr;
			Level::MazeEntry value = lev.getContentsOf(c, r, subL);
			switch (value)
			{
			case Level::empty:
				break;
			case Level::player:
			{
				Player* obj = new Player(this, c, r, subL);
				m_player.push_back(obj);
				break;
			}
			case Level::wall:
			{
				obj = new Wall(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::fake_wall:
			{
				obj = new fakeWall(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::gold:
			{
				obj = new Gold(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::hostage:
			{
				obj = new Hostage(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::extra_life:
			{
				obj = new ExtraLife(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::restore_health:
			{
				obj = new RestoreHealth(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::ammo:
			{
				obj = new Ammo(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::robot_boss:
			{
				obj = new RobotBoss(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::vert_gangster:
			{
				obj = new Gangster(this, c, r, subL, 1);
				s_obj.push_back(obj);
				break;
			}
			case Level::horiz_gangster:
			{
				obj = new Gangster(this, c, r, subL, 2);
				s_obj.push_back(obj);
				break;
			}
			case Level::farplane_gun:
			{
				obj = new Farplane(this, c, r, subL);
				s_obj.push_back(obj);
				break;
			}
			case Level::gate0:
			{
				obj = new Gate(this, c, r, subL, 0);
				s_obj.push_back(obj);
				break;
			}
			case Level::gate1:
			{
				obj = new Gate(this, c, r, subL, 1);
				s_obj.push_back(obj);
				break;
			}
			case Level::gate2:
			{
				obj = new Gate(this, c, r, subL, 2);
				s_obj.push_back(obj);
				break;
			}
			case Level::gate3:
			{
				obj = new Gate(this, c, r, subL, 3);
				s_obj.push_back(obj);
				break;
			}
			case Level::gate4:
			{
				obj = new Gate(this, c, r, subL, 4);
				s_obj.push_back(obj);
				break;
			}
			case Level::gate5:
			{
				obj = new Gate(this, c, r, subL, 5);
				s_obj.push_back(obj);
				break;
			}
			case Level::bully_nest:
			{
				obj = new BullyNest(this, c, r, subL);
				s_obj.push_back(obj);
			}
			}
		}
	}
	//push the 1D sublevel vector to the vector of vector,
	//which keeps track of all objects in that level
	objects.push_back(s_obj);
	return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::finishLev()
//check if there's any robot boss or gold or hostage left
//if not, level is finished
{
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].size(); j++)
		{
			int id = objects[i][j]->getID();
			if (id == IID_GOLD || id == IID_ROBOT_BOSS || id == IID_HOSTAGE)
				return false;
		}
	}
	return true;
}

int StudentWorld::init()
{
	moveToSub(0);
	if (getLevel() > 1)
		return GWSTATUS_PLAYER_WON;
	int mainLevelResult = loadLevel();	//load main level
	for (int i = 1; i <= 5; i++)
	{
		//load all the sublevel until all of them are all loaded
		int subLevelResult = loadSubLevel(i);
		if (subLevelResult == GWSTATUS_LEVEL_ERROR)
			break;
	}
	return mainLevelResult;
}

int StudentWorld::move()
{
	//update the statistics on the top
	setDisplayText();

	//call all other objects to do something
	int originalSize = objects[m_subLev].size();
	for (int i = 0; i < originalSize; i++)
		objects[m_subLev][i]->doSomething();

	//call player to do something
	int playerSize = m_player.size();
	for (int i = 0; i < playerSize; i++)
		m_player[m_subLev]->doSomething();
	
	//if an object does something that cause the player to die
	//return player dead
	if (m_player[m_subLev]->isAlive() == false)
	{
		decLives();
		restoreHealth();
		m_ammunition = 0;
		m_timeLimit = 3000;
		return GWSTATUS_PLAYER_DIED;
	}

	//if the player finished the level and stepped on the exit
	//increase the score 1500 points and the remaining timelimit
	//and say player finished level
	if (m_exit->isAlive() == false)
	{
		increaseScore(1500);
		increaseScore(m_timeLimit);
		m_timeLimit = 3000;
		return GWSTATUS_FINISHED_LEVEL;
	}

	//delete actors that died during the tick
	vector<GameObject*>::iterator ap;
	ap = objects[m_subLev].begin();
	while (ap != objects[m_subLev].end())
	{
		if ((*ap)->isAlive() == false)
		{
			delete *ap;
			ap = objects[m_subLev].erase(ap);
		}
		else 
			ap++;
	}

	//reduce time limit each tick
	if (m_timeLimit <= 0)
	{
		m_timeLimit = 3000;
		return GWSTATUS_PLAYER_DIED;
	}
	else
		m_timeLimit--;

	//expose the exit on the current main level if 
	//player got all the gold, defeated all robot bosses and saved all hostages
	if (finishLev())
	{
		for (int i = 0; i < objects[m_subLev].size(); i++)
			objects[m_subLev][i]->setVisible(true);
	}

	//update current sublevel
	m_subLev = m_newSubLev;

	return GWSTATUS_CONTINUE_GAME;
}

//delete all the objects in the StudentWorld
void StudentWorld::cleanUp()
{
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects[i].size(); j++)
		{
			if (objects[i][j] != nullptr)
				delete objects[i][j];
		}
		objects[i].clear();
	}
	objects.clear();

	for (int p = 0; p < m_player.size(); p++)
	{
		if (m_player[p] != nullptr)
			delete m_player[p];
	}
	m_player.clear();

	life.clear();
}

//get Objects on the (x,y) square
vector<GameObject*>& StudentWorld::getObjects(int x, int y)
{ 
	getObj.clear();
	int p_x = m_player[m_subLev]->getX();
	int p_y = m_player[m_subLev]->getY();

	if (p_x == x && p_y == y)
	{
		getObj.push_back(m_player[m_subLev]);
	}

	for (int i = 0; i < objects[m_subLev].size(); i++)
	{
		int m_x = objects[m_subLev][i]->getX();
		int m_y = objects[m_subLev][i]->getY();

		if (m_x == x && m_y == y)
			getObj.push_back(objects[m_subLev][i]);
	}
	return getObj;
}


string StudentWorld::formatStatText(int score, int level, int sublevel, int lives, int health, int ammo, int bonus)
{
	ostringstream oss;
	oss << "Score: ";
	oss.fill('0');
	oss << setw(7) << score;
	oss << "  ";
	oss << "Level: ";
	oss.fill('0');
	oss << setw(2) << level;
	oss << "-";
	oss.fill('0');
	oss << setw(2) << sublevel;
	oss << "  ";
	oss << "Lives: ";
	oss << setw(2) << lives;
	oss << "  ";
	oss << "Health: ";
	oss << setw(3) << (health*100)/20;
	oss << "%  Ammo: ";
	oss << setw(3) << ammo;
	oss << "  TimeLimit: ";
	oss << setw(4) << bonus;
	return oss.str();
}

void StudentWorld::setDisplayText()
{
	int score = getScore();
	int level = getLevel();
	int subLevel = getCurrentSubLevel();
	unsigned int timeLimit = getTimeLimit();
	int livesLeft = getLives();

	string s = formatStatText(score, level, subLevel, livesLeft, m_hitP, m_ammunition, timeLimit);

	setGameStatText(s);
	
}