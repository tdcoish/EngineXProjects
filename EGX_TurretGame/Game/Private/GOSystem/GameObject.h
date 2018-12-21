#pragma once

#include "Game/Private/GOSystem/ComponentTypes.h"
#include <vector>

#include "GameObjectHandles.h"

typedef unsigned int Hash;

class Component;

/******************************************************************************************************
Notes, especially with hashing. When we create a game object we aren't directly passing in a hash, we instead
pass in a string, and convert it to a hash by the time it reaches GameObject::GameObject(Hash _). So in our 
CreatePaddle() semi-factory call we are passing in the relevant info, but then also a string converted into a hash.


******************************************************************************************************/

// our game object, it's just a collection of components - that's it!
class GameObject
{
public:

	Hash mHash;			// why is this public?
	// Sort of weird that we aren't initializing mComponents to null the whole way around.
	// Is that because vectors are automatically resizable?
	GameObject(Hash hash);
	~GameObject();

	GameObjectHandle GetHandle() {
		GameObjectHandle temp;
		temp.mHash = mHash;
		return temp;
	}

	void Initialize();

	void AddComponent(Component* pComponent);

	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}

		return nullptr;
	}

	std::vector<Component*> mComponents;
};





