
#pragma once

/******************************************************************************************************************
Since this guy is already a Singleton I thought I might as well extend him to handle the deletion of our GO's at the 
end of each frame, although the appropriate bit of code must call him at the end of every frame.

Update:
I decided to up the size of the inventory, since I actually had overflow. This would be impossible in a game, but 
I had the zerglings endlessly stream, and sure enough if you wait a few minutes there are more than 256 handles, and 
you won't delete all the GO's when you hit destroy, even if all the hashes are unique, simply because you won't have a 
reference to them anymore.
The real solution is to crash or elegantly handle not having enough room. Or to use a vector. This is fine for now.

Woah- wait, that's just the num of buckets. Shouldn't really affect anything. Rethinking things.
******************************************************************************************************************/

#include "HashMap.h"
#include "Game/Private/Helpers/tdcArray.h"

typedef unsigned int Hash;

class GameObject;
// This should be a singleton probably.
// or something like this added to my World class perhaps
class GameObjectInventory
{
public:
	// Adds GO hash to the inventory
	void Register(GameObject* pGO);

	// This is okay because we have already gone through a handle to get here.
	void Unregister(GameObject* pGO);

	// Check this before doing anything else with an object.
	bool Exists(Hash hash) const;

	GameObject* Lookup(Hash hash);

	const GameObject* Lookup(Hash hash) const;

	// Never tried a singleton template class before. Should work.
	static GameObjectInventory* getInstance()
	{
		//This will be instantiated upon first use.
		static GameObjectInventory inventoryInstance;
		return &inventoryInstance;
	}

	void StoreGOForDeletion(GameObjectHandle handle);
	void DeleteQueuedHandles();

private:
	HashMap<GameObject*, 256>			mMap;
	tdcArray<GameObjectHandle>*			mHandlesForDeletion;
	GameObjectInventory();
};


//GameObjectInventory gGameObjectInventory;





