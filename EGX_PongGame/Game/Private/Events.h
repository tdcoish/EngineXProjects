#pragma once

#include <string>
/***************************************************************************************
I couldn't quite remember how to pass events from one component to another, so I just made 
this instead.
***************************************************************************************/

// yes this is pretty ghetto.

extern std::string side;


//// really all we care about is when the ball goes into an endzone. Really, we only need left or right.
//struct GameplayEvent {
//	std::string side;
//};
//
//class EventManager {
//public:
//	
//
//	static std::string side;
//
//	static void StoreEvent(std::string whichSide) {
//		side = whichSide;
//	}
//
//	static std::string GetEvent() {
//		return side;
//	}
//};
