#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Helpers/Collision.h"
#include "Game\Private\GOSystem\Component.h"

#include "Engine/Public/SDL.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include "Game\Private\GameStates\FSM.h"

#include <vector>



class COGPhysics;
class COGTransform;

// This is actually only used by the graphics. Ask James for a better system.
enum TurretStates { REGULAR, HYPER, GRENADE };

// all this needs to do is listen to keys and move itself
class COGTurret : public Component {
public:

	// Need a reference to the player
	COGTransform * pPlayerPos;

	static COGTurret* mInstance;

	COGTurret(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Turret; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	void Update(float fDeltaT);
	
	void ShootPlasmoid();
	void ShootGrenade();

	float time;			// keep track of time since creation. just for firing stuff.
	
	float plasmaShotInterval;
	float hyperShotInterval;
	float lastPlasmoidShot;
	
	float grenadeShotInterval;
	float lastGrenadeShot;
	float grenadeAmmo;

	float hyperShotMaxDuration;
	float hyperShotCurrentTime;

	TurretStates		mState;				// ONLY USED FOR GRAPHICS.

private:
	FSM mStates;
};