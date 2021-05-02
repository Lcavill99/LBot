/*
 *
 * Handles all scouting logic
 *
 */
#include "ScoutManager.h"

using namespace BWAPI;
using namespace Filter;

/*
 * Assign a worker to be the scout
 */
void ScoutManager::setScout()
{
	workerManager = new WorkerManager;
	// Get a worker to assign as a scout
	scout = workerManager->getWorker();
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
	
	// Loop through all start locations
	for (TilePosition baseLocation : startLocations)
	{
		// If the location is already explored, move on
		if (Broodwar->isExplored(baseLocation))
		{
			continue;
		}

		Position pos(baseLocation);
		Broodwar->drawCircleMap(pos, 32, Colors::Red, true);
		// Move to base location to scout
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