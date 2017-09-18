#include <iostream>
#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

GameObject::GameObject(StudentWorld* world, int image, int x, int y, Direction dir, int sub_lev, bool display)
	:GraphObject(image, x, y, dir, sub_lev)
{
	setVisible(display);
	m_world = world;
	m_alive = true;
	m_subLev = sub_lev;
}

//actos can't pass through these objects, bullet will be set to dead if collides with these objects
bool GameObject::block(GameObject* ap)
{
	if (ap != nullptr)
	{
		if (ap->getID() == IID_WALL || ap->getID() == IID_WATERPOOL || ap->getID() == IID_BULLY_NEST)
			return true;
	}
	return false;
}

//blocks the actors too, and bullet will damage those objects before setting itself to dead
bool GameObject::actBlock(GameObject* ap)
{
	if (ap != nullptr)
	{
		if (ap->getID() == IID_BULLY || ap->getID() == IID_GANGSTER || ap->getID() == IID_ROBOT_BOSS || ap->getID() == IID_PLAYER)
			return true;
	}
	return false;
}

//wall and fake wall doesn't do anything, it just get displayed
Wall::Wall(StudentWorld *world, int x, int y, int sub_lev)
	:GameObject(world, IID_WALL, x, y, none, sub_lev, true)
{

}

void Wall::doSomething()
{
	return;
}

fakeWall::fakeWall(StudentWorld *world, int x, int y, int sub_lev)
	:GameObject(world, IID_FAKE_WALL, x, y, none, sub_lev, true)
{

}

void fakeWall::doSomething()
{
	return;
}

//Bullet points to the same direction as the actor that new it
Bullet::Bullet(StudentWorld* world, int x, int y, Direction dir, int sub_lev)
	:GameObject(world, IID_BULLET, x, y, dir, sub_lev, true)
{
	m_dir = dir;
}

void Bullet::doSomething()
{
	//if not alive, just return
	if (!isAlive())
		return;

	int x = getX();
	int y = getY();
	
	//check if there's anything on its current spot
	const vector<GameObject*>& ap = getWorld()->getObjects(x, y);

	for (int i = 0; i < ap.size(); i++)
	{
		if (actBlock(ap[i]) && ap[i]->isAlive())
		{
			Actor* a = dynamic_cast<Actor*>(ap[i]);
			if (ap[i]->getID() == IID_PLAYER)
				getWorld()->decHitPoint(2);
			else
				a->decHitPoint(2);
			a->attacked();
			setDead();
			return;
		}
	}

	for (int i = 0; i < ap.size(); i++)
	{
		if (block(ap[i]) && ap[i]->isAlive())
		{
			setDead();
			return;
		}
	}

	//if didn't collides with the two types of blocks, move one square in the direction that it's pointing to
	if (m_dir == right)
	{
		moveTo(x + 1, y);
	}
	else if (m_dir == left)
	{
		moveTo(x - 1, y);
	}
	else if (m_dir == up)
	{
		moveTo(x, y + 1);
	}
	else if (m_dir == down)
	{
		moveTo(x, y - 1);
	}

	//check it's new spot after the moveTo
	const vector<GameObject*>& apAfter = getWorld()->getObjects(getX(), getY());
	for (int i = 0; i < apAfter.size(); i++)
	{
		//if collides with actors, damage the actors then set itself to dead
		if (actBlock(apAfter[i]) && ap[i]->isAlive())
		{
			Actor* a = dynamic_cast<Actor*>(ap[i]);
			if (ap[i]->getID() == IID_PLAYER)
				getWorld()->decHitPoint(2);
			else
				a->decHitPoint(2);
			a->attacked();
			setDead();
			return;
		}
	}

	//if collides with unmoved blocks, just set itself to dead
	for (int i = 0; i < apAfter.size(); i++)
	{
		if (block(apAfter[i]) && ap[i]->isAlive())
		{
			setDead();
		}
	}
}

Gate::Gate(StudentWorld* world, int x, int y, int sub_lev, int transTo)
	:GameObject(world, IID_GATE, x, y, none, sub_lev, true)
{
	m_goTo = transTo;
}

void Gate::doSomething()
{
	if (!isAlive())
		return;

	//if the player moved to the same square, set itself to dead and transport player to the correct sublevel
	if ((getWorld()->getPlayer()->getX() == getX()) && (getWorld()->getPlayer()->getY() == getY()))
	{
		setDead();
		getWorld()->moveToSub(m_goTo);
	}
}

Exit::Exit(StudentWorld* world, int x, int y, int sub_lev)
	:GameObject(world, IID_EXIT, x, y, none, sub_lev, false)
{

}

void Exit::doSomething()
{
	if (isVisible() && (getWorld()->getPlayer()->getX() == getX()) && (getWorld()->getPlayer()->getY() == getY()))
	{
		getWorld()->playSound(SOUND_FINISHED_LEVEL);
		setDead();
	}
}

BullyNest::BullyNest(StudentWorld* world, int x, int y, int sub_lev)
	:GameObject(world, IID_BULLY_NEST, x, y, none, sub_lev, true)
{
}

void BullyNest::getBullies()
{
	//count bullies in the region 3 left 3 right 3 up 3 down of the bully nest
	//store the pointers to the bullies to the vectors of bullies;
	for (int i = getX() - 3; i <= getX() + 3; i++)
	{
		for (int j = getY() - 3; j <= getY() + 3; j++)
		{
			if (i >= 0 && i < VIEW_WIDTH && j >= 0 && j < VIEW_WIDTH)
			{
				const vector<GameObject*>& ap = getWorld()->getObjects(i, j);
				for (int k = 0; k != ap.size(); k++)
				{
					if (ap[k]->getID() == IID_BULLY)
						bullies.push_back(ap[k]);
				}
			}
		}
	}
}

void BullyNest::doSomething()
{
	//if there are less than 3 bullies in the region
	getBullies();
	if (bullies.size() < 3)
	{
		//and none of the bullies are on the same square as the Bully Nest
		for (int i = 0; i < bullies.size(); i++)
		{
			if ((bullies[i]->getX() == this->getX()) && (bullies[i]->getY() == this->getY()))
			{
				bullies.clear();
				return;
			}
		}

		//then there's a 1 in 50 chance that a Bully will be created
		//push that bully to the vector in studentworld, play the right sound
		int random = rand() % 50;
		if (random == 15)
		{
			GameObject* bully = new Bully(getWorld(), getX(), getY(), subLev());
			getWorld()->addObject(bully);
			getWorld()->playSound(SOUND_BULLY_BORN);
		}
	}
	bullies.clear();
}

Actor::Actor(StudentWorld* world, int image, int x, int y, Direction dir, int sub_lev, int hitPoints)
	:GameObject(world, image, x, y, dir, sub_lev, true)
{
	m_hitP = hitPoints;	//all actors have life points
}

Player::Player(StudentWorld* world, int x, int y, int sub_lev)
	: Actor(world, IID_PLAYER, x, y, right, sub_lev, world->getHitPoint())
{

}

void Player::doSomething()
{
	//check if player is alive
	if (!isAlive())
		return;

	int ch;
	int x = getX();
	int y = getY();

	if (getWorld()->getKey(ch))
	{
		// user hit a key this tick!
		switch (ch)
		{
		case KEY_PRESS_ESCAPE:
			setDead();	//lose a life if user press the escape key
		case KEY_PRESS_SPACE:
		{	//add a Bullet in the square in front of the Player 
			//with the same direction as the player
			//if have ammunition;
			if (getWorld()->getAmmo() <= 0)
				return;
			GameObject *obj = nullptr;
			Direction dir = getDirection();
			int sub = subLev();
			switch (dir)
			{
			case left:
			{
				obj = new Bullet(getWorld(), x - 1, y, dir, sub);
				getWorld()->addObject(obj);
				break;
			}
			case right:
			{
				obj = new Bullet(getWorld(), x + 1, y, dir, sub);
				getWorld()->addObject(obj);
				break;
			}
			case down:
			{
				obj = new Bullet(getWorld(), x, y - 1, dir, sub);
				getWorld()->addObject(obj);
				break;
			}
			case up:
			{
				obj = new Bullet(getWorld(), x, y + 1, dir, sub);
				getWorld()->addObject(obj);
				break;
			}
			}
			getWorld()->decAmmo();
			getWorld()->playSound(SOUND_PLAYER_FIRE);
			break;
		}
		//move to different directions/squares base on the input from user
		case KEY_PRESS_LEFT:
		{
			vector<GameObject*> apL = getWorld()->getObjects(x - 1, y);
			setDirection(left);
			for (int i = 0; i < apL.size(); i++)
			{
				if (block(apL[i]) || actBlock(apL[i]))
					return;
			}
			moveTo(x - 1, y);	//move player to the left
			return;
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			vector<GameObject*> apR = getWorld()->getObjects(x + 1, y);
			setDirection(right);
			for (int i = 0; i < apR.size(); i++)
			{
				if (block(apR[i]) || actBlock(apR[i]))
					return;
			}
			moveTo(x + 1, y);	//move player to the right
			return;
			break;
		}
		case KEY_PRESS_DOWN:
		{
			vector<GameObject*> apD = getWorld()->getObjects(x, y - 1);
			setDirection(down);
			for (int i = 0; i < apD.size(); i++)
			{
				if (block(apD[i]) || actBlock(apD[i]))
					return;
			}
			moveTo(x, y - 1);	//move player to the right
			return;
			break;
		}
		case KEY_PRESS_UP:
		{
			vector<GameObject*> apU = getWorld()->getObjects(x, y + 1);
			setDirection(up);
			for (int i = 0; i < apU.size(); i++)
			{
				if (block(apU[i]) || actBlock(apU[i]))
					return;
			}
			moveTo(x, y + 1);	//move player to the right
			return;
		}
		}
	}
}

void Player::attacked()
{
	if (getWorld()->getHitPoint() <= 0 || !isAlive())
	{
		setDead();
		getWorld()->playSound(SOUND_PLAYER_DIE);
	}
	else
		getWorld()->playSound(SOUND_PLAYER_IMPACT);
}

Waterpool::Waterpool(StudentWorld* world, int x, int y, int sub_lev)
	:Actor(world, IID_WATERPOOL, x, y, right, sub_lev, 30)
{

}

//if waterpool is alive, it decrement its hitpoint by 1 every tick
//until its hitpoint is 0, set itself to dead
void Waterpool::doSomething()
{
	if (!isAlive())
		return;
	else
		decHitPoint(1);

	if (getHitPoint() <= 0)
		setDead();
}

//this includes bully, gangster, and robot boss
//all of them move slower than the player, the frequecy that they move
//depends on the level
BadGuys::BadGuys(StudentWorld* world, int image, int x, int y, Direction dir, int sub_lev, int hitPoints)
	:Actor(world, image, x, y, dir, sub_lev, hitPoints)
{
	tickToMove = (28 - world->getLevel()) / 4;
	if (tickToMove < 3)
		tickToMove = 3;
	m_tick = 0;
}

//this keeps track of what tick the bad guys are supposed to be in
void BadGuys::countTick()
{
	if (m_tick < tickToMove)
		m_tick++;
	else if (m_tick == tickToMove)
		m_tick = 1;
}

//check if the player is in the square
int BadGuys::ObjectsInSight(int x, int y)
{
	vector<GameObject*> ap = getWorld()->getObjects(x, y);
	if (ap.empty())
		return 0;
	else
	{
		for (int i = 0; i < ap.size(); i++)
		{
			//if there's something that can block the sight, return 1
			if (block(ap[i]) || ap[i]->getID() == IID_FAKE_WALL || (actBlock(ap[i]) && (ap[i]->getID() != IID_PLAYER)))
				return 1;
		}

		for (int i = 0; i < ap.size(); i++)
		{
			//if the player is in the square and there's no fake wall on the same square
			//then BadGuys can see the player, return 2
			if (ap[i]->getID() == IID_PLAYER)
				return 2;
		}

		//if there are no objects that can block the sight of the player, return 0
		return 0;
	}
}

//check if the bad guys should shoot
bool BadGuys::shoot(Direction dir)
{
	int x = getX();
	int y = getY();
	int sub = subLev();
	int i = x;
	int j = y;
	switch (dir)
	{
	case left:
	{
		//loop through all the squares that are left of the badGuys
		for (i = i - 1; i >= 0; i--)
		{
			int sight = ObjectsInSight(i, j);
			//if there's an object that can block the sight of the player, don't shoot
			//which means it appear before the player
			if (sight == 1)
				return false;
			//if the player is in the sight, shoot
			else if (sight == 2)
			{
				//create new bullet and push it into the vector in StudentWorld
				GameObject *obj = nullptr;
				obj = new Bullet(getWorld(), x - 1, y, dir, sub);
				getWorld()->addObject(obj);
				return true;
			}
		}
		break;
	}
	case right:
	{
		//loop through all the squares right of the bad guy
		for (i = i + 1; i < VIEW_WIDTH; i++)
		{
			//if player is in sight (sight == 2), shoot
			int sight = ObjectsInSight(i, j);
			if (sight == 1)
				return false;
			else if (sight == 2)
			{
				GameObject *obj = nullptr;
				obj = new Bullet(getWorld(), x + 1, y, dir, sub);
				getWorld()->addObject(obj);
				return true;
			}
		}
		break;
	}
	case up:
	{
		//loop through all the squares above the bad guy
		//shoot if player is in sight (sight == 2)
		for (j = j + 1; j < VIEW_HEIGHT; j++)
		{
			int sight = ObjectsInSight(i, j);
			if (sight == 1)
				return false;
			else if (sight == 2)
			{
				GameObject *obj = nullptr;
				obj = new Bullet(getWorld(), x, y + 1, dir, sub);
				getWorld()->addObject(obj);
				return true;
			}
		}
		break;
	}
	case down:
	{
		//loop through all the squares below the bad guys
		//shoot if player is in sight (sight == 2)
		for (j = j - 1; j >= 0; j--)
		{
			int sight = ObjectsInSight(i, j);
			if (sight == 1)
				return false;
			else if (sight == 2)
			{
				GameObject *obj = nullptr;
				obj = new Bullet(getWorld(), x, y - 1, dir, sub);
				getWorld()->addObject(obj);
				return true;
			}
		}
		break;
	}

	}
	return false;
}

//move the bad guys
bool BadGuys::move(Direction& dir)
{
	int x = getX();
	int y = getY();

	//base on the direction, if nothing is blocking their way
	//move to the adjacent square in the direction it is facing
	//if there's an obstacles blocking their way, then they turn around
	switch (dir)
	{
	case right:
	{
		vector<GameObject*> apR = getWorld()->getObjects(x + 1, y);
		for (int i = 0; i < apR.size(); i++)
		{
			if (block(apR[i]) || actBlock(apR[i]))
			{
				setDirection(left);
				return false;
			}
		}
		moveTo(x + 1, y);
		return true;
		break;
	}
	case left:
	{
		vector<GameObject*> apL = getWorld()->getObjects(x - 1, y);
		for (int i = 0; i < apL.size(); i++)
		{
			if (block(apL[i]) || actBlock(apL[i]))
			{
				setDirection(right);
				return false;
			}
		}
		moveTo(x - 1, y);
		return true;
		break;
	}
	case up:
	{
		vector<GameObject*> apU = getWorld()->getObjects(x, y + 1);
		for (int i = 0; i < apU.size(); i++)
		{
			if (block(apU[i]) || actBlock(apU[i]))
			{
				setDirection(down);
				return false;
			}
		}
		moveTo(x, y + 1);
		return true;
		break;
	}
	case down:
	{
		vector<GameObject*> apD = getWorld()->getObjects(x, y - 1);
		for (int i = 0; i < apD.size(); i++)
		{
			if (block(apD[i]) || actBlock(apD[i]))
			{
				setDirection(up);
				return false;
			}
		}
		moveTo(x, y - 1);
		return true;
		break;
	}
	}
}

Bully::Bully(StudentWorld* world, int x, int y, int sub_lev)
	:BadGuys(world, IID_BULLY, x, y, right, sub_lev, 5)
{
	distanceBeforeTurning = rand() % 6 + 1;
	m_dist = 0;
}

bool Bully::cannotMove()
{
	distanceBeforeTurning = rand() % 6 + 1;	//get the random distanceBeforeTurning
	Direction dir[4] = { right, left, up, down };
	int RandIndex = rand() % 4;
	Direction d = dir[RandIndex];	//pick a random direction
	for (int i = 0; i < 4; i++)
	{
		//remember which direction have checked already
		if (d == dir[i])
		{
			dir[i] = none;
			break;
		}
	}
	setDirection(d);
	bool attemptMove = move(d);	//attemp to move in the second direction
	if (attemptMove)
		return true;
	else	//if still can't move
	{
		for (int i = 0; i < 4; i++)
		{
			//only attempt to move to a new direction, will keep trying until successfully moved
			if (dir[i] != none)
			{
				setDirection(dir[i]);
				bool Attempt = move(dir[i]);
				dir[i] = none;
				if (Attempt == true)
					return true;
			}
		}
		setDirection(d);	//if visited all direction and can't move, set direction to d
		return false;
	}
}

void Bully::attacked()
{
	int x = getX();
	int y = getY();
	if (getHitPoint() <= 0 || !isAlive())
	{
		Bully* deadBully = dynamic_cast<Bully*>(this);
		vector<int> goodies = deadBully->refToGoodies();
		for (int g = 0; g < goodies.size(); g++)
		{
			GameObject* good = nullptr;
			switch (goodies[g])
			{
			case IID_EXTRA_LIFE:
			{
				good = new ExtraLife(getWorld(), x, y, subLev());
				getWorld()->addObject(good);
				break;
			}
			case IID_RESTORE_HEALTH:
			{
				good = new RestoreHealth(getWorld(), x, y, subLev());
				getWorld()->addObject(good);
				break;
			}
			case IID_AMMO:
			{
				good = new Ammo(getWorld(), x, y, subLev());
				getWorld()->addObject(good);
				break;
			}
			}
		}
		setDead();
		getWorld()->playSound(SOUND_ENEMY_DIE);
	}
	else
		getWorld()->playSound(SOUND_ENEMY_IMPACT);
}

void Bully::doSomething()
{
	if (!isAlive())
		return;

	countTick();

	if (getTick() == getTickMove())
	{
		//check if bully can shoot at player
		bool shootPlayer = shoot(getDirection());
		if (shootPlayer)
		{	//play the fire sound if it can shoot
			getWorld()->playSound(SOUND_ENEMY_FIRE);
			return;
		}
		else
		{
			//check if there are goodies to pick up
			int x = getX();
			int y = getY();
			vector<GameObject*> gds = getWorld()->getObjects(x, y);
			for (int i = 0; i < gds.size(); i++)
			{
				int id = gds[i]->getID();
				if (id == IID_AMMO || id == IID_EXTRA_LIFE || id == IID_RESTORE_HEALTH)
					//if there is goodies to pick up, steal it (set goodie to dead)
					//remember the goodies, so if it's killed, it will reappear
					//don't do anything at that tick after picking up goodies
				{
					goodies.push_back(id);
					getWorld()->playSound(SOUND_BULLY_MUNCH);
					gds[i]->setDead();
				}
			}

			//if there's no goodies to pick up and has not yet moved enough distance
			//try to move to the adjacent square in its direction
			if (m_dist < distanceBeforeTurning)
			{
				Direction go = getDirection();
				bool attemptMove = move(go);
				if (attemptMove == false)
				{
					if (!cannotMove())
						m_dist--;
				}
				m_dist++;
			}
			else
			{
				if (!cannotMove())
					m_dist = 0;
				else
					m_dist = 1;
			}
		}
	}
}

Gangster::Gangster(StudentWorld* world, int x, int y, int sub_lev, int dir)
	:BadGuys(world, IID_GANGSTER, x, y, right, sub_lev, 10)
{
	//start with 10 hit points, and it can either be a vertical gangster or horizontal gangster
	m_hitPoints = 10;
	if (dir == 1)
	{
		setDirection(down);
	}
	else
		setDirection(right);
}

void Gangster::attacked()
{
	if (getHitPoint() <= 0 || !isAlive())
	{//if a Gangster is killed, it forms a waterpool
	//user also gain 100 points
		GameObject* obj = new Waterpool(getWorld(), getX(), getY(), subLev());
		getWorld()->addObject(obj);
		getWorld()->increaseScore(100);
		setDead();
		getWorld()->playSound(SOUND_ENEMY_DIE);
	}
	else
		getWorld()->playSound(SOUND_ENEMY_IMPACT);
}

void Gangster::doSomething()
{
	if (!isAlive())
		return;

	//count its current tick, rest if not tick to move yet
	countTick();

	//if it's their tick to move
	if (getTick() == getTickMove())
	{
		//check if it should fire at the player
		bool shootPlayer = shoot(getDirection());
		//if can't fire at the player
		if (shootPlayer)
			//if it fires at the player, play the corresponding sound
			getWorld()->playSound(SOUND_ENEMY_FIRE);
		else
		{
			//move to the adjacent square in the direction it's facing
			Direction go = getDirection();
			move(go);
		}
	}
}

RobotBoss::RobotBoss(StudentWorld* world, int x, int y, int sub_lev)
	:BadGuys(world, IID_ROBOT_BOSS, x, y, right, sub_lev, 50)
{

}

void RobotBoss::attacked()
{
	if (getHitPoint() <= 0 || !isAlive())
	{	
		//if a robot boss is killed, user gain 100 points
		GameObject* obj = new Hostage(getWorld(), getX(), getY(), subLev());
		getWorld()->addObject(obj);
		getWorld()->increaseScore(100);
		setDead();
		getWorld()->playSound(SOUND_ENEMY_DIE);
	}
	else
		getWorld()->playSound(SOUND_ENEMY_IMPACT);
}

void RobotBoss::doSomething()
{
	if (!isAlive())
		return;

	countTick();

	//if it's their tick to move
	if (getTick() == getTickMove())
	{
		//check if it should fire at the player
		bool shootPlayer = shoot(getDirection());
		//if can't fire at the player
		if (shootPlayer)
			//if it fires at the player, play the corresponding sound
			getWorld()->playSound(SOUND_ENEMY_FIRE);
		else
		{
			//move to the adjacent square in the direction it's facing
			Direction go = getDirection();
			move(go);
		}
	}
}

Goodies::Goodies(StudentWorld *world, int image, int x, int y, int sub_lev)
	:GameObject(world, image, x, y, none, sub_lev, true)
{

}

bool Goodies::eaten()
//check if the player is in the same square as the goodies
{
	if ((getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()))
		return true;
	else
		return false;
}

Gold::Gold(StudentWorld * world, int x, int y, int sub_lev)
	:Goodies(world, IID_GOLD, x, y, sub_lev)
{

}

void Gold::doSomething()
{
	if (!isAlive())
		return;

	if (eaten())
	{
		//if the player is on the same square as the Gold
		//give user 100 points
		//play the right sound
		//set itself to dead
		getWorld()->increaseScore(100);
		getWorld()->playSound(SOUND_GOT_GOLD);
		setDead();
	}

}

Hostage::Hostage(StudentWorld * world, int x, int y, int sub_lev)
	:Goodies(world, IID_HOSTAGE, x, y, sub_lev)
{

}

void Hostage::doSomething()
{
	if (!isAlive())
		return;

	if (eaten())
	{
		//if the player is on the same square as the Gold
		//play the right sound
		//set itself to dead
		getWorld()->playSound(SOUND_GOT_GOODIE);
		setDead();
	}
}

ExtraLife::ExtraLife(StudentWorld * world, int x, int y, int sub_lev)
	:GameObject(world, IID_EXTRA_LIFE, x, y, none, sub_lev, false)
{
	
}

void ExtraLife::doSomething()
{
	if (!isAlive())
		return;

	//if (eaten())
	//{
	//	//if the player is on the same square as the Gold
	//	//give user 150 points
	//	//play the right sound
	//	//set itself to dead
	//	//tell StudentWorld that user gains extra life
	//	getWorld()->increaseScore(150);
	//	getWorld()->playSound(SOUND_GOT_GOODIE);
	//	getWorld()->incLives();
	//	setDead();
	//}
}

RestoreHealth::RestoreHealth(StudentWorld * world, int x, int y, int sub_lev)
	:Goodies(world, IID_RESTORE_HEALTH, x, y, sub_lev)
{

}

void RestoreHealth::doSomething()
{
	if (!isAlive())
		return;

	if (eaten())
	{
		//if the player is on the same square as the Gold
		//give user 250 points
		//play the right sound
		//set itself to dead
		//restore player to full health
		getWorld()->increaseScore(250);
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->restoreHealth();
		setDead();
	}
}

Ammo::Ammo(StudentWorld * world, int x, int y, int sub_lev)
	:Goodies(world, IID_AMMO, x, y, sub_lev)
{

}

void Ammo::doSomething()
{
	if (!isAlive())
		return;

	if (eaten())
	{
		//if the player is on the same square as the Gold
		//give user 150 points
		//play the right sound
		//set itself to dead
		//give player 25 rounds of ammunitions
		getWorld()->increaseScore(150);
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->addAmmo();
		setDead();
	}
}

Farplane::Farplane(StudentWorld* world, int x, int y, int sub_lev)
	:Goodies(world, IID_FARPLANE_GUN, x, y, sub_lev)
{

}

void Farplane::doSomething()
{
	if (!isAlive())
		return;

	if (eaten())
	{
		//set itself to dead
		setDead();
		//kill all the gangsters and bullies that are around it
		//where it's the center of a 9x9 grid
		for (int i = getX() - 4; i <= getX() + 4; i++)
		{
			for (int j = getY() - 4; j <= getY() + 4; j++)
			{
				if (i >= 0 && i < VIEW_WIDTH && j >= 0 && j < VIEW_WIDTH)
				{
					const vector<GameObject*>& ap = getWorld()->getObjects(i, j);
					for (int k = 0; k != ap.size(); k++)
					{
						if (ap[k]->getID() == IID_BULLY || ap[k]->getID() == IID_GANGSTER)
						{
							ap[k]->setDead();
							Actor* a = dynamic_cast<Actor*>(ap[k]);
							a->attacked();
						}
					}
				}
			}
		}
		//damage the player by 10 hit points
		getWorld()->playSound(SOUND_GOT_FARPLANE_GUN);
		getWorld()->decHitPoint(10);
		getWorld()->getPlayer()->attacked();
	}
}
