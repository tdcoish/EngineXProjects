#pragma once
/*********************************************
Objects do not do all of their updating in the update() function. Instead, they only update the parts of 
themselves that they can update. For example, if a hunter has a cooldown between it's charging, that is the type 
of thing that is updated by itself. However, obviously, it cannot update itself entirely if it has collided with
another entity, and parts of the AI might not be doable by itself.
*********************************************/

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Collision.h"

#include "Entity.h"
#include "EntityFactory.h"
#include "GraphicsHelpers.h"
#include "Sorting.h"

// for random
#include <stdlib.h>


void Frogger::SetUp() {
	area.x = 325;
	area.y = 550;

}


void Track::SetUp()
{
	// we always delete the list of blocks first
	//blocks->DeleteList();

	// now re-create the list 
	blocks = new tdcArray<Entity*>();
	
}

// Get input, set appropriately. All that.
void Frogger::Update() {
	InputManager* pInput = InputManager::getInstance();

	// First, move Frogger according to input
	if (pInput->leftPressed) {
		this->area.x -= 50;
	}
	if (pInput->rightPressed) {
		this->area.x += 50;
	}
	if (pInput->upPressed) {
		this->area.y -= 50;
	}
	if (pInput->downPressed) {
		this->area.y += 50;
	}
	// keep frogger within game world
	if (this->area.x < 0) this->area.x = 25;
	if (this->area.x > 800) this->area.x = 725;
	if (this->area.y > 550) this->area.y = 550;
	if (this->area.y < 0) this->area.y = 0;

	// now how are we going to handle the collisions?

}

// Move the track blocks appropriately. Spawn new lines appropriately.
void Track::Update() {
	for (int i = 0; i < this->blocks->numActive; i++) {
		// for now just move them slowly down the screen.
		blocks->list[i]->Update();

		// alright this is pretty ugly, I'm sure there's a better way
		Block* pBlk = (Block*)blocks->list[i];
		if (pBlk->deleteMe) {
			//blocks->DeleteItem(blocks->list[i]);
			blocks->RemoveItem(blocks->list[i]);
		}
	}

	// update our "timers", really a frame counter
	topSpawnTimer++;
	sideSpawnTimer++;


	topSpawnTimer %= 100;			//every x frames, do something
	if (topSpawnTimer == 0) {
		CreateLine();
	}

	sideSpawnTimer %= 20;			// every y frames, spawn or don't spawn from the sides.
	if (sideSpawnTimer == 0) {
		SpawnSides();
	}
}

// called from update if enough time has passed

// Alright, There are 8 slots. We're going to randomize the locations of the blocks.
// The rule is going to be that 
void Track::CreateLine() {

	// now we want to semi-randomize the placement of the blocks
	int res = rand();
	int startValue = 0;
	if (res % 2) startValue = 100;

	// create four blocks in the typical way
	int curActive = blocks->numActive;			// adding an item will increase numActive. So we can't use it in a for loop.
	for (int i = curActive; i < curActive + 4; i++) {
		Entity* pBlock = EntityFactory::CreateEntity(BLOCK);
		this->blocks->AddItem(pBlock);

		// now cast and place the blocks in the correct location
		Block* pBlk = (Block*)blocks->list[i];

		// SW = 800
		// SH = 600
		pBlk->area.h = 10;
		pBlk->area.w = 100;

		pBlk->area.x = startValue + 200 * (i - curActive);
		pBlk->area.y = 0;

		pBlk->flags |= pBlk->DOWN;
	}
}

void Track::SpawnSides() {
	// randomly spawn an object or not for each "level"
	// there are 6 "levels" of objects

	for (int i = 0; i < 12; i++) {
		// decide if we're going to spawn something on the level or not
		int result = rand();
		if (result % 10 == 0) {			// 1/x chance of spawning an object
			result = rand();

			Entity* pBlock = EntityFactory::CreateEntity(BLOCK);
			this->blocks->AddItem(pBlock);

			Block* pBlk = (Block*)blocks->list[blocks->numActive- 1];

			// these blocks are just semi-small cubes
			pBlk->area.w = 35;
			pBlk->area.h = 35;
			pBlk->area.y = 50 * i;


			if (i % 2) {		// either left or right
				// spawn object from left, moving right
				pBlk->area.x = 0;
				pBlk->flags |= pBlk->RIGHT;
			}
			else {
				// spawn object from right, moving left
				pBlk->area.x = 750;
				pBlk->flags |= pBlk->LEFT;
			}
		}
	}
}

// Basically just moves the block down the screen
void Block::Update() {
	// move the block in its direction
	if (flags & DOWN) {
		this->area.y += 2.0f;
	}

	if (flags & LEFT) area.x -= 2.f;
	if (flags & RIGHT) area.x += 2.f;

	// if it's gone down the screen too far, then make it dissappear.
	// How to trigger this event up the chain?
	if (area.y < 0 || area.y>600 || (area.x+area.w<0) || area.x>=800 ) {
		// get the track to delete you.
		deleteMe = true;
	}

}

// renders a box in the size of the char.
// blue for now.
void Physical::Render(exEngineInterface* mEngine) {
	
	tdcRenderRectangle(this->area, mEngine);
}

// Render all the entities owned by the track.
// Which is really just the blocks.
void Track::Render(exEngineInterface* mEngine) {
	for (int i = 0; i < this->blocks->numActive; i++) {
		blocks->list[i]->Render(mEngine);
	}
}