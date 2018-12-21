#pragma once

struct tdcRect {
	float x;
	float y;
	float w;
	float h;
};

//luckily, there's no obnoxious rotating making this difficult.
bool CheckCollisionWithRect(tdcRect one, tdcRect two);