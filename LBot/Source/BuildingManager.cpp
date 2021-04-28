/*
 *
 * Handles all building logic
 *
 */
#include "buildingManager.h"

using namespace BWAPI;

/*
 * Add unit to Unitset
 */
void BuildingManager::addUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.insert(u);
}

/*
 * Remove unit from unitset
 */
void BuildingManager::removeUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.erase(u);
}