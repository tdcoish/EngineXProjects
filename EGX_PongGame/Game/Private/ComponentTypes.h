
#pragma once

// all the different types of components
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	Bounce,
	Paddle,
	Ball,
	Roof,
	EndZone
};