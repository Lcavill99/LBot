#pragma once
#include <BWAPI.h>
#include "WorkerManager.h"

class ScoutManager
{	
	BWAPI::Unit scout;

	WorkerManager *workerManager;

public:
	void ScoutManager::setScout();
	BWAPI::Unit ScoutManager::getScout();
	void ScoutManager::goScout();
	void ScoutManager::sendHome();
};
