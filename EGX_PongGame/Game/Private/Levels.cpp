
#include "Game/Private/Game.h"
#include "Game/Public/InputManager.h"
#include "Game/Private/Collision.h"
#include "Game/Private/GraphicsHelpers.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include <string>
#include <cmath>


/******************************************************************************
NOTE: This engine automatically updates frames in the background. Do not write your
own while loop for any level, or it will hang on the same frame forever.
******************************************************************************/


//sets up objects in the level. Works for both Two player and VS AI
void MyGame::SetUpGame() {

	// need a way of reinitializing this to 0 every time.
	playerOneScore = 0;
	playerTwoScore = 0;
}


// physics functions, no idea what they're doing here
float FindVectorMagnitude(exVector2 vec) {
	return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}

float FindDotProduct(exVector2 vec1, exVector2 vec2) {
	return vec1.x*vec2.x + vec1.y*vec2.y;
}

exVector2 FindUnitVector(exVector2 vec) {
	float mag = FindVectorMagnitude(vec);

	vec.x /= mag;
	vec.y /= mag;

	return vec;
}

// Uses dot product to get the angle between two vectors.
float FindAngleBetweenObjects(exVector2 obj1, exVector2 obj2) {
	float dot = FindDotProduct(obj1, obj2);

	float obj1Mag = FindVectorMagnitude(obj1);
	float obj2Mag = FindVectorMagnitude(obj2);

	float angle = std::acos(dot / (obj1Mag*obj2Mag));
	// convert from radians to degrees?

	return angle;
}


void MyGame::DrawPlayersScores() {
	
	//Draw the "instructions" message
	std::string message = "First to 5 wins ";
	exVector2 msgLoc;
	msgLoc.x = 300;
	msgLoc.y = 50;
	mEngine->DrawText(mFontID, msgLoc, message.c_str(), textCol, 0);

	//Draw the first players score.
	std::string playerOneTxt = "Player 1 Score: " + std::to_string(playerOneScore);
	msgLoc.x = 10;
	mEngine->DrawText(mFontID, msgLoc, playerOneTxt.c_str(), textCol, 0);

	//draw the second players score.
	std::string playerTwoTxt = "Player 2 Score: " + std::to_string(playerTwoScore);
	msgLoc.x = 550;
	mEngine->DrawText(mFontID, msgLoc, playerTwoTxt.c_str(), textCol, 1);
}

void MyGame::HandlePlayerWinning() {
	// we'll say for now that if either scores 5 times, they win.
	if (playerOneScore >= 5) {
		//they win, perfect time for another event queue to be made
		eQueue.AddEvent(GO_TO_MENU);
	}
	if (playerTwoScore >= 5) {
		eQueue.AddEvent(GO_TO_MENU);
	}
}

void MyGame::Playing(float fDeltaT) {

	//Input stored earlier. Sort of elegant. Ask him later how this is done.
	// must be that game is a subclass of the app class (whatever it's called)
	if (pInput->kStore & pInput->kEscape) {
		eQueue.AddEvent(GO_TO_MENU);
	}

	this->mWorld.Update(fDeltaT, mEngine);

	HandlePlayerWinning();
	DrawPlayersScores();
}












