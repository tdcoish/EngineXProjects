/***************************************************************
Input is a singleton. I figured it was a natural fit. There are 
a lot of variables that we need in input, so we definitely want it
inside a class, but it doesn't make any sense to have multiple 
classes that all handle input.

Multiple classes that process that input of course makes sense, 
which is why we want this as a global variable.
***************************************************************/

#include "Game/Public/InputManager.h"

bool msDoubleClicked=false;
int lastMouseClick=-300;



InputManager::InputManager()
	: kStore(EMPTY)
	, msDoubleClicked(false)
	, lastMouseClick(0)
	, msX(0)
	, msY(0)
{
}

//InputManager::InputManager() {
//	kStore = EMPTY;
//	msDoubleClicked = false;
//	lastMouseClick = 0;
//	msX = 0;
//	msY = 0;
//
//	//SDL_SetRelativeMouseMode(SDL_TRUE);
//}

//Right now simply handles keys, so is fairly shallow. 
void InputManager::StoreInput()
{
	//msDoubleClicked=false;		//must be made false at each frame.

	while(SDL_PollEvent(&e)!=0){

		if (e.type == SDL_KEYDOWN)
			HandleKeyDown(e.key.keysym.sym);
		else if (e.type == SDL_KEYUP)
			HandleKeyUp(e.key.keysym.sym);
		/*else if (e.type == SDL_MOUSEBUTTONDOWN)
			HandleMouseButtonPressed(e.button.button);
		else if (e.type == SDL_MOUSEBUTTONUP)
			HandleMouseButtonReleased(e.button.button);*/
	}

	// get new mouse position every frame
	//UpdateMousePosition();
}

//Basically, just took out my polling code, to handle correctly Engine
void InputManager::HandleSingleEvent(SDL_Event* pE) {

	if (pE->type == SDL_KEYDOWN)
		HandleKeyDown(pE->key.keysym.sym);
	else if (pE->type == SDL_KEYUP)
		HandleKeyUp(pE->key.keysym.sym);
	/*else if (e.type == SDL_MOUSEBUTTONDOWN)
	HandleMouseButtonPressed(e.button.button);
	else if (e.type == SDL_MOUSEBUTTONUP)
	HandleMouseButtonReleased(e.button.button);*/
}

//Updates the position of the mouse, and updates state of mouse buttons
void InputManager::UpdateMousePosition() {
	int x, y;
	//SDL_GetRelativeMouseState(&x, &y);
	SDL_GetMouseState(&x, &y);


	msX = (float)x;
	msY = (float)y;

	//check if mouse is out of bounds
	/*if(msx<0) msx=0;
	if(msx>100)msx=100;
	if(msy<0) msy=0;
	if(msy>100) msy=100;*/
}

void InputManager::HandleMouseButtonPressed(Uint8 btn) {
	switch (btn) {
	case SDL_BUTTON_LEFT: kStore |= LMB; break;
	case SDL_BUTTON_RIGHT: kStore |= RMB; break;
	}
}

void InputManager::HandleMouseButtonReleased(Uint8 btn) {
	switch (btn) {
	case SDL_BUTTON_LEFT: kStore ^= LMB; break;
	case SDL_BUTTON_RIGHT: kStore ^= RMB; break;
	}
}

/********
Irrelevant right now, but allowing the user to change which keys do what is quite easy. I just need to create a bunch of variables in one struct that correspond to an SDL key.
eg:
SDL_keycode upKey=SDLK_W;		//can be changed by user
SDL_keycode leftKey=SDLK_A;		//again can be changed.
********/
void InputManager::HandleKeyDown(SDL_Keycode key)
{
	switch(key){
		case SDLK_ESCAPE: kStore|=kEscape; break;
		case SDLK_DOWN: kStore|=kDown; break;
		case SDLK_UP: kStore|=kUp; break;
		case SDLK_LEFT: kStore|=kLeft; break;
		case SDLK_RIGHT: kStore|=kRight; break;
		case SDLK_w: kStore |= kW; break;
		case SDLK_s: kStore |= kS; break;
		case SDLK_a: kStore |= kA; break;
		case SDLK_d: kStore |= kD; break;
		case SDLK_SPACE: kStore|=kSpace; break;
		case SDLK_LSHIFT: kStore|=kShift; break;
		case SDLK_BACKQUOTE: kStore|=kGrave; break;
		case SDLK_1: kStore |= N1;	break;
		case SDLK_2: kStore |= N2; break;
		case SDLK_3: kStore |= N3; break;
	}
}

//Don't need to handle anything yet.
void InputManager::HandleKeyUp(SDL_Keycode key)
{
	switch(key){
		case SDLK_ESCAPE: kStore^=kEscape; break;
		case SDLK_w: kStore^=kW; break;
		case SDLK_s: kStore^=kS; break;
		case SDLK_a: kStore^=kA; break;
		case SDLK_d: kStore^=kD; break;
		case SDLK_UP: kStore^=kUp; break;
		case SDLK_DOWN: kStore^=kDown; break;
		case SDLK_LEFT: kStore^=kLeft; break;
		case SDLK_RIGHT: kStore^=kRight; break;
		case SDLK_SPACE: kStore^=kSpace; break;
		case SDLK_LSHIFT: kStore^=kShift; break;
		case SDLK_BACKQUOTE: kStore ^= kGrave; break;
		case SDLK_1: kStore ^= N1; break;
		case SDLK_2: kStore ^= N2; break;
		case SDLK_3: kStore^=N3; break;
	}
}

//void InputManager::CheckMouseDoubleClicked(Timer eTimer){
//	//if it was too long ago
//	if(eTimer.getTicks()-lastMouseClick>300){
//		lastMouseClick=eTimer.getTicks();
//	}else{
//		msDoubleClicked=true;
//		lastMouseClick=-300;	//so user must double click again.
//	}
//}