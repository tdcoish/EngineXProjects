#include "Game/Private/Game.h"
#include "Game/Public/InputManager.h"
#include "Game/Private/Collision.h"
#include "Game/Private/GraphicsHelpers.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"


void MyGame::HandleMenuInput() {
	//Handle input
	if (pInput->kStore & pInput->N1) {
		eQueue.AddEvent(PLAY_TWO_PLAYER);
	}

	if (pInput->kStore & pInput->N2) {
		eQueue.AddEvent(PLAY_VS_AI);
	}

	if (pInput->kStore & pInput->N3) {
		eQueue.AddEvent(QUIT_GAME);
	}
}

void MyGame::RenderMenuScreen() {
	//position text options
	exVector2 center;
	center.x = 400;
	center.y = 250;

	//render the three options
	mEngine->DrawText(mFontID, center, "1. 1v1", textCol, 0);
	center.y += 50;
	mEngine->DrawText(mFontID, center, "2. Vs Computer", textCol, 0);
	center.y += 50;
	mEngine->DrawText(mFontID, center, "3. Quit", textCol, 0);
}

// menu is simply text with corresponding game modes.
void MyGame::Menu(float fDeltaT) {

	HandleMenuInput();
	RenderMenuScreen();
}




//Called from either of the menu screens
//Alright I can't actually figure out how to quit really, so we'll just pretend.
void MyGame::Quit(float fDeltaT) {

	//display thanks for playing message.
	exVector2 center;
	center.x = 400;
	center.y = 250;

	//render the three options

	mEngine->DrawText(mFontID, center, "Thanks for playing", textCol, 0);

	//figure this out later.
	//SDL_Delay(200);
	//SDL_Quit();

	if (pInput->kStore & pInput->kEscape) eQueue.AddEvent(GO_TO_MENU);
}







////Called from the game over screen, if the player played the computer
////displays score and gives option to play again or quit.
//void MyGame::GameOver(float fDeltaT) {
//
//}
