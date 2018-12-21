#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/InputManager.h"

#include "Collision.h"

//Converts from my rectangle to feed properly into the engine
void tdcRenderRectangle(tdcRect obj, exEngineInterface* pGFX);

//Yeah it's a touch hackish to use a box instead of a circle for circle collisions
void tdcRenderCircle(tdcRect obj, exEngineInterface* pGFX);


void tdcDrawText(tdcRect obj, exEngineInterface* pGFX, int fontID, const char* msg);