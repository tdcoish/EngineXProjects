#pragma once


/**********************************************************************
EnemySpawner is created and owned by the World object. It is responsible for 
calling the EnemyFactory singleton when appropriate to spawn more turrets and 
health.
**********************************************************************/


#pragma once

#include "Engine/Public/SDL.h"
#include "Engine\Public\EngineInterface.h"

class GameObject;


//Yeah should probably have more private vars, but this is convenient
class EnemySpawner {
private:
	EnemySpawner();

	float				currentTime;
	// the rate is the time in seconds between spawns
	float				lastHealthSpawn;
	float				healthSpawnRate;

	float				lastZerglingSpawn;
	float				zergSpawnRate;

public:

	static EnemySpawner* getInstance()
	{
		//This will be instantiated upon first use.
		static EnemySpawner ins;
		return &ins;
	}

	//disable copy constructor and assignment operator
	EnemySpawner(EnemySpawner const&) = delete;
	void operator=(EnemySpawner const&) = delete;

	// Ideally this would trigger some events
	// Or maybe World should be a singleton which is called upon creation of a new object
	bool CheckSpawnTime(float fDeltaT);
	void SpawnNewEnemy();
};


