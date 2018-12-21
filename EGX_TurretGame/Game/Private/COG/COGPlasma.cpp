

#include "Game/Private/COG/COGPlasma.h"
#include "Game/Private/COG/COGPhysics.h"
#include "Game\Private\COG\COGWall.h"
#include "COGZergling.h"

#include "Game\Private\GOSystem\GameObjectInventory.h"

std::vector<COGPlasma*> COGPlasma::mPlasmoidComponents;

COGPlasma::COGPlasma(GameObject* pGO)
	: Component(pGO)
{}

void COGPlasma::Initialize()
{
	AddToComponentVector(mPlasmoidComponents);

	// Again, for this project I'm just having objects listen to their own collisions.
	// However, I could have something like:
	// mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(AudioSystem::getInstance());
	// mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(ScoreSystem::getInstance());
	// mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(SomeThingElse::getInstance());
	mGO->FindComponent<COGPhysics>(ComponentType::Physics)->SetListener(this);
}

void COGPlasma::Destroy() {
	RemoveFromComponentVector(mPlasmoidComponents);
}

void COGPlasma::Update() {

}

void COGPlasma::OnCollision(COGPhysics* pMe, COGPhysics* pOther)
{
	// everything but the turret and player will trigger the plasmoid to delete itself
	COGZergling* pZerg = pOther->mGO->FindComponent<COGZergling>(ComponentType::Zergling);

	if (pZerg != nullptr) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());
	}

}
