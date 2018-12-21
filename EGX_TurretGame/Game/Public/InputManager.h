#pragma once

#include "Engine/Public/SDL.h"
//#include "Timer.h"

//Yeah should probably have more private vars, but this is convenient
class InputManager {
private:
	InputManager();
	void HandleKeyDown(SDL_Keycode key);

	void HandleKeyUp(SDL_Keycode key);

	//gets called every time the left mouse button gets pressed.
	//void CheckMouseDoubleClicked(Timer eTimer);
	void HandleMouseButtonPressed(Uint8 btn);
	void HandleMouseButtonReleased(Uint8 btn);
	void UpdateMousePosition();

public:

	//keyboard and mouse bit handling.
	Uint32 kStore;				//stores one bit for each valid key.
	const Uint32 EMPTY = 0;		//note: always = empty, never set with &
	const Uint32 kLeft = 1 << 0;				//1
	const Uint32 kRight = 1 << 1;	        //2
	const Uint32 kUp = 1 << 2;				//4
	const Uint32 kDown = 1 << 3;				//8
	const Uint32 kEscape = 1 << 4;			//16
	const Uint32 kShift = 1 << 5;	        //32
	const Uint32 kSpace = 1 << 6;	        //64
	const Uint32 mouse = 1 << 7;	        //128
	const Uint32 wheelUp = 1 << 8;			//256
	const Uint32 wheelDown = 1 << 9;	    //512
	const Uint32 kGrave = 1 << 10;
	const Uint32 LMB = 1 << 11;
	const Uint32 RMB = 1 << 12;
	const Uint32 kW = 1 << 13;
	const Uint32 kS = 1 << 14;
	const Uint32 kA = 1 << 15;
	const Uint32 kD = 1 << 16;
	const Uint32 N1 = 1 << 17;
	const Uint32 N2 = 1 << 18;
	const Uint32 N3 = 1 << 19;
	// ...and so on

	bool msDoubleClicked;
	int lastMouseClick;
	bool msLeftClickedThisFrame;
	bool msRightClickedThisFrame;

	float msX;
	float msY;

	// eventually going to create struct for all keys
	bool spacePressedThisFrame;

	//stores all keyboard/mouse events from the OS
	SDL_Event e;

	//stores keys currently down, also mouse buttons.
	void StoreInput();

	// Right now just works on spacePressed. Call this once per frame at the start of the frame.
	// Actually, in this engine, call it at the end of the frame.
	void ClearKeys() { spacePressedThisFrame = false; }

	void HandleSingleEvent(SDL_Event* pE);

	//Yeah I probably should have just made a template
	static InputManager* getInstance()
	{
		//This will be instantiated upon first use.
		static InputManager ins;
		return &ins;
	}

	//disable copy constructor and assignment operator
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;
};

