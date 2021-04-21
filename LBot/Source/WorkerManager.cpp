/*
 *
 * Handles all worker logic
 *
 */
#include "WorkerManager.h"

using namespace BWAPI;

/*
 * Select a worker
 */
BWAPI::Unit WorkerManager::getWorker()
{
	BWAPI::Unit worker;

	for (auto &u : Broodwar->self()->getUnits())
	{
		if (u->getType().isWorker() && !u->isConstructing())
		{
			worker = u;
			return worker;
		}
	}
}

/*
 * Remove unit
 */
void WorkerManager::removeUnit(BWAPI::Unit u)
{

}