
#include "Engine\Public\EngineInterface.h"

#include "COGGrenade.h"
#include "COGTransform.h"

#include "Game\Private\GOSystem\GameObjectInventory.h"
#include "Game\Private\Gameplay\EnemyFactory.h"

std::vector<COGGrenade*> COGGrenade::mGrenadeComps;

COGGrenade::COGGrenade(GameObject* pGO)
	: Component(pGO)
{}

void COGGrenade::Initialize()
{
	AddToComponentVector(mGrenadeComps);

	timeSinceSpawned = 0.0f;
	lifetime = 1.5f;
}

void COGGrenade::Destroy() {
	RemoveFromComponentVector(mGrenadeComps);
}

void COGGrenade::Update(float fDeltaT) {
	timeSinceSpawned += fDeltaT;

	if (timeSinceSpawned > lifetime) {
		GameObjectInventory::getInstance()->StoreGOForDeletion(this->mGO->GetHandle());
		exVector2 pos = mGO->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();

		// A real game we would look up the radius of an explosion or something
		// here I'm just hardcoding it as 40.0f
		float radius = 40.0f;
		pos.x -= radius;
		pos.y -= radius;
		EnemyFactory::getInstance()->CreateExplosion(pos);
	}
}


