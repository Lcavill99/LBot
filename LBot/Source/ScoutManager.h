#pragma once
#include <BWAPI.h>

class ScoutManager
{	
	BWAPI::Unit scout;

public:
	void ScoutManager::setScout();
	BWAPI::Unit ScoutManager::getScout();
	void ScoutManager::goScout();
};
