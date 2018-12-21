#pragma once

struct CollisionRect {
	float x;
	float y;
	float w;
	float h;
};

//luckily, there's no obnoxious rotating making this difficult.
bool CheckCollision(CollisionRect one, CollisionRect two);