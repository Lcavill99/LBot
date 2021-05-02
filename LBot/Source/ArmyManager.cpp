/*
 *
 * Handles all army logic
 *
 */
#include "ArmyManager.h"

using namespace BWAPI;
using namespace Filter;

/*
 * Add unit to Unitset
 */
void ArmyManager::addUnit(BWAPI::Unitset* set, BWAPI::Unit* u)
{
	set->insert(*u);
}

/*
 * Remove unit from unitset
 */
void ArmyManager::removeUnit(BWAPI::Unitset* set, BWAPI::Unit* u)
{
	set->erase(*u);
}

/*
 * Army group attacking
 */
void ArmyManager::groupAttack(BWAPI::Unitset* set)
{
	//if (set->size() < (set->max_size() / 2))
	//{
	//	//Retreat back to base and get to max size
	//	//if army is at base then continue
	//}
	//else
	//{
	//	for (Unit u : *set)
	//	{
	//		if (u->getHitPoints() < (u->getInitialHitPoints / 2))
	//		{
	//			//Retreat to back of group
	//			//get closest enemies position
	//			//get units position
	//			//if enemy is higher than unit, negative retreat
	//			//if enemy is lower than unit, positive retreat
	//		}
	//	}
	//}

	set->attack(set->getClosestUnit(Filter::IsEnemy));
}


