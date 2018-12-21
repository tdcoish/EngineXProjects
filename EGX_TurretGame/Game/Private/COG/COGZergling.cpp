

#include "Game/Private/COG/COGZergling.h"
#include "Game/Private/COG/COGPhysics.h"
#include "Game/Private/COG/COGPlayer.h"
#include "Game\Private\COG\COGWall.h"
#include "Game\Private\COG\COGExplosion.h"
#include "COGPlasma.h"

#include "Game\Private\GOSystem\GameObjectInventory.h"

std::vector<COGZergling*> COGZergling::mZerglingComponents;

COGZergling::COGZergling(GameObject* pGO)
	: Component(pGO)
{}

void COGZergling::Initialize()
{
	AddToComponentVector(mZerglingComponents);

	// Again, for this project I'm just having objects listen to their own collisions.
	// However, I could have something like:
	// mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(AudioSystem::getInstance());
	// mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(ScoreSystem::getInstance());
	// mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(SomeThingElse::getInstance());
	mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(this);

	// For now we just have it moving steadily towards the player
	COGPhysics* pPhys = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	pPhys->mVelocity.x = -100;
	pPhys->mVelocity.y = 0;
}

void COGZergling::Destroy() {
	RemoveFromComponentVector(mZerglingComponents);
}

void COGZergling::Update() {

}

void COGZergling::OnCollision(COGPhysics* pMe, COGPhysics* pOther)
{
	// Use players, walls, plasmoids
	COGPlayer* pPlayer = pOther->mGO->FindComponent<COGPlayer>(ComponentType::Player);
	COGWall*	pWall = pOther->mGO->FindComponent<COGWall>(ComponentType::Wall);
	COGPlasma* pPlasma = pOther->mGO->FindComponent<COGPlasma>(ComponentType::Plasmoid);
	COGExplosion* pExp = pOther->mGO->FindComponent<COGExplosion>(ComponentType::Explosion);
	
	// destroy yourself no matter what you hit. So I guess we could just write this line here and skip everything else.
	//GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());

	if (pWall != nullptr) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());
	}

	if (pPlayer != nullptr) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());
	}

	if (pPlasma != nullptr) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());
	}

	if (pExp != nullptr) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());
	}

}
