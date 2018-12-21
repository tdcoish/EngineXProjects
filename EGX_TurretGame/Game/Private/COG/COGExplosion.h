#pragma once

/***********************************
This class exists basically just to be an object 
that damages zergs and then deletes itself.
***********************************/

#include "Game\Private\GOSystem\Component.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>

class COGPhysics;

class COGExplosion : public Component, public IPhysicsCollisionEvent {
public:

	static std::vector<COGExplosion*> mExplosionComponents;

	COGExplosion(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Explosion; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) {}

	void Update(float fDeltaT);

	float timeSinceSpawned;
	float lifetime;

};