#pragma once
#include <BWAPI.h>

class BuildingManager
{

public:
	void BuildingManager::addUnit(BWAPI::Unitset set, BWAPI::Unit u);
	void BuildingManager::removeUnit(BWAPI::Unitset set, BWAPI::Unit u);
};