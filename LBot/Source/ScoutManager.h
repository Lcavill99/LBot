#pragma once
#include <BWAPI.h>
#include "WorkerManager.h"

class ScoutManager
{	
	/*
	 * Manager files
	 */
	WorkerManager *workerManager;

	/*
	 * BWAPI
	 */
	BWAPI::Unit scout;

public:
	BWAPI::Unit ScoutManager::setScout();
	BWAPI::Unit ScoutManager::getScout();
	void ScoutManager::goScout();
	void ScoutManager::sendHome();
};
