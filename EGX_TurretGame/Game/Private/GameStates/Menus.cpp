#include "Game/Private/Gameplay/Game.h"
#include "Game/Public/InputManager.h"
#include "Game/Private/Helpers/Collision.h"
#include "Game/Private/Helpers/GraphicsHelpers.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game\Private\Gameplay\GameplayEventsSystem.h"


void MyGame::HandleMenuInput() {
	//Handle input
	if (pInput->kStore & pInput->N1) {
		GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::PLAY_GAME);
	}

	if (pInput->kStore & pInput->N2) {
		GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::GO_TO_CREDITS);
	}

	if (pInput->kStore & pInput->N3) {
		GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::QUIT_GAME);
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
	mEngine->DrawText(mFontID, center, "2. Credits", textCol, 0);
	center.y += 50;
	mEngine->DrawText(mFontID, center, "3. Quit", textCol, 0);
}

// menu is simply text with corresponding game modes.
void MyGame::Menu(float fDeltaT) {

	HandleMenuInput();
	RenderMenuScreen();
}

void MyGame::Credits(float fDeltaT) {
	exVector2 center;
	center.x = 200;
	center.y = 100;

	// Well I guess I'd need to manually move the vector down to render an individual line.
	//
	std::string txt = "Copyright VFS. All rights reserved.\n";
	mEngine->DrawText(mFontID, center, txt.c_str(), textCol, 0);
	center.y += 80;

	txt = "Author: Timothy Coish\n";
	mEngine->DrawText(mFontID, center, txt.c_str(), textCol, 0);
	center.y += 80;

	txt = "Teacher: James Mansfield\n"; 
	mEngine->DrawText(mFontID, center, txt.c_str(), textCol, 0);
	center.y += 80;

	txt = "2018\n";
	mEngine->DrawText(mFontID, center, txt.c_str(), textCol, 0);
	center.y += 80;

	txt = "Name: Turret Game\n";
	mEngine->DrawText(mFontID, center, txt.c_str(), textCol, 0);
	center.y += 80;

	txt = "Assignment 3";
	mEngine->DrawText(mFontID, center, txt.c_str(), textCol, 0);

	if (pInput->kStore & pInput->kEscape) GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::GO_TO_MENU);
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

	if (pInput->kStore & pInput->kEscape) GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::GO_TO_MENU);
}







////Called from the game over screen, if the player played the computer
////displays score and gives option to play again or quit.
//void MyGame::GameOver(float fDeltaT) {
//
//}
