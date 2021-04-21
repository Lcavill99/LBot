#pragma once
#include <BWAPI.h>

class WorkerManager
{

public:
	BWAPI::Unit WorkerManager::getWorker();
	void WorkerManager::removeUnit(BWAPI::Unit u);
};