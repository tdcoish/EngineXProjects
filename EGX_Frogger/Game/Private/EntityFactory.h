#pragma once

#include "Entity.h"
#include "Track.h"


class EntityFactory {
public:
	static Entity * CreateEntity(EntityType type) {
		switch (type) {
		case TRACK: return new Track();		break;
		case FROGGER: return new Frogger(); break;
		case BLOCK: return new Block();		break;

		default: break;
		}
	}
};