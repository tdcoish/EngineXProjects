//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//


#include "Game/Private/Game.h"
#include "Game/Public/InputManager.h"
#include "Game/Private/Collision.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Events.h"


//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	, pInput(InputManager::getInstance())
	, RunLevel(&MyGame::Menu)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Well luckily there is no allocated memory except the game object itself.
MyGame::~MyGame()
{

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	// create game objects?

	mEngine = pEngine;

	mFontID = mEngine->LoadFont( "afternight.ttf", 32 );

	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	//default text colour
	textCol.mColor[0] = 0;
	textCol.mColor[1] = 0;
	textCol.mColor[2] = 0;

	//flush the event queue
	eQueue.FlushEvents();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

//Can't write my usual storeInput() because he polls in the background. 
//I can instead just write my code for handling any particular event.

void MyGame::OnEvent(SDL_Event* pE){
	pInput->HandleSingleEvent(pE);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{

}


//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{	
	// Call the function that runs the selected level
	(this->*(this->RunLevel))(fDeltaT);

	// Handles events that change the level
	HandleEvents();

	// as of right now only handles a player scoring.
	HandleGameplayEvents();
}


