/*
 *
 * Handles all scouting logic
 *
 */
#include "ScoutManager.h"

using namespace BWAPI;

/*
 * Assign a worker to be the scout **CAN MOVE THIS TO A UNIT MANAGER FILE**
 */
void ScoutManager::setScout()
{
	for (auto &u : Broodwar->self()->getUnits())
	{		
		if (u->getType().isWorker() && !u->isConstructing())
		{
			scout = u;
		}
	}	
}

/*
 * Return what unit is the scout
 */
BWAPI::Unit ScoutManager::getScout()
{
	return scout;
}

/*
 * Scouting logic
 */
void ScoutManager::goScout()
{	
	auto& startLocations = Broodwar->getStartLocations();

	for (TilePosition baseLocation : startLocations)
	{
		// if the location is already explored, move on
		if (Broodwar->isExplored(baseLocation))
		{
			continue;
		}		

		Position pos(baseLocation);
		Broodwar->drawCircleMap(pos, 32, Colors::Red, true);

		scout->move(pos);
		break;
	}
}

/*
 * Send scout back to command center
 */
void ScoutManager::sendHome()
{

}