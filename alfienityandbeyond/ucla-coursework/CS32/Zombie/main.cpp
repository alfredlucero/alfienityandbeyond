#include <cctype>
#include <cassert>
#include <ctime>
#include "Zombie.h"
#include "Player.h"
#include "History.h"
#include "Arena.h"
#include "Game.h"
#include "globals.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

      // Play the game
    g.play();
}