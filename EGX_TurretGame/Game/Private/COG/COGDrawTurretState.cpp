
#include "COGDrawTurretState.h"
#include "COGTransform.h"
#include "COGTurret.h"
#include "COGShape.h"
#include "COGPlayer.h"

#include "Game\Private\GOSystem\GameObjectHandles.h"

#include <string>

typedef unsigned int Hash;

COGDrawTurretState* COGDrawTurretState::mInstance;

COGDrawTurretState::COGDrawTurretState(GameObject* pGO)
	:Component(pGO)
{}

void COGDrawTurretState::Initialize() {

	// Luckily, again, there's only one turret, so we can just hash "TURRET" and get the turret whenever it's created.
	// Since there's only one player, and we always hash "PLAYER" for him, we can just get this guy.
	std::hash<std::string> s_hash;
	mTurretHandle.mHash = s_hash("TURRET");

	/*******************************
	* Basically this is a standin for actually having textures.
	*******************************/
	exColor reg = { 0, 0, 0, 255 };
	exColor hyp = { 255, 100, 100, 255 };

	this->pRegular->SetHeight(20.f);
	this->pHyper->SetHeight(20.f);
	this->pGrenade->SetRadius(20.f);

	this->pRegular->SetWidth(20.f);
	this->pHyper->SetWidth(20.f);

	this->pRegular->SetColour(reg);
	this->pHyper->SetColour(hyp);
	this->pRegular->SetColour(reg);
}


void COGDrawTurretState::Destroy() {
	mInstance = nullptr;
}

// TODO: move this to a better place
void SetGraphicToTransparent(COGShape* pShape) {
	exColor c = pShape->GetColour();
	c.mColor[3] = 0;
	pShape->SetColour(c);
}

void SetGraphicToVisible(COGShape* pShape) {
	exColor c = pShape->GetColour();
	c.mColor[3] = 255;
	pShape->SetColour(c);
}

/********************************************************************************
* It's quite hacky, but I couldn't find any easy way to disable images. The only solutions 
* I came up with were setting the transparency to 0, used here, or setting the layer to 
* something before the background layer.
********************************************************************************/
void COGDrawTurretState::Update() {
	
	if (this->mTurretHandle.IsValid()) {
		// set the correct one active
		COGTurret* pTurLog = this->mTurretHandle.Get()->FindComponent<COGTurret>(ComponentType::Turret);
		
		switch (pTurLog->mState) {
		case REGULAR:
			SetGraphicToTransparent(pGrenade);
			SetGraphicToTransparent(pHyper);
			SetGraphicToVisible(pRegular);
			break;
		case HYPER:
			SetGraphicToTransparent(pGrenade);
			SetGraphicToTransparent(pRegular);
			SetGraphicToVisible(pHyper);
			break;
		case GRENADE:
			SetGraphicToTransparent(pRegular);
			SetGraphicToTransparent(pHyper);
			SetGraphicToVisible(pGrenade);
			break;
		}
	}

}