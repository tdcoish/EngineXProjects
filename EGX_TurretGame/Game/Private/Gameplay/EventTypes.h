
#pragma once

// all the different types of components
enum class EventType : int
{
	NO_EVENT = 0,
	PLAY_GAME,
	PLAYER_DIED,
	ENEMY_DIED,
	GO_TO_MENU,
	GO_TO_CREDITS,
	QUIT_GAME
};