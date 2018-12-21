
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include <cmath>

namespace Physics
{
	// physics functions
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

	// Uses dot product to get the angle between two vectors.
	float FindAngleBetweenObjects(exVector2 obj1, exVector2 obj2) {
		float dot = FindDotProduct(obj1, obj2);

		float obj1Mag = FindVectorMagnitude(obj1);
		float obj2Mag = FindVectorMagnitude(obj2);

		float angle = std::acos(dot / (obj1Mag*obj2Mag));
		// convert from radians to degrees?

		return angle;
	}

	float FindAngleFromStraightUp(exVector2 obj1) {
		exVector2 yHat;
		yHat.x = 0;
		yHat.y = 1;

		return FindAngleBetweenObjects(obj1, yHat);
	}
}



