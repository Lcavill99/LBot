#pragma once
#include <BWAPI.h>
#include "WorkerManager.h"
#include "ScoutManager.h"

class BuildOrder
{
	int depot;
	int barracks;
	int refinery;
	int academy;
	int factory;

	WorkerManager *workerManager;
	ScoutManager *scoutManager;

public:
	void BuildOrder::buildOrder(BWAPI::Unitset set);	
	/*void BuildOrder::Zerg(BWAPI::Unitset set);
	void BuildOrder::Protoss(BWAPI::Unitset set);
	void BuildOrder::Terran(BWAPI::Unitset set);*/
};