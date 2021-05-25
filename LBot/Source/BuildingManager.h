#pragma once
#include <BWAPI.h>
#include "WorkerManager.h"
#include "ScoutManager.h"

class BuildingManager
{
	int depot;
	int barracks;
	int refinery;
	int academy;
	int factory;
	int armory;

	WorkerManager *workerManager;
	ScoutManager *scoutManager;

public:
	void BuildingManager::recruitUnit(BWAPI::Unit u);
	void BuildingManager::zergBuildings();
	void BuildingManager::protossBuildings();
	void BuildingManager::terranBuildings();
	void BuildingManager::academyTech(BWAPI::Unit u);
	void BuildingManager::armoryTech(BWAPI::Unit u);
};