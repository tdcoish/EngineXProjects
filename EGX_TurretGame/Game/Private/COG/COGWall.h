#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Private/Helpers/Collision.h"
#include "Game\Private\GOSystem\Component.h"

#include "Engine/Public/SDL.h"
#include "Game/Private/GOSystem/ComponentTypes.h"

#include <vector>


// all this needs to do is listen to keys and move itself
class COGWall : public Component {
public:

	static std::vector<COGWall*> mWallComponents;

	COGWall(GameObject* pGO);

	virtual ComponentType GetType() const { return ComponentType::Wall; }

	virtual void Initialize() override;
	virtual void Destroy() override;

	void Update(float fDeltaT);

private:

};