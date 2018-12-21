#pragma once

struct CollisionRect {
	float x;
	float y;
	float w;
	float h;
};

#include "Engine\Public\EngineInterface.h"

//luckily, there's no obnoxious rotating making this difficult.
bool CheckCollision(CollisionRect one, CollisionRect two);

bool CheckCircleCollision(exVector2 c1Pos, float c1Rad, exVector2 c2Pos, float c2Rad);