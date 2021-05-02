#pragma once
#include <BWAPI.h>

class WorkerManager
{	

public:	
	BWAPI::Unit WorkerManager::getWorker();
	BWAPI::Unit WorkerManager::getWorkerFromSet(BWAPI::Unitset* set);
	void WorkerManager::addUnit(BWAPI::Unitset* set, BWAPI::Unit* u);
	void WorkerManager::removeUnit(BWAPI::Unitset* set, BWAPI::Unit* u);	
	void WorkerManager::gatherMinerals(BWAPI::Unit* u);
	void WorkerManager::gatherGas(BWAPI::Unitset* set, BWAPI::Unit* u);
};