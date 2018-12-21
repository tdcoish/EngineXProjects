#include <string>

#include "Game/Public/InputManager.h"

#include "GameObject.h"
#include "Game/Private/GOSystem/Component.h"

#include "HashMap.h"
#include "Game/Private/GOSystem/GameObjectInventory.h"

#include "Game\Private\Gameplay\World.h"

class Component;

//typedef unsigned int Hash;

GameObject::GameObject(Hash hash) {
	mHash = hash;
	GameObjectInventory::getInstance()->Register(this);
}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

GameObject::~GameObject()
{
	
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();
		delete pComponent;
	}

	// unregister this handle with the game inventory
	GameObjectInventory::getInstance()->Unregister(this);

	// There's a problem in this code. I'm not really using the GOInventory.
	// The world just chugs along of its own accord.
}


void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}






