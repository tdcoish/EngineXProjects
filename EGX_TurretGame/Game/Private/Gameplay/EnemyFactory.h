#pragma once


/**********************************************************************
EnemyFactory is a Singleton responsible for the creation of all enemies. It 
will have any additional logic it needs passed to it.
**********************************************************************/


#pragma once

#include "Engine/Public/SDL.h"
#include "Engine\Public\EngineInterface.h"

#include <string>

typedef unsigned int Hash;

class GameObject;

//Yeah should probably have more private vars, but this is convenient
class EnemyFactory {
private:
	EnemyFactory();

	int turretIndex;
	int plasmaIndex;
	int healthIndex;
	int wallIndex;
	int zerglingIndex;
	int grenadeIndex;
	int explosionIndex;

	std::hash<std::string> s_hash;

public:

	//Yeah I probably should have just made a template
	static EnemyFactory* getInstance()
	{
		//This will be instantiated upon first use.
		static EnemyFactory ins;
		return &ins;
	}

	//disable copy constructor and assignment operator
	EnemyFactory(EnemyFactory const&) = delete;
	void operator=(EnemyFactory const&) = delete;

	void CreatePlayer();
	void CreateTurret(float xPos, float yPos);
	void CreateZergling(float xPos, float yPos);
	void CreateHealthBar(float xPos, float yPos);
	void CreateTurretStateGFX(float xPos, float yPos);
	void CreatePlasmoid(exVector2 pos, exVector2 dest);
	void CreateGrenade(exVector2 pos, exVector2 dest);
	void CreateExplosion(exVector2 pos);
	void CreateWall(float xPos, float yPos);
};


