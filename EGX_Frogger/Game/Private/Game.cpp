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
	, entities(new tdcArray<Entity*>())
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
	mEngine = pEngine;
	mFontID = mEngine->LoadFont( "afternight.ttf", 32 );

	//default text colour
	textCol.mColor[0] = 0;
	textCol.mColor[1] = 0;
	textCol.mColor[2] = 0;

	//flush the event queue
	eQueue.FlushEvents();

	// create game objects, add to game list
	// Add at least
	// 1. Frogger
	// 2. A track
	entities->ClearList();
	Entity* pFrogger = EntityFactory::CreateEntity(FROGGER);
	entities->AddItem(pFrogger);
	Entity* pTrack = EntityFactory::CreateEntity(TRACK);
	entities->AddItem(pTrack);

	// This will actually be called again, but this is just to be safe
	InitializeLevel();

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


void MyGame::OnEvent(SDL_Event* pE){
	
	pInput->HandleSingleEvent(pE);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	InputManager* pInput = InputManager::getInstance();
}


//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{	
	// Call the function that runs the selected level
	(this->*(this->RunLevel))(fDeltaT);

	// Handles events that change the level
	HandleEvents();
}
