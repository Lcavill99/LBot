/*
 *
 * Handles all worker logic
 *
 */
#include "WorkerManager.h"

using namespace BWAPI;
using namespace Filter;

/*
 * Select a worker out of all workers
 */
BWAPI::Unit WorkerManager::getWorker()
{
	BWAPI::Unit worker;

	// Loop through all units owned by the player
	for (auto &u : Broodwar->self()->getUnits())
	{
		if (u->getType().isWorker())
		{
			// Do not want to select a worker that is gathering gas or carrying any resources
			if (!u->isConstructing() && !u->isGatheringGas() && !u->isCarryingMinerals() && !u->isCarryingGas())
			{
				worker = u;
				return worker;
			}
		}		
	}
	// If no workers can be found, print an error
	Broodwar->printf("WorkerManager Error: No available workers");
	return NULL;
}

/*
 * Select a worker that can build from specific unitset
 */
BWAPI::Unit WorkerManager::getWorkerFromSet(BWAPI::Unitset* set)
{
	BWAPI::Unit worker;

	// Loop through all units in the unitset
	for (auto &u : *set)
	{
		// Do not want to select a worker that is gathering gas or carrying any resources
		if (!u->isConstructing() && !u->isGatheringGas() && (!u->isCarryingMinerals() || !u->isCarryingGas()))
		{
			worker = u;
			return worker;
		}		
	}
	// If no workers can be found, print an error
	Broodwar->printf("WorkerManager Error: No available workers");
	return NULL;
}

/*
 * Add unit to Unitset
 */
void WorkerManager::addUnit(BWAPI::Unitset* set, BWAPI::Unit* u)
{
	set->insert(*u);
}

/*
 * Remove unit from unitset
 */
void WorkerManager::removeUnit(BWAPI::Unitset* set, BWAPI::Unit* u)
{
	set->erase(*u);
}

/*
 * Worker gathering minerals
 */
void WorkerManager::gatherMinerals(BWAPI::Unit u)
{
	/*if (u->isCarryingMinerals())
	{
		u->returnCargo();
	}*/
	if (!u->getPowerUp()) // Worker cannot harvest anything if it is carrying a powerup
	{
		// Gather from the nearest mineral patch 
		if (!u->gather(u->getClosestUnit(IsMineralField)))
		{
			// If the call fails, then print the last error message
			Broodwar << Broodwar->getLastError() << std::endl;
		}
	}
}

/*
 * Worker gathering gas
 */
void WorkerManager::gatherGas(BWAPI::Unit u)
{
	/*if (u->isCarryingGas())
	{
		u->returnCargo();
	}*/
	if (!u->getPowerUp()) // Worker cannot harvest anything if it is carrying a powerup
	{
		// Gather from nearest refinery
		if (!u->gather(u->getClosestUnit(IsRefinery)))
		{
			// If the call fails, then print the last error message
			Broodwar << Broodwar->getLastError() << std::endl;
		}
	}
}