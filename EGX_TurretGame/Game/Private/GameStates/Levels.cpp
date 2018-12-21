
#include "Game/Private/Gameplay/Game.h"
#include "Game/Public/InputManager.h"
#include "Game/Private/Helpers/Collision.h"
#include "Game/Private/Helpers/GraphicsHelpers.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game\Private\Gameplay\GameplayEventsSystem.h"

#include <string>


/******************************************************************************
NOTE: This engine automatically updates frames in the background. Do not write your
own while loop for any level, or it will hang on the same frame forever.
******************************************************************************/

//sets up objects in the level. Works for both Two player and VS AI
void MyGame::SetUpGame() {

	// need a way of reinitializing this to 0 every time.
	playerOneScore = 0;
	playerTwoScore = 0;
}

// Eventually this stuff could be components, with maybe game objects that only have them in the world

void MyGame::DrawMessage() {
	// Draw the "instructions message
	std::string message = "Don't Die";
	exVector2 msgLoc;
	msgLoc.x = 350;
	msgLoc.y = 50;
	mEngine->DrawText(mFontID, msgLoc, message.c_str(), textCol, 0);
}

void MyGame::Playing(float fDeltaT) {

	//Input stored earlier. Sort of elegant. Ask him later how this is done.
	// must be that game is a subclass of the app class (whatever it's called)
	if (pInput->kStore & pInput->kEscape) {
		GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::GO_TO_MENU);
	}

	World::getInstance()->Update(fDeltaT, mEngine);

	DrawMessage();

	// handles a bunch of miscellaneous things.
	HandleEvents();

	// just a hack because I don't have proper access to storing inputs
	InputManager::getInstance()->ClearKeys();
}












