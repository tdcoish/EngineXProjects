
// for random spawn placement
#include <stdlib.h>

#include "EnemySpawner.h"
#include "EnemyFactory.h"

EnemySpawner::EnemySpawner()
	:currentTime(0.0f)
	,lastZerglingSpawn(0.0f)
	,zergSpawnRate(1.3f)
	,lastHealthSpawn(0.f)
	,healthSpawnRate(0.5f)
{
}

/**************************************************************************************
This class is called by the World object. It first checks if it needs to spawn an enemy.
If true SpawnEnemy() is called, and we store the returned GameObject.
***************************************************************************************/

// all random positions are generated between 200-600 in both axis
// let's make it two different functions
bool EnemySpawner::CheckSpawnTime(float fDeltaT) {
	currentTime += fDeltaT;

	bool spawn = false;

	if (currentTime - lastZerglingSpawn > zergSpawnRate) {
		spawn = true;
	}

	if (currentTime - lastHealthSpawn > healthSpawnRate) {
		spawn = true;
	}

	return spawn;
}

// Saving, not deleting this code, because we're going to need something like this for this current project
void EnemySpawner::SpawnNewEnemy() {
	if (currentTime - lastZerglingSpawn > zergSpawnRate) {
		// generate a random position
		float xPos = (float)(rand() % 20 + 760);
		float yPos = (float)(rand() % 20 + 390);

		EnemyFactory::getInstance()->CreateZergling(xPos, yPos);

		lastZerglingSpawn = currentTime;
	}

}