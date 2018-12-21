#pragma once

#include "Game\Private\GOSystem\Component.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>

class COGBoxShape;
class COGCircleShape;

class COGDrawTurretState : public Component {
public:

	static COGDrawTurretState* mInstance;

	COGDrawTurretState(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::GFX_Turret_State; }

	void Initialize() override;
	void Destroy() override;

	void Update();

	// Need reference to the turret object here.
	GameObjectHandle mTurretHandle;

//private:
	// renders a black background
	// then renders white just inside of it, to give it a nice layered effect
	// then renders a black health bar inside of all that, to look super classy
	COGBoxShape* pRegular;
	COGBoxShape* pHyper;
	COGCircleShape* pGrenade;
};