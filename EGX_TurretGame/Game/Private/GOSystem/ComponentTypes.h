
#pragma once

// all the different types of components
enum class ComponentType : int
{
	Transform = 0,
	Physics,
	BoxShape,
	CircleShape,
	Player,
	Turret,
	Plasmoid,
	Zergling,
	Health,
	Health_Drawer,
	Explosion,
	Grenade,
	GFX_Turret_State,
	Wall
};