

#include "EnemyFactory.h"
#include "World.h"
#include "Game/Private/GOSystem/GameObjectInventory.h"
#include "Game\Private\GOSystem\GameObjectHandles.h"

#include "Game/Private/COG/COGPhysics.h"
#include "Game/Private/COG/COGPlayer.h"
#include "Game/Private/COG/COGTurret.h"
#include "Game/Private/COG/COGPlasma.h"
#include "Game/Private/COG/COGTransform.h"
#include "Game/Private/COG/COGShape.h"
#include "Game\Private\COG\COGWall.h"
#include "Game\Private\COG\COGDrawHealth.h"
#include "Game\Private\COG\COGDrawTurretState.h"
#include "Game\Private\COG\COGGrenade.h"
#include "Game\Private\COG\COGExplosion.h"
#include "Game\Private\COG\COGZergling.h"

#include "Game\Private\Helpers\GraphicsLayers.h"

// this is a hack, take it out ASAP
#include "Game\Private\Helpers\Physics.h"

#include <string>

/****************************************************************************************
This function exists because I had that issue with zerglings where I immediately started 
getting repeating hashes, after ZERGLING8 and ZERGLING11 matched. I decided to just 
create this function since everything that spawns more than once basically needs this.

Weird bug -- The line: *index++
needed to be replaced with the line
*index+=1. 
Not sure if compiler error or language quirk. Ask James.
****************************************************************************************/ 
GameObjectHandle GenValidHandle(std::string name, int* index) {
	std::hash<std::string> s_hash;
	GameObjectHandle check;
	check.mHash = s_hash(name.c_str() + *index);
	*index+=1;
	if (check.IsValid()) {
		while (check.IsValid()) {
			check.mHash = s_hash(name.c_str() + *index);
			*index+=1;
		}
	}

	return check;
}

/************************************************************************************
It seems somehow very wrong that I'm adding GO pointers both to the GOInventory and 
the World object, which holds a vector of GO's. I felt that world was unnecessary, but I 
wasn't really sure how to correctly iterate through the GOInventory, or if that was truly
what should have been done.
************************************************************************************/

EnemyFactory::EnemyFactory()
	:turretIndex(0)
	,healthIndex(0)
	,plasmaIndex(0)
	,wallIndex(0)
	,zerglingIndex(0)
	,explosionIndex(0)
	,grenadeIndex(0)
{
}

// Create our hero, can only have one at a time
void EnemyFactory::CreatePlayer() {
	const float fPlayerSize = 12.0f;

	GameObject* pPlayer = new GameObject(s_hash("PLAYER"));

	COGPlayer::mInstance = new COGPlayer(pPlayer);
	pPlayer->AddComponent(COGPlayer::mInstance);

	COGTransform* pTransform = new COGTransform(pPlayer);
	pPlayer->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pPlayer, fPlayerSize, GraphicsLayers::PLAYER);
	pPlayer->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pPlayer, true);
	pPlayer->AddComponent(pPhysics);

	pPlayer->Initialize();

	World::getInstance()->AddEntity(pPlayer->GetHandle());
	GameObjectInventory::getInstance()->Register(pPlayer);
}

void EnemyFactory::CreateTurret(float xPos, float yPos) {
	const float fTurretSize = 15.0f;

	GameObject* pTurret = new GameObject(s_hash("TURRET"));

	COGTurret::mInstance = new COGTurret(pTurret);
	pTurret->AddComponent(COGTurret::mInstance);

	COGTransform* pTransform = new COGTransform(pTurret);
	pTurret->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pTurret, fTurretSize, GraphicsLayers::ENEMIES);
	pTurret->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pTurret, true);
	pTurret->AddComponent(pPhysics);

	pTurret->Initialize();

	pTransform->SetPosition(xPos, yPos);

	GameObjectInventory::getInstance()->Register(pTurret);
	World::getInstance()->AddEntity(pTurret->GetHandle());
}

void EnemyFactory::CreateZergling(float xPos, float yPos) {
	const float fZerglingSize = 15.0f;

	/**************************************************************************************************************
	* Since I'm worried that some zerglings are getting conflicting hashes, I'm going to check this first.
	* Wow, sure enough duplicate hashes were created. It's quite dissapointing that this system is giving duplicates 
	* This early. Leads me to believe that we're checking the 256 values, instead of the 4.3billion true hashes.
	* 
	* Update: This is a truly crazy bug. So it turns out that the hash "ZERGLING8" and "ZERGLING11" both convert to:
	* 2166136261 in the std::hash formula. It's totally insane that this formula could produce duplicates after just 
	* 11 iterations. Seeing that, I decided to put this while loop here to check if the hash is valid and just recheck
	* over and over again. Luckily, we only use zerglingIndex for hash functions, or this would really screw up some 
	* gameplay code that relied on it. Finally, I think I might have to extend this to other systems, although "ZERGLING"
	* might just really give weird results for some reason.
	**************************************************************************************************************/
	GameObjectHandle handle = GenValidHandle("ZERGLING", &this->zerglingIndex);

	GameObject* pZergling = new GameObject(handle.mHash);

	COGZergling* pZergLogic = new COGZergling(pZergling);
	pZergling->AddComponent(pZergLogic);

	COGTransform* pTransform = new COGTransform(pZergling);
	pZergling->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pZergling, fZerglingSize, GraphicsLayers::ENEMIES);
	pZergling->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pZergling, true);
	pZergling->AddComponent(pPhysics);

	pZergling->Initialize();

	pTransform->SetPosition(xPos, yPos);

	GameObjectInventory::getInstance()->Register(pZergling);
	World::getInstance()->AddEntity(pZergling->GetHandle());
}

void EnemyFactory::CreatePlasmoid(exVector2 pos, exVector2 dest) {
	const float fPlasmoidSize = 4.0f;

	// Didn't want another zergling issue on my hands, so I just decided to do this pre-emptively.
	GameObjectHandle handle = GenValidHandle("PLASMOID", &plasmaIndex);

	GameObject* pPlasmoid = new GameObject(handle.mHash);

	COGPlasma* pPlasmoidLogic = new COGPlasma(pPlasmoid);
	pPlasmoid->AddComponent(pPlasmoidLogic);

	COGTransform* pTransform = new COGTransform(pPlasmoid);
	pPlasmoid->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pPlasmoid, fPlasmoidSize, GraphicsLayers::PARTICLE_EFFECTS);
	pPlasmoid->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pPlasmoid, true);
	pPlasmoid->AddComponent(pPhysics);

	// Set position to passed in position
	pTransform->SetPosition(pos.x, pos.y);

	// Here we set the velocity based upon the passed in angle.
	// say speed == 10.0f for now.
	float spd = 400.0f;
	float angle = FindAngleBetweenObjects(pos, dest);
	pPhysics->mVelocity.x = std::sin(angle) * spd;
	pPhysics->mVelocity.y = std::cos(angle) * spd;

	// coordinate hacks. It's fine for now
	// I'll figure out my physics code bugs later
	pPhysics->mVelocity.y *= -1;		
	if (dest.x < pos.x) pPhysics->mVelocity.x *= -1;

	pPlasmoid->Initialize();

	GameObjectInventory::getInstance()->Register(pPlasmoid);
	World::getInstance()->AddEntity(pPlasmoid->GetHandle());
}

void EnemyFactory::CreateGrenade(exVector2 pos, exVector2 dest) {
	const float fGrenadeSize = 2.0f;

	// Didn't want another zergling issue on my hands, so I just decided to do this pre-emptively.
	GameObjectHandle handle = GenValidHandle("GRENADE", &grenadeIndex);

	GameObject* pGrenade = new GameObject(handle.mHash);

	COGGrenade* pGrenadeLogic = new COGGrenade(pGrenade);
	pGrenade->AddComponent(pGrenadeLogic);

	COGTransform* pTransform = new COGTransform(pGrenade);
	pGrenade->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pGrenade, fGrenadeSize, GraphicsLayers::PARTICLE_EFFECTS);
	pGrenade->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pGrenade, false);			// grenade also does not care about it's own collisions
	pGrenade->AddComponent(pPhysics);

	// Set position to passed in position
	pTransform->SetPosition(pos.x, pos.y);

	// Here we set the velocity based upon the passed in angle.
	// say speed == 10.0f for now.
	float spd = 100.0f;
	float angle = FindAngleBetweenObjects(pos, dest);
	pPhysics->mVelocity.x = std::sin(angle) * spd;
	pPhysics->mVelocity.y = std::cos(angle) * spd;

	// coordinate hacks. It's fine for now
	// I'll figure out my physics code bugs later
	pPhysics->mVelocity.y *= -1;
	if (dest.x < pos.x) pPhysics->mVelocity.x *= -1;

	pGrenade->Initialize();

	GameObjectInventory::getInstance()->Register(pGrenade);
	World::getInstance()->AddEntity(pGrenade->GetHandle());
}


void EnemyFactory::CreateExplosion(exVector2 pos) {
	const float fExplosionSize = 80.0f;

	// Didn't want another zergling issue on my hands, so I just decided to do this pre-emptively.
	GameObjectHandle handle = GenValidHandle("EXPLOSION", &explosionIndex);

	GameObject* pExplosion = new GameObject(handle.mHash);

	COGExplosion* pExplosionLogic = new COGExplosion(pExplosion);
	pExplosion->AddComponent(pExplosionLogic);

	COGTransform* pTransform = new COGTransform(pExplosion);
	pExplosion->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pExplosion, fExplosionSize, GraphicsLayers::PARTICLE_EFFECTS);
	pExplosion->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pExplosion, false);		// explosion does not care about it's own collisions
	pExplosion->AddComponent(pPhysics);

	// Set position to passed in position
	pTransform->SetPosition(pos.x, pos.y);

	pExplosion->Initialize();

	GameObjectInventory::getInstance()->Register(pExplosion);
	World::getInstance()->AddEntity(pExplosion->GetHandle());
}

void EnemyFactory::CreateHealthBar(float xPos, float yPos) {
	const float fBackWidth = 100.0f;
	const float fBackHeight = 10.0f;
	const float fBackInsideWidth = 98.0f;
	const float fBackInsideHeight = 9.0f;
	// actual health calculated procedurally, but forget that for now.
	float fHealthW = 96.0f;
	float fHealthH = 8.0f;

	// No need for an index, at least for now.
	GameObject* pHealthImgObj = new GameObject(s_hash("HEALTH_BAR"));

	COGDrawHealth* pHealthRenderer = new COGDrawHealth(pHealthImgObj);
	pHealthImgObj->AddComponent(pHealthRenderer);

	pHealthRenderer->pBackground = new COGBoxShape(pHealthImgObj, fBackWidth, fBackHeight, GraphicsLayers::UI0);
	pHealthImgObj->AddComponent(pHealthRenderer->pBackground);

	pHealthRenderer->pUnderLayer = new COGBoxShape(pHealthImgObj, fBackInsideWidth, fBackInsideHeight, GraphicsLayers::UI1);
	pHealthImgObj->AddComponent(pHealthRenderer->pUnderLayer);

	pHealthRenderer->pHealthBar = new COGBoxShape(pHealthImgObj, fHealthW, fHealthH, GraphicsLayers::UI2);
	pHealthImgObj->AddComponent(pHealthRenderer->pHealthBar);

	COGTransform* pTrans = new COGTransform(pHealthImgObj);
	pHealthImgObj->AddComponent(pTrans);
	pTrans->SetPosition(xPos, yPos);

	pHealthImgObj->Initialize();

	GameObjectInventory::getInstance()->Register(pHealthImgObj);
	World::getInstance()->AddEntity(pHealthImgObj->GetHandle());
}

void EnemyFactory::CreateTurretStateGFX(float xPos, float yPos) {
	const float fImageWidth = 20.0f;
	const float fImageHeight = 20.0f;

	// No need for an index, at least for now.
	GameObject* pTurretGFXObj = new GameObject(s_hash("TURRET_GRAPHICS"));

	COGDrawTurretState::mInstance = new COGDrawTurretState(pTurretGFXObj);
	pTurretGFXObj->AddComponent(COGDrawTurretState::mInstance);

	COGDrawTurretState::mInstance->pGrenade = new COGCircleShape(pTurretGFXObj, fImageWidth, GraphicsLayers::UI0);
	pTurretGFXObj->AddComponent(COGDrawTurretState::mInstance->pGrenade);

	COGDrawTurretState::mInstance->pRegular = new COGBoxShape(pTurretGFXObj, fImageWidth, fImageHeight, GraphicsLayers::UI0);
	pTurretGFXObj->AddComponent(COGDrawTurretState::mInstance->pRegular);

	COGDrawTurretState::mInstance->pHyper = new COGBoxShape(pTurretGFXObj, fImageWidth, fImageHeight, GraphicsLayers::UI0);
	pTurretGFXObj->AddComponent(COGDrawTurretState::mInstance->pHyper);

	COGTransform* pTrans = new COGTransform(pTurretGFXObj);
	pTurretGFXObj->AddComponent(pTrans);
	pTrans->SetPosition(xPos, yPos);

	pTurretGFXObj->Initialize();

	GameObjectInventory::getInstance()->Register(pTurretGFXObj);
	World::getInstance()->AddEntity(pTurretGFXObj->GetHandle());
}

// All walls will be 800x800
void EnemyFactory::CreateWall(float xPos, float yPos) {
	const float fWallWidth = 800.0f;
	const float fWallHeight = 800.0f;

	GameObject* pWall = new GameObject(s_hash("WALL" + wallIndex));

	COGWall* pWallLogic = new COGWall(pWall);
	pWall->AddComponent(pWallLogic);

	COGTransform* pTrans = new COGTransform(pWall);
	pWall->AddComponent(pTrans);
	pTrans->SetPosition(xPos, yPos);

	COGBoxShape* pBoxShape = new COGBoxShape(pWall, fWallWidth, fWallHeight, GraphicsLayers::BACKGROUND);
	pWall->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pWall, true);
	pWall->AddComponent(pPhysics);

	pWall->Initialize();

	GameObjectInventory::getInstance()->Register(pWall);
	World::getInstance()->AddEntity(pWall->GetHandle());
}

