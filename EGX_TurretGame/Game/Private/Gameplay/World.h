#pragma once

#include <vector>
#include "Engine\Public\EngineInterface.h"
#include "EnemySpawner.h"
#include "Game\Private\GOSystem\GameObjectHandles.h"


class GameObject;

/************************************************************************
This class has been changed from storing all of our game objects, to simply
iterating through the GameObjectInventory for valid hashes and seperating out
our SetUpLevel function.

Update: Nevermind, I decided to make this a singleton instead, because I wanted
a pure vector of GameObjects.
------------------------------------------------------------------------------
Update: With the advent of the GameObjectInventory, I decided that it was poor practice
to also have a singleton that stored raw GO*'s. However, since in many games I imagine 
that we might want something to control some actors this was staying. For example, if 
you go into a room in Skyrim, we might want to load some actors, but still have some 
active outside. To do that we want to seperate our GOInventory from the SceneLoader 
type object, which this is a stand in for.s
************************************************************************/

// the world, it contains all of our game objects and defines the order of updates
class World
{
private:

	World();

	//std::vector<GameObject*> mGameObjects;
	std::vector<GameObjectHandle> mGameObjHandles;

public:

	static World* getInstance()
	{
		//This will be instantiated upon first use.
		static World ins;
		return &ins;
	}

	//disable copy constructor and assignment operator
	World(World const&) = delete;
	void operator=(World const&) = delete;

	void Create();

	// now we're just iterating through the GameOBjectInventory finding all the handles we control and getting it to delete them
	void Destroy();

	void Update(float fDeltaT, exEngineInterface* pEngine);

	void SetUpLevel();

	void AddEntity(GameObjectHandle handle) { mGameObjHandles.push_back(handle); }
};