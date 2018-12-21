#pragma once

// Well this is unfortunate, but I think his graphics layers actually go closest-furthest
// Which means that 0 is the closest, and everything need to be in reverse order here.
enum class GraphicsLayers : int {
	UI3,
	UI2,
	UI1,
	UI0,
	PICKUPS,
	PARTICLE_EFFECTS,			// Like we're gonna have these
	PLAYER,
	ENEMIES,
	FLOOR,
	BACKGROUND,
	WALLPAPER,
	COUNT
};
