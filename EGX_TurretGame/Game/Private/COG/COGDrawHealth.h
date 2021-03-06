#pragma once

#include "Game\Private\GOSystem\Component.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>

class COGBoxShape;

class COGDrawHealth : public Component {
public:

	// initialize this in the .cpp
	static std::vector<COGDrawHealth*> mHealthDrawComponents;

	COGDrawHealth(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Health_Drawer; }

	void Initialize() override;
	void Destroy() override;

	void Update();

	// Need reference to the player object here.
	GameObjectHandle mPlayerHandle;

//private:
	// renders a black background
	// then renders white just inside of it, to give it a nice layered effect
	// then renders a black health bar inside of all that, to look super classy
	COGBoxShape* pBackground;
	COGBoxShape* pUnderLayer;
	COGBoxShape* pHealthBar;
};