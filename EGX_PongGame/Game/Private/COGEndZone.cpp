
#include "COGEndZone.h"

std::vector<COGEndZone*> COGEndZone::mZoneComponents;

void COGEndZone::Initialize()
{
	AddToComponentVector(mZoneComponents);
}

void COGEndZone::Destroy() {
	RemoveFromComponentVector(mZoneComponents);
}


