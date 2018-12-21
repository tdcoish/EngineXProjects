#pragma once

#include "EventTypes.h"

/**********************************************************************
The idea was to have a queue of events generated per frame. Personally I just 
decided to do this because I'm running out of time.
**********************************************************************/


#pragma once

#include <string>

#include "Game/Private/GOSystem/Component.h"
#include "Game\Private\Helpers\tdcArray.h"
#include "EventTypes.h"

/*******************************************************************************************
This class is a Singleton responsible for storing all the events that I care about. That partly 
means listening for physics collisions, but also it means just flat out storing any explicit 
state changes, such as if the player character dies, going to the menu screen.
******************************************************************************************/
class GameplayEventsSystem : public IPhysicsCollisionEvent {

private:
	GameplayEventsSystem();
	void Initialize();


public:
	// This is for manually creating events that change the overall Game State. eg PLAYING -> MENU, or MENU -> QUITSCREEN
	tdcArray<EventType>* mGameStateChangeQueue;

	//Yeah I probably should have just made a template
	static GameplayEventsSystem* getInstance()
	{
		//This will be instantiated upon first use.
		static GameplayEventsSystem ins;
		return &ins;
	}

	//disable copy constructor and assignment operator
	GameplayEventsSystem(GameplayEventsSystem const&) = delete;
	void operator=(GameplayEventsSystem const&) = delete;

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override;

};


