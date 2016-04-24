#include "Actor.h"
#include "StudentWorld.h"
#include "Level.h"
#include <queue>
#include <cmath>
using namespace std;

////// ZUMI IMPLEMENTATION //////

bool Zumi::attemptMove(int dir)
{
	// If a zumi can move in certain direction, move in that direction and return true; Otherwise, return false.
	switch(dir)
	{
		case 0: // MOVE NORTH
			if (getWorld()->zumiCanMoveTo(getX(), getY()+1))
			{
				moveTo(getX(), getY()+1);
				return true;
			}
				break;
		case 1:	// MOVE SOUTH
			if (getWorld()->zumiCanMoveTo(getX(), getY()-1))
			{
				moveTo(getX(), getY()-1);
				return true;
			}
				break;
		case 2: // MOVE EAST
			if (getWorld()->zumiCanMoveTo(getX()+1, getY()))
			{
				moveTo(getX()+1, getY());
				return true;
			}
				break;
		case 3: // MOVE WEST
			if (getWorld()->zumiCanMoveTo(getX()-1, getY()))
			{
				moveTo(getX()-1, getY());
				return true;
			}
				break;
	}
	return false;
}

////// SIMPLE ZUMI IMPLEMENTATION //////

void SimpleZumi::doSomething()
{
	if (isDead())
		return;
	
	increaseTicks();
	if (getTicks() == getTicksPerMove())
	{
		if (! attemptMove(getCurrentDirection()))
			setCurrentDirection((rand() % 4));
		resetTicks();
	}

}

void SimpleZumi::damage()
{
	// After a simple zumi has been hit by a bug spray, set it to dead, play sound effect, increase the score, and drop a goodie based off the probability.
	setDead();
	getWorld()->playSound(SOUND_ENEMY_DIE);
	getWorld()->increaseScore(100);
	if (getWorld()->canDropGoodie())
		getWorld()->addProperGoodie(getX(), getY());
}

////// COMPLEX ZUMI IMPLEMENTATION //////

void ComplexZumi::doSomething()
{
	if (isDead())
		return;
	if (getWorld()->isOnPlayer(getX(), getY()))
		getWorld()->setPlayerDead();

	increaseTicks();
	if (getTicks() == getTicksPerMove())
	{
		// If the Complex Zumi is within smell distance, check if a path exists to the Player.
		// Otherwise, move as if it were a SimpleZumi.
		if (isWithinSmellDistance())
		{
			// If the path exists attemptMove in currentDirection that has been set to a new direction.
			// Otherwise, attemptMove like a SimpleZumi with the currentDirection.
			if (isPath())
				attemptMove(getCurrentDirection());
			else if (! attemptMove(getCurrentDirection()))
			{
				setCurrentDirection((rand() % 4));
			}

			resetPath();
		}
		else
		{
			if (! attemptMove(getCurrentDirection()))
				setCurrentDirection((rand() % 4));
		}

		resetTicks();
	}

}

void ComplexZumi::damage()
{
	// After a complex zumi has been hit by a bug spray, set it to dead, play sound effect, increase the score, and drop a goodie based off the probability.
	setDead();
	getWorld()->playSound(SOUND_ENEMY_DIE);
	getWorld()->increaseScore(500);
	if (getWorld()->canDropGoodie())
		getWorld()->addProperGoodie(getX(), getY());
}

bool ComplexZumi::isWithinSmellDistance() const
{
	// Check if the Zumi is within smell distance of the Player.
	Player* p = getWorld()->getPlayer();
	int hDistance = abs(p->getX() - getX());
	int vDistance = abs(p->getY() - getY());
	
	return (hDistance <= m_smellDistance && vDistance <= m_smellDistance);
}

bool ComplexZumi::isPath()
{
	Player* p = getWorld()->getPlayer();

	// Check if there is a path to the Player by doing a breadth-first/queue search.
	// Push starting coordinates and update the level with 1 as discovered.
	queue<Coord> coordQueue;
	Coord start(getX(), getY());
	coordQueue.push(start);
	m_level[getY()][getX()] = 1;

	while (!coordQueue.empty())
	{
		// Pop the top coordinates and check if its position is equal to the end coordinates.
		Coord cur = coordQueue.front();
		coordQueue.pop();
		if (cur.x() == p->getX() && cur.y() == p->getY())
		{
			if (cur.dir() != -1)
				setCurrentDirection(cur.dir());
			return true;
		}

		// Check each place (n/s/e/w) <--> (0/1/2/3).
		if (m_level[cur.y()+1][cur.x()] == 0 && getWorld()->zumiCanMoveTo(cur.x(), cur.y()+1))
		{
			if (cur.dir() == -1)
				coordQueue.push(Coord(cur.x(),cur.y()+1, 0));
			else
				coordQueue.push(Coord(cur.x(), cur.y()+1, cur.dir()));
			m_level[cur.y()+1][cur.x()] = 1;
		}	// NORTH

		if (m_level[cur.y()-1][cur.x()] == 0 && getWorld()->zumiCanMoveTo(cur.x(), cur.y()-1))
		{
			if (cur.dir() == -1)
				coordQueue.push(Coord(cur.x(),cur.y()-1, 1));
			else
				coordQueue.push(Coord(cur.x(), cur.y()-1, cur.dir()));
			m_level[cur.y()-1][cur.x()] = 1;
		}	// SOUTH

		if (m_level[cur.y()][cur.x()+1] == 0 && getWorld()->zumiCanMoveTo(cur.x()+1, cur.y()))
		{
			if (cur.dir() == -1)
				coordQueue.push(Coord(cur.x()+1,cur.y(), 2));
			else
				coordQueue.push(Coord(cur.x()+1, cur.y(), cur.dir()));
			m_level[cur.y()][cur.x()+1] = 1;
		}	// EAST

		if (m_level[cur.y()][cur.x()-1] == 0 && getWorld()->zumiCanMoveTo(cur.x()-1, cur.y()))
		{
			if (cur.dir() == -1)
				coordQueue.push(Coord(cur.x()-1,cur.y(), 3));
			else
				coordQueue.push(Coord(cur.x()-1, cur.y(), cur.dir()));
			m_level[cur.y()][cur.x()-1] = 1;
		}	// WEST
	}

	// There is no path to the Player.
	return false;
}
		
void ComplexZumi::resetPath()
{
	// After checking for a path, reset to look again.
	for (int i = 0; i < VIEW_HEIGHT; i++)
		for (int k = 0; k < VIEW_WIDTH; k++)
			m_level[i][k] = 0;
}

////// EXTRA LIFE GOODIE IMPLEMENTATION //////

void ExtraLifeGoodie::doSomething()
{
	if (isDead())
		return;

	// Decrement its lifetime while its alive
	decLifetime();
	if (getLifetime() <= 0)
		setDead();

	// If a player is on the same spot as the goodie, give its effects and then set the goodie to dead to be removed.
	if (getWorld()->isOnPlayer(getX(), getY()))
	{
		getWorld()->incLives();
		getWorld()->increaseScore(1000);
		setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
}

////// WALK THROUGH WALLS GOODIE IMPLEMENTATION //////

void WalkThroughWallsGoodie::doSomething()
{
	if (isDead())
		return;
	
	decLifetime();
	if (getLifetime() <= 0)
		setDead();

	// If the player is on the goodie, inform the player of the effect before setting the goodie to dead.
	if (getWorld()->isOnPlayer(getX(), getY()))
	{
		// Set the effect's time duration and increase the score before setting the goodie to dead and playing the sounds.
		getWorld()->setWalkThroughEffect();
		getWorld()->increaseScore(1000);
		setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
}

////// INCREASE SIMULTANEOUS BUG SPRAYER GOODIE IMPLEMENTATION //////

void IncreaseSimultaneousBugSprayerGoodie::doSomething()
{
	if (isDead())
		return;

	decLifetime();
	if(getLifetime() <= 0)
		setDead();

	// If the player is on the goodie, inform the player of the effect before setting the goodie to dead.
	if (getWorld()->isOnPlayer(getX(), getY()))
	{
		// Set the effect's time duration, the new max number of sprayers, and increase the score before setting the goodie to dead and playing the sounds.
		getWorld()->setBoostedSprayerEffect();
		getWorld()->setNewMaxSprayers();
		getWorld()->increaseScore(1000);
		setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
}

////// BUG SPRAYER IMPLEMENTATION //////

void BugSprayer::doSomething()
{
	if (isDead())
	return;

	m_lifetime--;
	if (m_lifetime <= 0)
	{
		// Add Bug Spray objects in directions around the BugSprayer (doesn't go into permanent bricks).
		// Then set the BugSprayer to dead and play its sound.
		getWorld()->addBugSpray(getX(), getY());
		getWorld()->playSound(SOUND_SPRAY);
		setDead();
	}
}

////// BUG SPRAY IMPLEMENTATION //////

void BugSpray::doSomething()
{
	if (isDead())
		return;

	m_lifetime--;
	if (m_lifetime <= 0)
	{
		setDead();
	}

	// Destroy any targets on the spray that include zumis, destroyable bricks, players, and other bug sprayers.
	getWorld()->SprayDestroyPossibleTargets(getX(), getY());
}

////// PLAYER IMPLEMENTATION //////

void Player::doSomething()
{
	// If the player is dead, do nothing and return immediately.
	if (isDead())
		return;

	// Receive input from the user.
	// If the player can move in a certain direction, move to that certain spot.
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
			case KEY_PRESS_LEFT:
				if (getWorld()->playerCanMoveTo(getX()-1, getY()))
					moveTo(getX()-1, getY());
				break;
			case KEY_PRESS_RIGHT:
				if (getWorld()->playerCanMoveTo(getX()+1, getY()))
					moveTo(getX()+1, getY());
				break;
			case KEY_PRESS_DOWN:
				if (getWorld()->playerCanMoveTo(getX(), getY()-1))
					moveTo(getX(), getY()-1);
				break;
			case KEY_PRESS_UP:
				if (getWorld()->playerCanMoveTo(getX(), getY()+1))
					moveTo(getX(), getY()+1);
				break;
			case KEY_PRESS_SPACE:
				if (getWorld()->canDropSprayer(getX(), getY()))
					getWorld()->addSprayer(getX(), getY());
				break;
		}
	}

	// Check again if the player landed on a zumi or destroyable brick (w/o the effect) and set it to dead accordingly.
	if (getWorld()->isOnZumiOrDestroyableBrick(getX(), getY()))
	{
		setDead();
		getWorld()->playSound(SOUND_PLAYER_DIE);
		return;
	}

}

void Player::activateWalkThroughWalls()
{
	setWalkThroughStatus();
}

void Player::increaseSimultaneousSprayers()
{
	setBoostedSprayerStatus();
	getWorld()->setNewMaxSprayers();
}

////// EXIT IMPLEMENTATION //////

void Exit::doSomething()
{
	// If the exit is already exposed and the player is on the exit, set the level's status to be complete and play a sound; otherwise, return immediately.
	if (getWorld()->isExitExposed() && getWorld()->isOnPlayer(getX(), getY()))
	{
		getWorld()->playSound(SOUND_FINISHED_LEVEL);
		getWorld()->setCompletion();
	}
}

void Exit::exposeExit()
{
	// Show the exit once all zumis are dead.
	setVisible(true);
	getWorld()->playSound(SOUND_REVEAL_EXIT);
}