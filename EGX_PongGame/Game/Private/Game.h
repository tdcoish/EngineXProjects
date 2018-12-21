//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/InputManager.h"

#include "Game/Private/PongBall.h"
#include "Game/Private/Paddle.h"
#include "Game/Private/World.h"


#include <string>
#include <vector>

/***********************************************************************************


***********************************************************************************/

//-----------------------------------------------------------------
//-----------------------------------------------------------------

enum EventType {NO_EVENT, GO_TO_MENU, PLAY_TWO_PLAYER, PLAY_VS_AI, QUIT_GAME};

// iterate through all the events that are active. Flush at the end of the frame
// This is a good candidate for templates I believe
class EventQueue {
public:
	EventType events[256];
	int numActive = 0;	

	void AddEvent(EventType e) {
		events[numActive] = e;
		numActive++;
	}

	void FlushEvents() {
		for (int i = 0; i < 256; i++) {
			events[i] = NO_EVENT;
		}
		numActive = 0;
	}
};

class MyGame : public exGameInterface
{
public:
								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

	// The "levels" called by our Run function
	void						Menu(float fDeltaT);
	void						Quit(float fDeltaT);
	void						Playing(float fDeltaT);

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	//Have all the entities in the level
	World						mWorld;

	// Using the component pattern
	//std::vector<GameObject*> mGameObjects;

	exColor						textCol;

	//new input
	InputManager*				pInput;

	exVector2					mTextPosition;

	// this feels somewhat like cheating, I suppose I could create a COGScore for each player
	int							playerOneScore;
	int							playerTwoScore;

	//std::string					eventsQ[256];			//right now used just for handling level switches.
	EventQueue					eQueue;				//used for handling level switches.


	// pointer to the correct function for each level.
	// maybe get around to using typedef here
	void(MyGame::*RunLevel)(float);

	void(MyGame::*MovePaddles)(float);

	void HandleMenuInput();
	void RenderMenuScreen();

	//when a player scores, reset the ball, keep the score.
	//void ResetServe();
	void SetUpGame();	

	void HandlePlayerWinning();


	void DrawPlayersScores();

	void HandleEvents();

	void HandleGameplayEvents();

};

