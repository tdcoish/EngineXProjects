
#include "Collision.h"

//luckily, there's no obnoxious rotating making this difficult.
bool CheckCollision(CollisionRect one, CollisionRect two) {

	//one is entirely to the left of two
	if (one.x + one.w < two.x) return false;

	//one is entirely to the right of two
	if (one.x > two.x + two.w) return false;

	//one is entirely above two
	if (one.y + one.h < two.y) return false;

	//one is entirely below two
	if (one.y > two.y + two.h) return false;

	//we would have returned already if there wasn't a collision
	return true;
}