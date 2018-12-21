#pragma once

#include "Game\Private\GOSystem\Component.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>

class COGPhysics;

class COGGrenade : public Component, public IPhysicsCollisionEvent {
public:

	static std::vector<COGGrenade*> mGrenadeComps;

	COGGrenade(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Grenade; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	void OnCollision(COGPhysics* pMe, COGPhysics* pOther) {}


	void Update(float fDeltaT);

	float timeSinceSpawned;
	float lifetime;

};