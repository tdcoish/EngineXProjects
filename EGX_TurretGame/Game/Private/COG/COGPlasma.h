#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Helpers/Collision.h"
#include "Game\Private\GOSystem\Component.h"

#include "Engine/Public/SDL.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>

class COGPhysics;

// all this needs to do is listen to keys and move itself
class COGPlasma : public Component, public IPhysicsCollisionEvent {
public:

	static std::vector<COGPlasma*> mPlasmoidComponents;

	COGPlasma(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Plasmoid; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override;

	void Update();

};