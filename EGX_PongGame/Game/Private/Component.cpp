
#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Engine\Public\EngineInterface.h"
#include <vector>


class GameObject;

Component::Component(GameObject* pGO)
	: mGO(pGO)
{
}

// here he actually initializes the static components. This must be done or weird linker errors will happen.
std::vector<COGShape*> COGShape::mShapeComponents;


void COGShape::Initialize() 
{
	AddToComponentVector(mShapeComponents);
}

void COGShape::Destroy()
{
	RemoveFromComponentVector(mShapeComponents);
}






