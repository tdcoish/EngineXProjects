
#pragma once

// To get exVector2
#include "Engine\Public\EngineInterface.h"


float DegreesToRadians(float val);

float RadiansToDegrees(float val);

// physics functions, no idea what they're doing here
float FindVectorMagnitude(exVector2 vec);

float FindDotProduct(exVector2 vec1, exVector2 vec2);

exVector2 FindUnitVector(exVector2 vec);

// Uses dot product to get the angle between two vectors.
float FindAngleBetweenObjects(exVector2 obj1, exVector2 obj2);
float FindAngleBetweenVectors(exVector2 obj1, exVector2 obj2);

// Finds the angle from (0, 0) to obj
float FindAngleFromWorldCoordinates(exVector2 obj);