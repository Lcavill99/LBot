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
	 * BWAPI
	 */
	BWAPI::TilePosition base;

	/*
	 * Variables
	 */
	int depot;
	int barracks;
	int refinery;
	int academy;
	int factory;
	int armory;
	int commandCenter;

public:
	void BuildingManager::zergBuildings(BWAPI::Unitset set);
	void BuildingManager::protossBuildings(BWAPI::Unitset set);
	void BuildingManager::terranBuildings(BWAPI::Unitset set);
	void BuildingManager::academyTech(BWAPI::Unit u);
	void BuildingManager::armoryTech(BWAPI::Unit u);
	void BuildingManager::machineTech(BWAPI::Unit u);
};