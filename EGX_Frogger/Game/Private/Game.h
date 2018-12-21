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

#include "EntityFactory.h"
#include "Entity.h"
#include "Track.h"
#include "tdcArray.h"

#include <string>

/***********************************************************************************


***********************************************************************************/

//-----------------------------------------------------------------
//-----------------------------------------------------------------

enum EventType {NO_EVENT, GO_TO_MENU, PLAY_FROGGER, PLAY_VS_AI, QUIT_GAME};

// iterate through all the events that are active. Flush at the end of the frame
// This is a good candidate for templates I believe
struct EventQueue {
	EventType events[256];
	int numActive = 0;	

	void AddEvent(EventType e) {
		if (numActive < 256) {
			events[numActive] = e;
			numActive++;
		}
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

	exColor						textCol;

	//new input
	InputManager*				pInput;

	EventQueue					eQueue;				//used for handling level switches.

	tdcArray<Entity*>*			entities;			// array of game object pointers

	// calls our factory, and appropriately stores the entity
	void AddEntity(Entity* pObj);

	// pointer to the correct function for each level.
	// C++ Makes this kind of a syntax nightmare
	void(MyGame::*RunLevel)(float);

	void HandleMenuInput();
	void RenderMenuScreen();

	void InitializeLevel();

	//draws ball and paddles.
	void DrawObjects();

	void HandleEvents();
};

