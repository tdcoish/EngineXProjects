
#include "Game\Private\COG\COGPhysics.h"

#include "GameplayEventsSystem.h"
#include "Game.h"

GameplayEventsSystem::GameplayEventsSystem()
	: mGameStateChangeQueue( new tdcArray<EventType>())
{
}

void GameplayEventsSystem::Initialize() {
	mGameStateChangeQueue->ClearList();
}

// I can't even remember which entities I was going to be listening to.
void GameplayEventsSystem::OnCollision(COGPhysics* pMe, COGPhysics* pOther) {
	// do stuff
}



/************************************************************************************
Just the code for handling game state
************************************************************************************/
void MyGame::HandleEvents() {

	//do thing for event.
	GameplayEventsSystem* pE = GameplayEventsSystem::getInstance();

	// I mean, there will almost surely be only one active event per frame. would be weird if there were more
	for (int i = 0; i < pE->mGameStateChangeQueue->numActive; i++) {

		switch (pE->mGameStateChangeQueue->list[i]) {
			case EventType::NO_EVENT: break;

			case EventType::GO_TO_MENU:
				RunLevel = &MyGame::Menu;
				World::getInstance()->Destroy();
				break;

			case EventType::GO_TO_CREDITS:
				RunLevel = &MyGame::Credits;
				break;

			case EventType::PLAY_GAME:
				RunLevel = &MyGame::Playing;
				World::getInstance()->Create();
				World::getInstance()->SetUpLevel();
				break;

			case EventType::PLAYER_DIED:
				RunLevel = &MyGame::Menu;
				World::getInstance()->Destroy();
				break;

			case EventType::QUIT_GAME: RunLevel = &MyGame::Quit; break;
		}
	}

	pE->mGameStateChangeQueue->ClearList();
}
