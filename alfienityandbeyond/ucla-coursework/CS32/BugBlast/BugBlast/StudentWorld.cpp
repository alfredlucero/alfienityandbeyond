#include "StudentWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

////// STUDENTWORLD IMPLEMENTATIONS //////

GameWorld* createStudentWorld()
{
	return new StudentWorld();
}

////// LOCATION CHECK FUNCTIONS //////

Actor* StudentWorld::getAnActorAtTheProposedLocation(int x, int y) const
{
	// If an actor is at a certain location, return a pointer to that actor; otherwise, return a nullptr.
	for (int it = 0; it != m_vector.size(); it++)
	{
		if (m_vector[it]->getX() == x && m_vector[it]->getY() == y)
			return m_vector[it];
	}
	return nullptr;
}

Player* StudentWorld::getPlayer() const
{
	return m_player;
}

void StudentWorld::exposeTheExitInTheMaze()
{
	// If the level is already completed, that means the exit is already exposed.
	if (m_exitExposed)
		return;

	// Expose the exit and set level completion to true so that the exit will not be setVisible(true) more than once.
	Exit* ep;
	for (int i = 0; i != m_vector.size(); i++)
	{
		ep = dynamic_cast<Exit*>(m_vector[i]);
		if (ep != nullptr)
		{
			ep->exposeExit();
			m_exitExposed = true;
		}
	}
}

bool StudentWorld::playerCanMoveTo(int x, int y) const
{
	// If there is no actor in the spot where the actor is trying to go, return true;
	Actor* ap = getAnActorAtTheProposedLocation(x, y);
	if (ap == nullptr)
		return true;

	// If there is a brick there, check to see if it's a destroyable brick. The player can only go through
	// destroyable bricks if it has received a goodie to walk through bricks. Permanent bricks are not allowed.
	Brick* bp = dynamic_cast<Brick*>(ap);
	if (bp == nullptr)
		return true;
	else
	{
		DestroyableBrick* dp = dynamic_cast<DestroyableBrick*>(ap);
		if (dp != nullptr && (m_player->getWalkThroughStatus()))
			return true;
		else
			return false;
	}
}

bool StudentWorld::zumiCanMoveTo(int x, int y) const
{
	// If the zumi attempts to move into a bug sprayer or brick, return false; otherwise return true;
	Actor* ap = getAnActorAtTheProposedLocation(x, y);
	if (ap == nullptr)
		return true;

	Brick* bp = dynamic_cast<Brick*>(ap);
	BugSprayer* bsp = dynamic_cast<BugSprayer*>(ap);
	if (bp != nullptr || bsp != nullptr)
		return false;
	else
		return true;
}

bool StudentWorld::isOnZumiOrDestroyableBrick(int x, int y) const
{
	// If the player is on a zumi or a destroyable brick when it is not supposed to, return true; otherwise, return false.
	Zumi* zp;
	DestroyableBrick* dp;
	for (int i = 0; i != m_vector.size(); i++)
	{
		zp = dynamic_cast<Zumi*>(m_vector[i]);
		dp = dynamic_cast<DestroyableBrick*>(m_vector[i]);
		if (zp != nullptr && zp->getX() == x && zp->getY() == y)
			return true;
		else if (dp != nullptr && !m_player->getWalkThroughStatus() && dp->getX() == x && dp->getY() == y)
			return true;
	}
	return false;
}

bool StudentWorld::isOnPlayer(int x, int y) const
{
	// Check whether or not an actor is on the same position as a player.
	return (m_player->getX() == x && m_player->getY() == y);
}

////// SPRAY/SPRAYER/GOODIE RELATED FUNCTIONS //////

void StudentWorld::SprayDestroyPossibleTargets(int x, int y) const
{
	// If the spray is on player, return true and set the player to dead.
	if (isOnPlayer(x,y))
	{
		m_player->setDead();
		return;
	}

	// Check to see if the BugSpray is on a zumi, destroyable brick or bugsprayer to set off chain reactions.
	Actor* ap;
	Zumi* zp;
	DestroyableBrick* dbp;
	BugSprayer* bsp;
	for (int it = 0; it != m_vector.size(); it++)
	{
		ap = dynamic_cast<Actor*>(m_vector[it]);
		if (ap == nullptr)
			continue;
		if (ap->getX() == x && ap->getY() == y)
		{
			dbp = dynamic_cast<DestroyableBrick*>(m_vector[it]);
			zp = dynamic_cast<Zumi*>(m_vector[it]);
			bsp = dynamic_cast<BugSprayer*>(m_vector[it]);
			if (dbp != nullptr)
				dbp->setDead();
			else if(zp != nullptr)
				zp->damage();
			else if(bsp != nullptr)
				bsp->setChainReaction();
		}
	}
}

bool StudentWorld::canDropSprayer(int x, int y) const
{
	// Check to see if the player is already on a destroyable brick or bug sprayer.
	Actor* ap = getAnActorAtTheProposedLocation(x, y);
	Brick* bp = dynamic_cast<Brick*>(ap);
	BugSprayer* bsp = dynamic_cast<BugSprayer*>(ap);

	// If it is, return false.
	if ((bp != nullptr || bsp != nullptr))
		return false;
	
	// If the number of active sprayers is less than the max, return true; otherwise, return false.
	if (m_numSprayer < m_maxSprayer)
		return true;
	else
		return false;
}

bool StudentWorld::canDropGoodie() const
{
	// If the random number generated (chance) is less than the overall goodie drop rate, return true to eventually drop a goodie; otherwise, return false.
	int overallGoodieDropRate = m_curLevel->getOptionValue(optionProbOfGoodieOverall);
	int chance = (rand() % 100);

	return (chance < overallGoodieDropRate);
}

////// DYNAMIC ALLOCATION OF ACTORS IMPLEMENTATIONS //////

void StudentWorld::addSprayer(int x, int y)
{
	m_vector.push_back(new BugSprayer(x, y, this));
	m_numSprayer++;
}

void StudentWorld::addBugSpray(int x, int y)
{

	m_vector.push_back(new BugSpray(x, y, this));
	Actor* ap;
	PermanentBrick* permBrick;
	Brick* brick;

	// Add sprays EAST.
	for (int i = 1; i <= 2; i++)
	{
		ap = getAnActorAtTheProposedLocation(x+i, y);
		permBrick = dynamic_cast<PermanentBrick*>(ap);
		brick = dynamic_cast<Brick*>(ap);
		if (permBrick == nullptr)
			m_vector.push_back(new BugSpray(x+i,y, this));
		if (brick != nullptr)
			break;
	}

	// Add sprays WEST.
	for (int i = 1; i <= 2; i++)
	{
		ap = getAnActorAtTheProposedLocation(x-i, y);
		permBrick = dynamic_cast<PermanentBrick*>(ap);
		brick = dynamic_cast<Brick*>(ap);
		if (permBrick == nullptr)
			m_vector.push_back(new BugSpray(x-i,y, this));
		if (brick != nullptr)
			break;
	}

	// Add sprays NORTH.
	for (int i = 1; i <= 2; i++)
	{
		ap = getAnActorAtTheProposedLocation(x, y+i);
		permBrick = dynamic_cast<PermanentBrick*>(ap);
		brick = dynamic_cast<Brick*>(ap);
		if (permBrick == nullptr)
			m_vector.push_back(new BugSpray(x,y+i, this));
		if (brick != nullptr)
			break;
	}

	// Add sprays SOUTH.
	for (int i = 1; i <= 2; i++)
	{
		ap = getAnActorAtTheProposedLocation(x, y-i);
		permBrick = dynamic_cast<PermanentBrick*>(ap);
		brick = dynamic_cast<Brick*>(ap);
		if (permBrick == nullptr)
			m_vector.push_back(new BugSpray(x,y-i, this));
		if (brick != nullptr)
			break;
	}
	  m_numSprayer--;
}

void StudentWorld::addProperGoodie(int x, int y)
{
	// Invariant: Drop rates add up to 100 and a goodie will be dropped once this is called.
	// Gather up drop rates for the goodies.
	int elgRate = m_curLevel->getOptionValue(optionProbOfExtraLifeGoodie);
	int issRate = m_curLevel->getOptionValue(optionProbOfMoreSprayersGoodie);
	int wtwRate = m_curLevel->getOptionValue(optionProbOfWalkThruGoodie);

	// Set bounds for checking.
	int bound1 = elgRate + issRate;

	// Use random number generator for probability purposes. Chance numbers are from 0 to 100 inclusive.
	int chance = rand() % 100;

	if (elgRate > 0 && chance < elgRate)	// Checks for range of ExtraLifeGoodie
		addExtraLifeGoodie(x, y);
	else if (issRate > 0 && chance >= elgRate && chance < bound1)	// Checks for range of IncrSimSprayersGoodie
		addIncrSimSprayersGoodie(x, y);
	else // If neither an ELG or ISSG is dropped, then the WTWG must be dropped.
		addWalkThroughWallsGoodie(x, y);
}

void StudentWorld::addExtraLifeGoodie(int x, int y)
{
	m_vector.push_back(new ExtraLifeGoodie(x, y, m_curLevel->getOptionValue(optionGoodieLifetimeInTicks), this));
}

void StudentWorld::addWalkThroughWallsGoodie(int x, int y)
{
	m_vector.push_back(new WalkThroughWallsGoodie(x, y, m_curLevel->getOptionValue(optionGoodieLifetimeInTicks), this));
}

void StudentWorld::addIncrSimSprayersGoodie(int x, int y)
{
	m_vector.push_back(new IncreaseSimultaneousBugSprayerGoodie(x, y, m_curLevel->getOptionValue(optionGoodieLifetimeInTicks), this));
}

////// LEVEL INITIALIZATION AND CLEANUP FUNCTIONS //////

int StudentWorld::load()
{
	// Dynamically allocate and load a level.
	setLevelFile(getLevel());
	m_curLevel = new Level;
	Level::LoadResult result = m_curLevel->loadLevel(m_loadFile);

	// If the load was not successful, delete the allocated level and return -1 to break out.
	if (result == Level::load_fail_file_not_found || 
		result == Level::load_fail_bad_format)
	{
		delete m_curLevel;
		return -1;
	}
	else
    {
		// Level loaded successfully so set the bonus, maxSprays, and other level statistics.
		setBonus(m_curLevel->getOptionValue(optionLevelBonus));
		setNumSprayer();
		setNumZumi();
		setLevelStart();

		// Go through the contents of the level and allocate actors accordingly.
		Level::MazeEntry item;
		for (int x = 0; x < VIEW_WIDTH; x++)
		{
			for(int y = 0; y < VIEW_HEIGHT; y++)
			{
				item = m_curLevel->getContentsOf(x, y);
				initializeActors(item, x, y);
			}
		}
	}
	return 0;
}

void StudentWorld::initializeActors(Level::MazeEntry item, int x, int y)
{
	// Based on the item retrieved from the level at a certain position, dynamically allocate
	// the proper actors.
	switch(item)
	{
		case Level::MazeEntry::empty:
			break;
		case Level::MazeEntry::player:
			m_player = new Player (x, y, this);
			break;
		case Level::MazeEntry::perma_brick:
			m_vector.push_back(new PermanentBrick(x, y, this));
			break;
		case Level::MazeEntry::destroyable_brick:
			m_vector.push_back(new DestroyableBrick(x, y, this));
			break;
		case Level::MazeEntry::simple_zumi:
			m_vector.push_back(new SimpleZumi(x, y, m_curLevel->getOptionValue(optionTicksPerSimpleZumiMove), this));
			m_numZumi++;
			break;
		case Level::MazeEntry::complex_zumi:
			m_vector.push_back(new ComplexZumi(x, y, m_curLevel->getOptionValue(optionTicksPerComplexZumiMove), m_curLevel->getOptionValue(optionComplexZumiSearchDistance), this));
			m_numZumi++;
			break;
		case Level::MazeEntry::exit:
			m_vector.push_back(new Exit(x, y, this));
			break;
	}
}

void StudentWorld::setLevelFile(int level)
{
	// Set the proper level file to be used by the load function.
	ostringstream oss;

	oss << "level";
	oss.fill('0');
	oss << setw(2) << level << ".dat";

	m_loadFile = oss.str();
}

void StudentWorld::updateDisplayText()
{
	
	// Format display text with current score, level, lives, and bonus.
	string displayText = formatDisplayText(getScore(), getLevel(), getLives(), m_bonus);

	// Update the display with newly formatted string.
	setGameStatText(displayText);
}

string StudentWorld::formatDisplayText(int score, int level, int lives, int bonus)
{
	// "Score: 00000100 Level: 09 Lives: 003 Bonus: 345" -> Display Format
	// Format using ostringstream to account for leading zeros and leading blanks.
	ostringstream oss;
	oss << "Score: ";
	oss.fill('0');
	oss << setw(8) << score 
		<< "  Level: " << setw(2) << level
		<< "  Lives: " << setw(3) << lives
		<< "  Bonus:";
	oss.fill(' ');
	oss << setw(6) << bonus;

	return oss.str();
}

inline void StudentWorld::setBonus(int levelBonus)
{
	m_bonus = levelBonus;
}

inline void StudentWorld::decBonus()
{
	if (m_bonus > 0)
		m_bonus--;
}

inline void StudentWorld::setNumSprayer()
{
	m_numSprayer = 0;
	m_maxSprayer = 2;
}

inline void StudentWorld::setNumZumi()
{
	m_numZumi = 0;
}

inline void StudentWorld::decNumZumi()
{
	m_numZumi--;
}

inline void StudentWorld::setLevelStart()
{
	m_exitExposed = false;
	m_completedLevel = false;
	m_boostedSprayerTime = getBoostedSprayerTime();
	m_walkThroughTime = getWalkThroughTime();
}

void StudentWorld::setPlayerDead()
{
	m_player->setDead();
}

void StudentWorld::setCompletion()
{
	m_completedLevel = true;
}

bool StudentWorld::playerHasKilledAllZumiOnTheLevel() const
{
	// Return whether or not all the zumis have been killed in the world.
	return (m_numZumi == 0); 
}

bool StudentWorld::isExitExposed()
{
	return m_exitExposed;
}

void StudentWorld::setNewMaxSprayers()
{
	m_maxSprayer = m_curLevel->getOptionValue(optionMaxBoostedSprayers);
}

void StudentWorld::resetMaxSprayers()
{
	m_maxSprayer = 2;
}

void StudentWorld::setWalkThroughEffect()
{
	m_player->activateWalkThroughWalls();
}

void StudentWorld::setBoostedSprayerEffect()
{
	m_player->increaseSimultaneousSprayers();
}

int StudentWorld::getWalkThroughTime() const
{
	return (m_curLevel->getOptionValue(optionWalkThruLifetimeTicks));
}

int StudentWorld::getBoostedSprayerTime() const
{
	return (m_curLevel->getOptionValue(optionBoostedSprayerLifetimeTicks));
}

////// CLEANUP FUNCTION //////

void StudentWorld::removeDeadGameObjects()
{
	// Remove any dead game objects currently in the student world.
	// If it's a zumi, decrement the zumi count before erasing it from the world.
	Zumi* zp;
	for (vector<Actor*>::iterator it = m_vector.begin(); it != m_vector.end();)
	{
		if ((*it)->isDead())
		{
			zp = dynamic_cast<Zumi*>(*it);
			if (zp != nullptr)
				decNumZumi();
			delete (*it);
			it = m_vector.erase(it);
		}
		else
			it++;
	}
}

