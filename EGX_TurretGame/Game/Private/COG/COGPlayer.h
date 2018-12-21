#pragma once


#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Helpers/Collision.h"
#include "Game\Private\GOSystem\Component.h"

#include "Engine/Public/SDL.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>



class COGPhysics;

// all this needs to do is listen to keys and move itself
class COGPlayer : public Component , public IPhysicsCollisionEvent {
public:

	static COGPlayer* mInstance;

	// gets a pointer to a velocity component
	COGPhysics* pPhysComp;

	// Not sure this is really needed. Turret has plenty access to Input.
	GameObjectHandle mTurretHandle;

	COGPlayer(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Player; }

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override;

	virtual void Initialize() override;
	virtual void Destroy() override;

	void Update();

	// only used for turrets, which need a reference to the player
	static COGPlayer* getInstance() {
		return mInstance;
	}

	int health;

};