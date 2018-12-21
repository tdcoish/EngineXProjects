
#include "Game/Private/COG/COGPhysics.h"
#include "Game/Private/COG/COGTransform.h"
#include "Game/Private/COG/COGShape.h"

//Get rid of these immediately.
#include "Game/Private/COG/COGPlayer.h"
#include "Game/Private/COG/COGZergling.h"


std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;

COGPhysics::COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents)
	: Component(pGO)
	, mGenerateCollisionEvents(bGenerateCollisionEvents)
{
}

void COGPhysics::Initialize()
{

	mTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mBoxShape = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mCircleShape = mGO->FindComponent<COGCircleShape>(ComponentType::CircleShape);

	AddToComponentVector(mPhysicsComponents);
}

void COGPhysics::Destroy()
{
	RemoveFromComponentVector(mPhysicsComponents);
}

void COGPhysics::Update(float fDeltaT)
{	
	// integrate velocity
	exVector2& myPosition = mTransform->GetPosition();

	myPosition.x += mVelocity.x * fDeltaT;
	myPosition.y += mVelocity.y * fDeltaT;

	// check collisions
	if (mGenerateCollisionEvents)
	{
		for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
		{
			// do not collide with self
			if (pPhysicsOther == this)
			{
				continue;
			}

			// TODO - maybe have IsColliding produce a vector/struct that contains the normal and then pass that into OnCollision?
			const bool bResult = IsColliding(pPhysicsOther);

			if (bResult){
				
				// as of right now the only collision listener is the ball, which listens to itself. Eventually this won't be the case.
				for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners){
					pCollisionEventListener->OnCollision(this, pPhysicsOther);
				}
			}
		}
	}
}

/**************************************************************************************
Alright, it took a long time but I think I finally see what the purpose of this is. So right now the 
only object that has a listener is the ball which listens to itself, and then handles all its collision 
events. However, I think this would make more sense if we also had something like an audio system listening 
for ball collisions, along with a score system, and maybe a few other things. Since I don't have time I'm not 
going to change it now though, but in the future.
**************************************************************************************/
void COGPhysics::SetListener(IPhysicsCollisionEvent* pListener) {
	this->mCollisionEventListeners.push_back(pListener);
}

bool COGPhysics::IsColliding(COGPhysics* pOther)
{
	// This just means that mCircleShape is initialized, should always be true
	if (mCircleShape != nullptr && pOther->mBoxShape != nullptr)
	{
		// check a circle colliding with a box
		// This is pretty much just cheating, but I'm pretending that the circle is a box of w and h radius
		CollisionRect circle;
		exVector2 circlePos = this->mTransform->GetPosition();
		circle.x = circlePos.x;
		circle.y = circlePos.y;
		circle.w = this->mCircleShape->GetRadius();
		circle.h = circle.w;

		CollisionRect box;
		exVector2 boxPos = pOther->mTransform->GetPosition();
		box.x = boxPos.x;
		box.y = boxPos.y;
		box.w = pOther->mBoxShape->GetWidth();
		box.h = pOther->mBoxShape->GetHeight();

		if (CheckCollision(circle, box)) {
			return true;
		}
	}

	// if two circles colliding
	if (this->mCircleShape != nullptr && pOther->mCircleShape != nullptr) {
		if (CheckCircleCollision(mTransform->GetPosition(), mCircleShape->GetRadius(), pOther->mTransform->GetPosition(), pOther->mCircleShape->GetRadius())) {
			return true;
		}
	}

	// we don't cover the other cases
	// maybe assert here?

	return false;
}

