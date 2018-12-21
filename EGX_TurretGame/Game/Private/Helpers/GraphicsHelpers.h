#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/InputManager.h"
#include "GraphicsLayers.h"

//Converts from my rectangle to feed properly into the engine
void tdcRenderRectangle(CollisionRect obj, exEngineInterface* pGFX);
void tdcRenderRectangle(CollisionRect obj, exColor c, GraphicsLayers layer, exEngineInterface* pGFX);

//Yeah it's a touch hackish to use a box instead of a circle for circle collisions
void tdcRenderCircle(CollisionRect obj, GraphicsLayers layer, exEngineInterface* pGFX);


void tdcDrawText(CollisionRect obj, exEngineInterface* pGFX, int fontID, const char* msg);

