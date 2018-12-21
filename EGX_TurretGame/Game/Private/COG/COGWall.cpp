
#include "Game/Private/Helpers/Physics.h"

#include "COGWall.h"

#include "Game/Private/Gameplay/EnemyFactory.h"

std::vector<COGWall*> COGWall::mWallComponents;

COGWall::COGWall(GameObject* pGO)
	: Component(pGO)
{}

void COGWall::Initialize()
{
	AddToComponentVector(mWallComponents);
}

void COGWall::Destroy() {
	RemoveFromComponentVector(mWallComponents);
}
