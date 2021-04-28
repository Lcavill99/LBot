/*
 *
 * Handles all worker logic
 *
 */
#include "WorkerManager.h"

using namespace BWAPI;

/*
 * Select a worker out of all workers
 */
BWAPI::Unit WorkerManager::getWorker()
{
	BWAPI::Unit worker;

	for (auto &u : Broodwar->self()->getUnits())
	{
		if (u->getType().isWorker())
		{
			if (!u->isConstructing() && !u->isGatheringGas() && !u->isCarryingMinerals() && !u->isCarryingGas())
			{
				worker = u;
				return worker;
			}
		}		
	}
	Broodwar->printf("WorkerManager Error: No available workers");
	return NULL;
}

/*
 * Select a worker that can build from specific unitset
 */
BWAPI::Unit WorkerManager::getWorkerFromSet(BWAPI::Unitset set)
{
	BWAPI::Unit worker;

	for (auto &u : set)
	{
		if (!u->isConstructing() && !u->isGatheringGas() && (!u->isCarryingMinerals() || !u->isCarryingGas()))
		{
			worker = u;
			return worker;
		}		
	}
	Broodwar->printf("WorkerManager Error: No available workers");
	return NULL;
}

/*
 * Add unit to Unitset
 */
void WorkerManager::addUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.insert(u);
}

/*
 * Remove unit from unitset
 */
void WorkerManager::removeUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.erase(u);
}

/*
 * Worker gathering minerals
 */
void WorkerManager::gatherMinerals()
{

}

/*
 * Worker gathering gas
 */
void WorkerManager::gatherGas()
{

}