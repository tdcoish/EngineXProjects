
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include <cmath>


namespace Physics {
	float FindVectorMagnitude(exVector2 vec);

	float FindDotProduct(exVector2 vec1, exVector2 vec2);

	exVector2 FindUnitVector(exVector2 vec);

	// Uses dot product to get the angle between two vectors.
	float FindAngleBetweenObjects(exVector2 obj1, exVector2 obj2);
};


