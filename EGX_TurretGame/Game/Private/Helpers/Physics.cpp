
#include "Physics.h"
#include <cmath>

float DegreesToRadians(float val) {
	return 3.14159f / 180.0f * val;
}

float RadiansToDegrees(float val) {
	return 180.0f / 3.14159f * val;
}

// physics functions, no idea what they're doing here
float FindVectorMagnitude(exVector2 vec) {
	return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}

float FindDotProduct(exVector2 vec1, exVector2 vec2) {
	return vec1.x*vec2.x + vec1.y*vec2.y;
}

exVector2 FindUnitVector(exVector2 vec) {
	float mag = FindVectorMagnitude(vec);

	vec.x /= mag;
	vec.y /= mag;

	return vec;
}

/******************************************************************************
* Takes in two vectors. Calculates the dot product, and then uses this to get the
* angle using the other dot product formula.
* a dot b = |a||b|cos(angle).
* Therefore:
* angle = acos((a dot b)/|a||b|)
*
* Objects must be passed in the correct order
*****************************************************************************/
float FindAngleBetweenVectors(exVector2 vec1, exVector2 vec2) {
	float dot = FindDotProduct(vec1, vec2);

	float obj1Mag = FindVectorMagnitude(vec1);
	float obj2Mag = FindVectorMagnitude(vec2);

	float combinedMags = obj1Mag * obj2Mag;
	float dotOverMags = dot / combinedMags;
	float angle = std::acos(dotOverMags);

	//return RadiansToDegrees(angle);
	if (angle < 0) {
		RadiansToDegrees(angle);
	}
	return angle;
}

/********************************************************************************************
* Takes in two vectors. Converts them into a new vector, that represents the
* vector from a -> b.
* Use the dot product between this vector and a y^ unit vector, (0, 1), since this
* allows us to find the angle in the users coordinates, or screen space.
*
* We may have to convert to or from a system with a different orientation for the
* y axis.
********************************************************************************************/
float FindAngleBetweenObjects(exVector2 obj1, exVector2 obj2) {
	exVector2 dif;
	dif.x = obj1.x - obj2.x;
	dif.y = obj1.y - obj2.y;

	exVector2 yHat;
	yHat.x = 0;
	yHat.y = 1;

	return FindAngleBetweenVectors(dif, yHat);
}






