#pragma once
#include <BWAPI.h>

class BuildOrder
{
	int depot;
	int barracks;
	int refinery;
	int academy;
	int factory;
	bool scoutTime;

public:	
	void buildOrder(BWAPI::Unitset workers);	
};