


#include "Game/Private/Paddle.h"
#include "Game/Public/InputManager.h"
#include "COGPhysics.h"



std::vector<COGPaddle*> COGPaddle::mPaddleComponents;

COGPaddle::COGPaddle(GameObject* pGO, std::string type)
	: Component(pGO)
	, tag(type)
{}

void COGPaddle::Initialize()
{
	// give the paddle a reference to its physics component, needed for setting velocity
	this->pPhysComp = mGO->FindComponent<COGPhysics>(ComponentType::Physics);

	InputManager* pInput = InputManager::getInstance();
	if (this->tag== "Left") {
		this->downKey = pInput->kS;
		this->upKey = pInput->kW;
	}
	else if (this->tag == "Right") {
		this->downKey = pInput->kDown;
		this->upKey = pInput->kUp;
	}

	AddToComponentVector(mPaddleComponents);
}

void COGPaddle::Destroy() {
	RemoveFromComponentVector(mPaddleComponents);
}

void COGPaddle::Update() {
	InputManager* pInput = InputManager::getInstance();

	this->pPhysComp->mVelocity.y = 0;

	if (pInput->kStore & upKey) {
		this->pPhysComp->mVelocity.y -= 200;
	}

	if (pInput->kStore & downKey) {
		this->pPhysComp->mVelocity.y += 200;
	}

	// should we handle boxing it in here or in physics?
	// probably not here
}


















//void PongPaddle::Move(float fDeltaT) {
//	//update position by velocity
//
//	//get input reference
//	InputManager* pInput = InputManager::getInstance();
//
//	Uint32 upKeyForMe;
//	Uint32 downKeyForMe;
//	if (this->owner == PLAYER_ONE) {
//		upKeyForMe = pInput->kW;
//		downKeyForMe = pInput->kS;
//	}
//	if (this->owner == PLAYER_TWO) {
//		//change these
//		upKeyForMe = pInput->kUp;
//		downKeyForMe = pInput->kDown;
//	}
//
//	float runningVel = 0;			//they might be pressing both up and down
//									//spinning 
//	if (pInput->kStore & upKeyForMe) {
//		runningVel -= 400.0f*fDeltaT;
//	}
//	if (pInput->kStore & downKeyForMe) {
//		runningVel += 400.0f*fDeltaT;
//	}
//
//	this->vel.y = runningVel;
//
//	if (vel.y != 0) {
//
//	}
//
//	//change by delta time, no x position 
//	this->pos.y += this->vel.y;
//
//	if (pos.y < 0) {
//		pos.y = 0;
//	}
//	else if (pos.y > 600) {
//		pos.y = 600;
//	}
//
//	//make col and render rectangle equal the current position
//	col.x = pos.x;
//	col.y = pos.y;
//}







