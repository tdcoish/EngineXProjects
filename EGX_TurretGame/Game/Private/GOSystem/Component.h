
#pragma once
//#include "Engine\Public\EngineInterface.h"

// james's code below

#pragma once

#include "GameObject.h"
#include "Game/Private/GOSystem/ComponentTypes.h"
#include "Engine\Public\EngineInterface.h"
#include <vector>

#include "Game/Private/Helpers/Collision.h"
#include "Game/Private/Helpers/GraphicsHelpers.h"

#include <algorithm>

class GameObject;
class COGPhysics;

// our base component class
class Component
{
public:

	Component(GameObject* pGO);

	//virtual ComponentType GetType();
	virtual ComponentType GetType() const = 0;

	virtual void Initialize() { }
	virtual void Destroy() { }

//protected:

	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.erase(std::remove(componentVector.begin(), componentVector.end(), this), componentVector.end());
	}

//protected:

	GameObject * mGO;
};


// our interface that allows COGPhysics to talk to anyone

class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) = 0;

};

