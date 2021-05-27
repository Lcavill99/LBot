#pragma once
#include <BWAPI.h>

class WorkerManager
{ 
public:	
	BWAPI::Unit WorkerManager::getWorker();
	BWAPI::Unit WorkerManager::getWorkerFromSet(BWAPI::Unitset set);	
	void WorkerManager::gatherMinerals(BWAPI::Unit u);
	void WorkerManager::gatherGas(BWAPI::Unit u);
};