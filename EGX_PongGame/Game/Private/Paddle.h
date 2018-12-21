

#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Collision.h"
#include "Game\Private\Component.h"

#include "Engine/Public/SDL.h"
#include "ComponentTypes.h"

#include <vector>



class COGPhysics;

// all this needs to do is listen to keys and move itself
class COGPaddle : public Component {
public:

	static std::vector<COGPaddle*> mPaddleComponents;

	// the keys that control up and down
	Uint32 upKey;
	Uint32 downKey;
	
	// player 1 controlled, or player 2 controlled
	std::string tag;
	
	// gets a pointer to a velocity component
	// for now I'm just going to manually set the velocity
	COGPhysics* pPhysComp;

	COGPaddle(GameObject* pGO, std::string type);

	virtual ComponentType GetType() const { return ComponentType::Paddle; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	void Update();

};





