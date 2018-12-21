#pragma once

#include "Engine\Public\EngineInterface.h"
#include "Game\Private\GOSystem\Component.h"

// COGTransform - where we are in space
class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Transform; }

	exVector2& GetPosition() { return mPosition; }

	// sometimes we just have to manually set a position
	void SetPosition(float x, float y) {
		mPosition.x = x;
		mPosition.y = y;
	}

private:

	exVector2 mPosition;

};