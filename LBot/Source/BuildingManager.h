#pragma once
#include <BWAPI.h>
#include "WorkerManager.h"
#include "ScoutManager.h"

class BuildingManager
{
	/*
	 * Manager files
	 */
	WorkerManager *workerManager;
	ScoutManager *scoutManager;

	/*
	 * Variables
	 */
	int depot;
	int barracks;
	int refinery;
	int academy;
	int factory;
	int armory;

public:
	void BuildingManager::zergBuildings(BWAPI::Unitset set);
	void BuildingManager::protossBuildings();
	void BuildingManager::terranBuildings();
	void BuildingManager::academyTech(BWAPI::Unit u);
	void BuildingManager::armoryTech(BWAPI::Unit u);
};