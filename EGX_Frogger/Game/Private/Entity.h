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
#include "Engine\Public\SDL.h"

#include "Entity.h"
#include "tdcArray.h"


enum EntityType { FROGGER, TRACK, BLOCK, WHATVER };

struct Entity {

	EntityType type;

	/*Entity(EntityType model) {
		type = model;
	}*/

	virtual void SetUp() {};		// irl, we would just load levels in
	virtual void Update() {};
	virtual void Render(exEngineInterface* mEngine) {};

	Entity() {};
	~Entity() {};

	EntityType getType() { return type; }
	
};

// Pretty much everything is a physical. Even menu items are "physical" objects, in so far 
// as they have some size.
struct Physical : Entity {
	// position inside of the level
	exVector2 pos;
	exVector2 vel;

	tdcRect area;

	virtual void Render(exEngineInterface* mEngine);
};


// Frogger is our hero.
struct Frogger : Physical {
	Frogger() {
		area.h = 20;
		area.w = 20;
		area.x = 0;
		area.y = 0;	
	}


	virtual void SetUp();
	virtual void Update();
};

// An invisible game object, it serves as a manager for the track blocks
// actually, the track owns the blocks. It never gives them to the Game.entities list.
// When we do all the things with the game entities, have the track go and add its children.
struct Track : Entity {
	tdcArray<Entity*>*			blocks;

	// worlds worst timer
	int						topSpawnTimer;
	int						sideSpawnTimer;

	Track() {
		blocks = new tdcArray<Entity*>();
		topSpawnTimer = 0;
		sideSpawnTimer = 0;
	}
	~Track() {
		blocks->DeleteList();
	}


	// Generate the level
	virtual void SetUp();

	// Generate new Line
	void CreateLine();
	
	// Generate sideways blocks
	void SpawnSides();

	virtual void Update();
	// this calls render on all active block children.
	virtual void Render(exEngineInterface* mEngine);
};

// block has position and size. Otherwise controlled by the Track
struct Block : Physical {

	// sort of thought there would eventually be more flags. For different types and all that.
	Uint16						flags = 0;
	const Uint16				DOWN = 1 << 0;
	const Uint16				LEFT = 1 << 1;
	const Uint16				RIGHT = 1 << 2;

	bool						deleteMe = false;

	virtual void Update();

	Block() {

	}
};