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
BWAPI::Unit ScoutManager::setScout()
{
	workerManager = new WorkerManager;
	// Get a worker to assign as a scout
	scout = workerManager->getWorker();
	return scout;
}

/*
 * Return what unit is the scout
 */
BWAPI::Unit ScoutManager::getScout()
{
	return scout;
}

/*
 * Scouting
 */
void ScoutManager::goScout()
{
	auto& startLocations = Broodwar->getStartLocations();
	auto& enemyBase = Broodwar->enemy()->getStartLocation();

	//while (!Broodwar->isExplored(enemyBase))
	//{
		// Loop through all start locations
		for (TilePosition baseLocation : startLocations)
		{
			// If the location is already explored, move on
			if (Broodwar->isExplored(baseLocation))
			{
				continue;
			}

			Position pos(baseLocation);
			// Move to base location to scout
			scout->move(pos);
			break;
		}
	//}	
}

/*
 * Send scout back to command center
 */
void ScoutManager::sendHome()
{
	
}