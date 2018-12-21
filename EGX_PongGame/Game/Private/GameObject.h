#pragma once

#include "ComponentTypes.h"
#include <vector>

class Component;

// our game object, it's just a collection of components - that's it!
class GameObject
{
public:
	// Sort of weird that we aren't initializing mComponents to null the whole way around.
	// Is that because vectors are automatically resizable?
	GameObject();

	~GameObject();

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


// create our paddle
GameObject* CreatePaddle(std::string side);

// create ball (notice how it will generate events)
GameObject* CreateBall();

// creates either roof or floor
GameObject* CreateRoof(std::string tag);

// creates left or right end zone
GameObject* CreateEndZone(std::string tag);

