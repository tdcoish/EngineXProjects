

#include "Game/Private/COG/COGPhysics.h"
#include "COGExplosion.h"

#include "Game\Private\GOSystem\GameObjectInventory.h"

std::vector<COGExplosion*> COGExplosion::mExplosionComponents;

COGExplosion::COGExplosion(GameObject* pGO)
	: Component(pGO)
{}

void COGExplosion::Initialize()
{
	AddToComponentVector(mExplosionComponents);

	timeSinceSpawned = 0.0f;
	lifetime = 0.9f;			//lives for x seconds
}

void COGExplosion::Destroy() {
	RemoveFromComponentVector(mExplosionComponents);
}

void COGExplosion::Update(float fDeltaT) {
	timeSinceSpawned += fDeltaT;

	if (timeSinceSpawned > lifetime) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(mGO->GetHandle());
	}
}

