#include "Game.h"


/********************************************************************
for right now all this does is handle the level to be run. However, 
I wanted the practice of creating an mini-event system, to be expanded 
upon for future projects.

On second thought, there's something wrong about the term Event Handling.
It should be called something else, because it confuses with input events.

Anyway, since there is only one listener to these events, it doesn't 
bring us too much. However, I'm looking forward to adding this idea in 
to various areas. Specifically, it seems a natural fit for gameplay 
generated events such as (rockets hitting an enemy, player dying, health
pickup picked up), which are going to touch multiple seperate systems, such
as score, level selection, audio, etcetera.
********************************************************************/

void MyGame::HandleEvents() {
	for (int i = 0; i < eQueue.numActive; i++) {
		//do thing for event.
		switch (eQueue.events[i]) {
		case NO_EVENT: break;

		case GO_TO_MENU: RunLevel = &MyGame::Menu; break;

		case PLAY_FROGGER:
			// "Load" Level.
			InitializeLevel();
			RunLevel = &MyGame::Playing;
			break;

		case QUIT_GAME: RunLevel = &MyGame::Quit; break;
		}
	}

	//now that events are done, clear
	eQueue.FlushEvents();
}