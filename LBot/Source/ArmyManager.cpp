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
void ArmyManager::groupAttack(BWAPI::Unitset set)
{
	// If army is at half strength, retrat back to base until full strength
	if (set.size() < (set.max_size() / 2))
	{
		//Retreat back to base and get to max size
		//if army is at base then continue
		TilePosition base = Broodwar->self()->getStartLocation();
		Position pos(base);
		set.move(pos);

		if (set.size() == set.max_size())
		{
			groupAttack(set);
		}
	}
	else
	{
		set.attack(set.getClosestUnit(Filter::IsEnemy));

		// Retreat lower health units to the back of the group/kite
		for (Unit u :set)
		{
			if (u->getHitPoints() < (u->getInitialHitPoints() / 2))
			{
				//Retreat to back of group
				//get closest enemies position
				//get units position
				//if enemy is higher than unit, negative retreat
				//if enemy is lower than unit, positive retreat
			}
		}
	}	
}

// SWITCH TO FOR UNITS IN SET?


