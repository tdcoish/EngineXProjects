#pragma once

#include "Game\Private\GOSystem\Component.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>

class COGPhysics;

// all this needs to do is listen to keys and move itself
class COGZergling : public Component, public IPhysicsCollisionEvent {
public:

	static std::vector<COGZergling*> mZerglingComponents;

	COGZergling(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Zergling; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override;

	void Update();

};