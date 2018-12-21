










#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Collision.h"
#include "Component.h"

#include "Engine/Public/SDL.h"

#include "Events.h"

class COGPhysics;

// basically just the script for ball specific behaviours
class COGBall : public Component, public IPhysicsCollisionEvent {
public:

	static COGBall* mInstance;

	// gets a pointer to a velocity component
	// for now I'm just going to manually set the velocity
	COGPhysics* pPhysComp;

	COGBall(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Ball; }

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override;

	virtual void Initialize() override;
	virtual void Destroy() override;

	void Update();
};




