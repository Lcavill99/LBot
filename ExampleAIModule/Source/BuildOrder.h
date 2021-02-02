#pragma once
#include <BWAPI.h>

class BuildOrder
{
	int depot;
	int barracks;
	int refinery;
	int academy;

public:
	// Virtual functions for callbacks, leave these as they are.
	void buildOrder(BWAPI::UnitInterface *u);
};
