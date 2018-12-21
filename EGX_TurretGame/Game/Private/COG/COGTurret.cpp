
/******************************************************************************************************
Ironically, this game also has a turret, but it's our baby, there is only one, and it exists to destroy
the enemies coming from the right.
******************************************************************************************************/


#include "Game/Private/Helpers/Physics.h"

#include "COGTurret.h"
#include "COGPlayer.h"
#include "COGTransform.h"
#include "COGShape.h"

#include "Game/Private/Gameplay/EnemyFactory.h"

#include "Game\Private\GameStates\FSMTurret.h"


COGTurret* COGTurret::mInstance;

COGTurret::COGTurret(GameObject* pGO)
	: Component(pGO)
	, mStates(pGO)
{}

void COGTurret::Initialize()
{
	mStates.Initialize(mStates.Create<FSMTurretGrenadeShot>());

	this->time = 0.0f;
	this->lastGrenadeShot = 0.0f;
	this->lastPlasmoidShot = 0.0f;
	this->plasmaShotInterval = 0.3f;
	this->hyperShotInterval = 0.1f;
	this->grenadeShotInterval = 1.4f;
	this->hyperShotCurrentTime = 0.0f;			// is set by onEnter in the turret
	this->hyperShotMaxDuration = 2.5f;
}

void COGTurret::Destroy() {
	mInstance = nullptr;
}

// The turret will follow the player, and periodically fire things at them.
void COGTurret::Update(float fDeltaT) {
	time += fDeltaT;
	mStates.Update(fDeltaT);
}

void COGTurret::ShootPlasmoid() {
	// find the angle between the turret and the mouse.
	exVector2 turPos = this->mGO->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();

	exVector2 msPos;
	msPos.x = InputManager::getInstance()->msX;
	msPos.y = InputManager::getInstance()->msY;

	EnemyFactory::getInstance()->CreatePlasmoid(turPos, msPos);

	lastPlasmoidShot = time;
}

void COGTurret::ShootGrenade() {
	// find the angle between the turret and the mouse.
	exVector2 turPos = this->mGO->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();

	exVector2 msPos;
	msPos.x = InputManager::getInstance()->msX;
	msPos.y = InputManager::getInstance()->msY;

	EnemyFactory::getInstance()->CreateGrenade(turPos, msPos);

	lastGrenadeShot = time;
}