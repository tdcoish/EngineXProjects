
#include "COGRoof.h"
#include <string>
#include "GameObject.h"

std::vector<COGRoof*> COGRoof::mRoofComponents;

COGRoof::COGRoof(GameObject* pGO, std::string type)
	: Component(pGO)
	, tag(type)
{}


void COGRoof::Initialize()
{
	AddToComponentVector(mRoofComponents);
}

void COGRoof::Destroy()
{
	RemoveFromComponentVector(mRoofComponents);
}



