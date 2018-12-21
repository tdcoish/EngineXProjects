
#include "Game/Private/Helpers/Collision.h"
#include <cmath>

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

bool CheckCircleCollision(exVector2 c1Pos, float c1Rad, exVector2 c2Pos, float c2Rad) {
	// Find the distance between the centers of both objects
	float xDis = c1Pos.x - c2Pos.x;
	float yDis = c1Pos.y - c2Pos.y;

	float dis = std::sqrt(xDis*xDis + yDis * yDis);

	// Check if that distance is smaller than the combined radius of both objects.
	//float combinedRad = c1Rad + c2Rad;
	// Note, the above code should be right, but for some reason it's not working.
	// So instead I'm just dividing the distance required until I get something that looks reasonably accurate
	float combinedRad = c1Rad + c2Rad;
	combinedRad /= 2;
	if (dis < combinedRad) return true;

	return false;
}