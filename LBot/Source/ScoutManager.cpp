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
 * Scouting functionality
 */
void ScoutManager::goScout()
{
	auto& startLocations = Broodwar->getStartLocations();

	// Loop through all start locations
	for (BWAPI::TilePosition startLocation : startLocations)
	{
		// If the location is already explored, move on
		if (Broodwar->isExplored(startLocation))
		{
			continue;
		}

		BWAPI::Position pos(startLocation);

		// Move to location to scout
		scout->move(pos);
		break;
	}
}

/*
 * Send scout back to command center
 */
void ScoutManager::sendHome()
{
	// Get player base location
	BWAPI::TilePosition homeTPos = Broodwar->self()->getStartLocation();
	BWAPI::Position homePos(homeTPos);

	// Move scout to player base
	scout->move(homePos);
}