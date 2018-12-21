


#pragma once

#include "Component.h"
#include <vector>

// Is the top "roof" and the bottom "floor". Basically all I want is the tag. All this class does is let us 
// generate a collision event specifically to change the balls y Vel value.

class COGEndZone : public Component {
public:
	static std::vector<COGEndZone*> mZoneComponents;

	virtual ComponentType GetType() const { return ComponentType::EndZone; }

	COGEndZone(GameObject* pGO, std::string tag)
		: Component(pGO)
		, tag(tag)
	{
	}

	virtual void Initialize() override;
	virtual void Destroy() override;

	// endzone will be either left or right. I might give up and just make seperate endzone types
	std::string tag;
};

