#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <vector>
#include <string>

////// STUDENTWORLD IMPLEMENTATIONS //////

class StudentWorld : public GameWorld
{
	public:

		~StudentWorld()
		{
		
			// Destructor is a back-up in case cleanup() didn't already delete all dynamically allocated objects.
			// Delete actors in vector container.
			std::vector<Actor*>::iterator it;
			while (! m_vector.empty())
			{
				it = m_vector.end();
				it--;
				delete (*it);
				m_vector.pop_back();
			}
			// Delete player and level setup.
			delete m_player;
			delete m_curLevel;
		}

		virtual int init()
		{
			// Attempt to load the file.
			if (load() == -1)
			{
				// If the file failed to load and the level is not 0, the player completed all levels and won the game.
				if (getLevel() != 0)
					return GWSTATUS_PLAYER_WON;
			
				// Otherwise, the player didn't win, but the level files were non-existent or corrupted.
				return GWSTATUS_LEVEL_ERROR;
			}
		
			// Continue with the game after successful load.
			return GWSTATUS_CONTINUE_GAME;
		}

		virtual int move()
		{
			updateDisplayText();

			// Ask actors to do something each tick.
			for (int p = 0; p != m_vector.size(); p++)
			{
				// If the actors are not dead, do something accordingly
				if ( ! (m_vector[p]->isDead()))
				{
					m_vector[p]->doSomething();
					m_player->doSomething();

					// If the player is dead, decrement the number of lives and return that the player has died.
					if (m_player->isDead())
					{
						decLives();
						return GWSTATUS_PLAYER_DIED;
					}
				
					// If the level is completed, increase the score by the remaining bonus and return that the player has finished the level.
					if (m_completedLevel)
					{
						increaseScore(m_bonus);
						return GWSTATUS_FINISHED_LEVEL;
					}
				}
			}

			// Release all the dead dynamically allocated actors after each tick.
			removeDeadGameObjects();

			// If the player has a goodie effect, decrement its effect's duration.
			// When the effect's time is 0, turn off the special effect of the goodie and reset timers.
			if (m_player->getWalkThroughStatus())
			{
				m_walkThroughTime--;
				if (m_walkThroughTime == 0)
				{
					m_player->turnOffWalkThroughStatus();
					m_walkThroughTime = getWalkThroughTime();
				}
			}
			if (m_player->getBoostedSprayerStatus())
			{
				m_boostedSprayerTime--;
				if (m_boostedSprayerTime == 0)
				{
					m_player->turnOffBoostedSprayerStatus();
					resetMaxSprayers();
					m_boostedSprayerTime = getBoostedSprayerTime();
				}
			}
				
			// Decrement the bonus of the level per tick.
			decBonus();

			// If the player killed all the zumis, expose the exit in the maze.
			if (playerHasKilledAllZumiOnTheLevel())
				exposeTheExitInTheMaze();
	
			if (m_completedLevel)
			{
				increaseScore(m_bonus);
				return GWSTATUS_FINISHED_LEVEL;
			}

			// The player hasn't died, so continue playing the game.
			return GWSTATUS_CONTINUE_GAME;
		}

		virtual void cleanUp()
		{
			// Delete actors in vector container.
			std::vector<Actor*>::iterator it;
			while (! m_vector.empty())
			{
				it = m_vector.end();
				it--;
				delete (*it);
				m_vector.pop_back();
			}
			// Delete player and level setup.
			delete m_player;
			delete m_curLevel;
	 }

		// HANDLE LOCATION CHECKS
		Actor* getAnActorAtTheProposedLocation(int x, int y) const;
		Player* getPlayer() const;
		bool playerCanMoveTo(int x, int y) const;
		bool zumiCanMoveTo(int x, int y) const;
		bool isOnPlayer(int x, int y) const;
		bool isOnZumiOrDestroyableBrick(int x, int y) const;
		bool canDropSprayer(int x, int y) const;
		bool canDropGoodie() const;

		// HANDLE EXIT/COMPLETION
		bool isExitExposed();
		void exposeTheExitInTheMaze();
		void setCompletion();
		void setPlayerDead();
		bool playerHasKilledAllZumiOnTheLevel() const;
		
		// DYNAMICALLY ALLOCATE ACTORS
		void addProperGoodie(int x, int y);
		void addSprayer(int x, int y);
		void addBugSpray(int x, int y);
		void addExtraLifeGoodie(int x, int y);
		void addWalkThroughWallsGoodie(int x, int y);
		void addIncrSimSprayersGoodie(int x, int y);

		// HANDLE SPRAY/SPRAYER RELATED TASKS
		void SprayDestroyPossibleTargets(int x, int y) const;
		void setNewMaxSprayers();
		void resetMaxSprayers();

		// HANDLE GOODIE EFFECTS
		void setWalkThroughEffect();
		void setBoostedSprayerEffect();
		int getWalkThroughTime() const;
		int getBoostedSprayerTime() const;

	private:
		std::vector < Actor * > m_vector;
		Player* m_player;
		Level* m_curLevel;
		std::string m_loadFile;
		int m_bonus;
		int m_numSprayer;
		int m_maxSprayer;
		int m_numZumi;
		int m_walkThroughTime;
		int m_boostedSprayerTime;
		bool m_exitExposed;
		bool m_completedLevel;


		// HANDLE LEVEL INITIALIZATION
		int load();
		void initializeActors(Level::MazeEntry item, int x, int y);
		void setLevelFile(int level);
		inline void setBonus(int levelBonus);
		inline void decBonus();
		inline void setNumSprayer();
		inline void setNumZumi();
		inline void decNumZumi();
		inline void setLevelStart();

		// HANDLE UPPER DISPLAY TEXT
		void updateDisplayText();
		std::string formatDisplayText(int score, int level, int lives, int bonus);

		// CLEANUP
		void removeDeadGameObjects();
		
};

#endif // STUDENTWORLD_H_
