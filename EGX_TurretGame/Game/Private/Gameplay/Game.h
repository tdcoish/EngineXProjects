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

#include "Game/Private/Gameplay/World.h"


#include <string>
#include <vector>

/***********************************************************************************


***********************************************************************************/

//-----------------------------------------------------------------
//-----------------------------------------------------------------

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
	void						Credits(float fDeltaT);
	void						Quit(float fDeltaT);
	void						Playing(float fDeltaT);

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	// Using the component pattern
	//std::vector<GameObject*> mGameObjects;

	exColor						textCol;

	//new input
	InputManager*				pInput;

	exVector2					mTextPosition;

	// this feels somewhat like cheating, I suppose I could create a COGScore for each player
	int							playerOneScore;
	int							playerTwoScore;


	// pointer to the correct function for each level.
	// maybe get around to using typedef here
	void(MyGame::*RunLevel)(float);

	void(MyGame::*MovePaddles)(float);

	void HandleMenuInput();
	void RenderMenuScreen();

	//when a player scores, reset the ball, keep the score.
	//void ResetServe();
	void SetUpGame();	

	// All of these things should basically be components stuffed into empty game objects
	// and handled in the world.
	void DrawMessage();
	void DrawPlayerScore();

	void HandleEvents();

};

