/*
 *
 * Handles all army logic
 *
 */
#include "ArmyManager.h"

using namespace BWAPI;

/*
 * Add unit to Unitset
 */
void ArmyManager::addUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.insert(u);
}

/*
 * Remove unit from unitset
 */
void ArmyManager::removeUnit(BWAPI::Unitset set, BWAPI::Unit u)
{
	set.erase(u);
}

/*
 * Single unit attacking
 */
void ArmyManager::unitAttack(BWAPI::Unit u)
{

}

/*
 * Army group attacking
 */
void ArmyManager::groupAttack(BWAPI::Unitset set)
{

}


