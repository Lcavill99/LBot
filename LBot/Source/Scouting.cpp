#include "Scouting.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

void Scouting::scouting(BWAPI::Unit scout)
{
	//** SCOUTING **//		
	auto& startLocations = Broodwar->getStartLocations();

	for (TilePosition baseLocation : startLocations)
	{
		// if the location is already explored, move on
		if (Broodwar->isExplored(baseLocation))
		{
			continue;
		}

		// if scout is under attack, run away until enemies have stopped attacking
		// if scout has found enemy base, return to base

		Position pos(baseLocation);
		Broodwar->drawCircleMap(pos, 32, Colors::Red, true);

		scout->move(pos);
		break;
	}
}