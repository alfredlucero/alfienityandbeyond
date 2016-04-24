#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <queue>

class StudentWorld;

////// ACTOR BASE CLASS //////

class Actor : public GraphObject
{
	public:
		Actor(int imageID, int startX, int startY, StudentWorld* world)
			: GraphObject(imageID, startX, startY), m_dead(false), m_world(world)
		{ 
			setVisible(true); 
		}
		virtual ~Actor(){}
		virtual void doSomething() = 0;

		void setDead() 
		{ 
			m_dead = true; 
		}

		bool isDead() const
		{
			return m_dead;
		}

		StudentWorld* getWorld() const
		{
			return m_world;
		}

	private:
		bool m_dead;
		StudentWorld* m_world;
};

////// ZUMI CLASSES //////

class Zumi : public Actor
{
	public:
		Zumi(int imageID, int startX, int startY, int ticksPerMove, StudentWorld* world)
			: Actor(imageID, startX, startY, world), m_ticksPerMove(ticksPerMove), m_ticks(0)
		{}

		virtual ~Zumi() {}
		virtual void doSomething() = 0;
		virtual void damage() = 0;
		bool attemptMove(int dir);
		
		void increaseTicks()
		{
			m_ticks++;
		}

		void resetTicks()
		{
			m_ticks = 0;
		}

		int getTicksPerMove() const
		{
			return m_ticksPerMove;
		}

		int getTicks() const
		{
			return m_ticks;
		}
		
	    void setCurrentDirection(int dir)
		{
			m_currentDirection = dir;
		}

		void setRandomDirection()
		{
			m_currentDirection = (rand() % 4);
		}

		int getCurrentDirection() const
		{
			return m_currentDirection;
		}

	private:
		int m_ticksPerMove;
		int m_ticks;
		int m_currentDirection;
};

class SimpleZumi : public Zumi
{
	public:
		SimpleZumi(int startX, int startY, int ticksPerMove, StudentWorld* world)
			: Zumi(IID_SIMPLE_ZUMI, startX, startY, ticksPerMove, world)
		{
			setCurrentDirection(rand() % 4);
		}

		// NON-INLINE FUNCTIONS
		virtual void doSomething();
		virtual void damage();
};

struct Coord
{
	Coord(int x, int y, int dir = -1)
		: m_x(x), m_y(y), m_firstDir(dir)
	{}

	int x() const { return m_x; }
	int y() const { return m_y; }
	int dir() const { return m_firstDir; }

	private:
		int m_x;
		int m_y;
		int m_firstDir;
};

class ComplexZumi : public Zumi
{
	public:
		ComplexZumi(int startX, int startY, int ticksPerMove, int smellDistance, StudentWorld* world)
			: Zumi(IID_COMPLEX_ZUMI, startX, startY, ticksPerMove, world), m_smellDistance(smellDistance)
		{
			setCurrentDirection(rand() % 4);
			for (int i = 0; i < VIEW_HEIGHT; i++)
				for (int k = 0; k < VIEW_WIDTH; k++)
					m_level[i][k] = 0;
		}

		virtual void doSomething();
		virtual void damage();
		bool isWithinSmellDistance() const;
		bool isPath();
		void resetPath();

	private:
		int m_level[VIEW_HEIGHT][VIEW_WIDTH];
		int m_smellDistance;
};

////// BRICK CLASSES //////

class Brick : public Actor
{
	public:
		Brick(int imageID, int startX, int startY, StudentWorld* world)
			: Actor(imageID, startX, startY, world) 
		{}
		virtual ~Brick() {}
		virtual void doSomething()
		{}
		virtual bool isPermanent() = 0;
};

class PermanentBrick : public Brick
{
	public:
		PermanentBrick(int startX, int startY, StudentWorld* world)
			: Brick(IID_PERMA_BRICK, startX, startY, world)
		{}
		virtual bool isPermanent()
		{
			return true;
		}
};

class DestroyableBrick : public Brick
{
	public:
		DestroyableBrick(int startX, int startY, StudentWorld* world)
			: Brick(IID_DESTROYABLE_BRICK, startX, startY, world)
		{}
		virtual bool isPermanent()
		{
			return false;
		}
};

////// GOODIE CLASSES //////

class Goodie : public Actor
{
	public:
		Goodie (int imageID, int startX, int startY, int lifetime, StudentWorld* world)
			: Actor(imageID, startX, startY, world), m_lifetime(lifetime)
		{}

		virtual ~Goodie() {}
		virtual void doSomething() = 0;

		void decLifetime()
		{
			m_lifetime--;
		}

		int getLifetime() const
		{
			return m_lifetime;
		}
	
	private:
		int m_lifetime;
};

class ExtraLifeGoodie : public Goodie
{
	public:
		ExtraLifeGoodie(int startX, int startY, int lifetime, StudentWorld* world)
			: Goodie (IID_EXTRA_LIFE_GOODIE, startX, startY, lifetime, world)
		{}
		virtual void doSomething();
};

class WalkThroughWallsGoodie : public Goodie
{
	public:
		WalkThroughWallsGoodie(int startX, int startY, int lifetime, StudentWorld* world)
			: Goodie(IID_WALK_THRU_GOODIE, startX, startY, lifetime, world)
		{}
		virtual void doSomething();

};

class IncreaseSimultaneousBugSprayerGoodie : public Goodie
{
	public:
		IncreaseSimultaneousBugSprayerGoodie(int startX, int startY, int lifetime, StudentWorld* world)
		: Goodie(IID_INCREASE_SIMULTANEOUS_SPRAYER_GOODIE, startX, startY, lifetime, world)
		{}
		virtual void doSomething();
};

////// BUGSPRAYER/BUGSPRAY CLASSES //////

class BugSprayer : public Actor
{
	public:
		BugSprayer(int startX, int startY, StudentWorld* world)
			: Actor(IID_BUGSPRAYER, startX, startY, world), m_lifetime(40)
		{}

		// NON-INLINE FUNCTIONS
		virtual void doSomething();

		void setChainReaction()
		{
			m_lifetime = 0;
		}

	private:
		int m_lifetime;
};

class BugSpray : public Actor
{
	public:
		BugSpray(int startX, int startY, StudentWorld* world)
			: Actor(IID_BUGSPRAY, startX, startY, world), m_lifetime(3)
		{}
		virtual void doSomething();

	private:
		int m_lifetime;
};

////// PLAYER CLASS //////

class Player : public Actor
{
	public:
		Player(int startX, int startY, StudentWorld* world)
			: Actor(IID_PLAYER, startX, startY, world), m_canDropMoreSprayers(false),
			m_canWalkThroughBricks(false)
		{};

		virtual void doSomething();
		void activateWalkThroughWalls();
		void increaseSimultaneousSprayers();

		bool getWalkThroughStatus() const
		{
			return m_canWalkThroughBricks;
		}

		bool getBoostedSprayerStatus() const
		{
			return m_canDropMoreSprayers;
		}

		void setWalkThroughStatus()
		{
			m_canWalkThroughBricks = true;
		}

		void setBoostedSprayerStatus()
		{
			m_canDropMoreSprayers = true;
		}

		void turnOffWalkThroughStatus()
		{
			m_canWalkThroughBricks = false;
		}

		void turnOffBoostedSprayerStatus()
		{
			m_canDropMoreSprayers = false;
		}
	private:	
		bool m_canWalkThroughBricks;
		bool m_canDropMoreSprayers;
};

////// EXIT CLASS //////

class Exit : public Actor
{
	public:
		Exit(int startX, int startY, StudentWorld* world)
			: Actor(IID_EXIT, startX, startY, world)
		{
			setVisible(false);
		}

		virtual void doSomething();
		void exposeExit();
};

#endif // ACTOR_H_
