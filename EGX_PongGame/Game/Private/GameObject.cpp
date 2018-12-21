#include <string>

#include "Game/Public/InputManager.h"

#include "GameObject.h"
#include "Component.h"
#include "Paddle.h"
#include "PongBall.h"
#include "COGPhysics.h"
#include "COGEndZone.h"
#include "COGRoof.h"

class Component;

GameObject::GameObject() {}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

GameObject::~GameObject()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
}


void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}

// create our paddle
GameObject* CreatePaddle(std::string side)
{
	const float fPaddleWidth = 15.0f;
	const float fPaddleHeight = 50.0f;

	GameObject* pPaddle = new GameObject();

	COGPaddle* pPaddleLog = new COGPaddle(pPaddle, side);
	pPaddle->AddComponent(pPaddleLog);

	COGTransform* pTransform = new COGTransform(pPaddle);
	pPaddle->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pPaddle, fPaddleWidth, fPaddleHeight);
	pPaddle->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pPaddle, false);
	pPaddle->AddComponent(pPhysics);

	pPaddle->Initialize();
	
	return pPaddle;

	// we will set up initial position in ResetServe();
}

// create ball (notice how it will generate events)
GameObject* CreateBall()
{
	const float fBallRadius = 12.0f;

	GameObject* pBall = new GameObject();

	COGBall::mInstance = new COGBall(pBall);
	pBall->AddComponent(COGBall::mInstance);

	COGTransform* pTransform = new COGTransform(pBall);
	pBall->AddComponent(pTransform);

	COGCircleShape* pBoxShape = new COGCircleShape(pBall, fBallRadius);
	pBall->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pBall, true);
	pBall->AddComponent(pPhysics);

	pBall->Initialize();

	return pBall;
}

// should I be making one generic for these next two, and then initializing them seperately?
GameObject* CreateRoof(std::string tag) {
	const float fRoofWidth = 800.0f;
	const float fRoofHeight = 100.0f;

	GameObject* pRoof = new GameObject();

	COGRoof* pSomeRoof = new COGRoof(pRoof, tag);
	pRoof->AddComponent(pSomeRoof);

	COGTransform* pTransform = new COGTransform(pRoof);
	pRoof->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pRoof, fRoofWidth, fRoofHeight);
	pRoof->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pRoof, true);
	pRoof->AddComponent(pPhysics);

	pRoof->Initialize();

	return pRoof;
}


// should I be making one generic for these next two, and then initializing them seperately?
GameObject* CreateEndZone(std::string tag) {
	const float fZoneWidth = 20.0f;
	const float fZoneHeight = 800.0f;

	GameObject* pEndZone = new GameObject();

	COGEndZone* pZoneLogic = new COGEndZone(pEndZone, tag);
	pEndZone->AddComponent(pZoneLogic);

	COGTransform* pTransform = new COGTransform(pEndZone);
	pEndZone->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pEndZone, fZoneWidth, fZoneHeight);
	pEndZone->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pEndZone, true);
	pEndZone->AddComponent(pPhysics);

	pEndZone->Initialize();

	return pEndZone;
}





