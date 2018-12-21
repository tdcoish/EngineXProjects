
#include "COGDrawHealth.h"
#include "COGTransform.h"
#include "COGShape.h"
#include "COGPlayer.h"

#include <string>

typedef unsigned int Hash;

std::vector<COGDrawHealth*> COGDrawHealth::mHealthDrawComponents;

COGDrawHealth::COGDrawHealth(GameObject* pGO)
	:Component(pGO)
{}

void COGDrawHealth::Initialize() {
	AddToComponentVector(mHealthDrawComponents);

	// Since there's only one player, and we always hash "PLAYER" for him, we can just get this guy.
	std::hash<std::string> s_hash;
	mPlayerHandle.mHash = s_hash("PLAYER");

	/*******************************
	* Huh. I see that apparently we can only have one transform per GO. It seems too much to shove a transform
	* into the COGShape itself. So in that case I might have to create three mini-objects for the various bars.
	* On the other hand, I could just only create one COGBoxShape and just change its shape three times.
	* Although apparently not, seeing as how I don't control how the object is rendered
	* Whatever, it won't look amazing, but it'll look decent.
	* Only issue is that the outline will look stupid.
	*******************************/
	exColor c = { 0, 0, 0, 255 };
	exColor wte = { 255, 255, 255, 255 };
	this->pBackground->SetHeight(20.f);
	pBackground->SetWidth(110.f);
	pBackground->SetColour(c);
	pUnderLayer->SetHeight(18.f);
	pUnderLayer->SetWidth(105.f);
	pUnderLayer->SetColour(wte);
	pHealthBar->SetHeight(16.f);
	pHealthBar->SetWidth(100.f);		//reset each frame
	pHealthBar->SetColour(c);
}


void COGDrawHealth::Destroy() {
	RemoveFromComponentVector(mHealthDrawComponents);
}

// Gets the players health and then draws the health bar appropriately
void COGDrawHealth::Update() {
	
	float widthPercent = 100.f;

	// I mean, this assumes that their max health == 100.
	if (this->mPlayerHandle.IsValid()) {
		widthPercent = (float) this->mPlayerHandle.Get()->FindComponent<COGPlayer>(ComponentType::Player)->health;
	}

	this->pHealthBar->SetWidth(widthPercent);
}