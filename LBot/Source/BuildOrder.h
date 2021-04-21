#pragma once
#include <BWAPI.h>

class BuildOrder
{
	int depot;
	int barracks;
	int refinery;
	int academy;
	int factory;

public:	
	void BuildOrder::buildOrder(BWAPI::Unitset workers);	
};