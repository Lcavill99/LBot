#pragma once
#include <BWAPI.h>

class BuildingManager
{

public:
	void BuildingManager::addUnit(BWAPI::Unitset* set, BWAPI::Unit* u);
	void BuildingManager::removeUnit(BWAPI::Unitset* set, BWAPI::Unit* u);
	void BuildingManager::recruitUnit(BWAPI::Unit u);
	void BuildingManager::researchTech(BWAPI::Unit u);
};