
/*****************************************************************************************************************

*****************************************************************************************************************/

#include "Game/Private/COG/COGPlayer.h"

#include "Game/Public/InputManager.h"
#include "Game/Private/COG/COGPhysics.h"
#include "Game/Private/COG/COGPlasma.h"
#include "Game/Private/COG/COGTurret.h"
#include "Game/Private/COG/COGZergling.h"
#include "Game\Private\COG\COGWall.h"
#include "Game\Private\COG\COGTransform.h"

#include "Game\Private\Gameplay\GameplayEventsSystem.h"

// for storing the health bars hash
#include <string>

COGPlayer* COGPlayer::mInstance;

COGPlayer::COGPlayer(GameObject* pGO)
	: Component(pGO)
{}

void COGPlayer::Initialize()
{
	// give the player a reference to its physics component, needed for setting velocity
	// also needed for listening to its own collisions
	this->pPhysComp = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	pPhysComp->SetListener(this);
}

void COGPlayer::Destroy() {
	mInstance = nullptr;
}

void COGPlayer::Update() {
	InputManager* pInput = InputManager::getInstance();

	this->pPhysComp->mVelocity.y = 0;
	this->pPhysComp->mVelocity.x = 0;

	if (pInput->kStore & pInput->kW) {
		this->pPhysComp->mVelocity.y -= 200;
	}

	if (pInput->kStore & pInput->kS) {
		this->pPhysComp->mVelocity.y += 200;
	}

	if (pInput->kStore & pInput->kA) {
		this->pPhysComp->mVelocity.x -= 200;
	}
	if (pInput->kStore & pInput->kD) {
		this->pPhysComp->mVelocity.x += 200;
	}

	// Don't let the player run out of the level
	// maybe do this in collisions?
	
	// Handle firing

	// Handle dying - For now we just go to the menu.
	if (health <= 0.0f) {
		GameplayEventsSystem::getInstance()->mGameStateChangeQueue->AddItem(EventType::PLAYER_DIED);
	}
}


void COGPlayer::OnCollision(COGPhysics* pMe, COGPhysics* pOther)
{

	// Could do this by making these objects implement an interface. Ask James for the details.
	// Alternatively, I could make each object store a string that is of it's type
	// Alternatively, I could just do it this way, since this is a simple and small game.

	COGWall*   pWall = pOther->mGO->FindComponent<COGWall>(ComponentType::Wall);
	COGZergling* pZerg = pOther->mGO->FindComponent<COGZergling>(ComponentType::Zergling);

	// Take damage
	if (pZerg != nullptr) {
		health -= 10;
	}

	// keep us within the game world
	if (pWall != nullptr) {
		COGTransform* pTrans = this->mGO->FindComponent<COGTransform>(ComponentType::Transform);
		exVector2 pos = pTrans->GetPosition();
		if (pos.x < 0) pos.x = 0;
		if (pos.x > 800) pos.x = 800;
		if (pos.y < 0) pos.y = 0;
		if (pos.y > 800) pos.y = 800;
		pTrans->SetPosition(pos.x, pos.y);
	}

}

