
#include "World.h"
#include "Component.h"
#include "Engine\Public\EngineInterface.h"
#include "ComponentTypes.h"

#include "Paddle.h"
#include "COGPhysics.h"
#include "PongBall.h"
#include "COGEndZone.h"
#include "COGRoof.h"


void World::Create()
{
	mGameObjects.push_back(CreatePaddle("Left"));
	mGameObjects.push_back(CreatePaddle("Right"));
	mGameObjects.push_back(CreateBall());
	mGameObjects.push_back(CreateRoof("Roof"));
	mGameObjects.push_back(CreateRoof("Floor"));
	mGameObjects.push_back(CreateEndZone("Left"));
	mGameObjects.push_back(CreateEndZone("Right"));
}

void World::Destroy()
{
	for (GameObject* pGameObject : mGameObjects)
	{
		delete pGameObject;
	}

	mGameObjects.clear();
}

void World::Update(float fDeltaT, exEngineInterface* pEngine)
{
	// run things that take input first
	//COGPaddle::mInstance->Update();			//old code, back when there was just one.
	
	for (COGPaddle* pPaddle : COGPaddle::mPaddleComponents) {
		pPaddle->Update();
	}

	// run simulation first
	for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
	{
		pPhysics->Update(fDeltaT);
	}

	// then render everything
	for (COGShape* pShape : COGShape::mShapeComponents)
	{
		GameObject* pGO = pShape->mGO;
		COGTransform* pTrans = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		pShape->Render(pEngine, pTrans);
	}
}

void World::ResetServe() {
	// I made every different type of object have its own 
	// since every game object has a unique tag or identifier, it's not that hard to set their positions manually.
	for (GameObject* pObj : mGameObjects) {

		if (pObj->FindComponent<COGBall>(ComponentType::Ball)) {
			COGTransform* pTrans = pObj->FindComponent<COGTransform>(ComponentType::Transform);
			pTrans->SetPosition(400, 400);
			
			COGPhysics* pPhysics = pObj->FindComponent<COGPhysics>(ComponentType::Physics);
			pPhysics->mVelocity.x = 150;
			pPhysics->mVelocity.y = -100;
		}

		if (pObj->FindComponent<COGPaddle>(ComponentType::Paddle)) {
			COGTransform* pTrans = pObj->FindComponent<COGTransform>(ComponentType::Transform);
			if (pObj->FindComponent<COGPaddle>(ComponentType::Paddle)->tag == "Left") {
				pTrans->SetPosition(50, 200);
			}
			else {
				pTrans->SetPosition(700, 200);
			}
		}

		if (pObj->FindComponent<COGRoof>(ComponentType::Roof)) {
			COGTransform* pTrans = pObj->FindComponent<COGTransform>(ComponentType::Transform);
			if (pObj->FindComponent<COGRoof>(ComponentType::Roof)->tag == "Roof") {
					pTrans->SetPosition(0, -100);
			}
			else {
				pTrans->SetPosition(0, 600);
			}
		}
		if (pObj->FindComponent<COGEndZone>(ComponentType::EndZone)) {
			COGTransform* pTrans = pObj->FindComponent<COGTransform>(ComponentType::Transform);
			if (pObj->FindComponent<COGEndZone>(ComponentType::EndZone)->tag == "Left") {
				pTrans->SetPosition(0, 0);
			}
			else {
				pTrans->SetPosition(780, 0);
			}
		}
	}

}

