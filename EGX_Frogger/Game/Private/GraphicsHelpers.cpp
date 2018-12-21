
#include "Collision.h"
#include "Engine/Public/EngineInterface.h"


//Converts from my rectangle to feed properly into the engine
void tdcRenderRectangle(tdcRect obj, exEngineInterface* pGFX) {
	//Draw the paddle on the screen.
	exVector2 topLeft, botRight;

	//for now everything is black
	exColor c;
	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	//maybe use some math to draw centered, but not now.
	topLeft.x = obj.x;
	topLeft.y = obj.y;
	botRight.x = topLeft.x + obj.w;		//10 pixels width
	botRight.y = topLeft.y + obj.h;		//50 pixels height

	pGFX->DrawBox(topLeft, botRight, c, 0);
}

//Yeah it's a touch hackish to use a box instead of a circle for circle collisions
void tdcRenderCircle(tdcRect obj, exEngineInterface* pGFX) {
	//Draw the paddle on the screen.
	exVector2 center;

	//for now everything is black
	exColor c;
	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	center.x = obj.x + obj.w / 2;
	center.y = obj.y + obj.h / 2;

	pGFX->DrawCircle(center, obj.w / 2, c, 0);
}


void tdcDrawText(tdcRect obj, exEngineInterface* pGFX, int fontID, const char* msg) {

	exVector2 center;

	//for now everything is black
	exColor c;
	c.mColor[0] = 0;
	c.mColor[1] = 0;
	c.mColor[2] = 0;

	center.x = obj.x + obj.w / 2;
	center.y = obj.y + obj.h / 2;

	pGFX->DrawText(fontID, center, msg, c, 0);
}
