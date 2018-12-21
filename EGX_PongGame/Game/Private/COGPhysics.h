

#pragma once

#include "Engine\Public\EngineInterface.h"
#include <vector>
#include "Component.h"

// COGPhysics - lets move around
class COGPhysics : public Component
{
public:

	static std::vector<COGPhysics*> mPhysicsComponents;

public:

	COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents);

	virtual ComponentType GetType() const { return ComponentType::Physics; }

	virtual void Initialize() override;

	virtual void Destroy() override;

	virtual void Update(float fDeltaT);

	bool IsColliding(COGPhysics* pOther);

	// migrate this back to private later.
	exVector2 mVelocity;

	void SetListener(IPhysicsCollisionEvent* pListener);

private:

	// These are the individual objects physics components. One will always be null.
	COGTransform * mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;


	bool mGenerateCollisionEvents;
	// has vector of physics collision events. But needs vector of listeners
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;

};

