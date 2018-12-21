#include "EntityFactory.h"
#include "Game.h"

/*
This might be a bit confusing. Basically, we're having the game itself
wrap over the factory. The game "slots" the created factory in the correct spot in its 
own entity* array.
*/

