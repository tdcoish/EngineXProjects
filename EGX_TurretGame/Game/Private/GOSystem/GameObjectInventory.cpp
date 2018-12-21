
#include "GameObjectInventory.h"


GameObjectInventory::GameObjectInventory()
	:mHandlesForDeletion(new tdcArray<GameObjectHandle>())
{}

// Adds GO hash to the inventory
void GameObjectInventory::Register(GameObject* pGO)
{
	mMap.InsertNoCheck(pGO);
}

// This is okay because we have already gone through a handle to get here.
void GameObjectInventory::Unregister(GameObject* pGO)
{
	mMap.Remove(pGO->mHash);
}

// Check this before doing anything else with an object.
bool GameObjectInventory::Exists(Hash hash) const
{
	return (mMap.Find(hash) != nullptr);
}

GameObject* GameObjectInventory::Lookup(Hash hash)
{
	return mMap.Find(hash);
}

const GameObject* GameObjectInventory::Lookup(Hash hash) const
{
	return mMap.Find(hash);
}

void GameObjectInventory::StoreGOForDeletion(GameObjectHandle handle) {
	mHandlesForDeletion->AddItem(handle);
}

// I mean, we just clear the handles. We need a different system to iterate through all GO's, check if their handles are clear, and if not, delete them.
// We do that part in world
void GameObjectInventory::DeleteQueuedHandles() {
	for (int i = 0; i < mHandlesForDeletion->numActive; i++) {
		// it's theoretically possible that we are trying to delete the same object twice, so try not to do that.
		if (this->Exists(mHandlesForDeletion->list[i].mHash)) {
			GameObject* pTemp = mMap.Find(mHandlesForDeletion->list[i].mHash);
			this->Unregister(mHandlesForDeletion->list[i].Get());

			delete pTemp;
		}
	}
	mHandlesForDeletion->ClearList();
}






