#pragma once

#include <vector>
#include "Engine\Public\EngineInterface.h"

class GameObject;

// the world, it contains all of our game objects and defines the order of updates
class World
{
public:

	void Create();

	void Destroy();

	void Update(float fDeltaT, exEngineInterface* pEngine);

	void ResetServe();

private:
	std::vector<GameObject*> mGameObjects;
};