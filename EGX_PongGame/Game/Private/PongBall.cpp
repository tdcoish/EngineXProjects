

#include "Game/Private/PongBall.h"
#include "COGPhysics.h"
#include "COGEndZone.h"
#include "COGRoof.h"
#include "Paddle.h"

#include "ComponentTypes.h"

#include "Events.h"



COGBall* COGBall::mInstance;


// this hints that there is a queue of collision events for us to call, I don't think that's how James did it though.
void COGBall::Update() {

}

void COGBall::Initialize()
{
	// The ball gets a reference to the corresponding physics component, and also listens to its own collisions
	this->pPhysComp = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	pPhysComp->SetListener(this);

	/**********************************************
	Carlos and I were talking and we think that you wanted us to extend the listener system to something like this:
	
		AudioManager* pAudio = AudioSystem::getInstance();
		COGPhysics* pBallsPhysics = this->mGO->FindComponent<COGPhysics>(ComponentType::Physics);
		pBallsPhysics->SetListener(pAudio);

		ScoreManager* pScore = ScoreSystem::getInstance();
		pBallsPhysics->SetListener(pScore);

		WorldManager* pWorld = WorldSystem::getInstance();
		pBallsPhysics->SetListener(pWorld);

	Where AudioManager, Scoremanager, and WorldManager classes implement IPhysicsListener.

	// also, the COGBall/COGBounce component would listen to the physics objects collisions as well.
	***********************************************/
}

void COGBall::Destroy() {
	// seems risky. Uncomment later
	// COGBall::mInstance = nullptr;
}

void COGBall::OnCollision(COGPhysics* pMe, COGPhysics* pOther)
{
	// have to find the type of object that we've hit.
	// if paddle, change x vel
	// if top/bottom wall, change y vel
	// if we've hit an endzone, store which endzone we hit

	// Alright, so I can appreciate why Unity has tags for objects, since this is somewhat ridiculous.
	COGPaddle* pPaddle = pOther->mGO->FindComponent<COGPaddle>(ComponentType::Paddle);
	COGRoof* pRoof = pOther->mGO->FindComponent<COGRoof>(ComponentType::Roof);
	COGEndZone* pZone = pOther->mGO->FindComponent<COGEndZone>(ComponentType::EndZone);

	if (pPaddle!=nullptr) {
		this->pPhysComp->mVelocity.x *= -1;
	}

	if (pRoof!=nullptr) {
		this->pPhysComp->mVelocity.y *= -1;
	}

	if (pZone!=nullptr) {
		// change score, do other things.
		// alright this event manager is very hacky, but it sort of is the beginning of a real system.
		// what we do here is store what will be either "Left" or "Right"
		side = pOther->mGO->FindComponent<COGEndZone>(ComponentType::EndZone)->tag;
		//EventManager::StoreEvent(pOther->mGO->FindComponent<COGEndZone>(ComponentType::EndZone)->tag);
	}

}







