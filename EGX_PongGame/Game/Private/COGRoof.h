

#pragma once

#include "Component.h"
#include <vector>

// Is the top "roof" and the bottom "floor". Basically all I want is the tag. All this class does is let us 
// generate a collision event specifically to change the balls y Vel value.

class COGRoof : public Component {
public:
	static std::vector<COGRoof*> mRoofComponents;

	virtual ComponentType GetType() const { return ComponentType::Roof; }

	COGRoof(GameObject* pGO)
		: Component(pGO)
	{
	}

	COGRoof(GameObject* pGO, std::string type);

	virtual void Initialize() override;
	virtual void Destroy() override;

	// it will either be top or bottom, although it actually doesn't matter here
	std::string tag;

};
