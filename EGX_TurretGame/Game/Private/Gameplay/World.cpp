
#include "World.h"
#include "Game/Private/GOSystem/Component.h"
#include "Engine\Public\EngineInterface.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include "Game/Private/COG/COGPhysics.h"

#include "Game/Private/COG/COGPlayer.h"
#include "Game/Private/COG/COGPlasma.h"
#include "Game/Private/COG/COGTurret.h"
#include "Game/Private/COG/COGShape.h"
#include "Game/Private/COG/COGTransform.h"
#include "Game/Private/COG/COGDrawHealth.h"
#include "Game/Private/COG/COGDrawTurretState.h"
#include "Game/Private/COG/COGGrenade.h"
#include "Game/Private/COG/COGExplosion.h"

#include "EnemyFactory.h"
#include "EnemySpawner.h"

#include "Game/Private/GOSystem/GameObjectInventory.h"

#include <string>
#include <iostream>

typedef unsigned int Hash;

World::World()
{
}

void World::Create()
{
	EnemyFactory* pFactory = EnemyFactory::getInstance();

	pFactory->CreatePlayer();
	pFactory->CreateHealthBar(350, 20);	
	// Notice I create this object that needs a handle to the turret before I create the turret
	// Would be impossible with raw pointers. Or require searching per frame or something like that.
	pFactory->CreateTurret(100, 400);
	pFactory->CreateTurretStateGFX(20, 20);

	pFactory->CreateWall(0, -800);
	pFactory->CreateWall(-800, 0);
	pFactory->CreateWall(800, 0);
	pFactory->CreateWall(0, 800);
}

/**************************************************************************************
* The below code makes a ton more sense now, with our GOInventory system. Instead of also
* storing the raw pointers, we instead just make a list of the specific actors we want 
* deleted from the game world, which simulates the loading and unloading of part of a level, 
* for example.
**************************************************************************************/
void World::Destroy()
{
	GameObjectInventory* pInventory = GameObjectInventory::getInstance();
	for (GameObjectHandle handle : mGameObjHandles) {
		pInventory->StoreGOForDeletion(handle);
	}

	mGameObjHandles.clear();

	// This entire system I've written seems just a tad off,
	// TODO: Implement different system for iterating through GO's, calling GOInventory.
	pInventory->DeleteQueuedHandles();
}

/**************************************************************************************
What World basically does is churn through a bunch of static globals for each component 
and have them do their thing.
------------
Update: Since I didn't properly understand the point of handles I threw a bunch of isValid
checks in here, which makes little sense since we're already going through a pointer to get 
the handle. I have removed all of these, although I do store a handle in the COGDrawHealth 
component itself, since it needs a reference to the player object.
-----------
Update:
It's important to understand that World should probably not be calling this Update function,
or rather, it is a touch weird to have this update as a method of the World. Since World should 
be renamed something akin to "SceneObj", it probably should be seperate from a class or even just
loose function that iterates through all global components and updates them.
This is especially true in the above instance of our World/Level only owning a small portion of the 
currently active GO's in the game.
**************************************************************************************/
void World::Update(float fDeltaT, exEngineInterface* pEngine)
{
	// run things that take input first
	COGPlayer::mInstance->Update();

	// New turret actually just does it's thing. There is only one.
	COGTurret::mInstance->Update(fDeltaT);
	
	// run simulation second
	for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
	{
		pPhysics->Update(fDeltaT);
	}

	// plasmoid ball doesn't need to update itself, some COGs do
	// run things that take logic not requiring input third
	for (COGGrenade* pGrenade : COGGrenade::mGrenadeComps) {
		pGrenade->Update(fDeltaT);
	}
	for (COGExplosion* pExplosion: COGExplosion::mExplosionComponents) {
		pExplosion->Update(fDeltaT);
	}
	for (COGDrawHealth* pHealthBar : COGDrawHealth::mHealthDrawComponents) {
		pHealthBar->Update();
	}
	
	COGDrawTurretState::mInstance->Update();

	// then render everything
	for (COGShape* pShape : COGShape::mShapeComponents)
	{
		GameObject* pGO = pShape->mGO;
		COGTransform* pTrans = pGO->FindComponent<COGTransform>(ComponentType::Transform);
		pShape->Render(pEngine, pTrans);
	}

	// Empty our queue of objects to delete.
	GameObjectInventory::getInstance()->DeleteQueuedHandles();

	// Now spawn new objects in if appropriate
	EnemySpawner* pSpawner = EnemySpawner::getInstance();
	if (pSpawner->CheckSpawnTime(fDeltaT)) {
		pSpawner->SpawnNewEnemy();
	}
}

// Player has already been created
void World::SetUpLevel() {

	for (GameObjectHandle handle : mGameObjHandles) {
		if (handle.IsValid()) {
			if (handle.Get()->FindComponent<COGPlayer>(ComponentType::Player)) {
				COGTransform* pTrans = handle.Get()->FindComponent<COGTransform>(ComponentType::Transform);
				pTrans->SetPosition(80, 400);

				COGPlayer* pPlayer = handle.Get()->FindComponent<COGPlayer>(ComponentType::Player);
				pPlayer->health = 100;
			}
			// set up other gameobjects here, or not
		}
	}
}

////
//
//void World::Update(float fDeltaT, exEngineInterface* pEngine)
//{
//	// run things that take input first
//	COGPlayer::mInstance->Update();
//
//	// run simulation first
//	for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
//	{
//		pPhysics->Update(fDeltaT);
//	}
//
//	// plasmoid ball doesn't need to update itself, some COGs do
//
//	// Turret, for instance, seeks out player and fires at them
//	for (COGTurret* pTurret : COGTurret::mTurretComponents) {
//		pTurret->Update(fDeltaT);
//	}
//
//	// then render everything-
//	for (COGShape* pShape : COGShape::mShapeComponents)
//	{
//		GameObject* pGO = pShape->mGO;
//		COGTransform* pTrans = pGO->FindComponent<COGTransform>(ComponentType::Transform);
//		pShape->Render(pEngine, pTrans);
//	}
//
//	// Now spawn new objects in if appropriate
//	EnemySpawner* pSpawner = EnemySpawner::getInstance();
//	if (pSpawner->CheckSpawnTime(fDeltaT)) {
//		pSpawner->SpawnNewEnemy();
//	}
//}
