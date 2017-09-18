#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

//this class includes all objects
class GameObject : public GraphObject
{
public:
	GameObject(StudentWorld* world, int image, int x, int y, Direction dir, int sub_lev, bool display);
	virtual void doSomething() = 0;
	bool block(GameObject* ap);
	bool actBlock(GameObject* ap);
	StudentWorld* getWorld()
	{
		//return pointer to StudentWorld
		return m_world;
	}
	bool isAlive()
	{
		//check if object is alive
		return m_alive;
	}
	void setDead()
	{
		//set object to dead
		m_alive = false;
	}

	int subLev()
	{
		//return which sublevel it's in
		return m_subLev;
	}
private:
	StudentWorld *m_world;
	bool m_alive;
	int m_subLev;
};

class Wall : public GameObject
{
public:
	Wall(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
};

class fakeWall : public GameObject
{
public:
	fakeWall(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
};

class Bullet : public GameObject
{
public:
	Bullet(StudentWorld* world, int x, int y, Direction dir, int sub_lev);
	virtual void doSomething();
private:
	Direction m_dir;
	bool m_alive;
};

class Gate :public GameObject
{
public:
	Gate(StudentWorld* world, int x, int y, int sub_lev, int transTo);

	virtual void doSomething();
private:
	int m_goTo;
};

class Exit :public GameObject
{
public:
	Exit(StudentWorld* world, int x, int y, int sub_lev);

	virtual void doSomething();
private:

};

class BullyNest : public GameObject
{
public:
	BullyNest(StudentWorld* world, int x, int y, int sub_lev);

	virtual void doSomething();

	void getBullies();
private:
	std::vector<GameObject*> bullies;
};

//this include all the objects that have hit points
//player has its own count of hitPoint and ammunition count in syudent world
class Actor : public GameObject
{
public:
	Actor(StudentWorld* world, int image, int x, int y, Direction dir, int sub_lev, int hitPoints);
	virtual void doSomething() = 0;
	int getHitPoint()
	{
		//get how many hit point the actor (other than the player) has left
		return m_hitP;
	}
	void decHitPoint(int pt)
	{
		//decrement the hit point of the actor (other than player
		m_hitP -= pt;
	}
	virtual void attacked() = 0;
private:
	StudentWorld* m_world;
	int m_hitP;
};

//although this is an actor, it's changes of hitpoints are done in StudentWorld 
//instead of Actor.cpp
class Player : public Actor
{
public:
	Player(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
	virtual void attacked();
private:
	
};

//this include all the enemy classes
class BadGuys :public Actor
{
public:
	BadGuys(StudentWorld* world, int image, int x, int y, Direction dir, int sub_lev, int hitPoints);
	virtual void doSomething() = 0;
	int ObjectsInSight(int x, int y);
	bool shoot(Direction dir);
	bool move(Direction &dir);
	int getTick()
	{
		//return the tick that bad guys are at
		return m_tick;
	}
	int getTickMove()
	{
		//return the tick that they are suppose to move
		return tickToMove;
	}
	virtual void attacked() = 0;
	void countTick();	//update the tick
private:
	int tickToMove;
	int m_tick;
};

class Bully :public BadGuys
{
public:
	Bully(StudentWorld* world, int x, int y, int sub_lev);
	virtual void doSomething();
	std::vector<int>& refToGoodies()
	{
		return goodies;
	}
	bool cannotMove();
	virtual void attacked();
private:
	int distanceBeforeTurning;
	int m_dist;
	std::vector<int> goodies;
};

class Gangster :public BadGuys
{
public:
	Gangster(StudentWorld* world, int x, int y, int sub_lev, int dir);
	virtual void doSomething();
	virtual void attacked();
private:
	int m_hitPoints;
};

class RobotBoss :public BadGuys
{
public:
	RobotBoss(StudentWorld* world, int x, int y, int sub_lev);
	virtual void doSomething();
	virtual void attacked();
private:
};

class Waterpool :public Actor
{
public:
	Waterpool(StudentWorld* world, int x, int y, int sub_lev);
	virtual void doSomething();
	virtual void attacked() {};
private:
};

//this includes things that can be "picked up" by the player
class Goodies : public GameObject
{
public:
	Goodies(StudentWorld *world, int image, int x, int y, int sub_lev);
	virtual void doSomething() = 0;
	bool eaten();
private:
};

class Gold : public Goodies
{
public:
	Gold(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
private:

};

class Hostage : public Goodies
{
public:
	Hostage(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
private:
};

class ExtraLife : public GameObject
{
public:
	ExtraLife(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
private:
};

class RestoreHealth : public Goodies
{
public:
	RestoreHealth(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
private:
};

class Ammo : public Goodies
{
public:
	Ammo(StudentWorld *world, int x, int y, int sub_lev);
	virtual void doSomething();
private:
};

class Farplane : public Goodies
{
public:
	Farplane(StudentWorld* world, int x, int y, int sub_lev);
	virtual void doSomething();
private:
};

#endif // ACTOR_H_
