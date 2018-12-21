

#include "GameObjectHandles.h"
#include "Game/Private/GOSystem/GameObjectInventory.h"

bool GameObjectHandle::IsValid() const {
	bool temp = GameObjectInventory::getInstance()->Exists(mHash);
	return temp;
}

GameObject* GameObjectHandle::Get() const {
	GameObject* temp = GameObjectInventory::getInstance()->Lookup(mHash);
	return temp;
}


