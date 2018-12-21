
#include "Game/Private/Game.h"
#include "Game/Public/InputManager.h"
#include "Game/Private/Collision.h"
#include "Game/Private/GraphicsHelpers.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Collision.h"

#include <string>

/******************************************************************************
NOTE: This engine automatically updates frames in the background. Do not write your
own while loop for any level, or it will hang on the same frame forever.
******************************************************************************/

// Create Level

void MyGame::InitializeLevel() {
	// objects already have their SetUp() virtual function which we can call.
	for (int i = 0; i < entities->numActive; i++) {
		entities->list[i]->SetUp();
	}
}



// Create Level Line, add it to level

void MyGame::Playing(float fDeltaT) {

	// must make these false each frame

	if (pInput->kStore & pInput->kEscape) {
		eQueue.AddEvent(GO_TO_MENU);
	}
	
	// alright, now getting frogger up and running.
	// At regular timesteps, we need to procedurally generate the new level line.
	// Really, we might as well just make tetris.
	// nvm tetris is a bonus project now.

	for (int i = 0; i < this->entities->numActive; i++) {
		entities->list[i]->Update();
	}
	// Really irritating having to put these here. I should do this in a different way
	pInput->leftPressed = false;
	pInput->rightPressed = false;
	pInput->upPressed = false;
	pInput->downPressed = false;


	// Check for collisions with frogger.
	// Alright this is pretty bad
	// add all the things that can collide to a list
	Frogger* pFrog = (Frogger*)entities->list[0];
	Track* pTrack = (Track*)entities->list[1];
	for (int i = 0; i < pTrack->blocks->numActive; i++) {
		Block* pBlk = (Block*)pTrack->blocks->list[i];
		if (CheckCollisionWithRect(pFrog->area, pBlk->area)) {
			 //reset the level
			InitializeLevel();
		}
	}

	// In this case, they won
	if (pFrog->area.y <= 0) {
		InitializeLevel();
	}
	

	// For now just draw our characters
	for (int i = 0; i < this->entities->numActive; i++) {
		entities->list[i]->Render(this->mEngine);
	}

	// alright let's manually draw something where the frogger is. To make sure things are working.


}












